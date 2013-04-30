/*
  Copyright (c) 2013
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2013-Mar-17 23:15 (EDT)
  Function: 
 
  $Id$

*/

#include <conf.h>
#include <proc.h>
#include <gpio.h>
#include <stm32.h>

#ifdef PLATFORM_SM32F1
#  define GPIO_LED GPIO_B1
#else
#  define GPIO_LED GPIO_B8
#endif


static void
blinky(void){

    while(1){
        gpio_set( GPIO_LED );
        usleep( 250000 );
        gpio_clear( GPIO_LED );
        usleep( 250000 );
    }
}

void
main(void){
#ifdef PLATFORM_SM32F1
    gpio_init( GPIO_LED, GPIO_OUTPUT_PP | GPIO_OUTPUT_10MHZ );
#else
    gpio_init( GPIO_LED, GPIO_OUTPUT | GPIO_PUSH_PULL | GPIO_SPEED_25MHZ );
#endif
    /* fork off a blink proc */
    start_proc( 256, blinky, "blinky" );

}
