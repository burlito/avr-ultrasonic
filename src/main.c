#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "xitoa/xitoa.h"
#include "rtc/rtc.h"

volatile uint8_t mutex_usart = 0;
uint16_t start_time = 0;
uint16_t final_time = 0;
uint8_t state = 0;

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

void interr_meassure(void){
	PORTC |= _BV(PORTC0);
	EICRA |= _BV(ISC10) | _BV(ISC11);
	_delay_us(20);
	PORTC &= ~_BV(PORTC0);
}

ISR(INT1_vect)
{
	if (state == 0) {
		start_time = get_rtc();
		state = 1;
		EICRA &= ~_BV(ISC10);
	} else if (state == 1) {
		final_time = get_rtc() - start_time;
		state = 0;
		EICRA |= _BV(ISC10);
		interr_meassure();
	}
}

ISR(INT0_vect)
{
	if (!mutex_usart) {
		mutex_usart = 1;
		xprintf(PSTR("The button has been pressed.\n"));
		mutex_usart = 0;
	}
}

int main(void)
{
	xfunc_out = USARTWriteChar;
	DDRC |= _BV(DDC0);
	DDRC &= ~_BV(PORTC1);

	USARTInit(12);
	rtc_init();

	EIMSK |= _BV(INT0) | _BV(INT1);
	EICRA |= _BV(ISC01) | _BV(ISC00);
	interr_meassure();
	while (1) {
		_delay_ms(100);
		while (mutex_usart)
			;
		mutex_usart = 1;
		xprintf(PSTR("n: %d,t: %lu\n"),
			final_time, get_rtc_ms());
		mutex_usart = 0;
	}

	/*this should be unreachable*/
	return 0;
}
