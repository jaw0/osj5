/*
  Copyright (c) 2015
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2015-Oct-28 20:18 (EDT)
  Function: 

*/


#include <asmdefs.h>
#include "assym.h"
#include <conf.h>

#define RAMSTART	0x20400000


#ifndef RAMSIZE
#  ifdef CCM_SIZE
#    define RAMSIZE	(384*1024 - 2*CCM_SIZE)
#  else
#    define RAMSIZE	(384*1024)
#  endif
#endif

        .globl _estack
_estack =      (RAMSTART + RAMSIZE)

#ifdef USE_CCM
        .globl _ccmem
_ccmem = 0x20000000;
        .globl _dtcm
_dtcm  = 0x20000000;
        .globl _itcm
_itcm  = 0;
#endif
