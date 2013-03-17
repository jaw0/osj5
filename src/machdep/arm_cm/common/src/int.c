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

#include <stm32f10x.h>


void
SysTick_Handler(void){
    systime_tick();
}


void
fault(const char *name){

    kprintf("* * * * * FAULT - %s * * * * *\n", name);
    /* stack trace ? */

#ifdef USE_PROC
    kprintf("in process %x (%s)\n", currproc, (currproc && currproc->name)
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
CHardFault_Handler(unsigned long *sp){

    kprintf("\n* * * * * HARD FAULT * * * * *\n");
    kprintf("r0   %08x  r1   %08x  r2   %08x  r3   %08x\n", sp[0], sp[1], sp[2], sp[3]);
    kprintf("r12  %08x  LR   %08x  PC   %08x  PSR  %08x\n", sp[4], sp[5], sp[6], sp[7]);
    kprintf("sp   %08x  BFAR %08x  CFSR %08x  HFSR %08x\n", sp, SCB->BFAR, SCB->CFSR, SCB->HFSR);
    kprintf("AFSR %08x  DFSR %08x  SHCSR %08x\n", SCB->AFSR, SCB->DFSR, SCB->SHCSR);

    int cfsr = SCB->CFSR;
    if( cfsr & 0xFFFF0000 ){
        // break out usage bits
        kprintf("    CFSR: Usage Fault");
        if( cfsr & 0x200000 ) kprintf("<DIV BY ZERO>");
        if( cfsr & 0x100000 ) kprintf("<UNALIGNED>");
        if( cfsr & 0x80000 )  kprintf("<NO COPROC>");
        if( cfsr & 0x40000 )  kprintf("<INVALID PC>");
        if( cfsr & 0x20000 )  kprintf("<INVALID STATE>");
        if( cfsr & 0x10000 )  kprintf("<INVALID INSTR>");
        kprintf("\n");
    }
    if( cfsr & 0xFF00 ){
        // break out buserror bits
        kprintf("    CFSR: Bus Fault");
        if( cfsr & 0x8000 ) kprintf("<at BFAR>");
        if( cfsr & 0x2000 ) kprintf("<FP>");
        if( cfsr & 0x1000 ) kprintf("<Stacking>");
        if( cfsr & 0x0800 ) kprintf("<Unstacking>");
        if( cfsr & 0x0400 ) kprintf("<LOC UNKNOWN>");
        if( cfsr & 0x0200 ) kprintf("<at PC>");
        if( cfsr & 0x0100 ) kprintf("<Instr>");
        kprintf("\n");
    }
    if( cfsr & 0xFF ){
        // break out memerror bits
        kprintf("    CFSR: Mem Fault");
        if( cfsr & 0x80 ) kprintf("<at BFAR>");
        if( cfsr & 0x20 ) kprintf("<FP>");
        if( cfsr & 0x10 ) kprintf("<Stacking>");
        if( cfsr & 0x08 ) kprintf("<Unstacking>");
        if( cfsr & 0x02 ) kprintf("<Data>");
        if( cfsr & 0x01 ) kprintf("<Instr>");
        kprintf("\n");
    }

    kprintf("  currproc %x\n", currproc);

    extern void shell(void);
    shell();
    PANIC("hard fault");
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
