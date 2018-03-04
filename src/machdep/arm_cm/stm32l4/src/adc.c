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
#define CR_START	4
#define CR_ADON		1
#define CR_DEEPPWD	(1<<29)
#define CR_ADVREGEN	(1<<28)
#define SR_ARDY		1

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

    if( cn < 5 )  return;  // internal Vref on 0
    if( cn > 16 ) return;  // internal Temp on 17, Vbat on 18

    if( cn < 13 ){
        // adc5..12 -> A0..7
        gpio_init( GPIO_A0 + cn - 5, GPIO_ANALOG );
    }else if( cn < 17 ){
        // adc15,16 -> B0,1
        gpio_init( GPIO_B0 + cn - 15,  GPIO_ANALOG );
    }else{

    }
}


void
adc_init(int chan, int samp){
    ADC_TypeDef *dev = _adc_addr(chan);
    int cn = chan & 0x1F;

    RCC->AHB2ENR |= 1<<13;

    switch(chan>>5){
    case 0:
        if( cn < 16 )
            _adc12_conf_gpio( cn );
        break;
    default:
        PANIC("invalid ADC");
    }

    // adc starts in deep sleep - wake it, enable regulator
    if( dev->CR & CR_DEEPPWD ){
        dev->CR &= ~CR_DEEPPWD;
        dev->CR |= CR_ADVREGEN;
        // must wait 20us
        int i=1600;
        while(i-->0){
            __asm("nop");
        }

        // use default clock (from RCC)
        // enable vref, temp
        ADC123_COMMON->CCR = (0<<16) | (0<<18) | (3 <<22);

        dev->ISR = 0;
        dev->CR |= CR_ADON;	/* enable */
        while( (dev->ISR & SR_ARDY) == 0 ){} // wait for it
    }

    chan &= 0x1F;

    if( samp > 7 ) samp = 7;

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
    dev->SQR1 = chan << 6;

    dev->CR |= CR_START;

    while(1){
        // ~ 2usec
        if( dev->ISR & SR_EOC ) break;
        //printf("sr %x\n", dev->SR);
    }

    return dev->DR;
}

