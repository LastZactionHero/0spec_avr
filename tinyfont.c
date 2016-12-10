// #include <avr/pgmspace.h>
// #include "tinyfont.h"
// 
// int tinyfont_char_idx(char character) {
//   return character - TINYFONT_ARR_OFFSET;
// }
// 
// int tinyfont_char_width(char character) {
//   int font_idx = tinyfont_char_idx(character);
//   char w[1];
//   strncpy_P(w, (PGM_P)pgm_read_word(&(tinyfont_table[font_idx])), 1);
//   return atoi(w);
// }
