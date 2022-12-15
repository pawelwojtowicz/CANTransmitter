#include "circular_buffer.h"


t_circular_buffer rxBuffer;

t_circular_buffer* cb_initialize()
{
  rxBuffer.writePos = 0;
  rxBuffer.readPos = 0;
  rxBuffer.freeSpace = BUFFER_SIZE;
  rxBuffer.msgCount = 0;

  return &rxBuffer;
}

uint16_t getMessage( uint8_t* message )
{
    uint16_t messageSize = 0;

    if (rxBuffer.msgCount > 0 )
    {
        do
        {
            message[messageSize] = rxBuffer.buffer[(rxBuffer.readPos+messageSize)%BUFFER_SIZE];
            ++messageSize;
        } while ( rxBuffer.buffer[(rxBuffer.readPos+messageSize)%BUFFER_SIZE] != MSG_DELIMITER );

        rxBuffer.readPos = (rxBuffer.readPos+messageSize+1)%BUFFER_SIZE;
        rxBuffer.freeSpace += messageSize+1;
        --rxBuffer.msgCount;
    }

    return messageSize;
}
