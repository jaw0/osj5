
#ifndef __stm32f0_clock_h__
#define __stm32f0_clock_h__


#define HSICLOCK	 8000000

#ifndef SYSCLOCK
#  ifdef HSECLOCK
#    define SYSCLOCK HSECLOCK
#  else
#    define SYSCLOCK HSICLOCK
#  endif
#endif

#  define SYSMAX	 48000000
#  define AHBMAX   	 48000000	/* depends on voltage, and VOS bits */
#  define APB2MAX  	 48000000	/* depends on voltage, and VOS bits */
#  define APB1MAX  	 48000000	/* depends on voltage, and VOS bits */
#  define USBFREQ  	 48000000
#  define FLASHMAX 	 24000000       /* NB: depends on voltage */


extern int sys_clock_freq(), ahb_clock_freq(), apb1_clock_freq(), apb2_clock_freq();
#define APHCLOCK	ahb_clock_freq()
#define APB2CLOCK	apb2_clock_freq()
#define APB1CLOCK	apb1_clock_freq()


#endif /* __stm32f0_clock_h__ */
