#include <stdio.h>
#include <stdlib.h>

#include "../circular_buffer.h"

t_circular_buffer* pBuffer = 0;

void storeString( uint8_t* text)
{
    while(*text != 0 )
    {
        cb_storeCharacter(pBuffer, *text);
        ++text;
    }
}

int main()
{
    pBuffer = cb_initialize();

    storeString( "ZgodaBuduje;niezgodaRujnuje; atos pontos;");

	uint8_t output[100];
	uint16_t msgSize = getMessage(output);
	msgSize = getMessage(output);
	msgSize = getMessage(output);
	msgSize = getMessage(output);

	return 0;
}
