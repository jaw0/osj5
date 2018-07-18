/*
  Copyright (c) 2011
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2011-Dec-05 00:08 (EST)
  Function: 

*/

#ifndef __os_machdep_arm_cm4_arch_h__
#define __os_machdep_arm_cm4_arch_h__

#include <md_impl.h>

#define XE9(x)			/* QQQ */

#ifdef DMAALIGN
# define ALIGNMENT 	DMAALIGN
#else
# define ALIGNMENT	8	/* memory alignment */
#endif

#endif
