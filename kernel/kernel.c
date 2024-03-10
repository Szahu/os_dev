#include "screen.h"
#include "isr.h"
#include "timer.h"
#include "keyboard.h"
#include "string.h"

void main() {
    clear_screen();
    enable_cursor(0, MAX_ROWS);
    set_cursor(0x0);
    print("Startup\n");

    isr_install();
    __asm__ __volatile__ ("sti");
    init_keyboard();
}