#ifndef IDT_H
#define IDT_H

#include "types.h"

#define KERNEL_CS 0x08

typedef struct {
    uint16_t low_offset;
    uint16_t segment_selector;
    uint8_t always_0;
    uint8_t flags;
    uint16_t high_offset;
} __attribute__ ((packed)) idt_gate_t;

typedef struct {
    uint16_t limit;
    uint32_t base;
} __attribute__ ((packed)) idt_register_t;

#define IDT_ENTRIES 256

__attribute__((aligned(0x10))) static idt_gate_t idt[IDT_ENTRIES];
static idt_register_t idt_reg;

void set_idt_gate(int n, uint32_t handler_addr);
void set_idt();

#endif