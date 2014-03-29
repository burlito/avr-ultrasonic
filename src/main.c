#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

#include "xitoa/xitoa.h"

void USARTInit(uint16_t ubrr_value)
{
	UBRR0L = ubrr_value;
	UBRR0H = (ubrr_value>>8);
	UCSR0B = _BV(TXEN0);
	UCSR0C = _BV(UCSZ00)|_BV(UCSZ01);
}

void USARTWriteChar(uint8_t data)
{
	while (((UCSR0A & (1<<UDRE0)) == 0))
		;
	UDR0 = data;
}

/**/
int b_messure(void){
	int time = 0;

	DDRC |= _BV(DDC0);
	DDRC &= ~_BV(PORTC1);
	PORTC |= _BV(PORTC0);
	_delay_us(20);
	PORTC &= ~_BV(PORTC0);
	while (!(PINC & _BV(PINC1)))
		;

	while (PINC & _BV(PINC1)) {
		_delay_us(10);
		time++;
	}

	return time;
}

int main(void)
{
	xfunc_out = USARTWriteChar;

	USARTInit(12);
	while (1) {
		_delay_ms(25);
		xprintf(PSTR("nameral: %d\n"), b_messure());
	}

	/*this should be unreachable*/
	return 0;
}
