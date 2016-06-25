/*
  Copyright (c) 2013
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2013-Mar-11 00:46 (EDT)
  Function: atsam s70 hardware init

*/

#include <conf.h>
#include <atsam.h>
#include <proc.h>
#include <alloc.h>
#include <userint.h>

#define MHZ(x)	(x * 1000000)

#ifdef HSECLOCK
#  undef  HSICLOCK
#  define SRCCLOCK	HSECLOCK
#  ifndef SYSCLOCK
#    define SYSCLOCK HSECLOCK
#  endif
#else
#  ifndef HSICLOCK
#    ifndef SYSCLOCK
#      define SYSCLOCK 12000000
#    endif
#    if SYSCLOCK < 6000000
#      define HSICLOCK 4000000
#    elif SYSCLOCK < 10000000
#      define HSICLOCK 8000000
#    else
#      define HSICLOCK 12000000
#    endif
#  else
#    ifndef SYSCLOCK
#      define SYSCLOCK HSICLOCK
#    endif
#  endif
#  define SRCCLOCK	HSICLOCK
#endif


#ifdef LSECLOCK
#  define SLOWCLOCK	32768
#else
#  define SLOWCLOCK	32000
#endif


#define FLASH_ADDR	0x400000
#define MCK_MAXFREQ	MHZ(150)
#define HCLK_MAXFREQ	MHZ(300)
#define PLLA_MINFREQ	MHZ(160)
#define PLLA_MAXFREQ	MHZ(500)
#define FLASH_MAXFREQ	MHZ(20)

unsigned long bootflags = 0;

static int freq_hclk=MHZ(12), freq_mck=MHZ(12);
static int freq_measured=0;
static uint32_t uniqueid[4];

// MAINCLOCK = xtal or RC osc
// MAINCLOCK -> PLL, DIV => FCLK = HCLK
// FCLK -> DIV => Master Clock (MCK) = periph clock

// PLL : output 160 .. 500 MHz, input 8..32 main clock
//     : (MUL + 1)/DIV [MUL=1..62, DIV=1..255]
// UPLL: output 480 MHz, input is xtal (or main clock ?)
// USB : output 48 Mhz, input is UPLL or PLL


int sys_clock_freq(void){     return freq_hclk; }	// HCLK = FCLK = processor clock = 8*systick
int mck_clock_freq(void){     return freq_mck;  }	// MCK = peripheral clock = HCLK/n
int periph_clock_freq(void){  return freq_mck;  }
#define SYSTICK_FREQ	(freq_hclk / 2)			// docs say /8. wtf?

static inline void
enable_external_slow(void){
    // enable external 32k768 xtal
    // internal 32k RC is automatically disabled
    SUPC->SUPC_CR = SUPC_CR_KEY_PASSWD | SUPC_CR_XTALSEL_CRYSTAL_SEL;
}

static void __attribute__ ((section(".ramfunc")))
set_fmr(uint32_t f){
    EFC->EEFC_FMR = f;
}

static inline void
init_flash(int freq){

    int fws = freq / FLASH_MAXFREQ;
    if( fws > 15 ) fws = 15;

    EFC->EEFC_WPMR = 0x454643;		// disable write protect

    uint32_t f = EFC->EEFC_FMR;
    f &= 0xF00;
    f |= fws << 8;
    set_fmr(f);
}

static void __attribute__ ((section(".ramfunc")))
init_uniqueid(void){
    int i;

    // Execute the ‘Start Read Unique Identifier’ command by writing EEFC_FCR.FCMD with the STUI command
    EFC->EEFC_FCR = EEFC_FCR_FKEY_PASSWD | 0xE;
    // Wait until the bit EEFC_FSR.FRDY falls
    while( (EFC->EEFC_FSR & EEFC_FSR_FRDY) ){}

    for(i=0; i<4; i++)
        uniqueid[i] = ((u_long*)FLASH_ADDR)[i];

    // by writing EEFC_FCR.FCMD with the SPUI command
    EFC->EEFC_FCR = EEFC_FCR_FKEY_PASSWD | 0xF;
    // When the SPUI command has been executed, the bit EEFC_FSR.FRDY rises
    while( (EFC->EEFC_FSR & EEFC_FSR_FRDY) == 0 ){}

}

