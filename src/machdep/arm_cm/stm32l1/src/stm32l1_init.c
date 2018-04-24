/*
  Copyright (c) 2013
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2013-Mar-11 00:46 (EDT)
  Function: stm32L1 hardware init
*/

#include <conf.h>
#include <stm32l1xx.h>
#include <proc.h>
#include <alloc.h>
#include <clock.h>


#define R_FLASHKB_C1	((unsigned short *)(0x1FF8004C))
#define R_FLASHKB_CX	((unsigned short *)(0x1FF800CC))

#define R_UNIQUE_C1	((unsigned long*)(0x1FF80050))
#define R_UNIQUE_CX	((unsigned long*)(0x1FF800D0))

#ifdef HSECLOCK
#  define SRCCLOCK	HSECLOCK
#else
#  ifdef MSICLOCK
#    define SRCCLOCK	MISCLOCK
#  else
#    define SRCCLOCK	HSICLOCK
#  endif
#endif


/*
  MSI:
  65.536 kHz, 131.072 kHz, 262.144 kHz, 524.288 kHz, 1.048 MHz, 2.097 MHz (default value) and 4.194 MHz.

  USB = PLLVCO / 2 => 48MHz
  ADC = HSI .
  
*/

unsigned long bootflags = 0;
void stm32_putchar(int);
uint32_t *r_unique;

int freq_sys=MSIDEFAULT;

int sys_clock_freq(void){  return freq_sys;  }
int ahb_clock_freq(void){  return freq_sys;  }
int apb1_clock_freq(void){ return freq_sys; }
int apb2_clock_freq(void){ return freq_sys; }


// fvco = hse * plln / pllm
// fsys = fvco / pllp
// fusb = fvco / pllq = 48MHz

// hse / pllm must be 1-2MHz, 2=recommended
// fvco must be 192-432 MHz
// m - 6bits, n - 9 bits, q - 4 bits, p - 2 bits (2,4,6,8)

static inline void
also_adc_hsi(void){
    // hsi is needed for ADC clock
#ifdef USE_ADC
    RCC->CR	|= 1;	// HSI_ON
    while( RCC->CR & (1<<1) == 0 ) {}	// wait until ready
#endif
}

static void inline
set_clocksrc(int src){
    RCC->CFGR |= src;
    while( RCC->CFGR & 0xC == 0 ){} /* wait for it */
}

static const int  msifreq[] = { 65536, 131072, 262144, 524288, 1048000, 2097000, 4194000 };
static const char pllm[] = { 3, 4, 6, 8, 12, 16, 24, 32, 48 };

static void
clock_init(void){
    int clksrc = 0;
    int m;

#ifdef MSICLOCK
#  if MISCLOCK != MSIDEFAULT
    for(m=0; m<6; m++)
        if( msifreq[m] >= MISCLOCK ) break;
    RCC->ICSCR |= m << 13;
#  endif
    also_adc_hsi();
    freq_sys = msifreq[m];
    return;
#endif

#if !defined(HSECLOCK)
    RCC->CR	|= 1;	// HSI_ON
    while( RCC->CR & (1<<1) == 0 ) {}	// wait until ready
# if (SYSCLOCK == HSICLOCK)
    set_clocksrc(1);
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
    clksrc   = 2;
    freq_sys = HSECLOCK;
#endif

    /****************************************************************/

    /* flash wait states */
    if( SYSCLOCK > FLASHMAX ){
        RCC->APB1ENR |= 1<<28;	// pwr enable
        PWR->CR = 1<<11;	// "range 1" (1V8)
        FLASH->ACR |= 4;	// 64bit
        FLASH->ACR |= 1;	// wait-state
        FLASH->ACR |= 2;	// prefetch

        while( PWR->CSR & (1<<4) ){}	// wait for voltage
    }

    /****************************************************************/
    /* config PLL */

#if SYSCLOCK != SRCCLOCK

    clksrc = 3;
#  ifdef HSECLOCK
#    define PLLSRC	1
#  else
#    define PLLSRC 	0
#endif

#  define PLLM ((PLLVCOTARGET + SRCCLOCK - 1) / SRCCLOCK)
#  if (PLLM < 3) || (PLLM > 48)
#    error "cannot configure pll. hseclock should be 1MHz - 24MHz"
#  endif

#  define PLLFVIN	(SRCCLOCK * PLLM)
#  define PLLDIV	((PLLFVIN + SYSCLOCK - 1) / SYSCLOCK)
#  define PLLFOUT	(PLLFVIN / PLLDIV)

// RSN - check min/max, ...


    freq_sys = PLLFOUT;

    for(m=0; m<8; m++)
        if( pllm[m] >= PLLM ) break;

    RCC->CFGR |= ((PLLDIV - 1) << 22)
        | (m << 18)
        | (PLLSRC << 16);

    RCC->CR |= (1<<24);               /* enable pll */
    while( RCC->CR & (1<<25) == 0 ){} /* wait for it */


#endif /* PLL */

    /****************************************************************/

    /* set sysclock */
    set_clocksrc( clksrc );
    also_adc_hsi();
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
    unsigned short *fl=0;

    switch( id ){
    case 0x416:	// cat.1
    case 0x429: // cat.2
        fl  = R_FLASHKB_C1;
        r_unique = R_UNIQUE_C1;
        break;
    default:	// cat.3,4,5,6
        fl  = R_FLASHKB_CX;
        r_unique = R_UNIQUE_CX;
        break;
    }

    bootmsg("bootflags = 0x%x, cpuid %x/%x, %dk flash, %dk RAM\n", bootflags, SCB->CPUID, id, *fl, ram);
    bootmsg("clocks: sys %dMHz\n", freq_sys/1000000);
    bootmsg("uid %x-%x-%x\n", r_unique[0], r_unique[1], r_unique[2]);

}

void
power_down(void){

    RCC->APB1ENR |= 1<<28;	// pwr enable

    PWR->CR  |= 1<<2;	// clear WUF
    PWR->CR  |= 2;	// PDDS
    SCB->SCR |= 4;      // sleepdeep

    __asm__("wfi");
}

