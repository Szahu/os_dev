#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "isr.h"
#include "types.h"

static void keyboard_callback(registers_t regs);
void init_keyboard();

enum {
    EMPTY,
    KEY_ESCAPE,
    KEY_F1,
    KEY_F2,
    KEY_F3,
    KEY_F4,
    KEY_F5,
    KEY_F6,
    KEY_F7,
    KEY_F8,
    KEY_F9,
    KEY_F10,
    KEY_F11,
    KEY_F12,
    KEY_PRINT_SCREEN,
    KEY_SCROLL_LOCK,
    KEY_PAUSE,
    KEY_TILDE,
    KEY_1,
    KEY_2,
    KEY_3,
    KEY_4,
    KEY_5,
    KEY_6,
    KEY_7,
    KEY_8,
    KEY_9,
    KEY_0,
    KEY_MINUS,
    KEY_EQUALS,
    KEY_BACKSPACE,
    KEY_TAB,
    KEY_Q,
    KEY_W,
    KEY_E,
    KEY_R,
    KEY_T,
    KEY_Y,
    KEY_U,
    KEY_I,
    KEY_O,
    KEY_P,
    KEY_LEFT_BRACKET,
    KEY_RIGHT_BRACKET,
    KEY_BACKSLASH,
    KEY_CAPS_LOCK,
    KEY_A,
    KEY_S,
    KEY_D,
    KEY_F,
    KEY_G,
    KEY_H,
    KEY_J,
    KEY_K,
    KEY_L,
    KEY_SEMICOLON,
    KEY_APOSTROPHE,
    KEY_BACKTICK,
    KEY_ENTER,
    KEY_LEFT_SHIFT,
    KEY_Z,
    KEY_X,
    KEY_C,
    KEY_V,
    KEY_B,
    KEY_N,
    KEY_M,
    KEY_COMMA,
    KEY_PERIOD,
    KEY_SLASH,
    KEY_RIGHT_SHIFT,
    KEY_LEFT_CTRL,
    KEY_LEFT_SUPER,
    KEY_LEFT_ALT,
    KEY_SPACE,
    KEY_RIGHT_ALT,
    KEY_RIGHT_SUPER,
    KEY_MENU,
    KEY_RIGHT_CTRL,
    KEY_INSERT,
    KEY_HOME,
    KEY_PAGE_UP,
    KEY_DELETE,
    KEY_END,
    KEY_PAGE_DOWN,
    KEY_UP,
    KEY_LEFT,
    KEY_DOWN,
    KEY_RIGHT,
    KEY_NUM_LOCK,
    KEY_KP_DIVIDE,
    KEY_KP_MULTIPLY,
    KEY_KP_MINUS,
    KEY_KP_PLUS,
    KEY_KP_ENTER,
    KEY_KP_1,
    KEY_KP_2,
    KEY_KP_3,
    KEY_KP_4,
    KEY_KP_5,
    KEY_KP_6,
    KEY_KP_7,
    KEY_KP_8,
    KEY_KP_9,
    KEY_KP_0,
    KEY_KP_PERIOD
} typedef key_code_t;

#define KEY_BACKSPACE_ASCII 0x08

enum {
    KEY_PRESSED,
    KEY_RELEASED
} typedef key_action_t;

typedef struct {
    key_action_t action;
    uint8_t scancode;
    key_code_t keycode;
} key_info_t;

static key_code_t scancode_map[] = {
    EMPTY,              // 0x00
    KEY_ESCAPE,         // 0x01
    KEY_1,              // 0x02
    KEY_2,              // 0x03
    KEY_3,              // 0x04
    KEY_4,              // 0x05
    KEY_5,              // 0x06
    KEY_6,              // 0x07
    KEY_7,              // 0x08
    KEY_8,              // 0x09
    KEY_9,              // 0x0A
    KEY_0,              // 0x0B
    KEY_MINUS,          // 0x0C
    KEY_EQUALS,         // 0x0D
    KEY_BACKSPACE,      // 0x0E
    KEY_TAB,            // 0x0F
    KEY_Q,              // 0x10
    KEY_W,              // 0x11
    KEY_E,              // 0x12
    KEY_R,              // 0x13
    KEY_T,              // 0x14
    KEY_Y,              // 0x15
    KEY_U,              // 0x16
    KEY_I,              // 0x17
    KEY_O,              // 0x18
    KEY_P,              // 0x19
    KEY_LEFT_BRACKET,   // 0x1A
    KEY_RIGHT_BRACKET,  // 0x1B
    KEY_ENTER,          // 0x1C
    KEY_LEFT_CTRL,      // 0x1D
    KEY_A,              // 0x1E
    KEY_S,              // 0x1F
    KEY_D,              // 0x20
    KEY_F,              // 0x21
    KEY_G,              // 0x22
    KEY_H,              // 0x23
    KEY_J,              // 0x24
    KEY_K,              // 0x25
    KEY_L,              // 0x26
    KEY_SEMICOLON,      // 0x27
    KEY_APOSTROPHE,     // 0x28
    KEY_BACKTICK, 
    KEY_LEFT_SHIFT,     // 0x29
    KEY_BACKSLASH,      // 0x2A
    KEY_Z,              // 0x2B
    KEY_X,              // 0x2C
    KEY_C,              // 0x2D
    KEY_V,              // 0x2E
    KEY_B,              // 0x2F
    KEY_N,              // 0x30
    KEY_M,              // 0x31
    KEY_COMMA,          // 0x32
    KEY_PERIOD,         // 0x33
    KEY_SLASH,          // 0x34
    KEY_RIGHT_SHIFT,    // 0x35
    KEY_KP_MULTIPLY,    // 0x36
    KEY_LEFT_ALT,       // 0x37
    KEY_SPACE,          // 0x38
    KEY_CAPS_LOCK,      // 0x39
    KEY_F1,             // 0x3A
    KEY_F2,             // 0x3B
    KEY_F3,             // 0x3C
    KEY_F4,             // 0x3D
    KEY_F5,             // 0x3E
    KEY_F6,             // 0x3F
    KEY_F7,             // 0x40
    KEY_F8,             // 0x41
    KEY_F9,             // 0x42
    KEY_F10,            // 0x43
    EMPTY,              // 0x44 (No key for F11)
    KEY_NUM_LOCK,       // 0x45
    KEY_SCROLL_LOCK,    // 0x46
    EMPTY,              // 0x47 (No key for keypad 7)
    EMPTY,              // 0x48 (No key for keypad 8)
    EMPTY,              // 0x49 (No key for keypad 9)
    EMPTY,              // 0x4A (No key for keypad -)
    EMPTY,              // 0x4B (No key for keypad 4)
    EMPTY,              // 0x4C (No key for keypad 5)
    EMPTY,              // 0x4D (No key for keypad 6)
    EMPTY,              // 0x4E (No key for keypad +)
    EMPTY,              // 0x4F (No key for keypad 1)
    EMPTY,              // 0x50 (No key for keypad 2)
    EMPTY,              // 0x51 (No key for keypad 3)
    EMPTY,              // 0x52 (No key for keypad 0)
    EMPTY,              // 0x53 (No key for keypad .)
    EMPTY,              // 0x54
    EMPTY,              // 0x55
    EMPTY,              // 0x56
    KEY_F11             // 0x57
};

