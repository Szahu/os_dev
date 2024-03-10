#include "port_utils.h"

uint8_t port_byte_in(uint16_t port) {
  uint8_t rv = 0x0;
  __asm__("in %%dx, %%al" : "=a" (rv) : "d" (port));
  return rv;
}

void port_byte_out(uint16_t port, uint8_t data) {
  __asm__ __volatile__("out %%al, %%dx" : : "a" (data), "d" (port));
}