#include <avr/io.h>
#include "backlight.h"

void backlight_on() {
  ICR1 = 0x3D08; // Set counter top as 16-Bit
  OCR1A = 0x1E84; // set PWM for 50% duty cycle @ 16bit
  TCCR1A |= (1 << COM1A1)|(1 << COM1B1); // Non-inverting mode

  // Fast-PWM with ICR1 as TOP
  TCCR1A |= (1 << WGM11);
  TCCR1B |= (1 << WGM12)|(1 << WGM13);

  TCCR1B |= (1 << CS10); // No Prescaler
  // TCCR1B |= (1 << CS12)|(1 << CS10); // 1024 Prescaler
}