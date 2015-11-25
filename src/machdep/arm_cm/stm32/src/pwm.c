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
#include <pwm_impl.h>



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
#ifdef TIM1
    case 1:	return (TIM_T*)TIM1;
#endif
#ifdef TIM2
    case 2:	return (TIM_T*)TIM2;
#endif
#ifdef TIM3
    case 3:	return (TIM_T*)TIM3;
#endif
#ifdef TIM4
    case 4:	return (TIM_T*)TIM4;
#endif
#ifdef TIM5
    case 5:	return (TIM_T*)TIM5;
#endif
#ifdef TIM6
    case 6:	return (TIM_T*)TIM6;
#endif
#ifdef TIM7
    case 7:	return (TIM_T*)TIM7;
#endif
#ifdef TIM8
    case 8:	return (TIM_T*)TIM8;
#endif
#ifdef TIM9
    case 9:	return (TIM_T*)TIM9;
#endif
#ifdef TIM10
    case 10:	return (TIM_T*)TIM10;
#endif
#ifdef TIM11
    case 11:	return (TIM_T*)TIM11;
#endif
#ifdef TIM12
    case 12:	return (TIM_T*)TIM12;
#endif
#ifdef TIM13
    case 13:	return (TIM_T*)TIM13;
#endif
#ifdef TIM14
    case 14:	return (TIM_T*)TIM14;
#endif
#ifdef TIM15
    case 15:	return (TIM_T*)TIM15;
#endif
#ifdef TIM16
    case 16:	return (TIM_T*)TIM16;
#endif
#ifdef TIM17
    case 17:	return (TIM_T*)TIM17;
#endif
    default:
        PANIC("invalid timer");
    }
}

static void
_freq_set(int timer, int clock, int maxval, int freq){
    TIM_T *tim = _timer_addr(timer);

    int psc = clock / (maxval + 1) / freq;
    psc --;

    if( psc < 0 ) psc = 0;
    if( psc > 0xFFFF ) psc = 0xFFFF;

    tim->PSC = psc;
}

/****************************************************************/

void
pwm_init(int timer, int freq, int maxval){
    TIM_T *tim = _timer_addr(timer);
    int clock;

    int plx = splhigh();
    int t = timer >> 4;

    timer_rcc_init( t );
    clock = timer_clockspeed( t );

#if defined(TIM1) || defined(TIM8) || defined(TIM16) || defined(TIM17)
    if( t == 1 || t == 8 || t == 16 || t == 17 ){
        tim->BDTR  |= 0x8000;	// MOE
    }
#endif

    tim->CCMR1 |= 0x6868;       // chan1+2 pwm, CCR changes are buffered
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
    int clock  = timer_clockspeed( timer >> 4 );

    _freq_set(timer, clock, maxval, freq);
}

