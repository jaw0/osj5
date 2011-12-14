/*
  Copyright (c) 2011
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2011-Dec-05 17:04 (EST)
  Function: 
 
  $Id$

*/

#include <conf.h>
#include <proc.h>
#include <time.h>
#include <error.h>


int
init_ints(void){

    // set up handler stack
    // start systick ticking
}

void
SysTick_Handler(void){

    systime_tick();
}


void
fault(const char *type){

    kprintf("* * * * * ERROR - %s * * * * *\n", name);
    /* stack trace ? */

#ifdef USE_PROC
    kprintf("in process %0.8x (%s)\n", currproc, (currproc && currproc->name)
            ? currproc->name : "unknown");

    if( currproc->flags & PRF_IMPORTANT ){
        PANIC(name);
    }else{
        kprintf("killing process\n");
        sigkill( (proc_t)currproc );
        sched_yield();
    }
#else
    PANIC(name);
#endif
}

void
NMI_Handler(void){
    // RSN - enter debugger
    PANIC("NMI");
}

void
HardFault_Handler(void){
    fault("hard fault");
}

void
MemManage_Handler(void){
    fault("mem fault");
}

void
BusFault_Handler(void){
    fault("bus fault");
}

void
UsageFault_Handler(void){
    fault("usage fault");
}

void
SVC_Handler(void){
    kprintf("SVC?\n");
}
