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
#include <msgs.h>
#include <nstdio.h>
#include <gpio.h>
#include <pwm.h>
#include <i2c.h>
#include "lsm303.h"
#include "l3g.h"
#include "menu.h"
#include <setjmp.h>
#include <userint.h>

#define SLOW 200
#define FAST 512
#define ACCEL 100
#define DACCEL 50

#define K1 0.014082289650914*2
#define K2 0.0120674041980547*2
#define K3 0.959314433470033/5

#define SENSOR_L_S	0
#define SENSOR_L_F	1
#define SENSOR_L_D	2
#define SENSOR_R_D	3
#define SENSOR_R_F	4
#define SENSOR_R_S	5

#define SIGNAL_QUIET	16


extern void set_motors(int, int);
extern void beep(int,int,int);
extern void play(int, const char*);


// calibration data
static short gyro_off_z, accel_off_x, accel_off_y, accel_off_z;
static short sensor_off[6];

static jmp_buf restart;
static utime_t acc_z_time = 0;
static const char *curr_song = 0;
static proc_t song_proc = 0;

int volume_setting = 3;
int volume  = 8;	// music
int ivolume = 8;	// UI

int prev_maneuver  = 0;


#define SONG_MENU	1
#define SONG_GO		2
#define SONG_UNSAFE	3
#define SONG_UPAWAY	4
#define SONG_CHARIOTS	6
#define SONG_CUCARACHA	7

static const char const *songs[] = {
    "[32 c>>7 b>>7] z0",	// ray gun
    "A3A3D-3",			// menu
    "A3D-3D+3",			// go
    "g4e4f4f-3",		// unsafe
    "G-4G-4G-4AzG-4G-4G-4A",	// upside down
    "[4 D+>D->]",		// emergency

    "T66 c3 g3~a3~b3~ g e e3 c3 g3~a3~b3~ g g g3 c3 g3~a3~b3~ g e e3 e3 f3~e3~d3~ c1 c c>3~b3~a3~ b3 b4 g4 a3 a4 f4 g3 c>3~b3~a3~ b c>3 c>3~b3~a3~ b3 b4 g4 a3 a4 f4 g3 g4 e4 f3~e3~d3~ c1",	// chariots of fire

    // la cucaracha
    "T160 | c c3 f3 f3 a3 a3 S c+ a S c+ c+3 d+3 c+3 b3 a3 S b g S "
    "| c c3 e3 e3 g3 g3 S b g S c+ d+3 c+3 b3 a3 g3 S [2 a f z3 ] f S "
    "| f3>>f3z3 a3 z3 c3 c3 c3 S f3>>f3z3 a3 S f3 f3 f3 e3 e3 d3 d3 S c1 z3 c3 c3 c3 S "
    "| e3>>e3z3 g3 z3 c3 c3 c3 S e3>>e3z3 g3 S c+ d+3 c+3 b3 a3 g3 S [2 f z3>>z3z3 ] S ",


};


#define STOP_SONG()	ksendmsg(song_proc, SIGNAL_QUIET)
#define START_SONG(s)	curr_song = s
#define SYNC_SONG()	wakeup( &play )

static void
calibrate(){
    int tot = 0;
    int i,n;

    for(n=0; n<10; n++){
        read_imu();
        tot += read_gyro();
        usleep(1000);
    }
    gyro_off_z = tot/10;

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

    for(i=0; i<6; i++){
        tot = 0;
        for(n=0; n<10; n++){
            tot += get_sensor(i);
            usleep(1000);
        }
        sensor_off[i] = tot/10;
    }
}


