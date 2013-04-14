/*
  Copyright (c) 2013
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2013-Apr-13 00:07 (EDT)
  Function: wander around. 
 
  $Id$

*/

#include <math.h>
#include <stm32f10x.h>
#include <proc.h>
#include <gpio.h>
#include <pwm.h>
#include <i2c.h>
#include "lsm303.h"
#include "l3g.h"

#define SLOW 200
#define FAST 512

#define K1 0.014082289650914*2
#define K2 0.0120674041980547*2
#define K3 0.959314433470033/5

#define SENSOR_L_S	0
#define SENSOR_L_F	1
#define SENSOR_L_D	2
#define SENSOR_R_D	3
#define SENSOR_R_F	4
#define SENSOR_R_S	5

extern void set_motors(int, int);


// calibration data
static short gyro_off_z;
static short sensor_off[6];


static void
calibrate(){
    int tot = 0;
    int i,n;

    for(n=0; n<10; n++){
        tot += read_gyro();
        usleep(1000);
    }
    gyro_off_z = tot/10;

    for(i=0; i<6; i++){
        tot = 0;
        for(n=0; n<10; n++){
            tot += get_sensor(i);
            usleep(1000);
        }
        sensor_off[i] = tot/10;
    }
}

void
beepboop(){

    freq_set(TIMER_3_3, 600);
    pwm_set(TIMER_3_3,  2);
    usleep(250000);
    freq_set(TIMER_3_3, 400);
    usleep(250000);
    pwm_set(TIMER_3_3,  0);
}

void
dump_sensors(){
    int i;

    for(i=0; i<6; i++){
        int v = get_sensor(i);
        printf("%d:%4d%c", i, v, (i%3 == 2) ? '\n' : ' ');
    }
    sleep(5);
}

void
wait_for_button(void){

    while(1){
        if( gpio_get( GPIO_A14 ) ) break;
        yield();
    }
}


static inline void
beep(int freq, int vol, int dur){
    freq_set(TIMER_3_3, freq);
    pwm_set(TIMER_3_3,  vol);
    usleep(dur);
    pwm_set(TIMER_3_3,  0);
}

void
stop(){
    set_motors(0,0);
    //printf("STOP\n");
}

emergency(const char *msg){
    stop();
    sleep(1);
    printf("\e[J\e[16mUH OH!\n\e[15m%s\n", msg);

    while(1){
        beep(600, 32, 250000);
        usleep(250000);
        beep(150, 32, 250000);
        usleep(250000);
        if( gpio_get( GPIO_A14 ) ){
            usleep(250000);
            break;
        }
    }
}

int
sensor_is_safe(int n){
    int v = get_sensor(n);

    if( (n == SENSOR_L_D) || (n == SENSOR_R_D) ){
        if( (v < 100) || (v < sensor_off[n]/2) ){
            return 0;
        }
        return 1;
    }

    if( v > 2 * sensor_off[n] + 200 ){
        return 0;
    }
    return 1;
}

int
unsafe_bits(){
    int unsafe = 0;
    int i;

    for(i=0; i<6; i++){
        if( !sensor_is_safe(i) ) unsafe |= 1<<i;
    }
    return unsafe;
}

void
reverse_until_safe(){
    utime_t maxtime = get_time() + 1000000;
    int i;

    printf("reverse\n");
    set_motors(-SLOW, -SLOW);

    while( get_time() < maxtime ){
        // until down sensors + front sensors
        if( sensor_is_safe(SENSOR_L_F) && sensor_is_safe(SENSOR_L_D)
            && sensor_is_safe(SENSOR_R_D) && sensor_is_safe(SENSOR_R_F) ){

            usleep(100000);
            stop();
            return;
        }
        usleep(1000);
    }

    // maxtime - uh oh
    emergency("reverse/unsafe");
}

void
turn_right_until_safe(){
    utime_t maxtime = get_time() + 5000000;
    int i;

    printf("turn right\n");
    set_motors(-SLOW, SLOW);

    while( get_time() < maxtime ){
        if( sensor_is_safe(SENSOR_L_S) && sensor_is_safe(SENSOR_L_F)
            && sensor_is_safe(SENSOR_R_D) && sensor_is_safe(SENSOR_R_F) ){
            usleep(100000);
            stop();
            return;
        }
        usleep(1000);
    }

    // maxtime - uh oh
    emergency("turn right/unsafe");
}

void
turn_left_until_safe(){
    utime_t maxtime = get_time() + 5000000;
    int i;

    printf("turn left\n");
    set_motors(SLOW, -SLOW);

    while( get_time() < maxtime ){
        if( sensor_is_safe(SENSOR_R_S) && sensor_is_safe(SENSOR_R_F)
            && sensor_is_safe(SENSOR_R_D) && sensor_is_safe(SENSOR_R_F) ){
            usleep(100000);
            stop();
            return;
        }
        usleep(1000);
    }

    // maxtime - uh oh
    emergency("turn right/unsafe");
}

