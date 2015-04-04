
#ifndef __stm32f4_clock_h__
#define __stm32f4_clock_h__


#define HSICLOCK	16000000

#ifndef SYSCLOCK
#  ifdef HSECLOCK
#    define SYSCLOCK HSECLOCK
#  else
#    define SYSCLOCK HSICLOCK
#  endif
#endif


#ifdef STM32F411
#  define SYSMAX	100000000
#  define AHBMAX   	100000000	/* depends on voltage, and VOS bits */
#  define APB2MAX  	100000000	/* depends on voltage, and VOS bits */
#  define APB1MAX  	 50000000	/* depends on voltage, and VOS bits */
#  define ADCBMAX  	 36000000       /* NB: depends on voltage */
#  define USBFREQ  	 48000000
#  define FLASHMAX 	 30000000       /* NB: depends on voltage */
#  define PLLVCOTARGET    2000000
#  define PLLVCOMIN     100000000
#  define PLLVCOMAX     432000000
#else
#  define SYSMAX	168000000
#  define AHBMAX   	168000000
#  define APB2MAX  	 84000000
#  define APB1MAX  	 42000000
#  define ADCBMAX  	 36000000       /* NB: depends on voltage */
#  define USBFREQ  	 48000000
#  define FLASHMAX 	 30000000       /* NB: depends on voltage */
#  define PLLVCOTARGET    2000000
#  define PLLVCOMIN     192000000
#  define PLLVCOMAX     432000000
#endif

extern int sys_clock_freq(), apb1_clock_freq(), apb2_clock_freq();
#define APB2CLOCK	apb2_clock_freq()
#define APB1CLOCK	apb1_clock_freq()


#endif /* __stm32f4_clock_h__ */
