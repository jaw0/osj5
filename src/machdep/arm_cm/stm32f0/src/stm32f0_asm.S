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
#  define RAMSIZE	(16*1024)
#endif

        .globl _estack
_estack =      (RAMSTART + RAMSIZE)

