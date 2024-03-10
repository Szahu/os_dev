#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "isr.h"

static void keyboard_callback(registers_t regs);
void init_keyboard();

#endif