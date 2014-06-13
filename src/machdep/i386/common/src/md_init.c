/*
  Copyright (c) 2011
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2011-Dec-12 22:29 (EST)
  Function: 
 
  $Id$

*/
#include <conf.h>
#include <arch.h>

unsigned long bootflags = 0;
long k_paddr = 0, bootmem0 = 0, bootmem1 = 0;

void
init_hw(void){
    XE9('H');
    E9PRINTF(("\nkpa %x, bm0 %x, bm1 %x\n", k_paddr, bootmem0, bootmem1));
}

void
init_hw2(void){
    kprintf("bootflags = 0x%x\n", bootflags);
}