void *
set_volume(int v){
    if( v > 5 ) v = 5;
    volume_setting = v;
    ivolume = volume = 1<<v;
    if( ivolume < 2 ) ivolume = 2;
    beep(200, volume, 500000);
    return (void*)-1;
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

int
check_button(void){
    if( gpio_get( GPIO_A14 ) ){
        play(ivolume, "A3D-3");
        while( gpio_get( GPIO_A14 ) ) yield();
        return 1;
    }
    return 0;
}

void
wait_for_button(void){

    while(1){
        if( gpio_get( GPIO_A14 ) ) break;
        yield();
    }
}

int
wait_for_Rbutton(){
    while(1){
        if( gpio_get( GPIO_A14 ) ) return 'L';
        if( gpio_get( GPIO_B8  ) ) return 'R';
        yield();
    }
}

void
stop(){
    set_motors(0,0);
    STOP_SONG();
    //printf("STOP\n");
}

int
check_env(void){
    int a;

    if( check_button() ){
        stop();
        longjmp(restart, 1);
    }

    a = accel_z() - accel_off_z;

    if( a < 0 ){
        if( ! acc_z_time ) acc_z_time = get_time();
        if( get_time() - acc_z_time > 250000 ){
            stop();
            printf("accZ: %d\n", a);
            printf("UP UP and AWAY!\n");
            play(ivolume, songs[SONG_UPAWAY] );
            longjmp(restart, 1);
        }
    }else{
        acc_z_time = 0;
    }

    // RSN - gyro x, y

}

emergency(const char *msg){
    stop();
    sleep(1);
    printf("\e[J\e[16mUH OH!\n\e[15m%s\n", msg);

    while(1){
        play(32, "D+>D->");
        read_imu();
        check_env();
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
    utime_t maxtime = get_time() + 2000000;
    int i;

    printf("reverse\n");
    set_motors(-SLOW, -SLOW);

    while( get_time() < maxtime ){
        read_imu();
        // until down sensors + front sensors
        if( sensor_is_safe(SENSOR_L_F) && sensor_is_safe(SENSOR_L_D)
            && (sensor_is_safe(SENSOR_L_S) || sensor_is_safe(SENSOR_L_S))
            && sensor_is_safe(SENSOR_R_D) && sensor_is_safe(SENSOR_R_F) ){

            usleep(200000);
            stop();
            return;
        }

        check_env();
        usleep(1000);
    }

    // maxtime - uh oh
    emergency("reverse/unsafe");
}

void
reverse_a_bit(){
    utime_t maxtime = get_time() + 500000;
    int i;

    printf("reverse\n");
    set_motors(-SLOW, -SLOW);

    while( get_time() < maxtime ){
        read_imu();

        if( unsafe_bits() ){
            stop();
            return;
        }

        check_env();
        usleep(1000);
    }

}


void
turn_right_until_safe(){
    utime_t maxtime = get_time() + 5000000;
    int i;

    printf("turn right\n");
    set_motors(-SLOW, SLOW);

    while( get_time() < maxtime ){
        read_imu();
        if( sensor_is_safe(SENSOR_L_S) && sensor_is_safe(SENSOR_L_F)
            && sensor_is_safe(SENSOR_R_D) && sensor_is_safe(SENSOR_R_F) ){

            usleep(100000);
            stop();
            return;
        }

        check_env();
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
        read_imu();
        if( sensor_is_safe(SENSOR_R_S) && sensor_is_safe(SENSOR_R_F)
            && sensor_is_safe(SENSOR_R_D) && sensor_is_safe(SENSOR_R_F) ){

            usleep(100000);
            stop();
            return;
        }

        check_env();
        usleep(1000);
    }

    // maxtime - uh oh
    emergency("turn right/unsafe");
}

void
straight_until_unsafe(int maxspeed, int tacc, int tdacc){
    float preverr=0;
    float prevadj=0;
    int   prevgz=0;
    utime_t prevt;
    int   pos = 0;
    int   unsafecnt = 0;
    int   stuckcnt = 0;
    int   taccnt = 0;
    int   speed;
    int   i;

    printf("straight ahead\n");

    currproc->flags |= PRF_REALTIME;
    currproc->prio  = 0;
    usleep(1);	// sync to proc time
    prevt = get_time();

    while(1){
        utime_t t0 = get_hrtime();
        read_imu();
        short gz  = read_gyro() - gyro_off_z;
        pos += (gz + prevgz) / 2 * (t0 - prevt) / 1000;
        float err = -pos;
        float adj = K1 * err - K2 * preverr + K3 * prevadj;

        if( taccnt >= tacc )
            speed = maxspeed;
        else
            speed = (maxspeed * taccnt) / tacc;

        if( adj >= maxspeed *3/4 || adj <= -maxspeed*3/4 ){
            stuckcnt ++;
        }else{
            stuckcnt = 0;
        }
        if( adj > speed )  adj =  speed;
        if( adj < -speed ) adj = -speed;

        set_motors(speed + adj, speed - adj);

        preverr = err;
        prevadj = adj;
        prevgz  = gz;
        prevt   = t0;

        // check sensors
        // RSN - these can pipelined (on/read)

        if( unsafe_bits() ) unsafecnt ++;
        else unsafecnt = 0;
        if( unsafecnt > 3 ) return;

        check_env();

        // seem to be stuck
        if( stuckcnt > 1000 ) return;

        taccnt ++;
        if( taccnt > 1000 ) prev_maneuver = 0;
        int t = t0 + 1000 - get_hrtime();
        usleep( t );
    }

    // stop
    // RSN - pid
    for(taccnt=tdacc; taccnt >= 0; taccnt--){
        speed = (maxspeed * taccnt) / tdacc;
        set_motors(speed, speed);
        usleep(1000);
    }
    set_motors(0,0);
}

void
turn(int angle, int maxspeed, int tacc, int tdacc){
    utime_t ts = get_time();
    utime_t prevt = get_hrtime();
    int goal = angle * 32768 / 2000 * 1000;
    int pos  = 0;
    int accpos = 0;
    short prevgz = 0;
    int   unsafecnt = 0;
    int speed, comp;
    int taccnt = 0;

    printf("turn %d\n", angle);

    while(1){
        utime_t t0 = get_hrtime();
        read_imu();
        short gz   = read_gyro();
        pos += (gz + prevgz) / 2 * (t0 - prevt) / 1000;
        int err = goal - pos;

        if( taccnt >= tacc ){
            speed = maxspeed;
            if( !accpos ){
                accpos = pos;
                // it will take about this much to stop
                goal -= accpos * ACCEL / DACCEL;
            }
        }else
            speed = (maxspeed * taccnt) / tacc;

        // we are front heavy, apply centrifugal compensation
        comp = speed / 5;

        if( angle > 0 ){
            set_motors(speed - comp, -speed - comp);
        }else{
            set_motors(-speed - comp, speed - comp);
        }

        if( err < 1000  && goal > 0 ) break;
        if( err > -1000 && goal < 0 ) break;
        if( get_time() > ts + 5000000 ) break;

        if( unsafe_bits() ) unsafecnt ++;
        else unsafecnt = 0;

        if( unsafecnt > 3 ) break;

        check_env();

        int t = t0 + 1000 - get_hrtime();
        // printf(">> %d %d\n", err, gz);
        usleep(t);

        prevgz  = gz;
        prevt   = t0;
        taccnt ++;
    }

    for(taccnt=tdacc; taccnt >= 0; taccnt--){
        speed = (maxspeed * taccnt) / tdacc;
        set_motors(speed, speed);
        usleep(1000);
    }
    set_motors(0,0);

}


int
testsensors(){
    int i;

    printf("\e[Jsensor test mode\n");
    sleep(2);

    while(1){
        gpio_clear( GPIO_B1 );

        printf("\e[J    sensors\n");

        for(i=0; i<6; i++){
            int v = get_sensor(i);
            printf("%d:%4d%c", i, v, (i%3 == 2) ? '\n' : ' ');
            printf("\xB");
        }

        // LR - return
        if( check_button() ) return 0;

        gpio_set( GPIO_B1 );
        usleep( 25000 );
    }
}

int
testaccel(){
    int ax, ay, az;
    int maxx = 0, minx = 65535;
    int maxy = 0, miny = 65535;
    int maxz = 0, minz = 65535;

    printf("\e[Jaccel test mode\n");
    sleep(2);

    while(1){
        gpio_clear( GPIO_B1 );
        read_imu();
        ax = accel_x();
        ay = accel_y();
        az = accel_z();

        if( ax > maxx ) maxx = ax;
        if( ay > maxy ) maxy = ay;
        if( az > maxz ) maxz = az;
        if( ax < minx ) minx = ax;
        if( ay < miny ) miny = ay;
        if( az < minz ) minz = az;

        // RR to reset
        if( gpio_get( GPIO_B8 ) ){
            maxz = minz = az;
            minx = maxx = ax;
            miny = maxy = ay;
        }

        // LR - return
        if( check_button() ) return 0;

        printf("\e[J    accel\n");
        printf("x:%5d %5d %4d\ny:%5d %5d %4d\nz:%5d %5d %4d\n",
               ax, minx, maxx, ay, miny, maxy, az, minz, maxz);

        gpio_set( GPIO_B1 );
        usleep(25000);
    }
}

int
testgyro(){
    int gx, gy, gz;
    int maxx = 0, minx = 65535;
    int maxy = 0, miny = 65535;
    int maxz = 0, minz = 65535;

    printf("\e[Jgyro test mode\n");
    sleep(2);

    while(1){
        gpio_clear( GPIO_B1 );
        read_imu();
        gx = gyro_x();
        gy = gyro_y();
        gz = gyro_z();

        if( gx > maxx ) maxx = gx;
        if( gy > maxy ) maxy = gy;
        if( gz > maxz ) maxz = gz;
        if( gx < minx ) minx = gx;
        if( gy < miny ) miny = gy;
        if( gz < minz ) minz = gz;

        // RR - reset
        if( gpio_get( GPIO_B8 ) ){
            maxx = minx = gx;
            maxy = miny = gy;
            maxz = minz = gz;
        }

        // LR - return
        if( check_button() ) return 0;

        printf("\e[J    gyros\n");
        printf("x:%5d %5d %4d\ny:%5d %5d %4d\nz:%5d %5d %4d\n",
               gx, minx, maxx, gy, miny, maxy, gz, minz, maxz);

        gpio_set( GPIO_B1 );
        usleep(25000);
    }
}

static short rawdata[1024];
int
testacgo(void){
    int i = 0;

    printf("acc profile\npress LR\n");
    wait_for_button();
    while( gpio_get( GPIO_A14 ) ) yield();

    printf("away!\n");
    play(8, "dca1");

    while( 1 ){
        utime_t t = get_time();
        int speed;

        if( i < 100 ){
            // accel
            speed = (768 * i) / 100;
        }else if( i > 900 ){
            speed = 0;
        }else if( i > 800 ){
            // decel
            speed = (768 * (900 - i)) / 100;
        }else{
            speed = 768;
        }

        set_motors(speed, speed);

        read_imu();
        rawdata[i++] = - accel_x();
        if( i >= 1024 ) break;
        usleep( t + 1000 - get_time() );
    }

    set_motors(0,0);
    printf("done\nLR to dump\n");
    wait_for_button();

    for(i=0; i<1024; i++)
        fprintf(STDERR, "%d\n", rawdata[i]);

    return 0;
}

int
testplay(int n){

    sleep(1);
    play(4, songs[n]);
    return 0;
}

int
powerlevel(void){
    int l = adc_get(7);

    float v = 3.3 * l
        * 2.05607	// the resistors are not exactly equal
        / 4096.0;

    float p = (v - 3.2) * 100.0;
    if( p < 0 )   p = 0;
    if( p > 100 ) p = 100;

    printf("\e[15m   battery\n %.2fV  %d%%\n", v, (int)p);
    sleep(3);
}


void
maneuver_to_safety(void){

    int unsafe = unsafe_bits();
    printf("unsafe %x\n", unsafe);

    if( prev_maneuver ){
        reverse_until_safe();
        reverse_a_bit();
    }

    prev_maneuver = 1;

    if( (unsafe & (1<<SENSOR_L_D)) && (unsafe & (1<<SENSOR_R_D))){
        reverse_until_safe();

        if( (unsafe & (1<<SENSOR_L_S)) && ! (unsafe & (1<<SENSOR_R_S)) ){
            // right side clear, left blocked
            turn(-90, SLOW, ACCEL, DACCEL);
        }
        else if( (unsafe & (1<<SENSOR_R_S)) && ! (unsafe & (1<<SENSOR_L_S)) ){
            // left side clear, right blocked
            turn(90, SLOW, ACCEL, DACCEL);
        }
        else{
            turn(rand()%90 + 90 * ((rand()&1) ? -1 : 1), SLOW, ACCEL, DACCEL);	// any 90-270
        }
        return;
    }
    if( unsafe & (1<<SENSOR_L_D) ){
        reverse_until_safe();
        turn(-90, SLOW, ACCEL, DACCEL);
        return;
    }
    if( unsafe & (1<<SENSOR_R_D) ){
        reverse_until_safe();
        turn(90, SLOW, ACCEL, DACCEL);
        return;
    }
    if( (unsafe & (1<<SENSOR_L_F)) && (unsafe & (1<<SENSOR_R_F))){
        reverse_until_safe();

        if( (unsafe & (1<<SENSOR_L_S)) && ! (unsafe & (1<<SENSOR_R_S)) ){
            turn(-90, SLOW, ACCEL, DACCEL);
        }
        else if( (unsafe & (1<<SENSOR_R_S)) && ! (unsafe & (1<<SENSOR_L_S)) ){
            turn(90, SLOW, ACCEL, DACCEL);
        }
        else{
            turn(rand()%90 + 90 * ((rand()&1) ? -1 : 1), SLOW, ACCEL, DACCEL);	// any 90-270
        }
        return;
    }
    if( (unsafe & (1<<SENSOR_L_S)) && (unsafe & (1<<SENSOR_R_S)) ){
        reverse_until_safe();
        turn(rand()%60 + 120 * ((rand()&1) ? -1 : 1), SLOW, ACCEL, DACCEL);	// any 120-240
        return;
    }
    if( (unsafe & (1<<SENSOR_L_S)) || (unsafe & (1<<SENSOR_L_F))){
        turn_right_until_safe();
        turn( - rand() % 90, SLOW, ACCEL, DACCEL );
        return;
    }
    if( (unsafe & (1<<SENSOR_R_S)) || (unsafe & (1<<SENSOR_R_F))){
        turn_left_until_safe();
        turn( rand() % 90, SLOW, ACCEL, DACCEL );
        return;
    }

    // sensor glitch?
    reverse_until_safe();
    turn(180, SLOW, ACCEL, DACCEL);
}


static const char *dance_moves = "abaBA babAB babAB abaBA ";

void
dance_until_unsafe(void){
    int i = 0;
    int j;

    while(1){
        switch(dance_moves[i++]){
        case 'a':
            SYNC_SONG();
            turn( 45, FAST, ACCEL, DACCEL);
            break;
        case 'b':
            SYNC_SONG();
            turn(-45, FAST, ACCEL, DACCEL);
            break;
        case 'A':
            SYNC_SONG();
            turn( 90, FAST, ACCEL, DACCEL);
            break;
        case 'B':
            SYNC_SONG();
            turn(-90, FAST, ACCEL, DACCEL);
            break;
        case ' ':
            for(i=0; i<50; i++){
                usleep(10000);
                read_imu();
                check_env();
            }
            break;
        default:
            i = 0;
        }

        if( unsafe_bits() ) return;
        check_env();

        prev_maneuver = 0;
    }
}

int
dance(){

    if( setjmp(restart) ){
        stop();
        printf("\e[J\e[15mdance mode\n\e[10m");
        printf("button LR to start\n");
        printf("button RR for menu\n");
        int b = wait_for_Rbutton();

        if( b == 'R' ){
            // main menu
            play(ivolume, songs[SONG_MENU]);
            // debounce
            while(1){
                if( !gpio_get(GPIO_B8) ) break;
                yield();
            }
            usleep(10000);
            return 0;
        }
    }else{
        printf("\e[J\e[15mdance mode\n\e[10m");
    }

    STOP_SONG();
    play(ivolume, songs[SONG_GO]);
    sleep(1);
    calibrate();

    while(1){
        START_SONG( songs[SONG_CUCARACHA] );
        dance_until_unsafe();
        stop();
        play(8, songs[SONG_UNSAFE]);
        maneuver_to_safety();
    }
}


int
wander(){

    if( setjmp(restart) ){
        stop();
        printf("\e[J\e[15mexplore mode\n\e[10m");
        printf("button LR to start\n");
        printf("button RR for menu\n");
        int b = wait_for_Rbutton();

        if( b == 'R' ){
            // main menu
            play(ivolume, songs[SONG_MENU]);
            // debounce
            while(1){
                if( !gpio_get(GPIO_B8) ) break;
                yield();
            }
            usleep(10000);
            return 0;
        }
    }else{
        printf("\e[J\e[15mexplore mode\n\e[10m");
    }

    STOP_SONG();
    play(ivolume, songs[SONG_GO]);
    sleep(1);
    calibrate();

    while(1){
        START_SONG( songs[SONG_CHARIOTS] );
        straight_until_unsafe(FAST, ACCEL, DACCEL);
        stop();
        play(8, songs[SONG_UNSAFE]);
        maneuver_to_safety();
    }
}

extern void sing_song(void);
const struct Menu guitop, guisett, guidiag;


const struct Menu guiplay = {
    "Song", &guidiag, 0, {
        { "raygun",    MTYP_FUNC, (void*)testplay, 0 },
        { "menu",      MTYP_FUNC, (void*)testplay, 1 },
        { "start",     MTYP_FUNC, (void*)testplay, 2 },
        { "unsafe",    MTYP_FUNC, (void*)testplay, 3 },
        { "up/down",   MTYP_FUNC, (void*)testplay, 4 },
        { "emergency", MTYP_FUNC, (void*)testplay, 5 },
        { "chariots",  MTYP_FUNC, (void*)testplay, 6 },
        { "cucaracha", MTYP_FUNC, (void*)testplay, 7 },
        {}
    }
};

const struct Menu guidiag = {
    "Diag Menu", &guitop, 0, {
        { "power",   MTYP_FUNC, (void*)powerlevel },
        { "accel",   MTYP_FUNC, (void*)testaccel },
        { "sensor",  MTYP_FUNC, (void*)testsensors },
        { "gyro",    MTYP_FUNC, (void*)testgyro },
        { "music",   MTYP_MENU, (void*)&guiplay },
        { "accprof", MTYP_FUNC, (void*)testacgo },
        {}
    }
};

const struct Menu guivolume = {
    "Volume", &guisett, &volume_setting, {
        { "0", MTYP_FUNC, (void*)set_volume, 0 },
        { "1", MTYP_FUNC, (void*)set_volume, 1 },
        { "2", MTYP_FUNC, (void*)set_volume, 2 },
        { "3", MTYP_FUNC, (void*)set_volume, 3 },
        { "4", MTYP_FUNC, (void*)set_volume, 4 },
        { "5", MTYP_FUNC, (void*)set_volume, 5 },
        {}
    }
};

const struct Menu guisett = {
    "Settings", &guitop, 0, {
        { "volume", MTYP_MENU, (void*)&guivolume },
        // RSN speed, accel
        {}
    }
};

const struct Menu guitop = {
    "Main Menu", &guitop, 0, {
        { "explore",  MTYP_FUNC, (void*)wander   },
        { "dance",    MTYP_FUNC, (void*)dance    },
        { "diag",     MTYP_MENU, (void*)&guidiag },
        { "settings", MTYP_MENU, (void*)&guisett },
        {}
    }
};




void
botproc(void){

    FILE *f = fopen("dev:oled0", "w");
    STDOUT = f;

    sleep(2);
    menu( &guitop );
}

void
sing_song(void){
    Catchframe cf;
    int cn = 0;


    CATCHL(cf, SIGNAL_QUIET, quiet);
    if( 0 ){
    quiet:
        curr_song = 0;
        beep(0,0,0);
    }

    while(1){
        if( ! curr_song || ! volume ){
            usleep( 10000 );
            continue;
        }

        play( volume, curr_song );
    }
}


void
main(void){
    int i;

    start_proc( 1024, botproc,    "bot" );
    song_proc = start_proc( 1024, sing_song, "sing" );

}

