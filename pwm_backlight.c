// (PCINT1/OC1A) PB1: LCD Backlight on PWM
// OC1A (Timer/Counter1 Output Compare Match A Output)
// TC1 (16-bit async)
// TCNT1 - counter register, 16 Bit
// TCCR1A - Timer Control Register

// example: TCCR0 |= (1<<WGM00)|(1<<COM01)|(1<<WGM01)|(1<<CS00);

// TCCR1A -
// 0 1 X X - - 0 1
// 1<<COM11 | 1<<WGM10
//
// TCCR1B -
// 0 0 - 1 0 1 0 0
// 1<<WGM13 | 1<<CS12
//
// TCCR1C - Ignored for PWM mode?
//
// TCNT1L - Timer Counter Low Byte
// TCNT1H - Timer Counter High Byte
//
//
// Duty cycle?
// OCR1AL - Output Compare Low Byte
// OCR1AH - Output Compare High Byte
// OCR1AH - 0x7F
// OCR1AL - 0xFF
//
// TIMSK1 - Timer/Counter 1 Interrupt Mask Register
// - - 0 - - 0 0 0
//
// TIFR1 - TC1 Interrupt Flag Register
// - - 0 - - 0 0 0
//


// OC1A/PCINT1 – Port B, Bit 1
//   – OC1A: Output Compare Match output. The PB1 pin can serve as an external output for the
//     Timer/Counter1 Compare Match A. The PB1 pin has to be configured as an output (DDB1 set (one))
//     to serve this function. The OC1A pin is also the output pin for the PWM mode timer function.

// Clocked internally

// f-OCnA = (F clk) / (2 * N * (1 + OCRnA))

#include <avr/io.h>


#ifndef F_CPU
#define F_CPU 8000000UL // 8 MHz
#endif

#include <util/delay.h>

#define PIN_BACKLIGHT DDB1

#define set_output(portdir,pin) portdir |= (1<<pin)
#define output_low(port,pin) port &= ~(1<<pin)
#define output_high(port,pin) port |= (1<<pin)

int main(void) {
  DDRB |= (1 << PIN_BACKLIGHT); // Set PB1 as an output

  ICR1 = 0x3D08; // Set counter top as 16-Bit
  OCR1A = 0x1E84; // set PWM for 50% duty cycle @ 16bit
  TCCR1A |= (1 << COM1A1)|(1 << COM1B1); // Non-inverting mode

  // Fast-PWM with ICR1 as TOP
  TCCR1A |= (1 << WGM11);
  TCCR1B |= (1 << WGM12)|(1 << WGM13);

  TCCR1B |= (1 << CS10); // No Prescaler
  //TCCR1B |= (1 << CS12)|(1 << CS10); // 1024 Prescaler

  while (1);

  return 0;
}