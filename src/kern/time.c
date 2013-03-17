/*
  Copyright (c) 2011
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2011-Dec-13 16:35 (EST)
  Function: 
 
  $Id$

*/

#include <conf.h>
#include <proc.h>
#include <time.h>

utime_t systime = 0;

void
systime_tick(void){

    /* keep track of real time */
    systime += PROC_TIME;

#ifdef USE_PROC
    /* keep track of proc stats */
    if( currproc )
        currproc->estcpu ++;

    if( currproc && (--timeremain <= 0) ){
        sched_yield();
    }
#endif

}
