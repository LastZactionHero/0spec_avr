// PB1: LCD Backlight

#include <avr/io.h>

#ifndef F_CPU
#define F_CPU 8000000UL // 8 MHz
#endif

#define PIN_BACKLIGHT PB1

#define set_output(portdir,pin) portdir |= (1<<pin)
#define output_low(port,pin) port &= ~(1<<pin)
#define output_high(port,pin) port |= (1<<pin)

void delay_ms(uint16_t ms) {
  uint16_t delay_count = F_CPU / 17500;
  volatile uint16_t i;
  while(ms != 0) {
    for(i = 0; i != delay_count; i++);
    ms--;
  }
}

int main(void) {
  set_output(DDRB, PIN_BACKLIGHT);
  output_high(PORTB, PIN_BACKLIGHT);
  while(1) {
    output_high(PORTB, PIN_BACKLIGHT);
    delay_ms(4);
    output_low(PORTB, PIN_BACKLIGHT);
    delay_ms(4);
  }
  return 0;
}