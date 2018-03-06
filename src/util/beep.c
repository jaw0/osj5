/*
  Copyright (c) 2018
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2018-Mar-05 21:13 (EST)
  Function: beep

*/

#include <proc.h>
#include <userint.h>
#include <conf.h>
#include <pwm.h>

int volume_setting = 4;
int volume  = 16;       // music
int ivolume = 16;       // UI


void
set_volume(int v){
    if( v > 7 ) v = 7;
    volume_setting = v;
    ivolume = volume = 1<<v;
    if( ivolume < 2 ) ivolume = 2;
}

void
beep_set(int freq, int vol){
    if( vol > 128 ) vol = 128;
    if( vol < 0  )  vol = 0;

    freq_set(BEEP_TIMER, freq);
    pwm_set( BEEP_TIMER,  vol);
}

void
beep(int freq, int vol, int dur){
    if( vol > 128 ) vol = 128;
    if( vol < 1  )  vol = 1;

    freq_set(BEEP_TIMER, freq);
    pwm_set(BEEP_TIMER,  vol);
    usleep(dur);
    pwm_set(BEEP_TIMER,  0);
}


#ifdef USE_CLI
DEFUN(volume, "set volume")
{
    if( argc == 2 ){
        set_volume( atoi(argv[1]) );
    }else{
        printf("volume: %d\n", volume_setting);
    }

    return 0;
}

DEFUN(beep, "beep")
{

    if( argc > 2 )
        beep( atoi(argv[1]), atoi(argv[2]), 250000 );
    else
        fprintf(STDERR, "beep freq volume\n");

    return 0;
}
#endif


