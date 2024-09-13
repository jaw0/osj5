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

#ifdef ADC123_COMMON
#  define COMMON ADC123_COMMON
#else
#  define COMMON ADC12_COMMON
#endif


static inline ADC_TypeDef *
_adc_addr(int adc){
    switch(adc >> 5){
    case 0:	return (ADC_TypeDef*)ADC1;
    case 1:	return (ADC_TypeDef*)ADC2;
#ifdef ADC3
    case 2:	return (ADC_TypeDef*)ADC3;
#endif
#ifdef ADC4
    case 3:	return (ADC_TypeDef*)ADC4;
#endif
    default:
        PANIC("invalid ADC");
    }
}

static inline void
_adc12_conf_gpio(int cn){

    if( cn < 1 )  return;  // internal Vref on 0
    if( cn > 17 ) return;  // internal Temp on 17, Vbat on 18

    if( cn < 5 ){
        gpio_init( GPIO_C0 + cn - 1, GPIO_ANALOG );
    } else if( cn < 13 ){
        // adc5..12 -> A0..7
        gpio_init( GPIO_A0 + cn - 5, GPIO_ANALOG );
    }else if( cn < 15 ){
        // adc13,14 -> C4,5
        gpio_init( GPIO_C0 + cn - 9,  GPIO_ANALOG );
    }else if( cn < 17 ){
        // adc15,16 -> B0,1
        gpio_init( GPIO_B0 + cn - 15,  GPIO_ANALOG );
    }else{

    }
}

static const int prescale[] = {
    1, 2, 4, 6, 8, 10, 12, 16, 32, 64, 128, 256
};

void
adc_init(int chan, int samp){
    ADC_TypeDef *dev = _adc_addr(chan);
    int cn = chan & 0x1F;
    int i;

    if( !dev ) return;

#ifdef PLATFORM_STM32U5
    RCC->AHB2ENR1 |= 1<<10;
#else // L4
    RCC->AHB2ENR |= 1<<13;
#endif

    if( (chan >> 5) < 3 )
        _adc12_conf_gpio( cn );

    // adc starts in deep sleep - wake it, enable regulator
    if( dev->CR & CR_DEEPPWD ){
        dev->CR &= ~CR_DEEPPWD;
        dev->CR |= CR_ADVREGEN;

#ifdef PLATFORM_STM32U5
        // wait for it
        while( (dev->ISR & ADC_ISR_LDORDY) == 0) {}
#else
        // no rdy bit, must wait 20us
        i=1600;
        while(i-- > 0){
            __asm("nop");
        }
#endif

        // configure clock prescaler
        COMMON->CCR &= ~(0xF << 18);

        for(i=0; i<12; i++){
            if( ADCMAX * prescale[i] >= ahb_clock_freq() ){
                COMMON->CCR |= i << 18;
                break;
            }
        }

        // use default clock (from RCC)
        // enable vref, temp
        COMMON->CCR |= (7 <<22);

        dev->ISR = 0;

        dev->CR |= 1<<31; // calibrate
        while( dev->CR & (1<<31) ){}

        dev->CR |= CR_ADON;	/* enable */
        while( (dev->ISR & SR_ARDY) == 0 ){} // wait for it
    }

    chan &= 0x1F;

#ifdef PLATFORM_STM32U5
    dev->PCSEL |= 1 << chan;
#endif

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

/* init channel on ADC1+2 */
void
adc_init2(int chan, int samp){
    adc_init(chan, samp);
    adc_init(chan + ADC_2_0, samp);
}


int
adc_get(int chan){
    ADC_TypeDef *dev = _adc_addr(chan);

    chan &= 0x1F;

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

// dual simultaneous ADC
int
adc_get2(int chan1, int chan2){
    chan1 &= 0x1F;
    chan2 &= 0x1F;

    int v = ADC1->DR;	// clear any previous result
    v = ADC2->DR;

    ADC1->SQR1 = chan1 << 6;
    ADC2->SQR1 = chan2 << 6;

    COMMON->CCR  |= 6;	// simultaneous regular mode
    ADC1->CR |= CR_START;

    while(1){
        // ~ 2usec
        if( (ADC1->ISR & SR_EOC) && (ADC2->ISR & SR_EOC) ) break;
    }

    COMMON->CCR &= ~0xF;	// disable simultaneous mode

    // NB: CDR is only available using DMA
    return (ADC1->DR & 0xFFFF) | (ADC2->DR << 16);
}
