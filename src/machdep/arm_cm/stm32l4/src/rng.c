/*
  Copyright (c) 2013
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2013-Aug-10 20:05 (EDT)
  Function: rng
*/

#include <conf.h>
#include <arch.h>
#include <stm32.h>


static void
_wait(int cnt){
    while(cnt-->0){
        __asm("nop");
    }
}

int
rng_init(void){

    RCC->AHB2ENR |= 1<<18;

#ifdef XXX_PLATFORM_STM32L4PLUS

    // XXX something is broken on the L4+
    RNG->CR = 0x40F00D40; // config A
    _wait(1000);
    RNG->HTCR = 0x17590ABC;
    RNG->HTCR = 0x0000A2B3 ; // 0x0000AA74;

    RNG->CR = 0x00F00D44; // config A + RNG EN =1

#else
    RNG->CR = 1<<2;
#endif
    return 0;
}

void
rng_reset(void){
    RCC->AHB2RSTR |= 1<<18;
    rng_init();
}

int
rng_get(void){

    while(1){
        if( RNG->SR & 1 ) break;
        if( RNG->SR & 4 ) return 0;
    }

    return RNG->DR;
}

unsigned int
random(void){
    return rng_get() & 0x7FFFFFFF;
}

