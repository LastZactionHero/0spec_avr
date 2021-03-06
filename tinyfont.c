#include <avr/pgmspace.h>
#include <stdlib.h> // Reimplement this?
#include <string.h> // Reimplement this?
#include "tinyfont.h"

const char TINYFONT_EXCLAIM[] PROGMEM = "1-7a";
const char TINYFONT_DOUBLE_QUOTE[] PROGMEM = "1-02";
const char TINYFONT_POUND[] PROGMEM = "1-02";
const char TINYFONT_DOLLAR[] PROGMEM = "1-02";
const char TINYFONT_PERCENT[] PROGMEM = "1-02";
const char TINYFONT_AMP[] PROGMEM = "1-02";
const char TINYFONT_QUOTE[] PROGMEM = "1-02";
const char TINYFONT_LPAREN[] PROGMEM = "1-02";
const char TINYFONT_RPAREN[] PROGMEM = "1-02";
const char TINYFONT_STAR[] PROGMEM = "1-02";
const char TINYFONT_PLUS[] PROGMEM = "1-02";
const char TINYFONT_COMMA[] PROGMEM = "1-02";
const char TINYFONT_DASH[] PROGMEM = "3-000e00";
const char TINYFONT_PERIOD[] PROGMEM = "1-02";
const char TINYFONT_FWD_SLASH[] PROGMEM = "1-02";
const char TINYFONT_0[] PROGMEM = "4-06999960";
const char TINYFONT_1[] PROGMEM = "3-079248";
const char TINYFONT_2[] PROGMEM = "4-069168f0";
const char TINYFONT_3[] PROGMEM = "4-06921960";
const char TINYFONT_4[] PROGMEM = "4-0999f110";
const char TINYFONT_5[] PROGMEM = "4-0f8e1960";
const char TINYFONT_6[] PROGMEM = "4-068e9960";
const char TINYFONT_7[] PROGMEM = "4-0f124440";
const char TINYFONT_8[] PROGMEM = "4-06969960";
const char TINYFONT_9[] PROGMEM = "4-06997160";
const char TINYFONT_COLON[] PROGMEM = "1-12";
const char TINYFONT_SEMICOLON[] PROGMEM = "";
const char TINYFONT_LT[] PROGMEM = "";
const char TINYFONT_EQUAL[] PROGMEM = "";
const char TINYFONT_GT[] PROGMEM = "";
const char TINYFONT_QUESTION[] PROGMEM = "4-06912020";
const char TINYFONT_AT[] PROGMEM = "";
const char TINYFONT_UPPER_A[] PROGMEM = "5-0114afc620";
const char TINYFONT_UPPER_B[] PROGMEM = "5-07a3e8c7c0";
const char TINYFONT_UPPER_C[] PROGMEM = "5-03a30845c0";
const char TINYFONT_UPPER_D[] PROGMEM = "5-07a318c7c0";
const char TINYFONT_UPPER_E[] PROGMEM = "4-0f8e88f0";
const char TINYFONT_UPPER_F[] PROGMEM = "4-0f8e8880";
const char TINYFONT_UPPER_G[] PROGMEM = "5-03a309c5c0";
const char TINYFONT_UPPER_H[] PROGMEM = "5-0463f8c620";
const char TINYFONT_UPPER_I[] PROGMEM = "1-7e";
const char TINYFONT_UPPER_J[] PROGMEM = "3-049378";
const char TINYFONT_UPPER_K[] PROGMEM = "5-04654e4a20";
const char TINYFONT_UPPER_L[] PROGMEM = "4-088888f0";
const char TINYFONT_UPPER_M[] PROGMEM = "7-01071d5ab56480";
const char TINYFONT_UPPER_N[] PROGMEM = "5-047359c620";
const char TINYFONT_UPPER_O[] PROGMEM = "6-01e861861780";
const char TINYFONT_UPPER_P[] PROGMEM = "4-0f9f8880";
const char TINYFONT_UPPER_Q[] PROGMEM = "6-01c8a28a6781";
const char TINYFONT_UPPER_R[] PROGMEM = "5-07a31f4620";
const char TINYFONT_UPPER_S[] PROGMEM = "5-03a28345c0";
const char TINYFONT_UPPER_T[] PROGMEM = "5-07c8421080";
const char TINYFONT_UPPER_U[] PROGMEM = "5-046318c5c0";
const char TINYFONT_UPPER_V[] PROGMEM = "5-046318a880";
const char TINYFONT_UPPER_W[] PROGMEM = "7-0126ad5aa89100";
const char TINYFONT_UPPER_X[] PROGMEM = "5-0454422a20";
const char TINYFONT_UPPER_Y[] PROGMEM = "5-0463171080";
const char TINYFONT_UPPER_Z[] PROGMEM = "5-07c26643e0";
const char TINYFONT_LBRACKET[] PROGMEM = "1-02";
const char TINYFONT_BACKSLASH[] PROGMEM = "1-02";
const char TINYFONT_RBRACKET[] PROGMEM = "1-02";
const char TINYFONT_CARET[] PROGMEM = "1-02";
const char TINYFONT_UNDERSCORE[] PROGMEM = "1-02";
const char TINYFONT_TILDE[] PROGMEM = "1-02";
const char TINYFONT_LOWER_A[] PROGMEM = "4-00717970";
const char TINYFONT_LOWER_B[] PROGMEM = "4-088e99e0";
const char TINYFONT_LOWER_C[] PROGMEM = "4-00698960";
const char TINYFONT_LOWER_D[] PROGMEM = "4-01179970";
const char TINYFONT_LOWER_E[] PROGMEM = "4-0069f870";
const char TINYFONT_LOWER_F[] PROGMEM = "3-0d7490";
const char TINYFONT_LOWER_G[] PROGMEM = "4-00797197";
const char TINYFONT_LOWER_H[] PROGMEM = "4-088e9990";
const char TINYFONT_LOWER_I[] PROGMEM = "1-5e";
const char TINYFONT_LOWER_J[] PROGMEM = "2-1156";
const char TINYFONT_LOWER_K[] PROGMEM = "4-089aca90";
const char TINYFONT_LOWER_L[] PROGMEM = "1-7e";
const char TINYFONT_LOWER_M[] PROGMEM = "6-00083e965940";
const char TINYFONT_LOWER_N[] PROGMEM = "3-000d68";
const char TINYFONT_LOWER_O[] PROGMEM = "4-00069960";
const char TINYFONT_LOWER_P[] PROGMEM = "4-00e99e88";
const char TINYFONT_LOWER_Q[] PROGMEM = "4-00079711";
const char TINYFONT_LOWER_R[] PROGMEM = "3-027920";
const char TINYFONT_LOWER_S[] PROGMEM = "2-039c";
const char TINYFONT_LOWER_T[] PROGMEM = "3-017490";
const char TINYFONT_LOWER_U[] PROGMEM = "4-00099960";
const char TINYFONT_LOWER_V[] PROGMEM = "5-000118a880";
const char TINYFONT_LOWER_W[] PROGMEM = "6-000021b52480";
const char TINYFONT_LOWER_X[] PROGMEM = "4-00096690";
const char TINYFONT_LOWER_Y[] PROGMEM = "4-00099626";
const char TINYFONT_LOWER_Z[] PROGMEM = "4-00f248f0";

