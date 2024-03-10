#ifndef MEMORY_H
#define MEMORY_H

#include "types.h"

void memory_copy(void* dest, void* src, size_t count);
void memory_set(void* dest, uint8_t val, size_t count);

#endif