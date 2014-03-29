/**
  The MIT License (MIT)

  Copyright (c) 2014 Andrej Manduch, Adrián Matejov, XLC Team

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
*/

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

