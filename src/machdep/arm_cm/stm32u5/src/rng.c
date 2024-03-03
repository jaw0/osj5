/*
  Copyright (c) 2013
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2013-Aug-10 20:05 (EDT)
  Function: rng
*/

#include <conf.h>
#include <arch.h>
#include <stm32.h>

#ifdef KTESTING
# include <userint.h>
#endif

int
rng_init(void){

    RCC->AHB2ENR1 |= 1<<18;

    RNG->CR = 1<<2;
    return 0;
}

void
rng_reset(void){
    RCC->AHB2RSTR1 |= 1<<18;
    rng_init();
}

unsigned long
rng_get(void){

    while(1){
        if( RNG->SR & 1 ) break;
        if( RNG->SR & 4 ) return 0;
    }

    return RNG->DR;
}

unsigned long
random(void){
    return rng_get() & 0x7FFFFFFF;
}


#ifdef KTESTING

DEFUN(random, "random number")
{
    printf("%x\n", random());
    return 0;
}

#endif
