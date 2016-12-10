#ifndef TINYFONT
#define TINYFONT true

// Font starts at ASCII 0x21 - exclaimation point. No valid characters before this.
// Control characters like \n are handled explicitly.
#define TINYFONT_ARR_OFFSET 0x21;

int tinyfont_char_idx(char character);
int tinyfont_char_width(char character);
void tinyfont_char_data(char *dest, char character);
//void tinyfont_char_pixels(char *dest, char character);

#endif