#include "can_driver.h"
#include "circular_buffer.h"

t_circular_buffer* a;

int main(void) 
{
  a = cb_initialize();

  cb_storeCharacter(a,'a');
	initializeCANController();
	return 1;
}
