/*
  Copyright (c) 2013
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2013-Mar-11 00:46 (EDT)
  Function: stm32f1 hardware init
*/

#include <conf.h>
#include <proc.h>
#include <alloc.h>
#include <stm32.h>
#include <clock.h>

// NB: nvic handles external interrupts only, not internal exceptions
void
nvic_enable(int irq, int prio){

    int bi = irq / 32;
    int bb = irq & 31;

    int oi = irq / 4;
    int ob = irq & 3;

    NVIC->IPR[irq] |= prio;
    NVIC->ISER[bi] |= 1<<bb;	// enable
}

void
nvic_clearpending(int irq){

    int bi = irq / 32;
    int bb = irq & 31;

    NVIC->ICPR[bi] |= 1<<bb;
}

/****************************************************************/

void
tick_init(void){

    // systick @ PROC_TIME usec
    int counter = (SYSCLOCK / 1000000) * PROC_TIME / 8;
    SysTick->LOAD = counter;
    SysTick->CTRL = 3;

    SCB->SHPR[2]  = (IPL_CLOCK << 24) | (IPL_PROC << 16);
}

utime_t
get_hrtime(void){
    utime_t t;

    int plx = splhigh();
    int tk  = (PROC_TIME - SysTick->VAL / (SYSCLOCK / 1000000 / 8));
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

/* enter low power standby mode */
int
power_down(void){

    RCC->APB1ENR |= (1<<28);		// enable PWR system

    //– Set SLEEPDEEP in CortexTM-M4F System Control register
    //– Set PDDS bit in Power Control register (PWR_CR)
    //– Clear WUF bit in Power Control/Status register (PWR_CSR)

    SCB->SCR |= 4;	// sleepdeep
    PWR->CR  |= 2;	// PDDS
    PWR->CR  |= 4;	// clear WUF

    __asm__("wfi");
}
