/*
  Copyright (c) 2013
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2013-Mar-11 00:46 (EDT)
  Function: stm32f1 hardware init

  $Id$

*/

#include <conf.h>
#include <stm32f4xx.h>
#include <proc.h>
#include <alloc.h>
#include <clock.h>


#define R_FLASHKB	((unsigned short *)(0x1FFF7A22))
#define R_UNIQUE	((unsigned long*)(0x1FFF7A10))
#define R_DBGID		((unsigned long*)(0xE0042000))

#ifdef HSECLOCK
#  define SRCCLOCK	HSECLOCK
#else
#  define SRCCLOCK	HSICLOCK
#endif


unsigned long bootflags = 0;
uint16_t stm32f4_cpuid;
uint32_t *r_unique = R_UNIQUE;
uint16_t *r_flashkb = R_FLASHKB;


void stm32_putchar(int);

int freq_sys=HSICLOCK, freq_apb1=HSICLOCK, freq_apb2=HSICLOCK, freq_usb=HSICLOCK;
int freq_pll=0;

int sys_clock_freq(void){  return freq_sys;  }
int apb1_clock_freq(void){ return freq_apb1; }
int apb2_clock_freq(void){ return freq_apb2; }


// fvco = hse * plln / pllm
// fsys = fvco / pllp
// fusb = fvco / pllq = 48MHz

// hse / pllm must be 1-2MHz, 2=recommended
// fvco must be 192-432 MHz
// m - 6bits, n - 9 bits, q - 4 bits, p - 2 bits (2,4,6,8)

static void
clock_init(void){
    int clksrc = 0;

#if !defined(HSECLOCK) && (SYSCLOCK == HSICLOCK)
    // run on hsi, asis
    return;
#endif

#ifdef HSECLOCK
#  if (HSECLOCK < 4000000) || (HSECLOCK > 26000000)
#    error "not a valid HSE frequency. must be: 4MHz - 26MHz"
#  endif

    /* enable HSE */
    RCC->CR |= (1<<16);
    while( RCC->CR & (1<<17) == 0 ){} /* wait for it */
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

    clksrc = 2;
#  ifdef HSECLOCK
#    define PLLSRC	1
#  else
#    define PLLSRC 	0
#endif

#  define PLLM ((SRCCLOCK + PLLVCOTARGET - 1) / PLLVCOTARGET)
#  if (PLLM < 2) || (PLLM > 63)
#    error "cannot configure pll. hseclock should be 4MHz - 26MHz"
#  endif

#  define PLLFVIN	(SRCCLOCK / PLLM)

#  if   (PLLVCOMIN <= SYSCLOCK * 2) && (PLLVCOMAX >= SYSCLOCK * 2)
#    define PLLP	2
#    define PLLPB	0
#  elif (PLLVCOMIN <= SYSCLOCK * 4) && (PLLVCOMAX >= SYSCLOCK * 4)
#    define PLLP	4
#    define PLLPB	1
#  elif (PLLVCOMIN <= SYSCLOCK * 6) && (PLLVCOMAX >= SYSCLOCK * 6)
#    define PLLP	6
#    define PLLPB	2
#  elif (PLLVCOMIN <= SYSCLOCK * 8) && (PLLVCOMAX >= SYSCLOCK * 8)
#    define PLLP	8
#    define PLLPB	3
#  else
#    error "cannot configure requested sysclock. should be 24MHz - 216MHz"
#  endif

#  define PLLN		((SYSCLOCK * PLLP + PLLFVIN/2) / PLLFVIN)
#  define PLLFVCO 	(PLLFVIN * PLLN)
#  define PLLQ		((PLLFVCO + USBFREQ/2) / USBFREQ)

        freq_pll = PLLFVIN;
        freq_sys = PLLFVCO / PLLP;
        freq_usb = PLLFVCO / PLLQ;

        //bootmsg("pll: m %d, n %d, p %d, q %d; vco %d, sys: %d, usb %d\n", PLLM, PLLN, PLLP, PLLQ,
        //        PLLFVCO, freq_sys, freq_usb);

        RCC->PLLCFGR = (PLLSRC << 22)  // src
            | PLLM
            | (PLLN  << 6)
            | (PLLPB << 16)
            | (PLLQ  << 24)
            ;

    RCC->CR |= (1<<24);               /* enable pll */
    while( RCC->CR & (1<<25) == 0 ){} /* wait for it */
#endif

    /****************************************************************/

    /* config bus clocks */

    int cfgr =
#  if (SYSCLOCK <= APB1MAX)
        (0);			// all clocks not divided
    	freq_apb1 = freq_apb2 = freq_sys;
#  elif (SYSCLOCK <= APB2MAX)
        (0<<4)              	// ahb  = no divide
        | (0<<13)      		// apb2 = no divide
        | (4<<10);              // apb1 = divide by 2
        freq_apb2 = freq_sys;
        freq_apb1 = freq_sys / 2;
#  elif (SYSCLOCK <= AHBMAX)
        (0<<4)              	// ahb  = no divide
        | (4<<13)      		// apb2 = divide by 2
        | (5<<10);              // apb1 = divide by 4
        freq_apb2 = freq_sys / 2;
        freq_apb1 = freq_sys / 4;
#  else
        // unsupported - overclocking
        (8<<4)              	// ahb  = divide by 2
        | (5<<13)      		// apb2 = divide by 4
        | (6<<10);              // apb1 = divide by 8
        freq_apb2 = freq_sys / 4;
        freq_apb1 = freq_sys / 8;
#  endif


#  ifdef HSECLOCK
        cfgr  |= ((HSECLOCK / 1000000) << 16);	// rtc = hse / N
#  endif

    RCC->CFGR = cfgr;

    /****************************************************************/

    /* set sysclock */
    if( clksrc ){
        RCC->CFGR |= clksrc;
        while( RCC->CFGR & 0xC == 0 ){} /* wait for it */
    }

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

    stm32f4_cpuid = *R_DBGID & 0xFFF;

    int ram = (&_estack - &_sdata)/1024;
    bootmsg("bootflags = 0x%x, cpuid %x (%x), %dk flash, %dk RAM\n", bootflags, SCB->CPUID, *R_DBGID, *R_FLASHKB, ram);
    bootmsg("clocks: sys %dMHz, apb1 %dMHz, apb2 %dMHz, usb %dMHz\n",
            freq_sys/1000000, freq_apb1/1000000, freq_apb2/1000000, freq_usb/1000000);
    bootmsg("uid %x-%x-%x\n", R_UNIQUE[0], R_UNIQUE[1], R_UNIQUE[2]);
}

/* enter low power standby mode */
int
power_down(void){

    RCC->APB1ENR |= (1<<28);		// enable PWR system

    //– Set SLEEPDEEP in CortexTM-M4F System Control register
    //– Set PDDS bit in Power Control register (PWR_CR)
    //– Clear WUF bit in Power Control/Status register (PWR_CSR)

    SCB->SCR |= 4;	// sleepdeep
    PWR->CR  |= 2;	// PDDS
    PWR->CR  |= 4;	// clear WUF

    __asm__("wfi");
}


void
dcache_flush(void *buf, int len){
}

void
dcache_invalidate(void *buf, int len){
}
