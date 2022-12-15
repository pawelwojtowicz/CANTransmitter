#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include <inttypes.h>

#define BUFFER_SIZE 10
#define MSG_DELIMITER ';'


typedef struct
{
  uint8_t buffer[BUFFER_SIZE];
  volatile uint16_t writePos;
  volatile uint16_t readPos;
  volatile uint16_t freeSpace;
  volatile uint16_t msgCount;
} t_circular_buffer;

t_circular_buffer* cb_initialize();

inline void storeCharacter( t_circular_buffer* rxBuffer, uint8_t c)
{
	if ( rxBuffer->freeSpace > 0 )
	{
		rxBuffer->buffer[rxBuffer->writePos] = c;
		rxBuffer->writePos = (rxBuffer->writePos+1)%BUFFER_SIZE;
		--rxBuffer->freeSpace;
		if (MSG_DELIMITER == c )
		{
			++rxBuffer->msgCount;
		}
	}
}


uint16_t getMessage( uint8_t* message );

#endif
