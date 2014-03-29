#include <util/atomic.h>
#include <avr/io.h>
#include <avr/interrupt.h>

uint16_t high_bites;

void rtc_init(void)
{
	/* CS12 & CS10 is 1024 div presaller */
	TCCR1B |= _BV(CS12) | _BV(CS10);
	high_bites = 0;
	/*Timer 1 can be accessed from TCNT1H and TCNT1L */
}

uint16_t get_rtc(void)
{
	uint16_t tmp;
	uint8_t i;

	/* attem to read without blocking */
	for (i = 0; i < 4; i++) {
		((uint8_t *)&tmp)[1] = TCNT1H;
		((uint8_t *)&tmp)[0] = TCNT1L;
		if ((uint8_t)((&tmp)[1]) == TCNT1H)
			return tmp;
	}

	/* when non-block reading was not possible: */
	ATOMIC_BLOCK(ATOMIC_FORCEON) {
		tmp = TCNT1;
	}

	return tmp;
}

