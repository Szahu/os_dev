#ifndef PORT_UTILS_H
#define PORT_UTILS_H

#include "types.h"

uint8_t port_byte_in(uint16_t port);

void port_byte_out(uint16_t port, uint8_t data);

#endif