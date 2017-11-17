/*
  Copyright (c) 2013
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2013-Mar-11 00:46 (EDT)
  Function: stm32 hardware init
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

