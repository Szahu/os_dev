#include "idt.h"

void set_idt_gate(int n, uint32_t handler) {
    idt[n].low_offset = (uint16_t)(handler & 0xffff);
    idt[n].segment_selector = KERNEL_CS;
    idt[n].always_0 = 0;
    idt[n].flags = 0x8E; 
    idt[n].high_offset = (uint16_t)(handler >> 16);
}

void set_idt() {
    idt_reg.base = (uint32_t)&idt;
    idt_reg.limit = IDT_ENTRIES * sizeof(idt_gate_t) - 1;
    __asm__ __volatile__("lidtl (%0)" : : "r" (&idt_reg));
}