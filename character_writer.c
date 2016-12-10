#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include "backlight.h"
#include "clock.h"
#include "lcd.h"
#include "pins.h"
#include "text_writer.h"

#ifndef F_CPU
#define F_CPU 8000000UL // 8 MHz
#endif

ISR(TIMER0_COMPA_vect) {
  clock_increment();
}

int main(void) {
  // Control Pins
  DDRD = (1 << PIN_DISPLAY_SCE) | (1 << PIN_DISPLAY_RST) | (1 << PIN_DISPLAY_DC);
  DDRB = (1 << PB3) | (1 << PB5) | (1 << PB2) | (1 << PIN_BACKLIGHT);
  SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR1) | (1 << SPR0);

  // Reset the LCD to a known state
  PORTD &= ~(1 << PIN_DISPLAY_RST);
  PORTD |= (1 << PIN_DISPLAY_RST);

  sei();

  lcd_init();
  backlight_on();
  clock_init();

  while(1);
}