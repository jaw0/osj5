
#ifndef __stm32u5_clock_h__
#define __stm32u5_clock_h__


#define HSICLOCK	16000000
#define MSIDEFAULT	 4000000

#ifndef SYSCLOCK
#  ifdef HSECLOCK
#    define SYSCLOCK HSECLOCK
#  else
#    define SYSCLOCK HSICLOCK
#  endif
#endif

#define SYSMAX		160000000
#define AHBMAX   	160000000	/* depends on voltage, and VOS bits */
#define APB2MAX  	160000000	/* depends on voltage, and VOS bits */
#define APB1MAX  	160000000	/* depends on voltage, and VOS bits */
#define USBFREQ  	 48000000
#define ADCMAX           55000000
#define FLASHMAX 	 32000000       /* NB: depends on voltage; low power = 12MHz */
#define PLLVCOTARGET      4000000
#define PLLVCOMIN       128000000
#define PLLVCOMAX       544000000
#define EPODTARGET	  8000000     	/* must be 4-16 MHz */
#define HSPLLTARGET	 32000000	/* 16, 20, 24, 32 */

extern int sys_clock_freq(), ahb_clock_freq(), apb1_clock_freq(), apb2_clock_freq();
#define APHCLOCK	ahb_clock_freq()
#define APB2CLOCK	apb2_clock_freq()
#define APB1CLOCK	apb1_clock_freq()


#endif /* __stm32u5_clock_h__ */
