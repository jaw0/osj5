/*
  Copyright (c) 2013
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2013-Apr-09 19:58 (EDT)
  Function: init hw
*/


#include <math.h>
#include <stm32f10x.h>
#include <proc.h>
#include <nstdio.h>
#include <gpio.h>
#include <pwm.h>
#include <i2c.h>
#include <adc.h>

#include "lsm303.h"
#include "l3g.h"

static i2c_msg imuinit[] = {
    I2C_MSG_C2( LSM303_ADDRESS_MAG,   0, LSM303_REGISTER_MAG_MR_REG_M,      0 ),
    I2C_MSG_C2( LSM303_ADDRESS_MAG,   0, LSM303_REGISTER_MAG_CRA_REG_M,     0x9C ),		// temp enable, 220Hz (QQQ - data rate?)
    I2C_MSG_C2( LSM303_ADDRESS_MAG,   0, LSM303_REGISTER_MAG_CRB_REG_M,     LSM303_MAGGAIN_1_3 ),

    I2C_MSG_C2( LSM303_ADDRESS_ACCEL, 0, LSM303_REGISTER_ACCEL_CTRL_REG1_A, 0x77 ),		// enable, 400Hz (QQQ - data rate?)
    I2C_MSG_C2( LSM303_ADDRESS_ACCEL, 0, LSM303_REGISTER_ACCEL_CTRL_REG4_A, 8 ),		// high-res (12 bit) mode

    I2C_MSG_C2( L3GD20_ADDRESS,       0, L3G_CTRL_REG1, 0xFF ),					// enable. (QQQ - data rate, bandwidth?)
    I2C_MSG_C2( L3GD20_ADDRESS,       0, L3G_CTRL_REG4, 0x20 ),					// full scale = 2000dps
};

static char magbuf[6];
static char accbuf[6];
static char gyrbuf[6];

static i2c_msg imuread[] = {
    I2C_MSG_C1( LSM303_ADDRESS_MAG,   0,             LSM303_REGISTER_MAG_OUT_X_H_M ),
    I2C_MSG_DL( LSM303_ADDRESS_MAG,   I2C_MSGF_READ, 6, magbuf ),

    I2C_MSG_C1( LSM303_ADDRESS_ACCEL, 0,             LSM303_REGISTER_ACCEL_OUT_X_L_A | 0x80 ),
    I2C_MSG_DL( LSM303_ADDRESS_ACCEL, I2C_MSGF_READ, 6, accbuf ),

    I2C_MSG_C1( L3GD20_ADDRESS,       0,             L3G_OUT_X_L | 0x80 ),
    I2C_MSG_DL( L3GD20_ADDRESS,       I2C_MSGF_READ, 6, gyrbuf ),

};


static const char leds[6] = {
    GPIO_B4 , 	// S L
    GPIO_B3 ,	// F L
    GPIO_A15,	// D L
    GPIO_A12,	// D R
    GPIO_B14,	// F R
    GPIO_B12,	// S R
};

int
get_sensor(int n){
    gpio_set( leds[n] );
    int i; for(i=0; i<50; i++){ asm("nop"); }
    int v = adc_get(n);
    gpio_clear( leds[n] );
    return v;
}

void read_imu(void){

    i2c_xfer(0, 6, imuread, 100000);
}


int
read_gyro(void){

    short gz = (gyrbuf[5]<<8) | gyrbuf[4];
    return gz;
}

int
gyro_z(void){

    short gz = (gyrbuf[5]<<8) | gyrbuf[4];
    return gz;
}
int
gyro_x(void){

    short gz = (gyrbuf[1]<<8) | gyrbuf[0];
    return gz;
}
int
gyro_y(void){

    short gz = (gyrbuf[3]<<8) | gyrbuf[2];
    return gz;
}

int
accel_x(void){
    short ax = ((accbuf[1]<<8) | accbuf[0]);
    ax >>= 4;
    return ax;
}

int
accel_y(void){
    short ay = ((accbuf[3]<<8) | accbuf[2]);
    ay >>= 4;
    return ay;
}

int
accel_z(void){
    short az = ((accbuf[5]<<8) | accbuf[4]);
    az >>= 4;
    return az;
}


// (L)B2=0, (R)B5=1 => forward
void
set_motors(int r, int l){

    if( r < 0 ){
        r = -r;
        gpio_clear( GPIO_B5 );
    }else{
        gpio_set( GPIO_B5 );
    }

    if( l < 0 ){
        l = -l;
        gpio_set( GPIO_B2 );
    }else{
        gpio_clear( GPIO_B2 );
    }

    if( r > 1023 ) r = 1023;
    if( l > 1023 ) l = 1023;

    pwm_set( TIMER_1_1, r );	// right
    pwm_set( TIMER_1_4, l );	// left

}


/****************************************************************/

 void
beep(int freq, int vol, int dur){
    freq_set(TIMER_3_3, freq);
    pwm_set(TIMER_3_3,  vol);
    usleep(dur);
    pwm_set(TIMER_3_3,  0);
}


