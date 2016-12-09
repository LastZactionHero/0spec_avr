#include <avr/io.h>

#ifndef F_CPU
#define F_CPU 8000000UL // 8 MHz
#endif

#define PIN_BACKLIGHT PB1
#define PIN_DISPLAY_SCE PD7
#define PIN_DISPLAY_RST PD6
#define PIN_DISPLAY_DC  PD5

#define LCD_COMMAND  0
#define LCD_DATA     1
#define LCD_CONTRAST 50 // good values between 40 and 60

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

int main(void) {
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

  // Write some pixel data to the display
  uint16_t i = 0;
  for(i = 0; i < 504; i++){
    lcd_write(LCD_DATA, 0x0F);
  }

  while(1);
}