static char keycode_to_ascii[] = {
    '\0',   // EMPTY
    '\0',   // KEY_ESCAPE
    '\0',   // KEY_F1
    '\0',   // KEY_F2
    '\0',   // KEY_F3
    '\0',   // KEY_F4
    '\0',   // KEY_F5
    '\0',   // KEY_F6
    '\0',   // KEY_F7
    '\0',   // KEY_F8
    '\0',   // KEY_F9
    '\0',   // KEY_F10
    '\0',   // KEY_F11
    '\0',   // KEY_F12
    '\0',   // KEY_PRINT_SCREEN
    '\0',   // KEY_SCROLL_LOCK
    '\0',   // KEY_PAUSE
    '`',    // KEY_TILDE
    '1',    // KEY_1
    '2',    // KEY_2
    '3',    // KEY_3
    '4',    // KEY_4
    '5',    // KEY_5
    '6',    // KEY_6
    '7',    // KEY_7
    '8',    // KEY_8
    '9',    // KEY_9
    '0',    // KEY_0
    '-',    // KEY_MINUS
    '=',    // KEY_EQUALS
    KEY_BACKSPACE_ASCII, 
    '\t',   // KEY_TAB
    'q',    // KEY_Q
    'w',    // KEY_W
    'e',    // KEY_E
    'r',    // KEY_R
    't',    // KEY_T
    'y',    // KEY_Y
    'u',    // KEY_U
    'i',    // KEY_I
    'o',    // KEY_O
    'p',    // KEY_P
    '[',    // KEY_LEFT_BRACKET
    ']',    // KEY_RIGHT_BRACKET
    '\\',   // KEY_BACKSLASH
    '\0',   // KEY_CAPS_LOCK
    'a',    // KEY_A
    's',    // KEY_S
    'd',    // KEY_D
    'f',    // KEY_F
    'g',    // KEY_G
    'h',    // KEY_H
    'j',    // KEY_J
    'k',    // KEY_K
    'l',    // KEY_L
    ';',    // KEY_SEMICOLON
    '\'',   // KEY_APOSTROPHE
    '`',    // KEY_BACKTICK
    '\n',   // KEY_ENTER
    '\0',   // KEY_LEFT_SHIFT
    'z',    // KEY_Z
    'x',    // KEY_X
    'c',    // KEY_C
    'v',    // KEY_V
    'b',    // KEY_B
    'n',    // KEY_N
    'm',    // KEY_M
    ',',    // KEY_COMMA
    '.',    // KEY_PERIOD
    '/',    // KEY_SLASH
    '\0',   // KEY_RIGHT_SHIFT
    '\0',   // KEY_LEFT_CTRL
    '\0',   // KEY_LEFT_SUPER
    '\0',   // KEY_LEFT_ALT
    ' ',    // KEY_SPACE
    '\0',   // KEY_RIGHT_ALT
    '\0',   // KEY_RIGHT_SUPER
    '\0',   // KEY_MENU
    '\0',   // KEY_RIGHT_CTRL
    '\0',   // KEY_INSERT
    '\0',   // KEY_HOME
    '\0',   // KEY_PAGE_UP
    '\0',   // KEY_DELETE
    '\0',   // KEY_END
    '\0',   // KEY_PAGE_DOWN
    '\0',   // KEY_UP
    '\0',   // KEY_LEFT
    '\0',   // KEY_DOWN
    '\0',   // KEY_RIGHT
    '\0',   // KEY_NUM_LOCK
    '\0',   // KEY_KP_DIVIDE
    '\0',   // KEY_KP_MULTIPLY
    '\0',   // KEY_KP_MINUS
    '\0',   // KEY_KP_PLUS
    '\0',   // KEY_KP_ENTER
    '\0',   // KEY_KP_1
    '\0',   // KEY_KP_2
    '\0',   // KEY_KP_3
    '\0',   // KEY_KP_4
    '\0',   // KEY_KP_5
    '\0',   // KEY_KP_6
    '\0',   // KEY_KP_7
    '\0',   // KEY_KP_8
    '\0',   // KEY_KP_9
    '\0',   // KEY_KP_0
    '\0'    // KEY_KP_PERIOD
};

#endif