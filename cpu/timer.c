#include "timer.h"
#include "screen.h"
#include "isr.h"
#include "string.h"

uint32_t tick = 0;

static void timer_callback(registers_t regs) {
    tick++;
    print("Tick: ");
    char tick_ascii[256];
    string_int_to_ascii(tick, tick_ascii);
    print(tick_ascii);
    print("\n");
}       

void init_timer(uint32_t frequency) {
    register_interrupt_handler(IRQ0, timer_callback);

    uint32_t divisor = 1193180 / frequency;
    uint8_t low = (uint8_t)(divisor & 0xFF);
    uint8_t high = (uint8_t)((divisor >> 8) & 0xFF);

    port_byte_out(0x43, 0x36);
    port_byte_out(0x40, low);
    port_byte_out(0x40, high);
}
