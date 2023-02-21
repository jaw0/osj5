/*
  Copyright (c) 2013
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2013-Mar-11 00:46 (EDT)
  Function: stm32L4 hardware init
*/

#include <conf.h>
#include <stm32l4xx.h>
#include <proc.h>
#include <alloc.h>
#include <clock.h>


#define R_FLASHKB	((unsigned short *)(0x1FFF75E0))
#define R_UNIQUE	((unsigned long*)(0x1FFF7590))


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
  100k, 200k, 400k, 800k, 1M, 2M, 4M, 8M, 16M, 24M, 32M, 48M

  USB = PLLVCO / 2 => 48MHz
  ADC = HSI .
  
*/

unsigned long bootflags = 0;
uint32_t *r_unique = R_UNIQUE;
uint16_t *r_flashkb = R_FLASHKB;

void stm32_putchar(int);

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
also_adc_clk(void){
    // enable sysclock for ADC clock
#ifdef USE_ADC
    RCC->CCIPR |= 3 << 28; // adc clock is sysclock (else: none, pll)
#endif
}

static inline void
also_hsi48(void){
    // needed for usb, rng, sdio
#if defined(USE_USBD) || defined(USE_RNG) || defined(USE_SDIO)
    RCC->CRRCR |= 1;	// HSI48_ON
    while( RCC->CRRCR & (1<<1) == 0 ) {}	// wait until ready
#endif
}


static void inline
set_clocksrc(int src){
    RCC->CFGR |= src;
    while( RCC->CFGR & 0xC == 0 ){} /* wait for it */
}

static const int  msifreq[] = { 100000, 200000, 400000, 800000, 1600000, 2000000, 4000000, 8000000, 16000000, 24000000, 32000000, 48000000 };

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
    also_adc_clk();
    also_hsi48();
    freq_sys = msifreq[m];
    return;
#endif


#if !defined(HSECLOCK)
    RCC->CR	|= 1<<8;	// HSI_ON
    while( RCC->CR & (1<<10) == 0 ) {}	// wait until ready
    freq_sys = HSICLOCK;
# if (SYSCLOCK == HSICLOCK)
    set_clocksrc(1);
    also_adc_clk();
    also_hsi48();
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
        RCC->APB1ENR1 |= 1<<28;	// pwr enable
        PWR->CR1 = 1<<9;	// "range 1" (1V8)

        int fws = (SYSCLOCK + FLASHMAX - 1) / FLASHMAX - 1;
        FLASH->ACR &= 7;
        FLASH->ACR |= fws;

        FLASH->ACR |= 3<<9;	// cache enable
        FLASH->ACR |= 1<<8;	// prefetch

        while( PWR->SR2 & (1<<10) ){}	// wait for voltage (VOSF)
    }


    /****************************************************************/
    /* config PLL */


#if SYSCLOCK != SRCCLOCK

    clksrc = 3;
#  ifdef HSECLOCK
#    define PLLSRC	3
#  else
#    define PLLSRC 	2
    // 1 => msi
#endif

#  define PLLM ((SRCCLOCK + PLLVCOTARGET - 1) / PLLVCOTARGET)
#  if (PLLM < 1) || (PLLM > 8)
#    error "cannot configure pll. hseclock should be 1MHz - 24MHz"
#  endif

#  define PLLFVIN	(SRCCLOCK / PLLM)
#  define PLLR		2

#  define PLLN		((SYSCLOCK * PLLR + PLLFVIN/2) / PLLFVIN)
#  define PLLFVCO 	(PLLFVIN * PLLN)
#  define PLLFOUT	(PLLFVCO / PLLR)

// RSN - check min/max, ...


    freq_sys = PLLFOUT;
    RCC->PLLCFGR =
        PLLSRC
        | ( (PLLM-1) << 4) 	// PLLM
        | (PLLN <<8) 		// PLLN
        | (0 << 25) 		// R=2
        | (1 << 24) 		// enable R
        ;

    RCC->CR |= (1<<24);               /* enable pll */
    while( RCC->CR & (1<<25) == 0 ){} /* wait for it */


#endif /* PLL */

    /****************************************************************/

    /* set sysclock */
    set_clocksrc( clksrc );
    also_adc_clk();
    also_hsi48();
    // RSN - if using HSE+PLL use PLL for 48

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

/* enter low power shutdown mode
   nb. chip supports several other low power modes

   standby: LSI, LSE, RTC, BOR, IWDG
     0.03uA; 0.29uA w/RTC

   shutdown: LSE, RTC
     0.01uA; 0.20uA w/RTC

*/

int
power_down(void){

#ifdef USE_ADC
    // put adc into deep sleep mode
    ADC1->CR |= 1<<29;
    ADC2->CR |= 1<<29;
    ADC3->CR |= 1<<29;
#endif

    RCC->APB1ENR1 |= 1<<28;	// pwr enable

#if defined(USE_RTC) && !defined(LSECLOCK)
    PWR->CR1 |= 3;	// LPMS = standby mode
#else
    PWR->CR1 |= 4;	// LPMS = shutdown mode
#endif

    PWR->SCR = 0x1F;	// clear WUFx
    SCB->SCR |= 4;      // sleepdeep

    __asm__("wfi");
}
