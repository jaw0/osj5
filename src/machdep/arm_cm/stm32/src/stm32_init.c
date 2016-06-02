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

void
stm32_init(void){
    armcm_init();
}

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
