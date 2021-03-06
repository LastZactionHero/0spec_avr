#include <avr/eeprom.h>
#include <avr/io.h>
#include <stdio.h>
#include "clock.h"
#include "eeprom.h"
#include "text_writer.h"

uint16_t clock_timer_tick = 0;

uint8_t hour = 0;
uint8_t minute = 0;
uint8_t second = 0;

void save_time() {
  eeprom_write_byte((uint8_t *) EEPROM_ADDR_HOUR, hour);
  eeprom_write_byte((uint8_t *) EEPROM_ADDR_MINUTE, minute);
  eeprom_write_byte((uint8_t *) EEPROM_ADDR_SECOND, second);
}

void restore_time() {
  hour = eeprom_read_byte((uint8_t *) EEPROM_ADDR_HOUR);
  minute = eeprom_read_byte((uint8_t *) EEPROM_ADDR_MINUTE);
  second = eeprom_read_byte((uint8_t *) EEPROM_ADDR_SECOND);

  // Something wasn't right
  if(hour > 12 || minute > 60 || second > 60){
    hour = 0;
    minute = 0;
    second = 0;
  }
}

void clock_init() {
  TCNT0 = 0x00;
  OCR0A = 0xFF;
  TCCR0A = (1 << WGM01);
  TCCR0B = (1 << CS01) | (1 << CS00);
  TIMSK0 = (1 << OCIE0A);

  restore_time();
}

void write_time() {
  char clock_message_buffer[13];
  snprintf(clock_message_buffer, 13, "%02d:%02d:%02d", hour, minute, second);
  write_text(clock_message_buffer);
}

void second_increment() {
  second = (second + 1) % 60;
  if(second == 0) {
    minute = (minute + 1) % 60;
    if(minute == 0) {
      hour = (hour + 1) % 24;
    }
  }
}

void clock_increment() {
  clock_timer_tick++;
  if(clock_timer_tick == 488){
    clock_timer_tick = 0;
    second_increment();
    save_time();
    write_time();
  }
}