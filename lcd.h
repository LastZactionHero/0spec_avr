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

void lcd_write(uint8_t write_type, char data);
void lcd_goto_xy(int x, int y);
void lcd_update_display();
void lcd_mark_pixel(int x, int y, uint8_t bw);
void lcd_set_pixel(int x, int y);
void lcd_clear_pixel(int x, int y);
void lcd_clear_display(uint8_t bw);

#endif