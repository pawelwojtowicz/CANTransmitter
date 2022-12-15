#include "can_driver.h"
#include "uart_driver.h"
#include "circular_buffer.h"

int main(void) 
{
  uart_initialize();
  initializeCANController();


  uint8_t msgReceived = 0;
  uint8_t message[50];
  while (1)
  {
    while ( 0!= msgReceived )
    {
      msgReceived = uart_getMessage( message );
    }
    
  }
	return 1;
}
