#include <avr/io.h>

#ifndef LCD
#define LCD true

#define LCD_WIDTH 84
#define LCD_HEIGHT 48

#define LCD_COMMAND  0
#define LCD_DATA     1
#define LCD_CONTRAST 50 // good values between 40 and 60
#define LCD_WHITE 0
#define LCD_BLACK 1

void lcd_init();
void lcd_set_pixel(int x, int y);
void lcd_clear_pixel(int x, int y);
void lcd_clear_display(uint8_t bw);
void lcd_update_display();

#endif