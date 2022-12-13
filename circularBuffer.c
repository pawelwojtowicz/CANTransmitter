#include <inttypes.h>

#define BUFFER_SIZE 10
#define MSG_DELIMITER ';'

uint8_t buffer[BUFFER_SIZE];
volatile uint16_t writePos = 0;
volatile uint16_t readPos = 0;

volatile uint16_t freeSpace = BUFFER_SIZE;
volatile uint16_t msgCount = 0;

void storeCharacter( uint8_t c)
{
	if ( freeSpace > 0 )
	{
		buffer[writePos] = c;
		writePos = (writePos+1)%BUFFER_SIZE;
		--freeSpace;
		if (MSG_DELIMITER == c )
		{
			++msgCount;
		}
	}
}

uint16_t getMessage( uint8_t* message )
{
	uint16_t messageSize = 0;

	if (msgCount > 0 )
	{
		do
		{
			message[messageSize] = buffer[(readPos+messageSize)%BUFFER_SIZE];
			++messageSize;
		} while ( buffer[(readPos+messageSize)%BUFFER_SIZE] != MSG_DELIMITER );

		readPos = (readPos+messageSize+1)%BUFFER_SIZE;
        freeSpace += messageSize+1;
		--msgCount;
	}

	return messageSize;
}
