/*
  Copyright (c) 2013
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2013-Mar-11 00:46 (EDT)
  Function: stm32f1 hardware init

  $Id$

*/

#include <conf.h>
#include <atsam.h>
#include <proc.h>
#include <alloc.h>

#define LSECLOCK

#ifdef HSECLOCK
#  define SRCCLOCK	HSECLOCK
#else
#  define SRCCLOCK	HSICLOCK
#endif

#ifdef LSECLOCK
#  define SLOWCLOCK	32768
#else
#  define SLOWCLOCK	32000
#endif



unsigned long bootflags = 0;

int freq_hclk=12000000, freq_mck=12000000, freq_usb=0;

// MAINCLOCK = xtal or RC osc
// MAINCLOCK -> PLL, DIV => FCLK = HCLK
// FCLK -> DIV => Master Clock (MCK) = periph clock

int sys_clock_freq(void){ return freq_hclk; }		// HCLK = FCLK = processor clock = 8*systick
int mck_clock_freq(void){ return freq_mck;  }		// MCK = peripheral clock = HCLK/n
int periph_clock_freq(void){ return freq_mck;  }



static inline void
enable_external_slow(void){
    // enable external 32k768 xtal
    // internal 32k RC is automatically disabled
    SUPC->SUPC_CR = (0xA5 << 24) | (1 << 3);
}


static void
init_clock_internal(int sp){

    PMC->CKGR_MOR |= (CKGR_MOR_KEY_PASSWD | CKGR_MOR_MOSCRCEN);

    /* Wait the Fast RC to stabilize */
    while (!(PMC->PMC_SR & PMC_SR_MOSCRCS)){}

    /* Change Fast RC oscillator frequency */
    PMC->CKGR_MOR = (PMC->CKGR_MOR & ~CKGR_MOR_MOSCRCF_Msk) | CKGR_MOR_KEY_PASSWD | (sp << 4);

    /* Wait the Fast RC to stabilize */
    while (!(PMC->PMC_SR & PMC_SR_MOSCRCS));

    /* Switch to Fast RC */
    PMC->CKGR_MOR = (PMC->CKGR_MOR & ~CKGR_MOR_MOSCSEL) |  CKGR_MOR_KEY_PASSWD;

    /* wait MAIN clock status change for Fast RC oscillator */
    while (!(PMC->PMC_SR & PMC_SR_MOSCSELS));

    /* in case where MCK is running on MAIN CLK */
    while (!(PMC->PMC_SR & PMC_SR_MCKRDY));
}

static int
measure_internal_clock(void){

    PMC->CKGR_MCFR = 1<<20;			// start measurement
    while( (PMC->CKGR_MCFR & (1<<16)) == 0 ){}	// wait until ready
    int mf = PMC->CKGR_MCFR;

    mf &= 0xFFFF;
    return mf * SLOWCLOCK / 16;
}

static int
measure_external_clock(void){

    PMC->CKGR_MCFR = (1<<20) | (1<<24);		// start measurement
    while( PMC->CKGR_MCFR & (1<<16) == 0 ){}	// wait until ready
    int mf = PMC->CKGR_MCFR;

    mf &= 0xFFFF;
    return mf * SLOWCLOCK / 16;
}


static void
clock_init(void){
    // ...

#ifdef LSECLOCK
    enable_external_slow();
#endif

    //init_clock_internal(0);	// 4MHz
    init_clock_internal(2);	// 12MHz

    //PMC->PMC_MCKR = 1;		// master clock = main clock

    measure_internal_clock();		// measure and discard
    freq_mck = measure_internal_clock();

}


/****************************************************************/
void
init_ints(void){
}

void
init_hw(void){
    clock_init();
    tick_init();
    atsam_init();

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

    uint32_t id = CHIPID->CHIPID_CIDR;

    bootmsg("bootflags = 0x%x, cpuid %x", bootflags, id);

    // other values are possible,
    // but these are the ones we support here

    switch( (id>>20) & 0xFF ){
    case 0x10:	bootmsg(", SAM E70"); break;
    case 0x11:	bootmsg(", SAM S70"); break;
    case 0x12:	bootmsg(", SAM V71"); break;
    case 0x13:	bootmsg(", SAM V70"); break;
    default:	bootmsg(", arch %x", (id>>20) & 0xFF);
    }

    switch( (id>>8) & 0xF ){
    case 14:	bootmsg(", 2MB Flash");		break;
    case 12:	bootmsg(", 1MB Flash");		break;
    case 10:	bootmsg(", 512k Flash");	break;
    }

    switch( (id>>16) & 0xF ){
    case 15:	bootmsg(", 512k RAM");	break;
    case  2:	bootmsg(", 384k RAM");	break;
    case 13:	bootmsg(", 256k RAM");	break;
    case 12:	bootmsg(", 128k RAM");	break;
    }

    bootmsg("\n");

    bootmsg("clocks: measured %d\n", measure_internal_clock());

#if 0
    int ram = (&_estack - &_sdata)/1024;
    bootmsg("bootflags = 0x%x, cpuid %x, %dk flash, %dk RAM\n", bootflags, SCB->CPUID, *R_FLASHKB, ram);
    bootmsg("clocks: sys %dMHz, apb1 %dMHz, apb2 %dMHz, usb %dMHz\n",
            freq_sys/1000000, freq_apb1/1000000, freq_apb2/1000000, freq_usb/1000000);
    bootmsg("uid %x-%x-%x\n", R_UNIQUE[0], R_UNIQUE[1], R_UNIQUE[2]);
#endif

}

