/*
  Copyright (c) 2013
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2013-Mar-24 14:34 (EDT)
  Function: pwm
*/

#include <conf.h>
#include <arch.h>
#include <error.h>
#include <clock.h>
#include <proc.h>
#include <gpio.h>
#include <stm32.h>


// NB: the registers for timer1/8 + 2-5 are the same
// except for btdr vs reserved

#if defined(PLATFORM_STM32F1)
typedef TIM1_TypeDef TIM_T;
#else
typedef TIM_TypeDef TIM_T;
#endif

static inline TIM_T *
_timer_addr(int tim){
    switch(tim >> 4){
    case 1:	return (TIM_T*)TIM1;
    case 2:	return (TIM_T*)TIM2;
    case 3:	return (TIM_T*)TIM3;
    case 4:	return (TIM_T*)TIM4;
        // ...
    default:
        PANIC("invalid basic timer");
    }
}

static void
_freq_set(int timer, int clock, int maxval, int freq){
    TIM_T *tim = _timer_addr(timer);

    int psc = clock / (maxval + 1) / freq;
    psc --;

    if( psc < 0 ) psc = 0;
    if( psc > 0xFFFF ) 0xFFFF;

    tim->PSC = psc;
}

/****************************************************************/

void
pwm_init(int timer, int freq, int maxval){
    TIM_T *tim = _timer_addr(timer);
    int clock;

    int plx = splhigh();
    int t = timer >> 4;
#ifdef PLATFORM_STM32F1
    RCC->APB2ENR |= 1;	// AFIO
#endif

    switch( t ){
    case 1:
        // timer1
#ifdef PLATFORM_STM32F1
        RCC->APB2ENR |= 1 << 11;
#else
        RCC->APB2ENR |= 1;
#endif
        clock = APB2CLOCK;
        tim->BDTR  = 0x8000;	// MOE
        break;
    case 8:
        // timer 8
#ifdef PLATFORM_STM32F1
        RCC->APB2ENR |= 1 << 13;
#else
        RCC->APB2ENR |= 2;
#endif
        clock = APB2CLOCK;
        tim->BDTR  = 0x8000;	// MOE
        break;
    default:
        RCC->APB1ENR |= 1 << (t - 2);
        clock = APB1CLOCK;
        break;
    }


    tim->CCMR1 |= 0x6868;       // chan1+2 pwm
    tim->CCMR2 |= 0x6868;       // chan3+4 pwm
    tim->CCER  |= 0x1111;       // output enable chan1,2,3,4
    tim->ARR   = maxval;
    _freq_set(timer, clock, maxval, freq);
    tim->CR1   |= 1;    	// enable

    splx(plx);
}

void
pwm_set(int timer, int val){
    TIM_T *tim = _timer_addr(timer);

    switch( timer & 0x3 ){
    case 0:	tim->CCR1 = val;	break;
    case 1:	tim->CCR2 = val;	break;
    case 2:	tim->CCR3 = val;	break;
    case 3:	tim->CCR4 = val;	break;
    }
}


void
freq_set(int timer, int freq){
    TIM_T *tim = _timer_addr(timer);

    int maxval = tim->ARR;
    int clock = ( (timer>>4) & 0xF == 1) ? APB2CLOCK : APB1CLOCK;

    _freq_set(timer, clock, maxval, freq);
}

