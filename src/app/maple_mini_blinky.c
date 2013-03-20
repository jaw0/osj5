/*
  Copyright (c) 2013
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2013-Mar-17 23:15 (EDT)
  Function: 
 
  $Id$

*/

#include <stm32f10x.h>
#include <proc.h>

static void
blinky(void){

    while(1){
        GPIOB->ODR = (GPIOB->ODR & 0xFFFFFFFD) | 2;
        usleep( 250000 );
        GPIOB->ODR = (GPIOB->ODR & 0xFFFFFFFD) | 0;
        usleep( 250000 );
    }
}

void
main(void){

    /* Enable everything but wdg */
    RCC->APB2ENR |= 0x38FFFD;
    RCC->APB1ENR |= 0x3afec1ff;
    RCC->AHBENR  |= 0x557;

    /* blink B1 */
    GPIOB->CRL = 0x10;

    /* fork off a blink proc */
    start_proc( 1024, blinky, "blinky" );

}