PGM_P const tinyfont_table[] PROGMEM = {TINYFONT_EXCLAIM, TINYFONT_DOUBLE_QUOTE, TINYFONT_POUND, TINYFONT_DOLLAR, TINYFONT_PERCENT, TINYFONT_AMP, TINYFONT_QUOTE, TINYFONT_LPAREN, TINYFONT_RPAREN, TINYFONT_STAR, TINYFONT_PLUS, TINYFONT_COMMA, TINYFONT_DASH, TINYFONT_PERIOD, TINYFONT_FWD_SLASH, TINYFONT_0, TINYFONT_1, TINYFONT_2, TINYFONT_3, TINYFONT_4, TINYFONT_5, TINYFONT_6, TINYFONT_7, TINYFONT_8, TINYFONT_9, TINYFONT_COLON, TINYFONT_SEMICOLON, TINYFONT_LT, TINYFONT_EQUAL, TINYFONT_GT, TINYFONT_QUESTION, TINYFONT_AT, TINYFONT_UPPER_A, TINYFONT_UPPER_B, TINYFONT_UPPER_C, TINYFONT_UPPER_D, TINYFONT_UPPER_E, TINYFONT_UPPER_F, TINYFONT_UPPER_G, TINYFONT_UPPER_H, TINYFONT_UPPER_I, TINYFONT_UPPER_J, TINYFONT_UPPER_K, TINYFONT_UPPER_L, TINYFONT_UPPER_M, TINYFONT_UPPER_N, TINYFONT_UPPER_O, TINYFONT_UPPER_P, TINYFONT_UPPER_Q, TINYFONT_UPPER_R, TINYFONT_UPPER_S, TINYFONT_UPPER_T, TINYFONT_UPPER_U, TINYFONT_UPPER_V, TINYFONT_UPPER_W, TINYFONT_UPPER_X, TINYFONT_UPPER_Y, TINYFONT_UPPER_Z, TINYFONT_LBRACKET, TINYFONT_BACKSLASH, TINYFONT_RBRACKET, TINYFONT_CARET, TINYFONT_UNDERSCORE, TINYFONT_TILDE, TINYFONT_LOWER_A, TINYFONT_LOWER_B, TINYFONT_LOWER_C, TINYFONT_LOWER_D, TINYFONT_LOWER_E, TINYFONT_LOWER_F, TINYFONT_LOWER_G, TINYFONT_LOWER_H, TINYFONT_LOWER_I, TINYFONT_LOWER_J, TINYFONT_LOWER_K, TINYFONT_LOWER_L, TINYFONT_LOWER_M, TINYFONT_LOWER_N, TINYFONT_LOWER_O, TINYFONT_LOWER_P, TINYFONT_LOWER_Q, TINYFONT_LOWER_R, TINYFONT_LOWER_S, TINYFONT_LOWER_T, TINYFONT_LOWER_U, TINYFONT_LOWER_V, TINYFONT_LOWER_W, TINYFONT_LOWER_X, TINYFONT_LOWER_Y, TINYFONT_LOWER_Z};

