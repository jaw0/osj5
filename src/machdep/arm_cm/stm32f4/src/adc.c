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


#define SR_EOC		2
#define CR2_SWSTART	0x40000000
#define CR2_ADON	1

/* RSN - sequential conversions w/ DMA */

static inline ADC_TypeDef *
_adc_addr(int adc){
    switch(adc >> 5){
    case 0:	return (ADC_TypeDef*)ADC1;
    case 1:	return (ADC_TypeDef*)ADC2;
    case 2:	return (ADC_TypeDef*)ADC3;
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

    switch(chan>>5){
    case 0:
        RCC->APB2ENR |= 1<<8;
        _adc12_conf_gpio( cn );
        break;
    case 1:
        RCC->APB2ENR |= 1<<9;
        break;
    case 2:
        RCC->APB2ENR |= 1<<10;
        /* scattered throught PF */
        /* ... */
        break;
    default:
        PANIC("invalid ADC");
    }

    dev->CR2 |= CR2_ADON;	/* enable */

    ADC->CCR &= 0x00C37F1F;

    ADC->CCR |= (1<<23)	/* temp enable */
        | (1<<22)	/* vbat enable */
        | (1<<16)	/* ahb2clock / 4 */
        ;

    chan &= 0x1F;

    samp = 0;	// 3 cycles

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
    dev->CR2 |= CR2_SWSTART;

    while(1){
        // ~ 2usec
        if( dev->SR & SR_EOC ) break;
        //printf("sr %x\n", dev->SR);
    }

    return dev->DR;
}
