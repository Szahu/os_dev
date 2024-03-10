#ifndef STRING_H
#define STRING_H

#include "types.h"

size_t string_length(char* str);

void string_reverse(char* str);

void string_int_to_ascii(int n, char* buffer);

#endif