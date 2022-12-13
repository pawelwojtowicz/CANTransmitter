#include <stdio.h>
#include <stdlib.h>

#include "../circularBuffer.h"

int main()
{
	storeCharacter('a');
	storeCharacter('b');
	storeCharacter('c');
	storeCharacter('d');
	storeCharacter('e');
	storeCharacter(';');
	storeCharacter('g');
	storeCharacter('h');
	storeCharacter(';');
	storeCharacter('j');
	storeCharacter('k');
	uint8_t output[100];
	uint16_t msgSize = getMessage(output);
	msgSize = getMessage(output);
	msgSize = getMessage(output);
	msgSize = getMessage(output);
	storeCharacter('l');
	storeCharacter('m');
	storeCharacter('n');

	printf("Hello world!\n");
	return 0;
}
