#include "keyboard.h"
#include "port_utils.h"
#include "string.h"
#include "screen.h"

key_info_t get_key_info(uint8_t scancode) {
    key_action_t action = KEY_PRESSED;
    uint8_t norm_scancode = scancode;
    if (scancode > 0x80) {
        action = KEY_RELEASED;
        norm_scancode -= 0x80;
    }

    key_code_t keycode = scancode_map[norm_scancode];

    key_info_t res = {
        .action = action,
        .scancode = scancode,
        .keycode = keycode
    };

    return res;
}
 
static void keyboard_callback(registers_t regs) {
    uint8_t scancode = port_byte_in(0x60);
    key_info_t key_info = get_key_info(scancode);
    
    if (key_info.action == KEY_PRESSED) {
        print_char(keycode_to_ascii[key_info.keycode], -1, WHITE_ON_BLACK);
    }
}

void init_keyboard() {
    register_interrupt_handler(IRQ1, keyboard_callback);
}