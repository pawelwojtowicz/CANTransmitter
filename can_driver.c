#include <avr/interrupt.h>
#include <avr/iocan128.h>
#include <stdbool.h>
#include <inttypes.h>

#define SET_CAN_PAGE( page ) ( CANPAGE = page << 4) 

void can_initialize()
{
	// no overload frame request
	// no listening mode
	// no test mode
	// standby mode
	// software reset request
	CANGCON = _BV(SWRES);

	// enable general interrupt
	CANGIE = _BV( ENIT) ;

	// MOb 8 to 14 interrupt disable
	CANIE1 = 0x00 ; /*MOb 8~14*/
	// MOb 0 to 7 interrupts disabled
	CANIE2 = 0x00;
 
	// CAN bit timing registers
	// set the timing (baud) ? 250 KBaud with 16 Mhz clock 
	CANBT1 = 0x06 ;    // Baud Rate Prescaler
	CANBT2 = 0x0c ;    // Re-Synchronization & Propagation 
	CANBT3 = 0x37 ;    // Phase Segments & Sample Point(s) 

	uint8_t index = 0;

	for (index = 0 ; index < 15 ; ++index )
	{
		SET_CAN_PAGE(index);
		CANCDMOB = _BV(IDE);
		CANSTMOB = 0x00;
	}

	// CAN Timer Clock Period: 0.500 us 
	CANTCON = 0x00 ;

	// enter enable mode
	CANGCON = (1 << ENASTB);
}

bool can_sendMessage( const uint32_t canId, uint8_t* data, const uint8_t size )
{
	if ((CANEN2 & _BV( ENMOB0)) != 0) 
	{ 
      return false; 
   	}

	SET_CAN_PAGE(1);


	CANIDM1 = 0x00;  // no mask 
	CANIDM2 = 0x00; 
	CANIDM3 = 0x00; 
	CANIDM4 = 0x00;


	CANIDT1 = ( canId >> 21 ) & 0xff;
	CANIDT2 = ( canId >> 13 ) & 0xff; 
	CANIDT3 = ( canId >> 5 ) & 0xff;
	CANIDT4 = ( canId & 0b11111 )<<3;

	uint8_t index = 0;
	for ( index = 0 ; index < size ; ++index)
	{
		CANMSG = data[index];
	}

	CANCDMOB = (1 << CONMOB0) | (size & 0b1111) ; //enable transmission!! , data length = size
	CANSTMOB = 0x00;

	return true;
}
