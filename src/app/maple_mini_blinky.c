/*
  Copyright (c) 2013
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2013-Mar-17 23:15 (EDT)
  Function: 
 
  $Id$

*/

#include <stm32f10x.h>
#include <proc.h>
#include <gpio.h>

static void
blinky(void){

    while(1){
        gpio_set( GPIO_B1 );
        usleep( 250000 );
        gpio_clear( GPIO_B1 );
        usleep( 250000 );
    }
}

void
main(void){

    gpio_init( GPIO_B1, GPIO_OUTPUT_PP | GPIO_OUTPUT_10MHZ );

    /* fork off a blink proc */
    start_proc( 256, blinky, "blinky" );

}