int tinyfont_char_idx(char character) {
  return character - TINYFONT_ARR_OFFSET;
}

void tinyfont_char_data(char *dest, char character) {
  int font_idx = tinyfont_char_idx(character);
  strcpy_P(dest, (char*)pgm_read_word(&(tinyfont_table[font_idx])));
}

void tinyfont_char_pixels(char *dest, char character){
  int bit_posn = 0; // index into dest

  // Get the display bytes from the font
  char font_buffer[16];
  tinyfont_char_data(font_buffer, character);

  // Loop over the font and map to the character display buffer
  uint8_t char_idx = 0;
  for(char_idx = 0; char_idx < strlen(font_buffer); char_idx++){
    char byte_buff[2]; // one byte at a time (e.g. 'FF')

    // Determine the width of the letter
    if(char_idx >= 2){ // skip the first two characters - width and delimiter
      byte_buff[char_idx % 2] = font_buffer[char_idx]; // append to the byte buffer

      if(char_idx % 2 == 1){ // full buffer loaded, two characters (one byte)
        unsigned long hex = strtoul(byte_buff, NULL, 16); // convert string buffer to a number
        // identify active pixels in the byte
        uint8_t bit = 0;
        for(bit = 0; bit < 8; bit++){
          unsigned long mask = 1UL << (7 - bit);
          unsigned long result = mask & hex;
          dest[bit_posn] = (result > 0);
          bit_posn++;
        }
      }
    }
  }
}

int tinyfont_char_width(char character) {
  int font_idx = tinyfont_char_idx(character);
  char w[1];
  strncpy_P(w, (PGM_P)pgm_read_word(&(tinyfont_table[font_idx])), 1);
  return atoi(w);
}

