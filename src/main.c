#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

#include "xitoa/xitoa.h"

void USARTInit(uint16_t ubrr_value)
{
   /* Set Baud rate*/
   UBRR0L = ubrr_value;                     /* 0b01100111*/
   UBRR0H = (ubrr_value>>8);               /* 0b00000000*/
   
   /* Enable The receiver and transmitter*/
   UCSR0B = _BV(TXEN0);                     /* (1 << RXEN0)|(1 << TXEN0);*/
   
   /* Set Frame Format; Asynchronous mode, No Parity, 1 StopBit, char size 8*/
   UCSR0C = _BV(UCSZ00)|_BV(UCPHA0);          /* (0b11<<UCSZ0)*/
}

void USARTWriteChar(uint8_t data)
{
    /* Wait until the transmitter is ready */
    while(((UCSR0A & (1<<UDRE0))==0)){
    }
    /* Now write the data to USART buffer */
    UDR0=data;
}

int main (void)
{
    xfunc_out = USARTWriteChar;

    USARTInit(12);
    while(1) 
    {
    }
}
