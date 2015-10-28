/*
  Copyright (c) 2013
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2013-Mar-19 17:54 (EDT)
  Function: stm32 common
*/

#ifndef __machdep_stm32_h__
#define __machdep_stm32_h__

#ifdef PLATFORM_STM32F1
# include <stm32f10x.h>
# include <nvic.h>
#endif

#ifdef PLATFORM_STM32F4
# include <stm32f4xx.h>
#endif

#ifdef PLATFORM_STM32L1
# include <stm32l1xx.h>
#endif

#define PLATFORM_STM32


#endif /*  __machdep_stm32_h__ */
