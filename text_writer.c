#include <string.h> // Reimplement this?
#include "text_writer.h"
#include "lcd.h"
#include "tinyfont.h"

// Message Buffer - Current message written to the screen
#define MESSAGE_BUFFER_LEN 96
char message_buffer[MESSAGE_BUFFER_LEN];

// Text Properties
#define TEXT_LINE_HEIGHT 8
#define TEXT_MAX_CHAR_WIDTH 8
#define TEXT_SPACE_WIDTH 6
#define TEXT_LETTER_SPACE_WIDTH 2

uint8_t g_text_start_x = 0;
uint8_t g_text_start_y = 0;

void format_message_buffer() {
  int msg_x = 0; // Current X position
  int last_space_idx = -1;  // Index of the last space
  int last_split_idx = -1;  // Index of the last space we split into a new line
  int i = 0;

  for(i = 0; i < strlen(message_buffer); i++){
    if(message_buffer[i] == ' '){
      // Record the position of the last space. We might turn it into a newline later.
      last_space_idx = i;
      msg_x += TEXT_SPACE_WIDTH; // Append space width
    } else if(message_buffer[i] == '\n'){
      // A newline sends the X position back to 0. Also indicate that there are no valid
      // spaces to use (don't want to split on the previous line)
      msg_x = 0;
      last_space_idx = -1;
    } else {
      // Append character width
      msg_x += tinyfont_char_width(message_buffer[i]) + TEXT_LETTER_SPACE_WIDTH;

      // Are we're over the dislay width?
      if(msg_x > (LCD_WIDTH - TEXT_MAX_CHAR_WIDTH)){
        // Is there a valid space to split on?
        if(last_space_idx != -1 && last_split_idx != last_space_idx){
          // Yes there is- turn the last space into a newline, and start checking again from
          // that position
          message_buffer[last_space_idx] = '\n';
          last_split_idx = last_space_idx;
          i = last_space_idx + 1;
          msg_x = 0;
        } else {
          // No valid space- probably a really long word.
          // Nothing we can do, just wrap to the start.
          msg_x = 0;
        }
      }
    }
  }
}

int write_character(char character) {
  int char_width = tinyfont_char_width(character);

  char char_pixels[TEXT_MAX_CHAR_WIDTH * TEXT_LINE_HEIGHT];  // display buffer, maximum 8x8 size of character
  tinyfont_char_pixels(char_pixels, character);


  // Write the character buffer to the display buffer
  uint8_t x = 0;
  uint8_t y = 0;
  for(x = 0; x < char_width; x++){
    for(y = 0; y < TEXT_LINE_HEIGHT; y++){
      if(char_pixels[x + y * char_width]){
        lcd_set_pixel(x + g_text_start_x, y + g_text_start_y);
      } else {
        lcd_clear_pixel(x + g_text_start_x, y + g_text_start_y);
      }
    }
  }

  return char_width;
}

void write_text(char *message) {
  strncpy(message_buffer, message, MESSAGE_BUFFER_LEN);
  format_message_buffer(); // Preemptive word wrapping
  lcd_clear_display(LCD_WHITE);
  
  g_text_start_x = 0;
  g_text_start_y = 0;
  
  // Loop over the message buffer
  uint8_t i = 0;
  for(i = 0; i < MESSAGE_BUFFER_LEN; i++){
    // Wrap to the start of the line if we're over. Should only be encountered with very long words,
    // since addLineBreaksTomessage_buffer() is wrapping when appropriate.
    if(g_text_start_x > (LCD_WIDTH - TEXT_MAX_CHAR_WIDTH)){
      g_text_start_x = 0;
      g_text_start_y += TEXT_LINE_HEIGHT;
    }
  
    if(message_buffer[i] == 0){
      break; // all done
    } else if(message_buffer[i] == '\n') {
      // Move to start of the next line
      g_text_start_y += TEXT_LINE_HEIGHT;
      g_text_start_x = 0;
    } else if(message_buffer[i] == ' '){
      // Increment one space
      g_text_start_x += TEXT_SPACE_WIDTH;
    } else {
      // Write the character
      // Increment the letter width + some spacing
      g_text_start_x += write_character(message_buffer[i]) + TEXT_LETTER_SPACE_WIDTH;
    }
  }
  
  lcd_update_display();
}