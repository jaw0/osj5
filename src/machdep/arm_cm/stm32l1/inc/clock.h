
#ifndef __stm32l1_clock_h__
#define __stm32l1_clock_h__


#define HSICLOCK	16000000
#define MSIDEFAULT	 2097000

#ifndef SYSCLOCK
#  ifdef HSECLOCK
#    define SYSCLOCK HSECLOCK
#  else
#    define SYSCLOCK HSICLOCK
#  endif
#endif

#  define SYSMAX	 32000000
#  define AHBMAX   	 32000000	/* depends on voltage, and VOS bits */
#  define APB2MAX  	 32000000	/* depends on voltage, and VOS bits */
#  define APB1MAX  	 32000000	/* depends on voltage, and VOS bits */
#  define USBFREQ  	 48000000
#  define FLASHMAX 	 16000000       /* NB: depends on voltage */
#  define PLLVCOTARGET   96000000	/* required, for USB to work */
#  define PLLVCOMIN       2000000
#  define PLLVCOMAX      96000000


extern int sys_clock_freq(), ahb_clock_freq(), apb1_clock_freq(), apb2_clock_freq();
#define APHCLOCK	ahb_clock_freq()
#define APB2CLOCK	apb2_clock_freq()
#define APB1CLOCK	apb1_clock_freq()


#endif /* __stm32l1_clock_h__ */
