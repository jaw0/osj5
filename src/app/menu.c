/*
  Copyright (c) 2013
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2013-Apr-18 20:28 (EDT)
  Function: menus, accelerometer for user input
*/


#include <conf.h>
#include <proc.h>
#include <gpio.h>
#include <pwm.h>
#include <sys/types.h>

#include "menu.h"

/*
u+80	arrowleft
u+81	arrowup
u+82	arrowright
u+83	arrowdown
u+84	arrowupdn
u+85	arrowboth
*/


extern int volume;
static short accel_off_x, accel_off_y, accel_off_z;


static void
calibrate(){
    int tot = 0;
    int n;

    tot = 0;
    for(n=0; n<10; n++){
        read_imu();
        tot += accel_x();
        usleep(1000);
    }
    accel_off_x = tot/10;

    tot = 0;
    for(n=0; n<10; n++){
        read_imu();
        tot += accel_y();
        usleep(1000);
    }
    accel_off_y = tot/10;

    tot = 0;
    for(n=0; n<10; n++){
        read_imu();
        tot += accel_z() - 1000;
        usleep(1000);
    }
    accel_off_z = tot/10;
}

static inline void
beep(int freq, int dur){
    freq_set(TIMER_3_3, freq);
    pwm_set(TIMER_3_3,  2);
    usleep(dur);
    pwm_set(TIMER_3_3,  0);
}

static clear_line(int dir){
    int i;

    for(i=0; i<26; i++){
        if( dir > 0 )
            printf("\e[<");
        else
            printf("\e[>");
        printf("\xB");
        usleep(10000);
    }
}

#define AUTOREPEAT_X	250000
#define AUTOREPEAT_Y	1000000
#define TILT_MIN	500		// ~ 30 degree tilt

static int
get_input(void){
    static int     prevach = 0;
    static utime_t prevat  = 0;
    utime_t now;
    char flatct = 0;
    char leftct = 0;
    char rightct = 0;
    char upct = 0;
    char dnct = 0;

    while(1){
        // LR - enter
        if( gpio_get( GPIO_A14 ) ){
            beep(600, 250000);
            while( gpio_get( GPIO_A14 ) ) yield();
            beep(450, 250000);
            return '*';
        }

        // RR - back
        if( gpio_get( GPIO_B8 ) ){
            beep(600, 250000);
            while( gpio_get( GPIO_B8 ) ) yield();
            beep(450, 250000);
            return '^';
        }

        read_imu();
        int ax = accel_x() - accel_off_x;
        int ay = accel_y() - accel_off_y;
        now = get_time();

        // flat?
        if( ax < TILT_MIN && ax > -TILT_MIN && ay < TILT_MIN && ay > -TILT_MIN )
            flatct ++;
        else
            flatct = 0;

        if( ax > TILT_MIN )
            dnct ++;
        else
            dnct = 0;

        if( ax < -TILT_MIN )
            upct ++;
        else
            upct = 0;

        if( ay > TILT_MIN )
            rightct ++;
        else
            rightct = 0;

        if( ay < -TILT_MIN )
            leftct ++;
        else
            leftct = 0;

        if( flatct > 10 ){
            prevach = 0;
            prevat  = 0;
        }

        if( rightct > 10 )
            if( !prevach || (prevach == '>' && now - prevat > AUTOREPEAT_X) ){
                beep(400, 100000);
                prevat  = now;
                return prevach = '>';
            }

        if( leftct > 10 )
            if( !prevach || (prevach == '<' && now - prevat > AUTOREPEAT_X) ){
                beep(400, 100000);
                prevat  = now;
                return prevach = '<';
            }

        if( dnct > 10 )
            if( !prevach || (prevach == '*' && now - prevat > AUTOREPEAT_Y) ){
                beep(600, 100000);
                beep(300, 150000);
                prevat  = now;
                return prevach = '*';
            }

        if( upct > 10 )
            if( !prevach || (prevach == '^' && now - prevat > AUTOREPEAT_Y) ){
                beep(300, 100000);
                beep(320, 150000);
                prevat  = now;
                return prevach = '^';
            }

        usleep(10000);
    }
}



static const struct MenuOption *
domenu(const struct Menu *m){
    int nopt  = 0;
    int nopts = 0;

    // count options
    for(nopts=0; m->el[nopts].type; nopts++) {}

    // display in big font, top line: "title (count)     arrow"
    printf("\e[J\e[16m%s(%d)\e[-1G\x84\n\e[16m", m->title, nopts);

    if( m->startval ) nopt = * m->startval;

    while(1){
        // display current choice, bottom line: "choice     arrow"
        printf("\e[0G%s\e[99G%c\xB", m->el[nopt].text,
               (nopt==0 && nopts==1) ? ' ' :
               (nopt==0) ? '\x82' :
               (nopt==nopts-1) ? '\x80' : '\x85'
            );

        // get input
        int ch = get_input();

        switch(ch){
        case '<':
            nopt --;
            if( nopt < 0 ){
                nopt = 0;
                beep(200, 500000);
            }
            clear_line(-1);
            break;
        case '>':
            nopt ++;
            if( nopt > nopts - 1 ){
                nopt = nopts - 1;
                beep(200, 500000);
            }
            clear_line(1);
            break;
        case '^':
            return (void*)-1;
        case '*':
            return (void*) & m->el[nopt];
        }
    }
}



void
menu(const struct Menu *m){
    const struct MenuOption *opt;
    const void *r;

    calibrate();

    while(1){
        if( !m ) return;

        opt = domenu(m);

        if( opt == (void*)-1 || opt == 0 ){
            r = (void*)opt;
        }else{
            switch(opt->type){
            case MTYP_EXIT:
                return;
            case MTYP_MENU:
                r = opt->action;
                break;
            case MTYP_FUNC:
                printf("\e[10m\e[J");
                r = ((void*(*)(int))opt->action)(opt->arg);
                break;
            }
        }

        if( r == 0 ){
            // stay here
        }
        else if( r == (void*)-1 ){
            // go back
            m = m->prev;
        }else{
            // new menu
            m = (const struct Menu*)r;
        }
    }
}



