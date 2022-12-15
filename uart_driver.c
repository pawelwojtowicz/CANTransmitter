#include <avr/iocan128.h>
#include <util/atomic.h>
#include <avr/interrupt.h>
#include <string.h>
#include "circular_buffer.h"

//*************************************************************************
//**************Communication parameters***********************************
#define BAUD 19200
#define MYUBRR F_CPU/16/BAUD-1
//*************************************************************************


// TX Buffer params
#define TX_BUFFER_SIZE 50
static uint8_t txBuffer[TX_BUFFER_SIZE];
static uint8_t* txPointer = 0;
static uint8_t bytesToSend = 0;

// circular buffer for the received data
t_circular_buffer* rxCBuffer = 0;

void uart_initialize()
{
  rxCBuffer = cb_initialize();

  unsigned int ubrr = MYUBRR;
  
  UBRR0H = (unsigned char)(ubrr>>8);
  UBRR0L = (unsigned char)ubrr;
  UCSR0B = _BV(TXCIE0)|_BV(RXCIE0)|_BV(RXEN0)|_BV(TXEN0);
  /* 8-bit dane, 1-bit stopu, prak bitu parzystosci */
  UCSR0C = ( (0<<USBS0) | (3<<UCSZ00) );
}

uint8_t uart_send( uint8_t* buffer, uint8_t size )
{
  if ( bytesToSend > 0 )
  {
    return 0;
  }

  ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
  {
    memcpy( (void*) txBuffer, (void*)buffer, size );
    txPointer = txBuffer ;
    bytesToSend = size ;
    
    UDR0 = *txPointer;
    ++txPointer;
    --bytesToSend;
  }   
  return 1;
}

//------------------------------------------------------------------------------------------------------------------------------------

/** UART TX interrupt routine */
ISR( USART0_TX_vect )
{
  if ( bytesToSend > 0 )
  {
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
      UDR0 = *txPointer;
      ++txPointer;
      --bytesToSend;
    }
  }
}


//--------------------------RECEIVER PART-------------------------------------------------------------------------------------

uint8_t uart_getMessage( uint8_t* data )
{
  uint8_t size = 0;
  
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
  {
    size = cb_getMessage(data);
  }
  
  return size;
}

//------------------------------------------------------------------------------------------------------------------------------------

/** UART RX interrupt routine */
ISR( USART0_RX_vect )
{
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
  {
    cb_storeCharacter(rxCBuffer, UDR0);
  }
}

//------------------------------------------------------------------------------------------------------------------------------------
