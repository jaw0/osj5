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

#if 0
static void
delay(int n){
    int i;
    for(i=n*100000; i > 0; i--){
        asm("nop");	/* This stops it optimizing code out */
    }
}

static void
stm32_serial_init(void){

    // RCC->APB2ENR |= 0x4005;
    /* all periphs enabled */
    RCC->APB2ENR |= 0x38FFFD;
    RCC->APB1ENR |= 0x3afec1ff;
    RCC->AHBENR  |= 0x557;

    /* gpio A - output, serial afi */
    GPIOA->CRL = 0x11114b11;
    GPIOA->CRH = 0x111114b1;
    GPIOB->CRL = 0x11111111;


    USART1->BRR   = SYSCLOCK / 57600;
    USART1->CR1  |= 0x200C;	// enable, no parity, 8 bit, ...

//    stm32_putchar('\n');
}

void
stm32_putchar(int c){
    while( !(USART1->SR & 0x80) ) {}
    USART1->DR = c;
    if( c == '\n' ) stm32_putchar('\r');
}

void
talky(void){
    int n = 0;

    while(1){
        delay(1);
        n++;
        stm32_putchar( (n&0xF) + 0x40 );
        GPIOB->ODR = (n>>2) & 2;
    }
}

static void
blink_init(void){
/* Enable everything but wdg */
    RCC->APB2ENR |= 0x38FFFD;
    RCC->APB1ENR |= 0x3afec1ff;
    RCC->AHBENR  |= 0x557;

    /* blink B1 */
    GPIOB->CRL = 0x10;
}

void
blink(int n){

    for( ;n; n--){
        GPIOB->ODR = (GPIOB->ODR & 0xFFFFFFFD) | 2;
        delay(5);
        GPIOB->ODR = (GPIOB->ODR & 0xFFFFFFFD) | 0;
        delay(5);
    }
    delay(40);
}



void
xxxblinky(void){

    int n = 0;
    int i;

    stm32_putchar('!');
    
/* Enable everything but wdg */
    RCC->APB2ENR |= 0x38FFFD;
    RCC->APB1ENR |= 0x3afec1ff;
    RCC->AHBENR  |= 0x557;

/* gpio A,B,C - output, except serial1 */
    GPIOA->CRL = 0x11111111;
    GPIOA->CRH = 0x111114b1;
    GPIOB->CRL = 0x11111111;
    GPIOB->CRH = 0x11111111;
    GPIOC->CRL = 0x11111111;
    GPIOC->CRL = 0x11111111;

    while(1){
        delay(1);
        n++;
        /* blink on all gpio A,B,C */
        i = (n & 0xf) * 0x1111;

        GPIOA->ODR = (GPIOA->ODR & 0xFFFF0000) | i;
        GPIOB->ODR = (GPIOB->ODR & 0xFFFF0000) | i;
        GPIOC->ODR = (GPIOC->ODR & 0xFFFF0000) | i;

        stm32_putchar( (n&0xF) + 0x40 );
    }
}
#endif

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