void
straight_until_unsafe(int speed){
    float preverr=0;
    float prevadj=0;
    int   prevgz=0;
    utime_t prevt;
    int   pos = 0;
    int   unsafecnt = 0;
    int   i;

    printf("straight ahead\n");

    currproc->flags |= PRF_REALTIME;
    currproc->prio  = 0;
    usleep(1);	// sync to proc time
    prevt = get_time();

    while(1){
        utime_t t0 = get_hrtime();
        short gz  = read_gyro() - gyro_off_z;
        pos += (gz + prevgz) / 2 * (t0 - prevt) / 1000;
        float err = -pos;
        float adj = K1 * err - K2 * preverr + K3 * prevadj;

        if( adj > speed )  adj =  speed;
        if( adj < -speed ) adj = -speed;

        set_motors(speed + adj, speed - adj);

        preverr = err;
        prevadj = adj;
        prevgz  = gz;
        prevt   = t0;

        // check sensors
        // RSN - these can pipelined (on/read)
        int un = 0;
        for(i=0; i<6; i++){
            if( ! sensor_is_safe(i) ){
                un ++;
                break;
            }
        }
        if( un ) unsafecnt ++;
        else unsafecnt = 0;

        if( unsafecnt > 3 ) return;
        // RSN - check accelerometer for picked-up

        if( gpio_get( GPIO_A14 ) ) return;

        int t = t0 + 1000 - get_hrtime();
        usleep( t );
    }
}

void
turn(int angle){
    utime_t ts = get_time();
    utime_t prevt = get_hrtime();
    int goal = angle * 32768 / 2000 * 1000;
    int pos  = 0;
    short prevgz = 0;

    printf("turn %d\n", angle);
    if( angle > 0 ){
        set_motors(SLOW, -SLOW);
    }else{
        set_motors(-SLOW, SLOW);
    }

    while(1){
        utime_t t0 = get_hrtime();
        short gz   = read_gyro();
        pos += (gz + prevgz) / 2 * (t0 - prevt) / 1000;
        int err = goal - pos;

        if( err < 1000  && goal > 0 ) break;
        if( err > -1000 && goal < 0 ) break;
        if( get_time() > ts + 5000000 ) break;

        // RSN - check sensors


        int t = t0 + 1000 - get_hrtime();
        // printf(">> %d %d\n", err, gz);
        usleep(t);

        prevgz  = gz;
        prevt   = t0;
    }

    set_motors(0,0);

}

void
wander(){
    int unsafe;

    FILE *f = fopen("dev:oled0", "w");
    STDOUT = f;
    sleep(2);

    while(1){
        extern const char *ident;
        printf("\e[J\e[16m%s\n\e[10mexplore mode\n", ident);
        printf("button LR to start\n");
        wait_for_button();
        beepboop();
        calibrate();

        while(1){
            straight_until_unsafe(FAST);
            unsafe = unsafe_bits();
            printf("unsafe %x\n", unsafe);
            stop();
            beep(400, 8, 120000);

            if( (unsafe & (1<<SENSOR_L_D)) && (unsafe & (1<<SENSOR_R_D))){
                reverse_until_safe();
                turn(rand()%90 + 90 * ((rand()&1) ? -1 : 1));	// any 90-270
                continue;
            }
            if( unsafe & (1<<SENSOR_L_D) ){
                reverse_until_safe();
                turn(-90);
                continue;
            }
            if( unsafe & (1<<SENSOR_R_D) ){
                reverse_until_safe();
                turn(90);
                continue;
            }
            if( (unsafe & (1<<SENSOR_L_F)) && (unsafe & (1<<SENSOR_R_F))){
                reverse_until_safe();
                turn(rand()%90 + 90 * ((rand()&1) ? -1 : 1));	// any 90-270
                continue;
            }
            if( (unsafe & (1<<SENSOR_L_S)) || (unsafe & (1<<SENSOR_L_F))){
                turn_right_until_safe();
                continue;
            }
            if( (unsafe & (1<<SENSOR_R_S)) || (unsafe & (1<<SENSOR_R_F))){
                turn_left_until_safe();
                continue;
            }

            if( gpio_get( GPIO_A14 ) ){
                beep(450, 8, 250000);
                usleep(250000);
                beep(150, 8, 250000);
                usleep(250000);
                break;
            }

            // sensor glitch?
            reverse_until_safe();
            turn(180);
            continue;
        }
    }
}

//dance()



void
main(void){
    int i;

     start_proc( 1024, wander, "wander" );
}