static int
measure_clock(int extp){
    int val = 1<<20;
    if( extp ) val |= 1<<24;

    PMC->CKGR_MCFR = val;			// start measurement

    // wait until ready
    while( (PMC->CKGR_MCFR & (1<<16)) == 0 ){}
    int mf = PMC->CKGR_MCFR;

    mf &= 0xFFFF;
    return mf * SLOWCLOCK / 16;
}

static void
init_clock_internal(void){

    int sp;
#if HSICLOCK < 6000000
    sp = 0;
#elif HSICLOCK < 10000000
    sp = 1;
#else
    sp = 2;
#endif

    /* enable RC osc */
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

    // the internal RC osc is not very accurate,
    // use the measured freq
    measure_clock(0);
    freq_measured = measure_clock(0);
    freq_hclk = freq_mck = freq_measured;
}

#ifdef HSECLOCK
static void
init_clock_external(void){
/*
2. Enable the 3 to 20 MHz crystal oscillator by setting
CKGR_MOR.MOSCXTEN. The user can define a start- up time. This can be
achieved by writing a value in the CKGR_MOR.MOSCXTST. */


    PMC->CKGR_MOR |=
        CKGR_MOR_KEY_PASSWD
        | CKGR_MOR_MOSCXTEN	// enable xtal
        | (8 << 8)		// MOSCXTST = 8 => ~2msec
        ;

/* Once this register has been correctly configured, the user
   must wait for PMC_SR.MOSCXTS to be set. */

    while( (PMC->PMC_SR & PMC_SR_MOSCXTS) == 0 ){}

/* 3. Switch the main clock to the 3 to 20 MHz crystal oscillator by
   setting CKGR_MOR.MOSCSEL. */

    PMC->CKGR_MOR |= CKGR_MOR_KEY_PASSWD | CKGR_MOR_MOSCSEL;

/* 4. Wait for PMC_SR.MOSCSELS to be set to ensure the switchover is complete. */

    while( (PMC->PMC_SR & PMC_SR_MOSCSELS) == 0 ){}

/*
5. Check the main clock frequency: This frequency can be measured via
CKGR_MCFR.  Read CKGR_MCFR until the MAINFRDY field is set, after
which the user can read CKGR_MCFR.MAINF by performing an additional
read. This provides the number of main clock cycles that have been
counted during a period of 16 slow clock cycles.  If MAINF = 0, switch
the main clock to the 4/8/12 RC Oscillator by clearing
CKGR_MOR.MOSCSEL. If MAINF ≠ 0, proceed to Step 6.

*/

    measure_clock(1);		// measure and discard
    freq_measured = measure_clock(1);
    freq_hclk = freq_mck = HSECLOCK;
}
#endif

