/*
  Copyright (c) 2013
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2013-Mar-11 00:46 (EDT)
  Function: stm32f1 hardware init

  $Id$

*/

#include <conf.h>
#include <stm32f10x.h>
#include <proc.h>
#include <alloc.h>
#include <clock.h>

#define R_FLASHKB	((unsigned short *)(0x1FFFF7E0))
#define R_UNIQUE	((unsigned long*)(0x1FFFF7E8))

#ifdef HSECLOCK
#  define SRCCLOCK	HSECLOCK
#else
#  define SRCCLOCK	HSICLOCK
#endif


int freq_sys=HSICLOCK, freq_apb1=HSICLOCK, freq_apb2=HSICLOCK;


unsigned long bootflags = 0;
void stm32_putchar(int);

int sys_clock_freq(void){  return freq_sys;  }
int apb1_clock_freq(void){ return freq_apb1; }
int apb2_clock_freq(void){ return freq_apb2; }


static void
clock_init(void){
    int clksrc = 0;
    int cfgr   = 0;

#if !defined(HSECLOCK) && (SYSCLOCK == HSICLOCK)
    // run on hsi, asis
    return;
#endif

#ifdef HSECLOCK
#  if (HSECLOCK < 4000000) || (HSECLOCK > 25000000)
#    error "not a valid HSE frequency. must be: 4MHz - 25MHz"
#  endif

    /* enable HSE */
    RCC->CR |= 0x00010001;
    while( RCC->CR & 0x00020000 == 0 ){} /* wait for it */

    clksrc   = 1;
    freq_sys = HSECLOCK;
#endif

    /****************************************************************/
    /* flash wait states */
    if( SYSCLOCK > FLASHMAX ){
        int fws = (SYSCLOCK + FLASHMAX - 1) / FLASHMAX - 1;

        FLASH->ACR &= 7;
        FLASH->ACR |= fws;
    }


    /****************************************************************/
    /* config PLL */

#if SYSCLOCK != SRCCLOCK
    clksrc   = 2;

#  ifdef HSECLOCK
#    define PLLSRC	1
#    if ((SYSCLOCK * 2 / HSECLOCK) & 1) && (SYSCLOCK <= 8 * HSECLOCK)
#      define _SRCCLOCK	(HSECLOCK / 2)
       cfgr |= 3<<16; /* pllsrc = hse/2 */
#    else
#      define _SRCCLOCK	HSECLOCK
       cfgr |= 1<<16; /* pllsrc = hse */
#    endif
#  else
#    define PLLSRC 	0
#    define _SRCCLOCK	(HSICLOCK / 2)
#  endif

#  define PMUL ((SYSCLOCK + _SRCCLOCK - 1) / _SRCCLOCK - 2)

#  if (PMUL < 0) || (PMUL > 14)
#    error "cannot configure pll."
#  endif

       freq_sys = (PMUL+2) * _SRCCLOCK;
       cfgr |= PMUL << 18;

#endif

    /****************************************************************/

    /* config bus clocks */

    cfgr |=
#  if (SYSCLOCK <= APB1MAX)
        (0);			// all clocks not divided
    	freq_apb1 = freq_apb2 = freq_sys;
#  elif (SYSCLOCK <= APB2MAX)
        (0<<4)              	// apb  = no divide
        | (0<<11)      		// apb2 = no divide
        | (4<<8);               // apb1 = divide by 2
        freq_apb2 = freq_sys;
        freq_apb1 = freq_sys / 2;
#  else
        // unsupported - overclocking
        (8<<4)              	// apb  = divide by 2
        | (4<<11)      		// apb2 = divide by 2
        | (5<<8);               // apb1 = divide by 4
        freq_apb2 = freq_sys / 2;
        freq_apb1 = freq_sys / 4;
#  endif

    if( freq_apb2 > 6*ADCBMAX ){
        cfgr |= 3<<14;	// div by 8
    }else if( freq_apb2 > 4*ADCBMAX ){
        cfgr |= 2<<14;	// div by 6
    }else if( freq_apb2 > 2*ADCBMAX ){
        cfgr |= 1<<14;	// div by 4;
    }else{
        // div by 2
    }

    // QQQ - usb pre
#if SYSCLOCK > USBFREQ
    cfgr |= 1<<22;
#endif

    /****************************************************************/

    RCC->CFGR = cfgr;

    if( clksrc == 2 ){
        RCC->CR   |= 0x01000000;	 	 /* enable pll */
        while( RCC->CR & 0x02000000 == 0 ){} /* wait for it */
    }

    if( clksrc ){
        RCC->CFGR |= clksrc;
        while( RCC->CFGR & 0x0000000C == 0 ){} /* wait for it */
    }
}

/****************************************************************/
void
init_ints(void){

    SCB->SHPR[1]  = (IPL_PROC  << 24); /* SVC */
}

void
init_hw(void){
    clock_init();
    tick_init();

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
    bootmsg("bootflags = 0x%x, cpuid %x, %dk flash, %dk RAM\n", bootflags, SCB->CPUID, *R_FLASHKB, ram);
    bootmsg("clocks: sys %dMHz, apb1 %dMHz, apb2 %dMHz\n", freq_sys/1000000, freq_apb1/1000000, freq_apb2/1000000);
    bootmsg("uid %x-%x-%x\n", R_UNIQUE[0], R_UNIQUE[1], R_UNIQUE[2]);

    // RSN - uid, devid, mem, ...

}

