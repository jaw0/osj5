/*
  Copyright (c) 2013
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2013-Mar-19 17:54 (EDT)
  Function: stm32 common
*/

#ifndef __machdep_stm32_h__
#define __machdep_stm32_h__

#ifdef PLATFORM_STM32F0
# include <stm32f0xx.h>
#endif

#ifdef PLATFORM_STM32F1
# include <stm32f10x.h>
# include <nvic.h>
#endif

#ifdef PLATFORM_STM32F4
# include <stm32f4xx.h>
#endif

#ifdef PLATFORM_STM32F7
# include <stm32f7xx.h>
#endif

#ifdef PLATFORM_STM32L1
# include <stm32l1xx.h>
#endif

#ifdef PLATFORM_STM32L4
# if defined(STM32L4Q)
#   include <stm32l4q.h>
# elif defined(STM32L4S)
#   include <stm32l4s.h>
# else
#   include <stm32l4xx.h>
# endif
#endif

#define PLATFORM_STM32


#endif /*  __machdep_stm32_h__ */
