#include "lcd.h"
#include "pins.h"

// Display buffer
char display_map[LCD_WIDTH * LCD_HEIGHT / 8];

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

void lcd_init() {
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

void lcd_clear_display(uint8_t bw){
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

// Because I keep forgetting to put bw variable in when setting...
void lcd_set_pixel(int x, int y)
{
  lcd_mark_pixel(x, y, LCD_BLACK); // Call setPixel with bw set to Black
}

void lcd_clear_pixel(int x, int y)
{
  lcd_mark_pixel(x, y, LCD_WHITE); // call setPixel with bw set to white
}