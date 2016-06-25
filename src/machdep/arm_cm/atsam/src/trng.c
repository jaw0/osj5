/*
  Copyright (c) 2016
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2016-Jun-25 11:02 (EDT)
  Function: random number generator

*/

#include <conf.h>
#include <arch.h>
#include <atsam.h>
#include <pmc.h>

int
trng_init(void){

    pmc_enable( ID_TRNG );
    TRNG->TRNG_CR = TRNG_CR_KEY_PASSWD | TRNG_CR_ENABLE;
    return 0;
}

int
trng_get(void){

    while(1){
        if( TRNG->TRNG_ISR & TRNG_ISR_DATRDY ) break;
    }

    return TRNG->TRNG_ODATA;
}

unsigned int
random(void){
    return trng_get() & 0x7FFFFFFF;
}

