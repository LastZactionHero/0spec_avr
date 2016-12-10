#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdlib.h> // Reimplement this?
#include <string.h> // Reimplement this?
#include "tinyfont.h"


#ifndef F_CPU
#define F_CPU 8000000UL // 8 MHz
#endif

#define PIN_DISPLAY_SCE PD7
#define PIN_DISPLAY_RST PD6
#define PIN_DISPLAY_DC  PD5
#define PIN_BACKLIGHT DDB1

#define LCD_COMMAND  0
#define LCD_DATA     1
#define LCD_CONTRAST 50 // good values between 40 and 60
#define LCD_WHITE 0
#define LCD_BLACK 1

// Message Buffer - Current message written to the screen
#define MESSAGE_BUFFER_LEN 96
char message_buffer[MESSAGE_BUFFER_LEN];

// Text Properties
#define TEXT_LINE_HEIGHT 8
#define TEXT_MAX_CHAR_WIDTH 8
#define TEXT_SPACE_WIDTH 6
#define TEXT_LETTER_SPACE_WIDTH 2

// Display buffer
#define LCD_WIDTH 84
#define LCD_HEIGHT 48
char display_map[LCD_WIDTH * LCD_HEIGHT / 8];

uint8_t g_text_start_x = 0;
uint8_t g_text_start_y = 0;


// Write command to LCD module
void lcd_write(uint8_t write_type, char data) {
  if(write_type == LCD_DATA){
    // Sending pixel data: set D/C line high
    PORTD |= (1 << PIN_DISPLAY_DC);
  } else {
    // Sending pixel data: set D/C line low
    PORTD &= ~(1 << PIN_DISPLAY_DC);
  }

  // Set chip select low
  PORTD &= ~(1 << PIN_DISPLAY_SCE);

  // Send the data byte
  SPDR = data;

  // Wait for interrupt to indicate sending has finished
  while (!(SPSR & (1<<SPIF)));

  // Set chip select high
  PORTD |= (1 << PIN_DISPLAY_SCE);
}

void lcd_goto_xy(int x, int y)
{
  lcd_write(0, 0x80 | x);  // Column
  lcd_write(0, 0x40 | y);  // Row
}

void lcd_update_display()
{
  lcd_goto_xy(0, 0);

  uint16_t i = 0;
  for(i = 0; i < (LCD_WIDTH * LCD_HEIGHT / 8); i++)
  {
    lcd_write(LCD_DATA, display_map[i]);
  }
}

// This function sets a pixel on display_map to your preferred
// color. 1=Black, 0= white.
void lcd_mark_pixel(int x, int y, uint8_t bw)
{
  // First, double check that the coordinate is in range.
  if ((x >= 0) && (x < LCD_WIDTH) && (y >= 0) && (y < LCD_HEIGHT))
  {
    char shift = y % 8;

    if (bw) // If black, set the bit.
      display_map[x + (y/8)*LCD_WIDTH] |= 1<<shift;
    else   // If white clear the bit.
      display_map[x + (y/8)*LCD_WIDTH] &= ~(1<<shift);
  }
}

// Because I keep forgetting to put bw variable in when setting...
void lcd_set_pixel(int x, int y)
{
  lcd_mark_pixel(x, y, LCD_BLACK); // Call setPixel with bw set to Black
}

void lcd_clear_pixel(int x, int y)
{
  lcd_mark_pixel(x, y, LCD_WHITE); // call setPixel with bw set to white
}

void clear_display(uint8_t bw){
  uint16_t i = 0;
  for (i = 0; i<(LCD_WIDTH * LCD_HEIGHT / 8); i++)
  {
    if (bw) {
      display_map[i] = 0xFF;
    } else {
      display_map[i] = 0;
    }
  }
}

int tinyfont_char_idx(char character) {
  return character - TINYFONT_ARR_OFFSET;
}

int tinyfont_char_width(char character) {
  int font_idx = tinyfont_char_idx(character);
  char w[1];
  strncpy_P(w, (PGM_P)pgm_read_word(&(tinyfont_table[font_idx])), 1);
  return atoi(w);
}

void format_message_buffer() {
  int msg_x = 0; // Current X position
  int last_space_idx = -1;  // Index of the last space
  int last_split_idx = -1;  // Index of the last space we split into a new line
  int i = 0;

  for(i = 0; i < strlen(message_buffer); i++){
    if(message_buffer[i] == ' '){
      // Record the position of the last space. We might turn it into a newline later.
      last_space_idx = i;
      msg_x += TEXT_SPACE_WIDTH; // Append space width
    } else if(message_buffer[i] == '\n'){
      // A newline sends the X position back to 0. Also indicate that there are no valid
      // spaces to use (don't want to split on the previous line)
      msg_x = 0;
      last_space_idx = -1;
    } else {
      // Append character width
      msg_x += tinyfont_char_width(message_buffer[i]) + TEXT_LETTER_SPACE_WIDTH;

      // Are we're over the dislay width?
      if(msg_x > (LCD_WIDTH - TEXT_MAX_CHAR_WIDTH)){
        // Is there a valid space to split on?
        if(last_space_idx != -1 && last_split_idx != last_space_idx){
          // Yes there is- turn the last space into a newline, and start checking again from
          // that position
          message_buffer[last_space_idx] = '\n';
          last_split_idx = last_space_idx;
          i = last_space_idx + 1;
          msg_x = 0;
        } else {
          // No valid space- probably a really long word.
          // Nothing we can do, just wrap to the start.
          msg_x = 0;
        }
      }
    }
  }
}

