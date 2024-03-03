/*
  Copyright (c) 2013
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2013-Mar-11 00:46 (EDT)
  Function: stm32L4 hardware init
*/

#include <conf.h>
#include <stm32u5xx.h>
#include <proc.h>
#include <alloc.h>
#include <clock.h>
#include <gpio.h>

// XXX testing
#define USE_ADC
#define USE_SDIO
#define STM32_MCO_ENABLE
#define USE_USBD
//#define SYSCLOCK 12000000


#define R_FLASHKB	((unsigned short *)(0x0BFA07A0))
#define R_UNIQUE	((unsigned long*)(0x0BFA0700))

#define MHZ 1000000
#define KHZ 1000


#ifdef HSECLOCK
#  define SRCCLOCK	HSECLOCK
#else
#  ifdef MSICLOCK
#    define SRCCLOCK	MSICLOCK
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
static const char *freq_src = "default";

int sys_clock_freq(void){  return freq_sys; }
int ahb_clock_freq(void){  return freq_sys; }
int apb1_clock_freq(void){ return freq_sys; }
int apb2_clock_freq(void){ return freq_sys; }


static inline void
busy_wait(int n){
    while( n-- > 0 ){ __asm("nop"); }
}

static void inline
pwr_enable(){
    RCC->AHB3ENR |= 1<<2;		// pwr enable
}

static inline void
also_adc_clk(void){
    // enable sysclock for ADC clock
#ifdef USE_ADC
    // RCC->CCIPR3 |= 1 << 12; // adc clock is sysclock (else: 0=hclk, ...)
#endif
}

static inline void
also_hsi48(void){
    // needed for usb, rng, sdio
#if defined(USE_USBD) || defined(USE_RNG) || defined(USE_SDIO)
    RCC->CR |= 1<<12;	// HSI48_ON
    while( RCC->CR & (1<<13) == 0 ) {}	// wait until ready
#endif
}

static inline void
also_hs60p(){
#if defined(USE_USBD)

    RCC->APB3ENR |= 1<<1;	// syscfg
    RCC->CCIPR2  |= 1<<30;	// HS_PHY clock = PLL1p

    switch( HSPLLTARGET ){
        // I know, weird, right?
    case 16000000:
        SYSCFG->OTGHSPHYCR = 3 << 2;
        break;
    case 19200000:
        SYSCFG->OTGHSPHYCR = 8 << 2;
        break;
    case 20000000:
        SYSCFG->OTGHSPHYCR = 9 << 2;
        break;
    case 24000000:
        SYSCFG->OTGHSPHYCR = 10 << 2;
        break;
    case 26000000:
        SYSCFG->OTGHSPHYCR = 14 << 2;
        break;
    case 32000000:
        SYSCFG->OTGHSPHYCR = 11 << 2;
        break;
    }
#endif
}

static void inline
set_clocksrc(int src){
    uint32_t r = RCC->CFGR1;
    RCC->CFGR1 = (r & ~3) | src;
    while( RCC->CFGR1 & 0xC == 0 ){} /* wait for it */
}

static void
flash_latency(){

    /* flash wait states */
    if( SYSCLOCK > FLASHMAX ){

        PWR->VOSR |= 3<<16;		// "range 1" (1V8)
        while( PWR->VOSR & (1<<15) ){}	// wait for vos ready

        PWR->VOSR |= 1<<18;		// epod boost enable
        while( PWR->VOSR & (1<<14) ){}	// wait for boost ready

        int fws = (SYSCLOCK + FLASHMAX - 1) / FLASHMAX - 1;
        FLASH->ACR &= ~0xF;
        FLASH->ACR |= fws;
        FLASH->ACR |= 1<<8;	// prefetch

        while ((FLASH->ACR & 0xF) == 0){}

        // bootmsg("flash clk %d, fws %d\n", SYSCLOCK, fws);
    }
}

static void
mco_enable(){
#ifdef STM32_MCO_ENABLE
    // RSN - choice of clock
    gpio_init( GPIO_A8, GPIO_AF(0) | GPIO_SPEED_2MHZ | GPIO_PUSH_PULL );
    RCC->CFGR1 &= ~(0xFF << 24);
    //RCC->CFGR1 |= (4 << 28) | (5 << 24);	    // PLL / 16
    RCC->CFGR1 |= (4 << 28) | (6 << 24);	    // LSI / 16
    //RCC->CFGR1 |= (4 << 28) | (7 << 24);	    // LSE / 16

#endif
}

static const int  msifreq[] = {
    48*MHZ, 24*MHZ, 16*MHZ, 12*MHZ, 4*MHZ, 2*MHZ, 1330*KHZ, 1*MHZ,
    3072*KHZ, 1536*KHZ, 1024*KHZ, 768*KHZ, 400*KHZ, 200*KHZ, 133*KHZ, 100*KHZ
};

