#ifndef SCREEN_H_
#define SCREEN_H_

#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80
#define WHITE_ON_BLACK 0x0f

#define REG_SCREEN_CTRL 0x3D4
#define REG_SCREEN_DATA 0x3D5

#include "types.h"

void set_cursor(uint16_t);
uint16_t get_cursor();
void clear_screen();
void enable_cursor(uint8_t cursor_start, uint8_t cursor_end);
void disable_cursor();
void print(char* str); 

#endif