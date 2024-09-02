/*
  Copyright (c) 2024
  Author: Jeff Weisberg <tcp4me.com!jaw>
  Created: 2024-Mar-19 19:42 (EDT)
  Function: beeper

*/

#include <conf.h>
#include <proc.h>
#include <userint.h>
#include <gpio.h>
#include <pwm.h>

#include <board.h>

int volume_setting = 5;
int volume         = 16;

#ifndef HWCF_AFUNC_AUDIO
#  define HWCF_AFUNC_AUDIO 2
#endif

void
sounds_init(void){

    gpio_init( HWCF_GPIO_AUDIO,    GPIO_AF(HWCF_AFUNC_AUDIO) | GPIO_SPEED_2MHZ );
    pwm_init(  HWCF_TIMER_AUDIO,   440, 255 );
    pwm_set(   HWCF_TIMER_AUDIO,   0 );

}

void
set_volume(int v){
    if( v < 0 ) v = 0;
    if( v > 8 ) v = 8;
    volume_setting = v;
    volume = v ? 1<<(v - 1) : 0;
}

DEFUN(volume, "set volume")
{
    if( argc == 2 ){
        set_volume( atoi(argv[1]) );
    }else{
        printf("volume: %d\n", volume_setting);
    }

    return 0;
}

void
beep_set(int freq, int vol){
    if( vol > 128 ) vol = 128;
    if( vol < 0  )  vol = 0;

    freq_set(HWCF_TIMER_AUDIO, freq);
    pwm_set(HWCF_TIMER_AUDIO,  vol);
}

void
beep(int freq, int vol, int dur){
    if( vol > 128 ) vol = 128;
    if( vol < 0  )  vol = 0;

    freq_set(HWCF_TIMER_AUDIO, freq);
    pwm_set(HWCF_TIMER_AUDIO,  vol);
    usleep(dur);
    pwm_set(HWCF_TIMER_AUDIO,  0);
}

DEFUN(beep, "beep")
{

    if( argc > 2 )
        beep( atoi(argv[1]), atoi(argv[2]), 250000 );

    return 0;
}