int write_character(char character) {
  int char_width = tinyfont_char_width(character);

  char char_pixels[TEXT_MAX_CHAR_WIDTH * TEXT_LINE_HEIGHT];  // display buffer, maximum 8x8 size of character
  int bit_posn = 0; // index into char_pixels
  
  // Get the display bytes from the font
  int font_idx = tinyfont_char_idx(character);
  char font_buffer[16];
  strcpy_P(font_buffer, (char*)pgm_read_word(&(tinyfont_table[font_idx])));
  
  // Loop over the font and map to the character display buffer
  uint8_t char_idx = 0;
  for(char_idx = 0; char_idx < strlen(font_buffer); char_idx++){
    char byte_buff[2]; // one byte at a time (e.g. 'FF')
  
    // Determine the width of the letter
    if(char_idx >= 2){ // skip the first two characters - width and delimiter
      byte_buff[char_idx % 2] = font_buffer[char_idx]; // append to the byte buffer
  
      if(char_idx % 2 == 1){ // full buffer loaded, two characters (one byte)
        unsigned long hex = strtoul(byte_buff, NULL, 16); // convert string buffer to a number
        // identify active pixels in the byte
        uint8_t bit = 0;
        for(bit = 0; bit < 8; bit++){
          unsigned long mask = 1UL << (7 - bit);
          unsigned long result = mask & hex;
          char_pixels[bit_posn] = (result > 0);
          bit_posn++;
        }
      }
    }
  }

  // Write the character buffer to the display buffer
  uint8_t x = 0;
  uint8_t y = 0;
  for(x = 0; x < char_width; x++){
    for(y = 0; y < TEXT_LINE_HEIGHT; y++){
      if(char_pixels[x + y * char_width]){
        lcd_set_pixel(x + g_text_start_x, y + g_text_start_y);
      } else {
        lcd_clear_pixel(x + g_text_start_x, y + g_text_start_y);
      }
    }
  }

  return char_width;
}

void write_message_to_lcd(char *message) {
  strncpy(message_buffer, message, MESSAGE_BUFFER_LEN);
  format_message_buffer(); // Preemptive word wrapping
  clear_display(LCD_WHITE);
  
  g_text_start_x = 0;
  g_text_start_y = 0;
  
  // Loop over the message buffer
  uint8_t i = 0;
  for(i = 0; i < MESSAGE_BUFFER_LEN; i++){
    // Wrap to the start of the line if we're over. Should only be encountered with very long words,
    // since addLineBreaksTomessage_buffer() is wrapping when appropriate.
    if(g_text_start_x > (LCD_WIDTH - TEXT_MAX_CHAR_WIDTH)){
      g_text_start_x = 0;
      g_text_start_y += TEXT_LINE_HEIGHT;
    }
  
    if(message_buffer[i] == 0){
      break; // all done
    } else if(message_buffer[i] == '\n') {
      // Move to start of the next line
      g_text_start_y += TEXT_LINE_HEIGHT;
      g_text_start_x = 0;
    } else if(message_buffer[i] == ' '){
      // Increment one space
      g_text_start_x += TEXT_SPACE_WIDTH;
    } else {
      // Write the character
      // Increment the letter width + some spacing
      g_text_start_x += write_character(message_buffer[i]) + TEXT_LETTER_SPACE_WIDTH;
    }
  }
  
  lcd_update_display();
}

int main(void) {
  uint16_t i = 0;

  // Control Pins
  DDRD = (1 << PIN_DISPLAY_SCE) | (1 << PIN_DISPLAY_RST) | (1 << PIN_DISPLAY_DC);
  DDRB = (1 << PB3) | (1 << PB5) | (1 << PB2) | (1 << PIN_BACKLIGHT);
  SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR1) | (1 << SPR0);

  // Reset the LCD to a known state
  PORTD &= ~(1 << PIN_DISPLAY_RST);
  PORTD |= (1 << PIN_DISPLAY_RST);

  // LCD Setup
  lcd_write(LCD_COMMAND, 0x21); // Tell LCD extended commands follow
  lcd_write(LCD_COMMAND, 0xB0); // Set LCD Vop (Contrast)
  lcd_write(LCD_COMMAND, 0x04); // Set Temp coefficent
  lcd_write(LCD_COMMAND, 0x14); // LCD bias mode 1:48 (try 0x13)
  lcd_write(LCD_COMMAND, 0x20); //We must send 0x20 before modifying the display control mode
  lcd_write(LCD_COMMAND, 0x0C); //Set display control, normal mode.
  lcd_write(LCD_COMMAND, 0x21); //Tell LCD that extended commands follow
  lcd_write(LCD_COMMAND, 0x80 | LCD_CONTRAST); //Set LCD Vop (Contrast): Try 0xB1(good @ 3.3V) or 0xBF if your display is too dark
  lcd_write(LCD_COMMAND, 0x20); //Set display mode

  write_message_to_lcd("Hello world!");

  ICR1 = 0x3D08; // Set counter top as 16-Bit
  OCR1A = 0x1E84; // set PWM for 50% duty cycle @ 16bit
  TCCR1A |= (1 << COM1A1)|(1 << COM1B1); // Non-inverting mode

  // Fast-PWM with ICR1 as TOP
  TCCR1A |= (1 << WGM11);
  TCCR1B |= (1 << WGM12)|(1 << WGM13);

  //TCCR1B |= (1 << CS10); // No Prescaler
  TCCR1B |= (1 << CS12)|(1 << CS10); // 1024 Prescaler
  
  while(1);
}