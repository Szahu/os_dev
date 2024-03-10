#include "memory.h"

void memory_copy(void* dest, void* src, size_t count) {
    uint8_t* const dest_byte_ptr = (uint8_t*)(dest);
    uint8_t* const src_byte_ptr = (uint8_t*)(src);
    for (size_t i = 0; i < count; ++i) {
        dest_byte_ptr[i] = src_byte_ptr[i];
    }
}

void memory_set(void* dest, uint8_t val, size_t count) {
    uint8_t* const dest_byte_ptr = (uint8_t*)(dest);
    for (size_t i = 0;i < count; ++i) {
        dest_byte_ptr[i] = val;
    }
}