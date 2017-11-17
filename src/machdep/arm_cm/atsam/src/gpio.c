/*
  Copyright (c) 2013
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2013-Mar-24 12:10 (EDT)
  Function: gpio pins

*/

#include <conf.h>
#include <proc.h>
#include <arch.h>
#include <atsam.h>
#include <gpio.h>
#include <pmc.h>

void
_enable_pio(int io){

    // enable the pio
    switch(io){
    case 0:
        pmc_enable( ID_PIOA );
        break;
    case 1:
        pmc_enable( ID_PIOB );
        break;
    case 2:
        pmc_enable( ID_PIOC );
        break;
    case 3:
        pmc_enable( ID_PIOD );
        break;
    case 4:
        pmc_enable( ID_PIOE );
        break;
    }
}

void
_unprotect(Pio *addr){
    addr->PIO_WPMR = 0x50494F << 8;
}

void
_protect(Pio *addr){
    addr->PIO_WPMR = (0x50494F << 8) | 1;

}

void
gpio_init(uint32_t pin, uint32_t mode){

    int plx = splhigh();
    int io  = pin >> 5;

    Pio *addr = _gpio_addr(pin);
    pin &= 0x1F;

    _unprotect(addr);

    // (1:input schmitt) (1:input deglitch) (2:pull up/dn) (1:push/pull,open-drain) (2:AF) (2:mode)

    switch( mode & 3 ){
    case GPIO_INPUT:
        _enable_pio(io);
        // fall through
    case GPIO_ANALOG:
        addr->PIO_PER = 1<<pin;
        addr->PIO_ODR = 1<<pin;
        break;
    case GPIO_OUTPUT:
        _enable_pio(io);
        addr->PIO_PER  = 1<<pin;
        addr->PIO_OER  = 1<<pin;
        addr->PIO_OWER = 1<<pin;	// permit writes via odsr
        break;
    default:
        addr->PIO_PDR = 1<<pin;
        addr->PIO_ODR = 1<<pin;

        switch( mode & 0xF ){
        case GPIO_AF_A:
            addr->PIO_ABCDSR[0] &= ~(1<<pin);
            addr->PIO_ABCDSR[1] &= ~(1<<pin);
            break;
        case GPIO_AF_B:
            addr->PIO_ABCDSR[0] |=   1<<pin;
            addr->PIO_ABCDSR[1] &= ~(1<<pin);
            break;
        case GPIO_AF_C:
            addr->PIO_ABCDSR[0] &= ~(1<<pin);
            addr->PIO_ABCDSR[1] |=  1<<pin;
            break;
        case GPIO_AF_D:
            addr->PIO_ABCDSR[0] |=   1<<pin;
            addr->PIO_ABCDSR[1] |=   1<<pin;
            break;

        }
        break;
    }

    // push-pull or open-drain
    if( mode & GPIO_OPEN_DRAIN )
        addr->PIO_MDER |= 1<<pin;
    else
        addr->PIO_MDDR |= 1<<pin;

    // pull up, pull down?
    if( mode & GPIO_PULL_UP )
        addr->PIO_PUER |= 1<<pin;
    else
        addr->PIO_PUDR |= 1<<pin;

    if( mode & GPIO_PULL_DN )
        addr->PIO_PPDER |= 1<<pin;
    else
        addr->PIO_PPDDR |= 1<<pin;

    // input filters
    if( mode & GPIO_SCHMITT )
        addr->PIO_SCHMITT |= 1<<pin;
    else
        addr->PIO_SCHMITT &= ~(1<<pin);

    // ...


    //_protect(addr);
    splx(plx);
}

/*
PIO Enable Register
PIO_PER

Output Enable Register
PIO_OER

Output Disable Register
PIO_ODR

Glitch Input Filter Enable Register
PIO_IFER
Glitch Input Filter Disable Register
PIO_IFDR

Multi-driver Enable Register
PIO_MDER
Multi-driver Disable Register
PIO_MDDR

Pull-up Enable Register
PIO_PUER
Pull-up Disable Register
PIO_PUDR

Pull-down Enable Register
PIO_PPDER
Pull-down Disable Register
PIO_PPDDR

Peripheral Select Register 1
PIO_ABCDSR1
Peripheral Select Register 2
PIO_ABCDSR2

Schmitt Trigger Register
PIO_SCHMITT

PIO Enable Register
PIO_PER
*/



