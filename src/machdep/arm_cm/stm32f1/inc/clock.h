

#ifndef __stm32f1_clock_h__
#define __stm32f1_clock_h__

#ifndef SYSCLOCK
#  define SYSCLOCK	72000000
#endif

#define HSICLOCK 8000000
#define APBMAX   72000000
#define APB2MAX  72000000
#define APB1MAX  36000000
#define ADCBMAX  14000000
#define USBFREQ  48000000
#define FLASHMAX 24000000


extern int sys_clock_freq(), apb1_clock_freq(), apb2_clock_freq();
#define APB2CLOCK	apb2_clock_freq()
#define APB1CLOCK	apb1_clock_freq()


#endif /* __stm32f1_clock_h__ */


