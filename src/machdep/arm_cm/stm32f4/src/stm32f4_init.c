/*
  Copyright (c) 2013
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2013-Mar-11 00:46 (EDT)
  Function: stm32f1 hardware init

  $Id$

*/

#include <conf.h>
#include <stm32f4xx.h>
#include <proc.h>
#include <alloc.h>
#include <clock.h>


#define R_FLASHKB	((unsigned short *)(0x1FFF7A22))
#define R_UNIQUE	((unsigned long*)(0x1FFF7A10))


unsigned long bootflags = 0;
void stm32_putchar(int);

int
sys_clock_freq(void){
    return SYSCLOCK;
}

static void
clock_init(void){

    /* enable HSE */
    RCC->CR |= (1<<16);
    while( RCC->CR & (1<<17) == 0 ){} /* wait for it */

    FLASH->ACR |= 5;            /* flash mem wait states */

    RCC->PLLCFGR = (1<<22)      // src=hse
        | 6                     // pllm
        | (168 << 6)            // plln
        | (0<<16)               // pllp=2
        | (7<<24)               // pllq
        ;

    RCC->CFGR  = (4<<13)        // apb2 = divide by 2
        | (5<<10)               // apb1 = divide by 4
        | (0<<4)                // ahb =  no divide
        | (12<<16)              // rtc = hse / 12
        ;

    RCC->CR    |= (1<<24);               /* enable pll */
    while( RCC->CR & (1<<25) == 0 ){} /* wait for it */

    /* Set SYSCLK as PLL */
    RCC->CFGR |= 0x2;
    while( RCC->CFGR & 0xC == 0 ){} /* wait for it */

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

