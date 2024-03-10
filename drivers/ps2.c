#include "ps2.h"
#include "port_utils.h"

void wait_for_ps2() {
    while ((port_byte_in(PS2_CTRL_PORT) & 0x02) != 0x0) {} 
}