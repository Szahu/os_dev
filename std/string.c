#include "string.h"

size_t string_length(char* str) {
    size_t size = 0;
    for (;str[size] != 0; size++) {}
    return size;
}

void string_reverse(char* str) {
    size_t len = string_length(str);
    int l = 0, r = len - 1;
    while (l < r) {
        char tmp = str[l];
        str[l] = str[r];
        str[r] = tmp;
        l++;
        r--;
    }
}

void string_int_to_ascii(int n, char* str) {
    int i, sign;
    if ((sign = n) < 0) n = -n;
    i = 0;
    do {
        str[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);

    if (sign < 0) str[i++] = '-';
    str[i] = '\0';
    string_reverse(str);
}