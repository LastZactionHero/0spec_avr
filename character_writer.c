#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdlib.h> // Reimplement this?
#include "pins.h"
#include "lcd.h"
#include "text_writer.h"

#ifndef F_CPU
#define F_CPU 8000000UL // 8 MHz
#endif

int main(void) {
  uint16_t i = 0;

  // Control Pins
  DDRD = (1 << PIN_DISPLAY_SCE) | (1 << PIN_DISPLAY_RST) | (1 << PIN_DISPLAY_DC);
  DDRB = (1 << PB3) | (1 << PB5) | (1 << PB2) | (1 << PIN_BACKLIGHT);
  SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR1) | (1 << SPR0);

  // Reset the LCD to a known state
  PORTD &= ~(1 << PIN_DISPLAY_RST);
  PORTD |= (1 << PIN_DISPLAY_RST);

  lcd_init();
  write_text("Hello ay!");

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