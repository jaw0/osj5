
#ifndef __stm32l4_clock_h__
#define __stm32l4_clock_h__


#define HSICLOCK	16000000
#define MSIDEFAULT	 4000000

#ifndef SYSCLOCK
#  ifdef HSECLOCK
#    define SYSCLOCK HSECLOCK
#  else
#    define SYSCLOCK HSICLOCK
#  endif
#endif

#ifdef STM32L4_PLUS
#  define SYSMAX	120000000
#  define AHBMAX   	120000000	/* depends on voltage, and VOS bits */
#  define APB2MAX  	120000000	/* depends on voltage, and VOS bits */
#  define APB1MAX  	120000000	/* depends on voltage, and VOS bits */
#  define USBFREQ  	 48000000
#  define ADCMAX         80000000
#  define FLASHMAX 	 20000000       /* NB: depends on voltage; low power = 6MHz */
#  define PLLVCOTARGET   16000000
#  define PLLVCOMIN      64000000
#  define PLLVCOMAX     344000000

#else
#  define SYSMAX	 80000000
#  define AHBMAX   	 80000000	/* depends on voltage, and VOS bits */
#  define APB2MAX  	 80000000	/* depends on voltage, and VOS bits */
#  define APB1MAX  	 80000000	/* depends on voltage, and VOS bits */
#  define USBFREQ  	 48000000
#  define ADCMAX         80000000
#  define FLASHMAX 	 16000000       /* NB: depends on voltage; low power = 6MHz */
#  define PLLVCOTARGET   16000000
#  define PLLVCOMIN      64000000
#  define PLLVCOMAX     344000000
#endif

extern int sys_clock_freq(), ahb_clock_freq(), apb1_clock_freq(), apb2_clock_freq();
#define APHCLOCK	ahb_clock_freq()
#define APB2CLOCK	apb2_clock_freq()
#define APB1CLOCK	apb1_clock_freq()


#endif /* __stm32l4_clock_h__ */
