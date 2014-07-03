/*
  Copyright (c) 2011
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2011-Dec-05 15:26 (EST)
  Function: 
 
  $Id$

*/

#include <sys/types.h>
#include <sys/param.h>
#include <nstdio.h>
#include <md_proc.h>

void
panic(const char *m, int l, const char *f){

    kprintf("PANIC: %s at line %d of %s (currproc=%x)\nhalting\n", m, l, f, currproc);

    splhigh();

#ifdef PROJECT_PANIC
    extern void PROJECT_PANIC (const char *);
    PROJECT_PANIC(m);
#endif

    splhigh();
    while(1){
        // halt the processor
        idle();
    }
}
