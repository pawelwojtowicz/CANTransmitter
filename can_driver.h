#ifndef CAN_DRIVER_H
#define CAN_DRIVER_H

#include <inttypes.h>
#include <stdbool.h>

void can_initialize();

bool can_sendMessage( const uint32_t canId, uint8_t* data, const uint8_t size );

#endif //CAN_DRIVER_H
