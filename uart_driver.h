#ifndef UART_DRIVER_H
#define UART_DRIVER_H

#include <inttypes.h>

void uart_initialize();

uint8_t uart_send( uint8_t* buffer, uint8_t size );

uint8_t uart_getMessage( uint8_t* msg );

#endif
