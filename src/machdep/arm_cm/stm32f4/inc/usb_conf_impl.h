

#ifndef __stm32f4_usb_conf_impl_h__
#define __stm32f4_usb_conf_impl_h__

#define CONTROLSIZE	64

#ifdef STM32F413
// NB: has newer version of usb peripheral
#  define NUMENDPOINTS	6
#else
#  define NUMENDPOINTS	4
#  define NOVBUSSENS
#endif


#endif /* __stm32f4_usb_conf_impl_h__ */
