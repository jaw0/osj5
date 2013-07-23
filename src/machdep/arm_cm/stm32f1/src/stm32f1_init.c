/*
  Copyright (c) 2013
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2013-Mar-11 00:46 (EDT)
  Function: stm32f1 hardware init

  $Id$

*/

#include <conf.h>
#include <stm32f10x.h>
#include <proc.h>
#include <alloc.h>


#define HSICLOCK 8000000
#define APB1MAX  36000000
#define ADCBMAX  14000000
#define SYSCLOCK 72000000

#define R_FLASHKB	((unsigned short *)(0x1FFFF7E0))
#define R_UNIQUE	((unsigned long*)(0x1FFFF7E8))


unsigned long bootflags = 0;
void stm32_putchar(int);

int
sys_clock_freq(void){
    return SYSCLOCK;
}

static void
clock_init(void){

    /* enable HSE */
    RCC->CR |= 0x00010001;
    while( RCC->CR & 0x00020000 == 0 ){} /* wait for it */

    FLASH->ACR   |= 2;		/* flash mem wait states */

    RCC->CFGR |= 0x5d8400;	/* 72Mhz, full speed */

    RCC->CR   |= 0x01000000;	 	 /* enable pll */
    while( RCC->CR & 0x02000000 == 0 ){} /* wait for it */

    /* Set SYSCLK as PLL */
    RCC->CFGR |= 0x00000002;
    while( RCC->CFGR & 0x0000000C == 0 ){} /* wait for it */

}

/****************************************************************/
void
init_ints(void){

    SCB->SHPR[1]  = (IPL_PROC  << 24); /* SVC */
}

void
init_hw(void){
    clock_init();
    tick_init();

#ifdef KSTACK_SIZE
    extern void _switch_kstack(char*);
    char *nsp = alloc(KSTACK_SIZE);
    _switch_kstack(nsp + KSTACK_SIZE);
#endif
}

/****************************************************************/

extern char _sdata, _estack;
void
init_hw2(void){
    int i;

    int ram = (&_estack - &_sdata)/1024;
    bootmsg("bootflags = 0x%x, cpuid %x, %dk flash, %dk RAM\n", bootflags, SCB->CPUID, *R_FLASHKB, ram);
    bootmsg("uid %x-%x-%x\n", R_UNIQUE[0], R_UNIQUE[1], R_UNIQUE[2]);

    // RSN - uid, devid, mem, ...

}