static void
clock_init(void){
    int clksrc = 0;
    int m;

#ifdef MSICLOCK
# define PLLSRC 	0
#  if MSICLOCK != MSIDEFAULT
    for(m=0; m<16; m++)
        if( msifreq[m] == MSICLOCK ) break;
    if( m >= 16 ){
        bootmsg("invalid MSI clock %d\n", MSICLOCK);
        return;
    }

    // QQQ - is this safe?
    uint32_t r = RCC->ICSCR1;
    RCC->ICSCR1 = (r & ~(0xF<<24)) | (m << 24);
    RCC->ICSCR1 |= 1<<23; // use range here, not CR
    freq_sys = msifreq[m];
    freq_src = "MSI";
#  endif
# if (SYSCLOCK == MSICLOCK)
    also_adc_clk();
    also_hsi48();
    return;
# endif
#endif


#if !defined(HSECLOCK)
    RCC->CR	|= 1<<8;	// HSI_ON
    while( RCC->CR & (1<<10) == 0 ) {}	// wait until ready
    freq_sys = HSICLOCK;
    freq_src = "HSI";
# if (SYSCLOCK == HSICLOCK)
    set_clocksrc(1);
    also_adc_clk();
    also_hsi48();
    return;
# endif
# define PLLSRC 	2
#endif


#ifdef HSECLOCK
#  if (HSECLOCK < 4000000) || (HSECLOCK > 50000000)
#    error "not a valid HSE frequency. must be: 4MHz - 50MHz"
#  endif
#  define PLLSRC	3

    /* enable HSE */
    RCC->CR |= (1<<16);
    while( RCC->CR & (1<<17) == 0 ){} /* wait for it */
    freq_sys = HSECLOCK;
    freq_src = "HSE";
# if (SYSCLOCK == HSECLOCK)
    set_clocksrc(2);
    also_adc_clk();
    also_hsi48();
    return;
# endif
#endif

    /****************************************************************/

#if SYSCLOCK != SRCCLOCK
#  define BOOST (SRCCLOCK / (2 * EPODTARGET))

    RCC->PLL1CFGR &= ~(0xF << 12);
    RCC->PLL1CFGR |= (BOOST << 12) | PLLSRC;

#endif


    /****************************************************************/
    /* config PLL */

    // fvco = hse * plln / pllm
    // fsys = fvco / pllr

    // hse / pllm must be 4-16MHz
    // fvco must be 128-544 MHz
    // m - 4bits, n - 9 bits, q/p/r - 7 bits

#if SYSCLOCK != SRCCLOCK

#  define PLLM ((SRCCLOCK + PLLVCOTARGET - 1) / PLLVCOTARGET)
#  if (PLLM < 1) || (PLLM > 16)
#    error "cannot configure pll. hseclock should be 1MHz - 24MHz"
#  endif

#  define PLLFVIN	(SRCCLOCK / PLLM)
#  define PLLR		2

#  define PLLN		((SYSCLOCK * PLLR + PLLFVIN/2) / PLLFVIN)
#  define PLLFVCO 	(PLLFVIN * PLLN)
#  define PLLFOUT	(PLLFVCO / PLLR)
#  define PLLRGE	((PLLFVIN >= 8000000) ? 3 : 0)
#  define PLLP		(PLLFVCO / HSPLLTARGET)

#if 0 // XXX
    bootmsg("pll cf M %d, N %d, P %d, fvin %d, vco %d, fo %d\n", PLLM, PLLN, PLLP, PLLFVIN, PLLFVCO, PLLFOUT);
    bootmsg("pll src %d\n", PLLSRC);
    set_clocksrc(2);
    //return;
#endif

    RCC->PLL1DIVR = (PLLN - 1) | ((PLLR - 1) << 24)
#  ifdef USE_USBD
        | ((PLLP - 1) << 9)
#  endif
        ;

    RCC->PLL1CFGR =
        PLLSRC
        | ((PLLM - 1) << 8)
        | (PLLRGE << 2)
        | (BOOST << 12)
        | (1 << 18)	// enable R
#  ifdef USE_USBD
        | (1 << 16)	// enable P
#  endif
        ;

    RCC->CR |= (1<<24);               /* enable pll */
    while( RCC->CR & (1<<25) == 0 ){} /* wait for it */

    flash_latency();
    clksrc = 3;
    freq_sys = PLLFOUT;
    freq_src = "PLL";

#endif /* PLL */

    /****************************************************************/

    /* set sysclock */
    set_clocksrc( clksrc );

    also_adc_clk();
    also_hsi48();
    also_hs60p();

}

/****************************************************************/
void
init_ints(void){
}

void
init_hw(void){

    pwr_enable();
    mco_enable();
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
    bootmsg("clocks: src %s, sys %dMHz\n", freq_src, freq_sys/1000000);
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
#endif

    RCC->APB1ENR1 |= 1<<28;	// pwr enable

#if defined(USE_RTC) && !defined(LSECLOCK)
    PWR->CR1 |= 3;	// LPMS = standby mode
#else
    PWR->CR1 |= 4;	// LPMS = shutdown mode
#endif

    PWR->WUSCR = 0xFF;	// clear WUFx
    SCB->SCR |= 4;      // sleepdeep

    __asm__("wfi");
}
