#include "keyboard.h"
#include "port_utils.h"

static void keyboard_callback(registers_t regs) {
    uint8_t scancode = port_byte_in(0x60);
    char scancode_char[] = {scancode};
    print("key pressed: ");
    print(scancode_char);
    print("\n"); 
}

void init_keyboard() {
    register_interrupt_handler(IRQ1, keyboard_callback);
}