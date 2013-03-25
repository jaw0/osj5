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
#include <pwm.h>

#define SYSCLOCK 72000000


static void
blinky(void){
    int n   = 0;
    int dir = 2;

    pwm_set( TIMER_1_1, 10 );
    pwm_set( TIMER_1_4, 50 );

    while(1){
        pwm( n );
        freq_set( TIMER_1_1, 3*n + 500 );
        n += dir;
        if( n >= 1023 ) dir = -dir;
        if( n <= 0 ) dir = -dir;
        usleep( 1000 );
    }
}

void
pwm(int val){

//    pwm_set( TIMER_1_1, val );
//    pwm_set( TIMER_1_2, val );
//    pwm_set( TIMER_1_3, val );
//    pwm_set( TIMER_1_4, val );

    pwm_set( TIMER_2_1, val );
    pwm_set( TIMER_2_2, val );
    pwm_set( TIMER_2_3, val );
    pwm_set( TIMER_2_4, val );

    pwm_set( TIMER_3_1, val );
    pwm_set( TIMER_3_2, val );
    pwm_set( TIMER_3_3, val );
    pwm_set( TIMER_3_4, val );

    pwm_set( TIMER_4_1, val );
    pwm_set( TIMER_4_2, val );
    pwm_set( TIMER_4_3, val );
    pwm_set( TIMER_4_4, val );

}


void
main(void){

    // T1
    gpio_init( GPIO_A8,  GPIO_AF_OUTPUT_PP | GPIO_OUTPUT_50MHZ );	// ok
//    gpio_init( GPIO_A9,  GPIO_AF_OUTPUT_PP | GPIO_OUTPUT_50MHZ );	// no - ser
//    gpio_init( GPIO_A10, GPIO_AF_OUTPUT_PP | GPIO_OUTPUT_50MHZ );	// ok - ser
    gpio_init( GPIO_A11, GPIO_AF_OUTPUT_PP | GPIO_OUTPUT_50MHZ );	// ok - usb, not labeled as pwm

    // T2
    gpio_init( GPIO_A0,  GPIO_AF_OUTPUT_PP | GPIO_OUTPUT_50MHZ );	// ok
    gpio_init( GPIO_A1,  GPIO_AF_OUTPUT_PP | GPIO_OUTPUT_50MHZ );	// ok
    gpio_init( GPIO_A2,  GPIO_AF_OUTPUT_PP | GPIO_OUTPUT_50MHZ );	// ok
    gpio_init( GPIO_A3,  GPIO_AF_OUTPUT_PP | GPIO_OUTPUT_50MHZ );	// ok

    // T3
    gpio_init( GPIO_A6,  GPIO_AF_OUTPUT_PP | GPIO_OUTPUT_50MHZ );	// ok
    gpio_init( GPIO_A7,  GPIO_AF_OUTPUT_PP | GPIO_OUTPUT_50MHZ );	// ok
    gpio_init( GPIO_B0,  GPIO_AF_OUTPUT_PP | GPIO_OUTPUT_50MHZ );	// ok
    gpio_init( GPIO_B1,  GPIO_AF_OUTPUT_PP | GPIO_OUTPUT_50MHZ );	// ok - blue light

    // T4
    gpio_init( GPIO_B6,  GPIO_AF_OUTPUT_PP | GPIO_OUTPUT_50MHZ );	// ok
    gpio_init( GPIO_B7,  GPIO_AF_OUTPUT_PP | GPIO_OUTPUT_50MHZ );	// ok (don't enable i2c)
    gpio_init( GPIO_B8,  GPIO_AF_OUTPUT_PP | GPIO_OUTPUT_50MHZ );	// ok, button

    pwm_init( TIMER_1_1, 1000000, 100 );
    pwm_init( TIMER_2_1, 1000000, 1023 );
    pwm_init( TIMER_3_1, 1000000, 1023 );
    pwm_init( TIMER_4_1, 1000000, 1023 );


    printf("timer2 %x\n", TIM2);
    /* fork off a blink proc */
    start_proc( 1024, blinky, "blinky" );

}
