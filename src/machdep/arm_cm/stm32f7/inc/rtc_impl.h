/*
  Copyright (c) 2018
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2018-Mar-05 00:01 (EST)
  Function: platform dependent rtc init

*/

#ifndef __stm32f7_rtc_impl_h__
#define __stm32f7_rtc_impl_h__

static inline const char *
_rtc_init(int *pre_s, int *pre_a){

    RCC->APB1ENR |= (1<<28);		// enable PWR system
    PWR->CR1 |= (1<<8);			// enable backup domain (DBP)

#  ifdef LSECLOCK
    // QQQ - support other frequencies?
    RCC->BDCR |= 3<<3;			// LSE - high drive?
    RCC->BDCR |= 1;			// enable LSE
    while( (RCC->BDCR & 2) == 0 ) {}	// wait for it
    RCC->BDCR |= 1<<8;			// src = lse
    *pre_s = 256;
    const char *info = "LSE 32768Hz";
#  else
    // QQQ - are all chips 32kHz?
    RCC->CSR  |= 1;			// enable LSI
    while( (RCC->CSR & 2) == 0 ) {}	// wait for it
    RCC->BDCR |= 2<<8;			// src = lsi
    *pre_s = 250;
    const char *info = "LSI 32kHz";
#  endif
    RCC->BDCR |= 1<<15;			// enable rtc

    return info;
}

#endif /* __stm32f7_rtc_impl_h__ */
