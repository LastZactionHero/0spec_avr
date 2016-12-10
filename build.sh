avr-gcc -g -Os -mmcu=atmega328p -c character_writer.c lcd.c tinyfont.c text_writer.c backlight.c
avr-gcc -g -mmcu=atmega328p -o character_writer.elf character_writer.o lcd.o tinyfont.o text_writer.o backlight.o
avr-objcopy -j .text -j .data -O ihex character_writer.elf character_writer.hex