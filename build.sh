avr-gcc -g -Os -mmcu=atmega328p -c character_writer.c
avr-gcc -g -mmcu=atmega328p -o character_writer.elf character_writer.o
avr-objcopy -j .text -j .data -O ihex character_writer.elf character_writer.hex