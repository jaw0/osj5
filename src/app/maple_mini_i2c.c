/*
  Copyright (c) 2013
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2013-Mar-17 23:15 (EDT)
  Function: 
 
  $Id$

*/

#include <stm32f10x.h>
#include <proc.h>
#include "lsm303.h"
#include <i2c.h>

static void
blinky(void){
    int i = (int)currproc % 100;

    while(1){
        GPIOB->ODR = (GPIOB->ODR & 0xFFFFFFFD) | 2;
        usleep( 250000 + i * 100);
        GPIOB->ODR = (GPIOB->ODR & 0xFFFFFFFD) | 0;
        usleep( 250000 );
    }
}

// addr, flags, len, 0, data, cdata[]

i2c_msg lsminit[4] = {
    I2C_MSG_C2( LSM303_ADDRESS_MAG,   0, LSM303_REGISTER_MAG_MR_REG_M,      0x00 ),
    I2C_MSG_C2( LSM303_ADDRESS_MAG,   0, LSM303_REGISTER_MAG_CRA_REG_M,     0x9C ),
    I2C_MSG_C2( LSM303_ADDRESS_MAG,   0, LSM303_REGISTER_MAG_CRB_REG_M,     LSM303_MAGGAIN_1_3 ),
    I2C_MSG_C2( LSM303_ADDRESS_ACCEL, 0, LSM303_REGISTER_ACCEL_CTRL_REG1_A, 0x77 ),
};


char lsmmagbuf[6]; // x, z, y: hi,lo
char lsmaccbuf[6]; // x, y, z: lo,hi
char lsmtmpbuf[2]; // hi,lo

i2c_msg lsmread[6] = {
    I2C_MSG_C1( LSM303_ADDRESS_MAG,   0,             LSM303_REGISTER_MAG_OUT_X_H_M ),
    I2C_MSG_DL( LSM303_ADDRESS_MAG,   I2C_MSGF_READ, 6, lsmmagbuf ),

    I2C_MSG_C1( LSM303_ADDRESS_ACCEL, 0,             LSM303_REGISTER_ACCEL_OUT_X_L_A | 0x80 ),
    I2C_MSG_DL( LSM303_ADDRESS_ACCEL, I2C_MSGF_READ, 6, lsmaccbuf ),

    I2C_MSG_C1( LSM303_ADDRESS_MAG,   0,             LSM303_REGISTER_MAG_TEMP_OUT_H_M ),
    I2C_MSG_DL( LSM303_ADDRESS_MAG,   I2C_MSGF_READ, 2, lsmtmpbuf ),

};

static void
i2ctest(void){
    short mx, my, mz, ax, ay, az, tmp;

    // enable + init
    i2c_xfer(0, 4, lsminit, 1000000);

    while(1){
        int s;
        GPIOB->ODR = (GPIOB->ODR & 0xFFFFFFFD) | 2;

        // read data
        i2c_xfer(0, 6, lsmread, 1000000);

        mx = (lsmmagbuf[0]<<8) | lsmmagbuf[1];
        mz = (lsmmagbuf[2]<<8) | lsmmagbuf[3];
        my = (lsmmagbuf[4]<<8) | lsmmagbuf[5];

        ax = lsmaccbuf[0] | (lsmaccbuf[1]<<8);
        ay = lsmaccbuf[2] | (lsmaccbuf[3]<<8);
        az = lsmaccbuf[4] | (lsmaccbuf[5]<<8);

        tmp = (lsmtmpbuf[0]<<8) | lsmtmpbuf[1];

        printf("ACC: %d,%d,%d; MAG: %d,%d,%d; TMP: %d\n",
               ax,ay,az, mx,my,mz, tmp);

        // Enable the magnetometer 0x1e
        // i2c_write2(0, LSM303_ADDRESS_MAG, LSM303_REGISTER_MAG_MR_REG_M,  0x00);
        // i2c_write2(0, LSM303_ADDRESS_MAG, LSM303_REGISTER_MAG_CRB_REG_M, LSM303_MAGGAIN_1_3);

        // Enable the accelerometer
        // i2c_write2(0, LSM303_ADDRESS_ACCEL, LSM303_REGISTER_ACCEL_CTRL_REG1_A, 0x27);

        // printf("ic2 status %x\n");
        // Set the gain to a known level
        //printf("ic2 status %x\n");


        GPIOB->ODR = (GPIOB->ODR & 0xFFFFFFFD) | 0;

        sleep(5);
    }
}



void
main(void){

    /* Enable everything but wdg */
    RCC->APB2ENR |= 0x38FFFD;
    RCC->APB1ENR |= 0x3afec1ff;
    RCC->AHBENR  |= 0x557;

    /* blink B1 */
    GPIOB->CRL &= ~0xF0;
    GPIOB->CRL |= 0x10;

    /* fork off a blink proc */
    //start_proc( 1024, blinky,  "blinky" );
    //start_proc( 1024, blinky,  "blinky" );
    start_proc( 1024, i2ctest, "i2ctest" );

}
