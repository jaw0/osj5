/*
  Copyright (c) 2013
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2013-Sep-10 19:25 (EDT)
  Function: core-coupled memory

*/
#include <conf.h>
#include <arch.h>
#include <stm32.h>


int
ccm_init(void){

    RCC->AHB1ENR |= 1<<20;
    return 0;
}
