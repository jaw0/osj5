/*
  Copyright (c) 2013
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2013-Mar-11 00:46 (EDT)
  Function: stm32F0 hardware init
*/

#include <conf.h>
#include <stm32f0xx.h>
#include <proc.h>
#include <alloc.h>
#include <clock.h>


#define R_FLASHKB	((unsigned short *)(0x1FFFF7CC))
#define R_UNIQUE	((unsigned long*)(0x1FFFF7AC))


#ifdef HSECLOCK
#  define SRCCLOCK	HSECLOCK
#else
#  define SRCCLOCK	HSICLOCK
#endif


unsigned long bootflags = 0;
void stm32_putchar(int);

int freq_sys=HSICLOCK;

int sys_clock_freq(void){  return freq_sys;  }
int ahb_clock_freq(void){  return freq_sys;  }
int apb1_clock_freq(void){ return freq_sys; }
int apb2_clock_freq(void){ return freq_sys; }

static inline void
also_adc_hsi(void){
    // hsi14 is needed for ADC clock
#ifdef USE_ADC
    RCC->CR2	|= 1;	// HSI14_ON
    while( RCC->CR2 & (1<<1) == 0 ) {}	// wait until ready
#endif
}

static void inline
set_clocksrc(int src){
    RCC->CFGR |= src;
    while( RCC->CFGR & 0xC == 0 ){} /* wait for it */
}

static const char pllm[] = { 3, 4, 6, 8, 12, 16, 24, 32, 48 };

static void
clock_init(void){
    int clksrc = 0;
    int m;

    also_adc_hsi();

#if !defined(HSECLOCK)
    RCC->CR	|= 1;	// HSI_ON
    while( RCC->CR & (1<<1) == 0 ) {}	// wait until ready
# if (SYSCLOCK == HSICLOCK)
    set_clocksrc(0);
    freq_sys = HSICLOCK;
    return;
# endif
#endif

#ifdef HSECLOCK
#  if (HSECLOCK < 1000000) || (HSECLOCK > 24000000)
#    error "not a valid HSE frequency. must be: 1MHz - 24MHz"
#  endif

    /* enable HSE */
    RCC->CR |= (1<<16);
    while( RCC->CR & (1<<17) == 0 ){} /* wait for it */
    clksrc   = 1;
    freq_sys = HSECLOCK;

#endif

    /* flash wait states */
    if( SYSCLOCK > FLASHMAX ){
        int fws = (SYSCLOCK + FLASHMAX - 1) / FLASHMAX - 1;

        FLASH->ACR &= 7;
        FLASH->ACR |= fws;
    }

#if HSECLOCK == SYSCLOCK
    set_clocksrc(clksrc);
    return;
#endif

    /* config PLL */

#if SYSCLOCK != SRCCLOCK
    clksrc = 2;
#  ifdef HSECLOCK
#    define PLLSRC	2
#  else
#    define PLLSRC 	1
#  endif

    RCC->CFGR2 = 1;	// div by 2

#  define PLLM ((SYSCLOCK + SRCCLOCK/2 - 1) / (SRCCLOCK / 2))

    RCC->CFGR |= ((PLLM - 2) << 18) | (PLLSRC<<15);

    RCC->CR |= (1<<24);               /* enable pll */
    while( RCC->CR & (1<<25) == 0 ){} /* wait for it */


    freq_sys = SYSCLOCK;
#endif

    set_clocksrc(clksrc);

}

/****************************************************************/
void
init_ints(void){
}

void
init_hw(void){
    clock_init();
    tick_init( freq_sys / 8, 1 );
    stm32_init();

#ifdef KSTACK_SIZE
    extern void _switch_kstack(char*);
    char *nsp = alloc(KSTACK_SIZE);
    _switch_kstack(nsp + KSTACK_SIZE);
#endif
}

/****************************************************************/


extern char _sdata, _estack;
void
init_hw2(void){
    int i;

    int ram = (&_estack - &_sdata)/1024;
    int id  = DBGMCU->IDCODE & 0xFFF;

    bootmsg("bootflags = 0x%x, cpuid %x/%x, %dk flash, %dk RAM\n", bootflags, SCB->CPUID, id, *R_FLASHKB, ram);
    bootmsg("clocks: sys %dMHz\n", freq_sys/1000000);
    bootmsg("uid %x-%x-%x\n", R_UNIQUE[0], R_UNIQUE[1], R_UNIQUE[2]);

}


void __sync_synchronize(){}

int
__sync_lock_test_and_set_4(int *l, int v){
    int plx = splhigh();
    int c   = *l;
    *l = v;
    splx(plx);
    return c;
}