// sort-of:
//   http://en.wikipedia.org/wiki/Music_Macro_Language#Classical_MML_2
void
play(int vol, const char *tune){
    int freq=0, dur=4, octave=0, sharp=0, ratio=8;

    while( *tune ){
        switch(tolower(*tune)){
        case '+': octave ++;   break;
        case '-': octave --;   break;
        case '>': ratio += 4;  break;	// not standard
        case '<': ratio /= 2;  break;	// not standard
        case '#': sharp ++;    break;
        case '0': dur = 64;    break;
        case '1': dur = 32;    break;
        case '2': dur = 16;    break;
        case '3': dur =  8;    break;
        case '4': dur =  4;    break;
        case '5': dur =  2;    break;
        case '6': dur =  1;    break;
        case 'c': freq = 262;  break;
        case 'd': freq = 294;  break;
        case 'e': freq = 330;  break;
        case 'f': freq = 349;  break;
        case 'g': freq = 392;  break;
        case 'a': freq = 440;  break;
        case 'b': freq = 494;  break;
        default:
            freq = 0;
        }

        if( !tune[1] || isalpha(tune[1]) ){
            if( octave > 0 )
                freq <<= octave;
            if( octave < 0 )
                freq >>= -octave;
            if( ratio < 1 )  ratio = 1;
            if( ratio > 16 ) ratio = 16;

            if( sharp ) freq += (freq * 3900) / 65536;

            if( freq && vol && dur )
                beep(freq, vol, 125000 * ratio / dur);
            else if( dur )
                usleep( 125000 * ratio / dur );

            if( ratio != 16 )
                usleep( 125000 * (16 - ratio) / dur );

            dur    = 4;
            octave = 0;
            sharp  = 0;
            freq   = 0;
            ratio  = 8;
        }

        tune++;
    }
}

/****************************************************************/

void
init_bot_hw(void){

    /* disable jtag to make more A13-15,B3-4 avail */
    AFIO->MAPR   |= 0x4000000;

    gpio_init( GPIO_B1, GPIO_OUTPUT_PP    | GPIO_OUTPUT_10MHZ );	// blinky

    gpio_init( GPIO_B0, GPIO_AF_OUTPUT_PP | GPIO_OUTPUT_10MHZ);		// beeper
    pwm_init(TIMER_3_3, 440, 63);
    pwm_set(TIMER_3_3,  0);

    // buttons
    gpio_init( GPIO_A13, GPIO_INPUT_PU_PD );	// front left
    gpio_init( GPIO_A14, GPIO_INPUT_PU_PD );	// rear L
    gpio_init( GPIO_B8,  GPIO_INPUT_FLOATING );	// rear R
    gpio_clear( GPIO_A13 ); // enable pull downs
    gpio_clear( GPIO_A14 );

    // motors
    gpio_init( GPIO_A8,  GPIO_AF_OUTPUT_PP | GPIO_OUTPUT_10MHZ);
    gpio_init( GPIO_A11, GPIO_AF_OUTPUT_PP | GPIO_OUTPUT_10MHZ);
    pwm_init(TIMER_1_1, 20000, 1024);
    pwm_set( TIMER_1_1, 0);	// right motor
    pwm_set( TIMER_1_4, 0);	// left motor

    // motor dir
    gpio_init( GPIO_B5, GPIO_OUTPUT_PP | GPIO_OUTPUT_10MHZ);	// right motor
    gpio_init( GPIO_B2, GPIO_OUTPUT_PP | GPIO_OUTPUT_10MHZ);	// left motor
    // B2=0, B5=1 => forward
    gpio_set( GPIO_B5 );

    // leds
    gpio_init( GPIO_B3,  GPIO_OUTPUT_PP | GPIO_OUTPUT_50MHZ );
    gpio_init( GPIO_B4,  GPIO_OUTPUT_PP | GPIO_OUTPUT_50MHZ );
    gpio_init( GPIO_A12, GPIO_OUTPUT_PP | GPIO_OUTPUT_50MHZ );
    gpio_init( GPIO_A15, GPIO_OUTPUT_PP | GPIO_OUTPUT_50MHZ );
    gpio_init( GPIO_B12, GPIO_OUTPUT_PP | GPIO_OUTPUT_50MHZ );
    gpio_init( GPIO_B14, GPIO_OUTPUT_PP | GPIO_OUTPUT_50MHZ );

    // ADC
    adc_init( ADC_1_0, 1 );
    adc_init( ADC_1_1, 1 );
    adc_init( ADC_1_2, 1 );
    adc_init( ADC_1_3, 1 );
    adc_init( ADC_1_4, 1 );
    adc_init( ADC_1_5, 1 );
    adc_init( ADC_1_6, 1 );
    adc_init( ADC_1_7, 1 );

    // IMU
    i2c_xfer(0, 7, imuinit, 1000000);
}
