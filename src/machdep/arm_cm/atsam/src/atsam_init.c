/*
  Copyright (c) 2013
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2013-Mar-11 00:46 (EDT)
  Function: stm32f1 hardware init
*/

#include <conf.h>
#include <proc.h>
#include <alloc.h>
#include <atsam.h>

void
atsam_init(void){
    armcm_init();
}

/* enter low power standby mode */
int
power_down(void){


    //– Set SLEEPDEEP in CortexTM-M4F System Control register
    // turn off vreg

    SCB->SCR |= 4;	// sleepdeep
    SUPC->SUPC_CR = 0xA5000004;

    __asm__("wfi");
}
