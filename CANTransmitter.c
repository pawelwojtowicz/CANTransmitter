#include "can_driver.h"
#include "circular_buffer.h"

t_circular_buffer a;

int main(void) 
{
	initializeCANController();
	return 1;
}
