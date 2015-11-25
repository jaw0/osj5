/*
  Copyright (c) 2013
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2013-Apr-05 19:59 (EDT)
  Function: 

*/

#include <conf.h>
#include <arch.h>
#include <error.h>
#include <clock.h>
#include <proc.h>
#include <gpio.h>
#include <adc.h>
#include <stm32.h>


#define SR_EOC		4
#define CR2_SWSTART	0x40000000

static inline ADC_TypeDef *
_adc_addr(int adc){
    switch(adc >> 5){
    case 0:	return (ADC_TypeDef*)ADC1;
    default:
        PANIC("invalid ADC");
    }
}

static inline void
_adc12_conf_gpio(int cn){

    if( cn < 8 ){
        gpio_init( GPIO_A0 + cn, GPIO_ANALOG );
    }else if( cn < 10 ){
        gpio_init( GPIO_B0 + cn - 8,  GPIO_ANALOG );
    }else{
        gpio_init( GPIO_C0 + cn - 10, GPIO_ANALOG );
    }
}

void
adc_init(int chan, int samp){
    ADC_TypeDef *dev = _adc_addr(chan);
    int cn = chan & 0x1F;

    RCC->APB2ENR |= 1<<9;

    switch(chan>>5){
    case 0:
        if( cn < 16 )
            _adc12_conf_gpio( cn );
        break;
    default:
        PANIC("invalid ADC");
    }

    dev->CR |= 1;	/* enable */

    if( samp > 7 ) samp = 7;

    // bizarre relationship
    dev->SMPR = samp;

}


int
adc_get(int chan){
    ADC_TypeDef *dev = _adc_addr(chan);

    int v = dev->DR;	// clear any previous result
    dev->CHSELR = 1 << (chan & 0x1F);
    dev->CR |= 4; // start

    while(1){
        // ~ 2usec
        if( dev->ISR & SR_EOC ) break;
        //printf("sr %x\n", dev->SR);
    }

    return dev->DR;
}

