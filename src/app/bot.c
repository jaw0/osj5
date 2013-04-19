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
#include "menu.h"
#include <setjmp.h>

#define SLOW 200
#define FAST 512
#define ACCEL 100
#define DACCEL 50

#define K1 0.014082289650914*2
#define K2 0.0120674041980547*2
#define K3 0.959314433470033/5

#define CHARIOTS_OF_FIRE        1


#define SENSOR_L_S	0
#define SENSOR_L_F	1
#define SENSOR_L_D	2
#define SENSOR_R_D	3
#define SENSOR_R_F	4
#define SENSOR_R_S	5


extern void set_motors(int, int);
extern void beep(int,int,int);
extern void play(int, const char*);


// calibration data
static short gyro_off_z, accel_off_x, accel_off_y, accel_off_z;
static short sensor_off[6];

static jmp_buf restart;
static utime_t acc_z_time = 0;
int curr_song = 0;
int quietmode = 0;
int volume  = 8;	// music
int ivolume = 8;	// UI


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
    curr_song = 0;
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
        if( get_time() - acc_z_time > 100000 ){
            stop();
            printf("accZ: %d\n", a);
            printf("UP UP and AWAY!\n");
            play(ivolume, "G-2G-2G-2AzG-2G-2G-2A");
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
            speed = maxspeed * taccnt / tacc;

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
        int t = t0 + 1000 - get_hrtime();
        usleep( t );
    }

    // stop
    // RSN - pid
    for(taccnt=tdacc; taccnt >= 0; taccnt--){
        speed = maxspeed * taccnt / tdacc;
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
    int speed;
    int taccnt = 0;

    printf("turn %d\n", angle);
    if( angle > 0 ){
        set_motors(SLOW, -SLOW);
    }else{
        set_motors(-SLOW, SLOW);
    }

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
            speed = maxspeed * taccnt / tacc;

        if( angle > 0 ){
            set_motors(speed, -speed);
        }else{
            set_motors(-speed, speed);
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
        speed = maxspeed * taccnt / tdacc;
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
        if( ax < minz ) minx = ax;
        if( ay < minz ) miny = ay;
        if( az < minz ) minz = az;

        // RR to reset
        if( gpio_get( GPIO_B8 ) ){
            maxz = minz = az;
            maxx = ax;
            maxy = ay;
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
        if( gx < minz ) minx = gx;
        if( gy < minz ) miny = gy;
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

void
maneuver_to_safety(void){

    int unsafe = unsafe_bits();
    printf("unsafe %x\n", unsafe);

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

    while(1){

        switch(dance_moves[i++]){
        case 'a':
            turn( 45, FAST, ACCEL, DACCEL);
            beep(400, volume, 100000);
            break;
        case 'b':
            turn(-45, FAST, ACCEL, DACCEL);
            beep(400, volume, 100000);
            break;
        case 'A':
            turn( 90, FAST, ACCEL, DACCEL);
            beep(440, volume, 100000);
            break;
        case 'B':
            turn(-90, FAST, ACCEL, DACCEL);
            beep(440, volume, 100000);
            break;
        case ' ':
            usleep(500000);
            break;
        default:
            i = 0;
        }

        if( unsafe_bits() ) return;
        check_env();
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
            play(ivolume, "A3A3D-3");
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

    play(ivolume, "A3D-3D+3");

    sleep(1);
    curr_song = 0;
    calibrate();

    while(1){
        dance_until_unsafe();
        stop();
        beep(150, 8, 120000);
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
            play(ivolume, "A3A3D-3");
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

    play(ivolume, "A3D-3D+3");

    sleep(1);
    curr_song = 0;
    calibrate();


    while(1){
        curr_song = CHARIOTS_OF_FIRE;
        straight_until_unsafe(FAST, ACCEL, DACCEL);
        stop();
        beep(150, 8, 120000);
        maneuver_to_safety();
    }
}

extern void sing_song(void);
const struct Menu guitop;
const struct Menu guisett;


const struct Menu guidiag = {
    "Diag Menu", &guitop, {
        { "accel",  MTYP_FUNC, (void*)testaccel },
        { "sensor", MTYP_FUNC, (void*)testsensors },
        { "gyro",   MTYP_FUNC, (void*)testgyro },
        {}
    }
};

const struct Menu guivolume = {
    "Volume", &guisett, {
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
    "Settings", &guitop, {
        { "volume", MTYP_MENU, (void*)&guivolume },
        // RSN speed, accel
        {}
    }
};

const struct Menu guitop = {
    "Main Menu", &guitop, {
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
main(void){
    int i;

    start_proc( 1024, botproc,    "bot" );
    start_proc( 1024, sing_song, "sing" );

}


