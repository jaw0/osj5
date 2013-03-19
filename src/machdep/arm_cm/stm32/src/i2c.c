/*
  Copyright (c) 2013
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2013-Mar-19 16:48 (EDT)
  Function: 
 
  $Id$

*/
#include <conf.h>
#include <proc.h>
#include <arch.h>
#include <dev.h>
#include <error.h>
#include <clock.h>
#include <nvic.h>

/* NB: stm32f1 + f4 are compat, but at different addrs */
#include <stm32.h>


static I2C_TypeDef*
_i2c_addr(dev){
    if( dev == 0 ) return I2C1;
    if( dev == 1 ) return I2C2;
    // ...
    PANIC("invalid i2c device");
}

int
i2c_init(struct Device_Conf *dev){
    int i    = dev->unit;
    I2C_TypeDef *addr = _i2c_addr(i);

    bootmsg("%s unit %d at io 0x%xn", dev->name, i, addr);

}

#if 0
_i2c_reset(dev){
}
_i2c_start(dev, addr){
}
_i2c_stop(dev){
}
_i2c_put(dev, dat){
}
_i2c_get(dev){
}

/****************************************************************/

i2c_write(dev, addr, data*, len){
}

i2c_read(dev, addr, data*, len){
}

i2c_write2(dev, addr, reg, data){
}

i2c_read2(dev, addr, reg, *data){
}


#endif
