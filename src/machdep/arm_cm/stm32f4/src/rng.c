/*
  Copyright (c) 2013
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2013-Aug-10 20:05 (EDT)
  Function: rng
*/

#include <conf.h>
#include <arch.h>
#include <stm32.h>


int
rng_init(void){

    RCC->AHB2ENR |= 1<<6;
    RNG->CR = 1<<2;
    return 0;
}

int
rng_get(void){

    while(1){
        if( RNG->SR & 1 ) break;
    }

    return RNG->DR;
}


