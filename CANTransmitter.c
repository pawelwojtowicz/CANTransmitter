#include "can_driver.h"
#include "uart_driver.h"
#include <avr/interrupt.h>

int main(void) 
{
  uart_initialize();

  //importante - activate the interrupts globally
  sei();

  uint8_t txSize = 0;
  uint8_t message[50];
  uint8_t txPrefix[] = {"\nYou said: "};

  while (1)
  {
    do
    {
      txSize = uart_getMessage( message );
    } while (0== txSize);


    uart_send(txPrefix, 14);
    while ( 0 == uart_send( message, txSize) )
    {
    }

  }

	return 1;
}
