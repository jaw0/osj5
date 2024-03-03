/*
  Copyright (c) 2018
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2018-Mar-05 00:01 (EST)
  Function: platform dependent rtc init

*/

#ifndef __stm32u5_rtc_impl_h__
#define __stm32u5_rtc_impl_h__

#define RTC_GET_WUTF()	(RTC->SR & 4)
#define RTC_CLR_WUTF()	(RTC->SCR |= 4)

static inline const char *
_rtc_init(int *pre_s, int *pre_a){

    RCC->AHB3ENR |= 1<<2;	// pwr enable
    RCC->APB3ENR |= 1<<21;	// rtc-apb enable
    PWR->BDCR1 |= 1;		// enable bkp ram
    PWR->DBPR |= 1;		// DBP

    while( (PWR->DBPR & 1) == 0 ){}

#  ifdef LSECLOCK
    // QQQ - support other frequencies?
    RCC->BDCR |= 3 << 24;
    RCC->BDCR |= 1;			// enable LSE
    while( (RCC->BDCR & 2) == 0 ) {}	// wait for it
    RCC->BDCR |= 1<<8;			// src = lse
    *pre_s = 256;
    const char *info = "LSE 32768Hz";

#  else
    // QQQ - are all chips 32kHz?
    RCC->BDCR |= 1 << 24;
    RCC->BDCR  |= 1<<26;			// enable LSI
    while( (RCC->BDCR & (1<<27)) == 0 ) {}	// wait for it
    RCC->BDCR |= 2<<8;				// src = lsi
    *pre_s = 250;
    const char *info = "LSI 32kHz";
#  endif

    RCC->BDCR |= 1<<15;			// enable rtc

    return info;
}

#endif /* __stm32u5_rtc_impl_h__ */
