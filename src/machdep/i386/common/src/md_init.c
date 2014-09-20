/*
  Copyright (c) 2011
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2011-Dec-12 22:29 (EST)
  Function: 
 
  $Id$

*/
#include <conf.h>
#include <arch.h>
#include <userint.h>

// set by boot loader
DEFVAR(unsigned long, bootflags, 0, UV_TYPE_UL, "bootflags")
DEFVAR(long, k_paddr,  0, UV_TYPE_UL | UV_TYPE_RO, "")
DEFVAR(long, bootmem0, 0, UV_TYPE_UL | UV_TYPE_RO, "")
DEFVAR(long, bootmem1, 0, UV_TYPE_UL | UV_TYPE_RO, "")

void
init_hw(void){
    XE9('H');
    E9PRINTF(("\nkpa %x, bm0 %x, bm1 %x\n", k_paddr, bootmem0, bootmem1));
}

void
init_hw2(void){
    kprintf("bootflags = 0x%x, mem %dkB\n", bootflags, bootmem0 + bootmem1);
}