// SRCCLOCK -> SYSCLOCK
static void
init_clock_pll(void){
/*
6.
In the names PLLx, DIVx, MULx, LOCKx, PLLxCOUNT, and CKGR_PLLxR, ‘x’ represents A.
All parameters needed to configure PLLx and the divider are located in CKGR_PLLxR.
CKGR_PLLxR.DIVx is used to control the divider itself. This parameter can be programmed between 0 and 127. Divider output is divider input divided by DIVx parameter. By default, DIVx field is cleared which means that the divider and PLLx are turned off.
CKGR_PLLxR.MULx is the PLLx multiplier factor. This parameter can be programmed between 0 and 62. If MULx is cleared, PLLx will be turned off, otherwise the PLLx output frequency is PLLx input frequency multiplied by (MULx + 1).
CKGR_PLLxR.PLLxCOUNT specifies the number of slow clock cycles before PMC_SR.LOCKx is set after CKGR_PLLxR has been written.
Once CKGR_PLLxR has been written, the user must wait for PMC_SR.LOCKx to be set. This can be done either by polling PMC_SR.LOCKx or by waiting for the interrupt line to be raised if the associated interrupt source (LOCKx) has been enabled in PMC_IER. All fields in CKGR_PLLxR can be programmed in a single write operation. If MULx or DIVx is modified, the LOCKx bit goes low to indicate that PLLx is not yet ready. When PLLx is locked, LOCKx is set again. The user must wait for the LOCKx bit to be set before using the PLLx output clock.
*/

    int mul = (SYSCLOCK / SRCCLOCK) - 1;
    int div = 1;	// RSN - support more speeds
    int mdv = (SYSCLOCK > MCK_MAXFREQ) ? 1 : 0;	// divide by 2 : 1

    if( !mul ) return;
    if( mul > 62 ) mul = 62;

    freq_hclk = SRCCLOCK * (mul + 1) / div;
    freq_mck  = mdv ? freq_hclk / 2 : freq_hclk;

    init_flash( freq_mck );

    PMC->CKGR_PLLAR = (1<<29)
        | (2 << 8) 	// PLLCOUNT - wait 2 slow cycles
        | (mul << 16)
        | (div)
        ;

    while( (PMC->PMC_SR & PMC_SR_LOCKA) == 0 ){}

/*
7. Select the master clock and processor clock:
The master clock and the processor clock are configurable via PMC_MCKR.
PMC_MCKR.CSS is used to select the clock source of the master clock and processor clock dividers. By default, the selected clock source is the main clock.
PMC_MCKR.PRES is used to define the processor clock and master clock prescaler. The user can choose between different values (1, 2, 3, 4, 8, 16, 32, 64). Prescaler output is the selected clock source frequency divided by the PRES value.
PMC_MCKR.MDIV is used to define the master clock divider. It is possible to choose between different values (0, 1, 2, 3). The master clock output is the processor clock frequency divided by 1, 2, 3 or 4, depending on the value programmed in MDIV.
By default, MDIV is cleared, which indicates that the processor clock is equal to the master clock.
Once the PMC_MCKR has been written, the user must wait for PMC_SR.MCKRDY to be set. This can be done either by polling PMC_SR.MCKRDY or by waiting for the interrupt line to be raised if the associated interrupt source (MCKRDY) has been enabled in PMC_IER. PMC_MCKR must not be programmed in a single write operation. The programming sequence for PMC_MCKR is as follows:
If a new value for PMC_MCKR.CSS corresponds to PLL clock:
a. Program the PMC_MCKR.PRES.
b. Wait for PMC_SR.MCKRDY to be set.
c. Program the PMC_MCKR.MDIV.
d. Wait for PMC_SR.MCKRDY to be set.
e. Program the PMC_MCKR.CSS.
f. Wait for PMC_SR.MCKRDY to be set.
If CSS, MDIV or PRES are modified at any stage, the MCKRDY bit goes low to indicate that the master clock and the processor clock are not yet ready. The user must wait for MCKRDY bit to be set again before using the master and processor clocks.

*/

    uint32_t v = PMC->PMC_MCKR;
    v &= ~(3<<8);
    v |= mdv << 8;	// MDIV
    PMC->PMC_MCKR = v;
    while( (PMC->PMC_SR & PMC_SR_MCKRDY) == 0 ){}

    v &= ~3;
    v |= PMC_MCKR_CSS_PLLA_CLK;
    PMC->PMC_MCKR = v;
    while( (PMC->PMC_SR & PMC_SR_MCKRDY) == 0 ){}


}



static void
clock_init(void){
    // ...

#ifdef LSECLOCK
    enable_external_slow();
#endif

#ifdef HSICLOCK
    init_clock_internal();
#endif
#ifdef HSECLOCK
    init_clock_external();
#endif
#if SYSCLOCK > SRCCLOCK
    init_clock_pll();
#endif


    // usb

}


/****************************************************************/
void
init_ints(void){
}

void
init_hw(void){
    clock_init();
    tick_init( SYSTICK_FREQ );
    // init_uniqueid();
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

    bootmsg("clocks: hclk %dMHz mck %dMHz\n", freq_hclk/1000000, freq_mck/1000000 );
    // bootmsg("uid %x-%x-%x-%x\n", uniqueid[0], uniqueid[1], uniqueid[2], uniqueid[3]);


}

#ifdef KTESTING
DEFUN(measfreq, "measure freq")
{
    int f = measure_clock(1);
    printf("F: %d\n", f);
    return 0;

}
#endif
