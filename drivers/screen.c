#include "screen.h"
#include "types.h"
#include "port_utils.h"
#include "memory.h"

uint16_t get_screen_offset(uint16_t col, uint16_t row) {
    return (row * MAX_COLS + col) * 2;
}

void enable_cursor(uint8_t cursor_start, uint8_t cursor_end) {
	port_byte_out(REG_SCREEN_CTRL, 0x0A);
	port_byte_out(REG_SCREEN_DATA, (port_byte_in(REG_SCREEN_DATA) & 0xC0) | cursor_start);
 
	port_byte_out(REG_SCREEN_CTRL, 0x0B);
	port_byte_out(REG_SCREEN_DATA, (port_byte_in(REG_SCREEN_DATA) & 0xE0) | cursor_end);
}

void disable_cursor() {
    port_byte_out(REG_SCREEN_CTRL, 0x0A);
	port_byte_out(REG_SCREEN_DATA, 0x20);
}

void set_cursor(uint16_t offset) {
    offset /= 2;
    port_byte_out(REG_SCREEN_CTRL, 0x0F);
	port_byte_out(REG_SCREEN_DATA, (uint8_t) (offset & 0xFF));
	port_byte_out(REG_SCREEN_CTRL, 0x0E);
	port_byte_out(REG_SCREEN_DATA, (uint8_t) ((offset >> 8) & 0xFF));
}

uint16_t get_cursor() {
    port_byte_out(REG_SCREEN_CTRL, 0x0E);
	uint16_t offset = port_byte_in(REG_SCREEN_DATA) << 8;
	port_byte_out(REG_SCREEN_CTRL, 0x0F);
	offset += port_byte_in(REG_SCREEN_DATA);
    return offset * 2;
}

void print_char(char character, int offset, uint8_t attributes) {
    uint8_t* const vid_mem = (uint8_t*)(VIDEO_ADDRESS);

    vid_mem[offset] = character;
    vid_mem[offset + 1] = attributes;
}

void print(char* str) {
    uint16_t offset = get_cursor();
    for (int i = 0;str[i] != 0x0; ++i) {
        char ch = str[i];
        switch (ch) {
            case '\n':
                const uint16_t row = (offset / 2) / MAX_COLS;
                offset = get_screen_offset(0, row + 1);
                break;
            default:
                print_char(ch, offset, WHITE_ON_BLACK);
                offset += 2;
        }
        set_cursor(offset);
        if (offset >= MAX_COLS * MAX_ROWS * 2) {
            uint8_t* const vid_mem = (uint8_t*)(VIDEO_ADDRESS);
            offset -= MAX_COLS * 2;
            set_cursor(offset);
            for (int i = 0;i < MAX_ROWS - 1; ++i) {
                memory_copy(vid_mem + get_screen_offset(0, i), 
                            vid_mem + get_screen_offset(0, i + 1), 
                            MAX_COLS * 2);
            }
            for (int i = 0;i < MAX_COLS; ++i) {
                vid_mem[get_screen_offset(i, MAX_ROWS - 1)] = ' ';
                vid_mem[get_screen_offset(i, MAX_ROWS - 1) + 1] = WHITE_ON_BLACK;
            }
        }
    }
}

void clear_screen() {
    for (int y = 0;y < MAX_ROWS; ++y) {
        for (int x = 0;x < MAX_COLS; ++x) {
            print_char(' ', get_screen_offset(x, y), WHITE_ON_BLACK);
        }
    }
}
