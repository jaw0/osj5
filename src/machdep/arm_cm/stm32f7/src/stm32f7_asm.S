/*
  Copyright (c) 2015
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2015-Oct-28 20:18 (EDT)
  Function: 

*/


#include <asmdefs.h>
#include "assym.h"
#include <conf.h>

#define RAMSTART	0x20000000


#ifndef RAMSIZE
#  define RAMSIZE	(128*1024)
#endif

        .globl _estack
_estack =      (RAMSTART + RAMSIZE)


/* dtcm starts at 0x2000_0000, size varies
   sram immediately follows, size varies
*/
#ifdef USE_CCM
# ifndef DTCMSIZE
#  define DTCMSIZE 65536
# endif
#endif

#ifdef DTCMSIZE
        .globl _ccmem
        .section .dtcm,"a",%nobits
        .size _ccmem, DTCMSIZE
_ccmem:
        .space DTCMSIZE, 0
#endif
