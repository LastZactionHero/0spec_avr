# 0spec_avr

```
avr-gcc -g -Os -mmcu=atmega328p -c spi_test.c
avr-gcc -g -mmcu=atmega328p -o spi_test.elf spi_test.o
avr-objcopy -j .text -j .data -O ihex spi_test.elf spi_test.hex

avrdude -p m328p -c usbtiny -F -U flash:w:spi_test.hex:i
```