/*
  Copyright (c) 2016
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2016-Jun-01 21:04 (EDT)
  Function: arm cortex-m common

*/

#include <conf.h>
#include <chip.h>
#include <proc.h>
#include <time.h>
#include <error.h>

static int tick_base;

// NB: nvic handles external interrupts only, not internal exceptions
void
nvic_enable(int irq, int prio){
    NVIC_EnableIRQ(irq);
    NVIC_SetPriority(irq, prio);
}

void
nvic_clearpending(int irq){
    NVIC_ClearPendingIRQ(irq);
}

/****************************************************************/

void
armcm_init(void){
    NVIC_SetPriority(PendSV_IRQn,  IPL_PROC);
    NVIC_SetPriority(SVCall_IRQn,  IPL_PROC);
}

/****************************************************************/

void
tick_init(int freq){

    // systick @ PROC_TIME usec
    int counter = (freq / 1000000) * PROC_TIME - 1;
    tick_base = freq / 1000000;
    SysTick->LOAD = counter;
    SysTick->CTRL = 3;

    NVIC_SetPriority(SysTick_IRQn, IPL_CLOCK);
}

utime_t
get_hrtime(void){
    utime_t t;

    int plx = splhigh();
    int tk  = PROC_TIME - SysTick->VAL / tick_base;
    t = get_time() + tk;
    // is systick irq pending? adjust
    if( (SCB->ICSR & (1<<26)) && (tk < (PROC_TIME>>1)) ) t += PROC_TIME;
    splx(plx);
    return t;
}


/****************************************************************/
int
reboot(void){
    SCB->AIRCR = (SCB->AIRCR & (0x700)) | (0x5FA << 16) | (1<<2);
}
/****************************************************************/

void
idle(void){
    // QQQ - at sam wfi wtf?
#ifndef PLATFORM_ATSAM
    __asm__("wfi");
#endif

}
