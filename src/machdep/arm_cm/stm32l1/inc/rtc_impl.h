/*
  Copyright (c) 2018
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2018-Mar-05 00:01 (EST)
  Function: platform dependent rtc init

*/

#ifndef __stm32l1_rtc_impl_h__
#define __stm32l1_rtc_impl_h__

static inline const char *
_rtc_init(int *pre_s, int *pre_a){

    RCC->APB1ENR |= (1<<28);		// enable PWR system
    PWR->CR |= (1<<8);			// enable backup domain (DBP)

#  ifdef LSECLOCK
    RCC->CSR |= 1<<8;			// enable LSE
    while( (RCC->CSR & (1<<9)) == 0 ){} // wait for it
    RCC->CSR |= 1<<16;			// src = lse
    *pre_s = 256;
    const char *info = "LSE 32768Hz";
#  else
    // QQQ - are all chips 32kHz?
    RCC->CSR  |= 1;			// enable LSI
    while( (RCC->CSR & 2) == 0 ){}	// wait for it
    RCC->CSR |= 2<<16;			// src = lsi
    *pre_s = 296;
    *pre_a = 125;
    const char *info = "LSI 37kHz";	// wtf?
#  endif
    RCC->CSR |= 1<<22;			// enable rtc

    return info;
}

#endif /* __stm32l1_rtc_impl_h__ */
