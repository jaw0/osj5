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

#define nvic_setprio(irq, prio) NVIC_SetPriority((irq), (prio)>>4)

// NB: nvic handles external interrupts only, not internal exceptions
void
nvic_enable(int irq, int prio){

    NVIC_EnableIRQ(irq);
    nvic_setprio(irq, prio);
}

void
nvic_clearpending(int irq){
    NVIC_ClearPendingIRQ(irq);
}

/****************************************************************/

void
armcm_init(void){
    nvic_setprio(PendSV_IRQn,  IPL_PROC);
    nvic_setprio(SVCall_IRQn,  IPL_PROC);
}

/****************************************************************/

void
tick_init(int freq, int ext){

    // systick @ PROC_TIME usec
    int counter = (freq / 1000000) * PROC_TIME - 1;
    tick_base = freq / 1000000;
    SysTick->LOAD = counter;
    SysTick->CTRL = ext ? 3 : 7;

    nvic_setprio(SysTick_IRQn, IPL_CLOCK);
    //bootmsg("systick f %d, L %d\n", freq, counter);
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
    __asm__("wfi");

}
