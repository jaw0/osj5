/*
  Copyright (c) 2013
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2013-Apr-05 19:59 (EDT)
  Function: 
 
  $Id$

*/

#include <conf.h>
#include <arch.h>
#include <error.h>
#include <clock.h>
#include <proc.h>
#include <gpio.h>
#include <stm32.h>


#define SR_EOC	2


/* RSN - sequential conversions w/ DMA */

static inline ADC_TypeDef *
_adc_addr(int adc){
    switch(adc >> 5){
    case 0:	return (ADC_TypeDef*)ADC1;
    case 1:	return (ADC_TypeDef*)ADC2;
    default:
        PANIC("invalid ADC");
    }
}

void
adc_init(int chan, int samp){
    ADC_TypeDef *dev = _adc_addr(chan);
    int cn = chan & 0x1F;

    switch(chan>>5){
    case 0:
        RCC->APB2ENR |= 1<<9;
        if( cn < 8 )
            gpio_init( GPIO_A0 + cn, GPIO_INPUT_ANALOG );
        break;
    case 1:
        RCC->APB2ENR |= 1<<10;
        if( cn < 8 )
            gpio_init( GPIO_B0 + cn, GPIO_INPUT_ANALOG );
        break;
    case 2:
        RCC->APB2ENR |= 1<<15;
        if( cn < 8 )
            gpio_init( GPIO_C0 + cn, GPIO_INPUT_ANALOG );
        break;
    default:
        PANIC("invalid ADC");
    }

    dev->CR2 |= 1;	/* enable */
    dev->CR2 |= 1<<23;	/* enable temp sensor */

    chan &= 0x1F;

    if( chan < 10 ){
        dev->SMPR1 &= ~ (7<< (3 * chan));
        dev->SMPR1 |= (samp & 0x7) << (3 * chan);
    }else{
        chan -= 10;
        dev->SMPR2 &= ~ (7<< (3 * chan));
        dev->SMPR2 |= (samp & 0x7) << (3 * chan);
    }
}

int
adc_get(int chan){
    ADC_TypeDef *dev = _adc_addr(chan);

    int v = dev->DR;	// clear any previous result
    dev->SQR3 = chan;
    dev->CR2 |= 1;

    while(1){
        // ~ 2usec
        if( dev->SR & SR_EOC ) break;
    }

    return dev->DR;
}
