/*
  Copyright (c) 2015
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2015-Oct-27 21:26 (EDT)
  Function: 

*/

#ifndef __atsams70_serial_impl_h__
#define __atsams70_serial_impl_h__

static inline void serial_pins_init(int i, int altpins){

    switch(i){
    case 0:
        pmc_enable( ID_UART0 );
        gpio_init( GPIO_A9,  GPIO_AF_A );
        gpio_init( GPIO_A10, GPIO_AF_A );
        break;

    default:
        PANIC("invalid serial");
        break;
    }
}

#endif /* __stsams70_serial_impl_h__ */

