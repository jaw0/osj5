/*
  Copyright (c) 2024
  Author: Jeff Weisberg <tcp4me.com!jaw>
  Created: 2024-Mar-19 13:36 (EDT)
  Function: LEDs

*/

#include <conf.h>
#include <proc.h>
#include <userint.h>
#include <gpio.h>
#include <pwm.h>

#include <board.h>

#define msleep(x)      usleep(x * 1000)


void lights_throb_slow(void**);

static void (*current_blink_proc)(void**) = 0;


static inline void
init_led_pwm(int gpio, int timer, int afunc){
    gpio_init( gpio,   GPIO_AF(afunc) | GPIO_PUSH_PULL | GPIO_SPEED_2MHZ );
    pwm_init(  timer,  10000, 255 );
    pwm_set(   timer,  0x7f);	// start with lights on
}

static inline void
init_led_bool(int gpio){
    gpio_init( gpio,   GPIO_OUTPUT | GPIO_PUSH_PULL | GPIO_SPEED_2MHZ );
    gpio_set( gpio );
}


void
lights_init(void){

#ifdef HWCF_GPIO_LED_1
#  ifdef HWCF_TIMER_LED_1
    init_led_pwm( HWCF_GPIO_LED_1, HWCF_TIMER_LED_1, HWCF_AFUNC_LED_1 );
#  else
    init_led_bool( HWCF_GPIO_LED_1 );
#  endif
#endif

#ifdef HWCF_GPIO_LED_2
#  ifdef HWCF_TIMER_LED_2
    init_led_pwm( HWCF_GPIO_LED_2, HWCF_TIMER_LED_2, HWCF_AFUNC_LED_2 );
#  else
    init_led_bool( HWCF_GPIO_LED_2 );
#  endif
#endif

#ifdef HWCF_GPIO_LED_3
#  ifdef HWCF_TIMER_LED_3
    init_led_pwm( HWCF_GPIO_LED_3, HWCF_TIMER_LED_3, HWCF_AFUNC_LED_3 );
#  else
    init_led_bool( HWCF_GPIO_LED_3 );
#  endif
#endif

    current_blink_proc = lights_throb_slow;
}

void
debug_led(int a){
#ifdef HWCF_GPIO_LED_1
    gpio_init( HWCF_GPIO_LED_1,   GPIO_OUTPUT | GPIO_PUSH_PULL );
    if( a ){
        gpio_set( HWCF_GPIO_LED_1 );
    }else{
        gpio_clear( HWCF_GPIO_LED_1 );
    }
#endif
}


#ifdef HWCF_GPIO_LED_1
void
set_led_1(int v){
#  ifdef HWCF_TIMER_LED_1
#    ifdef LIGHT_FLAG_INVERT
    v = 255 - v;
#    endif
    pwm_set( HWCF_TIMER_LED_1, v );
#  else
#    ifdef LIGHT_FLAG_INVERT
    v = !v;
#    endif
        if( v )
            gpio_set( HWCF_GPIO_LED_1 );
        else
            gpio_clear( HWCF_GPIO_LED_1 );
#  endif
}
#endif

#ifdef HWCF_GPIO_LED_2
void
set_led_2(int v){
#  ifdef HWCF_TIMER_LED_2
#    ifdef LIGHT_FLAG_INVERT
    v = 255 - v;
#    endif
    pwm_set( HWCF_TIMER_LED_2, v );
#  else
#    ifdef LIGHT_FLAG_INVERT
    v = !v;
#    endif
        if( v )
            gpio_set( HWCF_GPIO_LED_2 );
        else
            gpio_clear( HWCF_GPIO_LED_2 );
#  endif
}
#endif

#ifdef HWCF_GPIO_LED_3
void
set_led_3(int v){
#  ifdef HWCF_TIMER_LED_3
#    ifdef LIGHT_FLAG_INVERT
    v = 255 - v;
#    endif
    pwm_set( HWCF_TIMER_LED_3, v );
#  else
#    ifdef LIGHT_FLAG_INVERT
    v = !v;
#    endif
        if( v )
            gpio_set( HWCF_GPIO_LED_3 );
        else
            gpio_clear( HWCF_GPIO_LED_3 );
#  endif
}
#endif


void
set_leds(int a, int b, int c){
#ifdef HWCF_GPIO_LED_1
    set_led_1(a);
#endif
#ifdef HWCF_GPIO_LED_2
    set_led_2(b);
#endif
#ifdef HWCF_GPIO_LED_3
    set_led_3(c);
#endif
}

void
set_leds_rgb(int v){
#ifdef HWCF_GPIO_LED_1
    set_led_1( (v >> 16) & 0xFF );
#endif
#ifdef HWCF_GPIO_LED_2
    set_led_2( (v >>  8) & 0xFF );
#endif
#ifdef HWCF_GPIO_LED_3
    set_led_3( (v      ) & 0xFF );
#endif
}

void
set_led1_rgb(int v){
    set_leds_rgb(v);
}


static const u_char throb_slow[40] = {
    1, 2, 4, 8, 16,
    16, 8, 4, 2, 1,
    1, 2, 4, 8, 16,
    16, 8, 4, 2, 1,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
};

void
lights_throb_slow(void **p){
    int i;

    while(1){
        for(i=0; i<sizeof(throb_slow); i++){
            if( p && (*p != lights_throb_slow) ) return;
            set_leds( throb_slow[i], throb_slow[i], throb_slow[i] );
            msleep(25);
        }
    }
}

void
blinky(void){

    while(1){
        if( current_blink_proc )
            current_blink_proc( &current_blink_proc );

        msleep(100);
    }
}

void
set_blinky(void * p){
    current_blink_proc = p;
}


DEFUN(testleds, "test leds")
{

    void *p = current_blink_proc;
    current_blink_proc = 0;

    set_leds( 0xFF, 0, 0);
    usleep( 500000 );
    set_leds( 0, 0xFF, 0);
    usleep( 500000 );
    set_leds( 0, 0, 0xFF);
    usleep( 500000 );

    set_leds(0xFF, 0xFF, 0xFF);
    sleep(1);

    set_leds(0x1F, 0x1F, 0x1F);
    sleep(1);

    set_leds( 0, 0, 0 );
    current_blink_proc = p;

    return 0;
}

