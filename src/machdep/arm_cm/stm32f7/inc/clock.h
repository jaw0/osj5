
#ifndef __stm32f7_clock_h__
#define __stm32f7_clock_h__


#define HSICLOCK	16000000

#ifndef SYSCLOCK
#  ifdef HSECLOCK
#    define SYSCLOCK HSECLOCK
#  else
#    define SYSCLOCK HSICLOCK
#  endif
#endif

#ifndef PLLVCOTARGET
// ST recommends 2MHz, but other values may be prefered
#  define PLLVCOTARGET    2000000
#endif

#ifdef STM32F7_OVERDRIVE
#  define SYSMAX	216000000
#  define AHBMAX   	216000000
#  define APB2MAX  	108000000
#  define APB1MAX  	 54000000
#  define ADCBMAX  	 36000000       /* NB: depends on voltage */
#  define USBFREQ  	 48000000
#  define FLASHMAX 	 30000000       /* NB: depends on voltage */
#  define PLLVCOMIN     100000000
#  define PLLVCOMAX     432000000

#else
#  define SYSMAX	180000000
#  define AHBMAX   	180000000	/* with over-drive not enabled */
#  define APB2MAX  	 90000000	/* "" */
#  define APB1MAX  	 45000000	/* "" */
#  define ADCBMAX  	 36000000       /* NB: depends on voltage */
#  define USBFREQ  	 48000000
#  define FLASHMAX 	 30000000       /* NB: depends on voltage */
#  define PLLVCOMIN     100000000
#  define PLLVCOMAX     432000000
#endif

extern int sys_clock_freq(), apb1_clock_freq(), apb2_clock_freq();
#define APB2CLOCK	apb2_clock_freq()
#define APB1CLOCK	apb1_clock_freq()


#endif /* __stm32f7_clock_h__ */
