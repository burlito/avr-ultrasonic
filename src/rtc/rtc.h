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

/**
	this RTC library is made for ATMega328p and uses Timer1 as source
	of time.
*/

#include "config.h"

/** void rtc_init(void)
	\brief initialize rtc

	rtc_init should be used in the very beginig of your code.
*/
void rtc_init(void);

/**
	\brief will safelly return value of internal T1 counter

	Basically this function will return internal timer
	register without any changes but you should use this
	and not use direct copy of TCNT1 register becouse
	this function will return TCNT1 in thread safe way.

	\return 16 bit unsigned value of current timer counter.
*/
uint16_t get_rtc(void);

/**
	\brief function will return 32 bit value of rtc

	This function will return you full 32 bit value which is
	internal TCNT1 register plus 16 bit timer overflow counter.
	This function is way slower than get_rtc() so if there is a
	way to user get_rtc() instead you should use get_rtc().

	\return 32 bit unsigned value of current rtc value
*/
#ifdef RTC_32_BIT
uint32_t get_full_rtc(void);
#endif /* RTC_32_BIT */
/**
	\brief it's used to messure time in miliseconds

	Function internally read rtc timer and overflow var and
	compute time in ms in most sufficient way.

	\return 32 bit undigned value of current ms from start timer initialization
*/
#ifdef RTC_32_BIT
uint32_t get_rtc_ms(void);
#else /* RTC_32_BIT */
uint16_t get_rtc_ms(void);
#endif /* RTC_32_BIT */

/**
	\brief it's used to messure time in microseconds

	Function internally read rtc timer and overflow var and
	compute time in ms in most sufficient way.

	\return 32 bit undigned value of current ms from start timer initialization
*/
#ifdef RTC_32_BIT
uint32_t get_rtc_us(void);
#else /* RTC_32_BIT */
uint16_t get_rtc_us(void);
#endif /* RTC_32_BIT */

/**
	\brief transform TC1 ticks to miliseconds

	function translate get_rtc and get_full_rtc value in to
	miliseconds. Is useful if you want to make high resolution
	time diferrence with very small error.

	\param ticks number of TC1 ticks.

	\return unsigned 32 bit integer in miliseconds
*/
#ifdef RTC_32_BIT
uint32_t ticks2ms(uint32_t);
#else /* RTC_32_BIT */
uint16_t ticks2ms(uint16_t);
#endif /* RTC_32_BIT */

/**
	\brief transform TC1 ticks to microseconds

	see ticks2ms()
*/
#ifdef RTC_32_BIT
uint32_t ticks2us(uint32_t);
#else /* RTC_32_BIT */
uint16_t ticks2us(uint16_t);
#endif /* RTC_32_BIT */
