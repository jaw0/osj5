/*
  Copyright (c) 2013
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2013-Mar-19 16:48 (EDT)
  Function: i2c
*/

// parts adapted from:
//   https://github.com/leaflabs/libmaple/blob/master/libmaple/i2c.c
    /**********************************************************************
     * The MIT License
     *
     * Copyright (c) 2010 Perry Hung.
     * Copyright (c) 2012 LeafLabs, LLC.
     *
     * Permission is hereby granted, free of charge, to any person
     * obtaining a copy of this software and associated documentation
     * files (the "Software"), to deal in the Software without
     * restriction, including without limitation the rights to use, copy,
     * modify, merge, publish, distribute, sublicense, and/or sell copies
     * of the Software, and to permit persons to whom the Software is
     * furnished to do so, subject to the following conditions:
     *
     * The above copyright notice and this permission notice shall be
     * included in all copies or substantial portions of the Software.
     *
     * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
     * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
     * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
     * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
     * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
     * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
     * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
     * SOFTWARE.
     **********************************************************************/


#include <conf.h>
#include <proc.h>
#include <arch.h>
#include <locks.h>
#include <dev.h>
#include <error.h>
#include <clock.h>
#include <i2c.h>
#include <gpio.h>
#include <nvic.h>

/* NB: stm32f1 + f4 are compat, but at different addrs */
#include <stm32.h>

#define CFFLAGS_ALTPINS	3	// 2 bits of flags - alt set of pins

// define in config file:
//#define I2C_VERBOSE

#define CR1_PE		1
#define CR1_START	0x100
#define CR1_STOP	0x200
#define CR1_ACK		0x400
#define CR1_PEC		0x1000

#define CR2_IRQ_BUF	0x400
#define CR2_IRQ_EVT     0x200
#define CR2_IRQ_ERR     0x100

#define SR1_SB		1
#define SR1_ADDR	2
#define SR1_BTF		4
#define SR1_RXNE	0x40
#define SR1_TXE		0x80

#define SR2_BUSY	2

#define I2C_STATE_DISABLED          0
#define I2C_STATE_IDLE              1
#define I2C_STATE_XFER_DONE         2
#define I2C_STATE_BUSY              3
#define I2C_STATE_ERROR             -1


static u_long cur_crumb = 0;

#ifdef I2C_VERBOSE
struct crumb {
    const char *event;
    int arg0;
    int arg1;
};

#define NR_CRUMBS       128
static struct crumb crumbs[NR_CRUMBS];

static inline void
_i2c_drop_crumb(const char *event, u_long arg0, u_long arg1) {
    if (cur_crumb < NR_CRUMBS) {
        struct crumb *crumb = &crumbs[cur_crumb++];
        crumb->event = event;
        crumb->arg0 = arg0;
        crumb->arg1 = arg1;
        //kprintf("%s\n", event);
    }
}
#define I2C_CRUMB(event, arg0, arg1) _i2c_drop_crumb(event, arg0, arg1)
#else
#define I2C_CRUMB(event, arg0, arg1)
#endif


struct I2CInfo {
    I2C_TypeDef 	*addr;
    int 	  	irq;

    lock_t		lock;
    int			state;
    u_long		errorflags;
    i2c_msg		*msg;
    int			num_msg;

} i2cinfo[ N_I2C ];


int
i2c_init(struct Device_Conf *dev){
    int i    = dev->unit;
    I2C_TypeDef *addr;
    int tmp;

    bzero(i2cinfo+i, sizeof(struct I2CInfo));
    int altpins = dev->flags & CFFLAGS_ALTPINS;

#if defined(PLATFORM_STM32F1)
    switch(i){
    case 0:
        // CL=B6, DA=B7
        i2cinfo[i].addr = addr = I2C1;
        i2cinfo[i].irq  = IRQ_I2C1_EV;

        RCC->APB2ENR |= 1;		// AFI
        RCC->APB1ENR |= 0x200000;	// i2c1
        gpio_init( GPIO_B6, GPIO_AF_OUTPUT_OD | GPIO_OUTPUT_10MHZ );
        gpio_init( GPIO_B7, GPIO_AF_OUTPUT_OD | GPIO_OUTPUT_10MHZ );

        break;
    case 1:
        // CL=B10, DA=B11
        i2cinfo[i].addr = addr = I2C2;
        i2cinfo[i].irq  = IRQ_I2C2_EV;

        RCC->APB2ENR |= 1;		// AFI
        RCC->APB1ENR |= 0x400000;	// i2c2
        gpio_init( GPIO_B10, GPIO_AF_OUTPUT_OD | GPIO_OUTPUT_10MHZ );
        gpio_init( GPIO_B11, GPIO_AF_OUTPUT_OD | GPIO_OUTPUT_10MHZ );

        break;
    default:
        PANIC("invalid i2c device");
    }
#elif defined(PLATFORM_STM32F4)

    int mode = GPIO_AF(4) | GPIO_OPEN_DRAIN | GPIO_SPEED_25MHZ ;
#  ifdef I2C_PULLUPS
    mode |= GPIO_PULL_UP;
#  endif

    switch(i){
    case 0:
        // CL=B6, DA=B7 or CL=B8, DA=B9
        i2cinfo[i].addr = addr = I2C1;
        i2cinfo[i].irq  = IRQ_I2C1_EV;
        RCC->APB1ENR   |= 1<<21;
        if( altpins ){
            gpio_init( GPIO_B8, mode );
            gpio_init( GPIO_B9, mode );
        }else{
            gpio_init( GPIO_B6, mode );
            gpio_init( GPIO_B7, mode );
        }
        break;
    case 1:
        // CL=B10, DA=B11
        i2cinfo[i].addr = addr = I2C2;
        i2cinfo[i].irq  = IRQ_I2C2_EV;
        RCC->APB1ENR   |= 1<<22;
        gpio_init( GPIO_B10, mode );
        gpio_init( GPIO_B11, mode );
        break;
    case 2:
        // CL=A8, DA=C9
        i2cinfo[i].addr = addr = I2C3;
        i2cinfo[i].irq  = IRQ_I2C3_EV;
        RCC->APB1ENR   |= 1<<23;
        gpio_init( GPIO_A8, mode );
        gpio_init( GPIO_C9, mode );
        break;
    default:
        PANIC("invalid i2c device");
    }
#endif
    int speed = dev->baud;
    if( !speed ) speed = 100000;
    int fastmode = 0;

    addr->CR1 = 0x8000;		// reset
    addr->CR1 = 0;

    addr->CR2   = APB1CLOCK / 1000000;
    addr->CR1  &= ~3;
    addr->TRISE = (APB1CLOCK / 1000000) + 1;

    speed = i2c_set_speed(i, speed);

    i2cinfo[i].state = I2C_STATE_IDLE;
    nvic_enable( i2cinfo[i].irq,     IPL_I2C );
    nvic_enable( i2cinfo[i].irq + 1, IPL_I2C );

    bootmsg("%s at io 0x%x irq %d speed %dkHz\n", dev->name, i2cinfo[i].addr, i2cinfo[i].irq, speed);
    return 0;
}

int
i2c_set_speed(int unit, int speed){
    if( unit >= N_I2C ) return -1;

    struct I2CInfo *ii = i2cinfo + unit;
    I2C_TypeDef *addr   = ii->addr;

    if( speed > 100000 ){
        int ccr = (APB1CLOCK/speed + 24)/25;	// ceil
        addr->CCR   = 0xC000 | ccr;		// fast mode
        speed = APB1CLOCK/ccr/25000;
    }else{
        addr->CCR   = (APB1CLOCK/speed/2);
        speed = APB1CLOCK/addr->CCR/2000;
    }

    return speed;
}




static void
_i2c_dump_crumb(void){
    int i;

#ifdef I2C_VERBOSE
    for(i=0; i<cur_crumb; i++){
        kprintf("[i2c] %s\t%x %x\n", crumbs[i].event, crumbs[i].arg0, crumbs[i].arg1);
    }
#endif
}


static inline void
_i2c_wait(I2C_TypeDef *dev){

    while (1){
        if( ! (dev->CR1 & (CR1_START | CR1_STOP | CR1_PEC)) ) return;
    }
}

static inline void
_i2c_start(I2C_TypeDef *dev){

    _i2c_wait(dev);
    dev->CR1 |= CR1_START;
}

static inline void
_i2c_stop(I2C_TypeDef *dev){

    _i2c_wait(dev);
    dev->CR1 |= CR1_STOP;
    _i2c_wait(dev);
}
static inline void
_i2c_send_addr(I2C_TypeDef *dev, int addr, int rw){
    dev->DR = (addr << 1) | rw;
}

static inline void
_i2c_wait_sb(I2C_TypeDef *dev){
    while(1){
        if( dev->SR1 & SR1_SB ) return;
    }
}
static inline void
_i2c_wait_addr(I2C_TypeDef *dev){
    int sr1, sr2;
    while(1){
        sr1 = dev->SR1;
        sr2 = dev->SR2;
        if( sr1 & SR1_ADDR ) return;
    }
}

static inline void
_i2c_wait_txe(I2C_TypeDef *dev){
    while(1){
        if( dev->SR1 & SR1_TXE ) return;
    }
}

/****************************************************************/

static inline int
_msg_len(i2c_msg *m){
    return m->clen + m->dlen;
}

static inline void
_msg_init(i2c_msg *m){
    m->cpos = 0;
    m->dpos = 0;
}

static inline int
_msg_next(i2c_msg *m){

    if( m->cpos < m->clen )
        return m->cdata[ m->cpos ++ ];
    return m->data[ m->dpos ++ ];
}

static inline void
_msg_add(i2c_msg *m, int d){
    if( m->cpos < m->clen ){
        m->cdata[ m->cpos ++ ] = d;
    }else{
        m->data[ m->dpos ++ ] = d;
    }
}

static inline int
_msg_onemore(i2c_msg *m){
    return (m->cpos + m->dpos) == (m->clen + m->dlen - 1);
}

static inline int
_msg_done(i2c_msg *m){
    return (m->cpos >= m->clen) && (m->dpos >= m->dlen);
}

/****************************************************************/
int
i2c_xfer(int unit, int nmsg, i2c_msg *msgs, int timeo){
    if( unit >= N_I2C ) return -1;

    struct I2CInfo *ii = i2cinfo + unit;
    I2C_TypeDef *dev   = ii->addr;
    int i = 0;


    /* wait for device */
#ifdef I2C_VERBOSE
    kprintf("i2c xfer waiting, state %d\n", ii->state);
#endif

    sync_lock( & ii->lock, "i2c.L" );

    cur_crumb = 0;
    int plx = spldisk();
    ii->msg       = msgs;
    ii->num_msg   = nmsg;
    ii->state     = I2C_STATE_BUSY;

#ifdef I2C_VERBOSE
    kprintf("i2c xfer starting, %d msgs\n", nmsg);
#endif

    // enable irqs + device
    dev->CR2  |= CR2_IRQ_BUF | CR2_IRQ_EVT | CR2_IRQ_ERR;
    dev->CR1  |= CR1_PE;

    _i2c_start(dev);
    splx(plx);

    utime_t expires = timeo ? get_time() + timeo : 0;


    while( ii->state == I2C_STATE_BUSY ){
        if( currproc ){
#ifdef I2C_VERBOSE
            kprintf("i2c xfer tsleep %d\n", timeo ? expires - get_time() : 0);
#endif
            tsleep( ii, -1, "i2c", timeo ? expires - get_time() : 0 );
        }
        if( expires && get_time() >= expires ){
            I2C_CRUMB("timeout", 0,0);
            break;
        }
    }

#ifdef I2C_VERBOSE
    _i2c_dump_crumb();
    kprintf("i2c xfer done %d\n\n", ii->state);
#endif

    int r;
    switch(ii->state){
    case I2C_STATE_XFER_DONE:	r = I2C_XFER_OK;	break;
    case I2C_STATE_ERROR:	r = ii->errorflags;	break;
    default:			r = I2C_XFER_TIMEOUT;	break;	// QQQ - reset?
    }

    // disable
    dev->CR1 &= ~CR1_PE;
    dev->CR2 &= ~ (CR2_IRQ_BUF | CR2_IRQ_EVT | CR2_IRQ_ERR);

    ii->state = I2C_STATE_IDLE;
    sync_unlock( & ii->lock );

    return I2C_XFER_OK;
}

// write one msg - busy waiting
int
i2c_write1(int unit, i2c_msg *msg){
    struct I2CInfo *ii = i2cinfo + unit;
    I2C_TypeDef *dev   = ii->addr;

    if( currproc )
        return i2c_xfer(unit, 1, msg, 1000000);

    sync_lock( & ii->lock, "i2c.L" );
    dev->CR1  |= CR1_PE;

    _i2c_start(dev);
    _i2c_wait_sb(dev);
    _i2c_send_addr(dev, msg->slave, 0);
    _i2c_wait_addr(dev);
    _msg_init(msg);

    while( !_msg_done(msg) ){
        _i2c_wait_txe(dev);
        dev->DR = _msg_next(msg);
    }

    _i2c_wait_txe(dev);
    _i2c_stop(dev);

    dev->CR1 &= ~CR1_PE;

    sync_unlock( & ii->lock );
    return I2C_XFER_OK;
}


/****************************************************************/

static void
_i2c_ev_irq(int unit){
    struct I2CInfo *ii = i2cinfo + unit;
    I2C_TypeDef *dev   = ii->addr;
    i2c_msg *msg       = ii->msg;

    int read   = msg->flags & I2C_MSGF_READ;
    u_long sr1 = dev->SR1;
    u_long sr2 = dev->SR2;
    I2C_CRUMB("entry", sr1, sr2);

    /* EV5: Start condition sent */
    if( sr1 & SR1_SB ){
        I2C_CRUMB("start", 0,0);
        _msg_init(msg);
        dev->CR2 |= CR2_IRQ_BUF;

        /* Master receiver */
        if( read ){
            dev->CR1 |= CR1_ACK;
        }

        _i2c_send_addr(dev, msg->slave, read);
        return;
    }

    /* EV6: Slave address sent */
    if( sr1 & SR1_ADDR ){
        /*
         * Special case event EV6_1 for master receiver.
         * Generate NACK and restart/stop condition after ADDR
         * is cleared.
         */
        if( read ){
            if( _msg_len(msg) == 1 ){
                dev->CR1 &= ~CR1_ACK;

                if (ii->num_msg > 1) {
                    _i2c_start(dev);
                    I2C_CRUMB("rx-addr-start", 0, 0);
                } else {
                    _i2c_stop(dev);
                    I2C_CRUMB("rx-addr-stop", 0, 0);
                }
            }
        }else{
            /*
             * Master transmitter: write first byte to fill shift
             * register.  We should get another TXE interrupt
             * immediately to fill DR again.
             */
            I2C_CRUMB("tx-addr", 0, 0);
            if( _msg_len(msg) != 1 ){
                dev->DR = _msg_next( msg );
            }
        }
        return;
    }

    /*
     * EV8: Master transmitter
     * Transmit buffer empty, but we haven't finished transmitting the last
     * byte written.
     */
    if( (sr1 & SR1_TXE) && !(sr1 & SR1_BTF) ){
        I2C_CRUMB("txe-only", 0, 0);
        if( ii->num_msg ){
            dev->DR = _msg_next( msg );

            if( _msg_done(msg) ){
                /*
                 * End of this message. Turn off TXE/RXNE and wait for
                 * BTF to send repeated start or stop condition.
                 */
                dev->CR2 &= ~ CR2_IRQ_BUF;
                ii->num_msg--;
            }
        } else {
            /*
             * This should be impossible...
             */
            PANIC("i2c send botch");
        }
        return;
    }

    /*
     * EV8_2: Master transmitter
     * Last byte sent, program repeated start/stop
     */
    if( (sr1 & SR1_TXE) && (sr1 & SR1_BTF) ){
        I2C_CRUMB("txe-btf", 0, 0);

        if (ii->num_msg) {
            I2C_CRUMB("test", 0, 0);
            /*
             * Repeated start insanity: We can't disable ITEVTEN or else SB
             * won't interrupt, but if we don't disable ITEVTEN, BTF will
             * continually interrupt us. What the fuck ST?
             */
            _i2c_start(dev);
            while( !(dev->SR1 & SR1_SB))
                ;
            ii->msg++;
        }else{
            _i2c_stop(dev);

            /*
             * Turn off event interrupts to keep BTF from firing until
             * the end of the stop condition. Why on earth they didn't
             * have a start/stop condition request clear BTF is beyond
             * me.
             */
            dev->CR2 &= ~ CR2_IRQ_EVT;
            I2C_CRUMB("stop-sent", 0, 0);
            ii->state = I2C_STATE_XFER_DONE;
            wakeup( ii );
        }
        return;
    }

    /* EV7: Master Receiver */
    if( sr1 & SR1_RXNE ){
        I2C_CRUMB("rxne-only", 0, 0);
        _msg_add( msg, dev->DR );

        /*
         * EV7_1: Second to last byte in the reception? Set NACK and generate
         * stop/restart condition in time for the last byte. We'll get one more
         * RXNE interrupt before shutting things down.
         */
        if( _msg_onemore(msg) ){
            dev->CR1 &= ~CR1_ACK;

            if( ii->num_msg > 2 ){
                _i2c_start(dev);
                I2C_CRUMB("rxne-start-sent", 0, 0);
            }else{
                _i2c_stop(dev);
                I2C_CRUMB("rxne-stop-sent", 0, 0);
            }
        }else if( _msg_done(msg) ){
            ii->num_msg--;
            if( ii->num_msg == 0 ){
                /*
                 * We're done.
                 */
                I2C_CRUMB("rxne-done", 0, 0);
                ii->state = I2C_STATE_XFER_DONE;
                wakeup( ii );
            }else{
                ii->msg++;
            }
        }
    }

}

static void
_i2c_er_irq(int unit){
    struct I2CInfo *ii = i2cinfo + unit;
    I2C_TypeDef *dev   = ii->addr;


    I2C_CRUMB("errorirq", dev->SR1, dev->SR2);
    ii->errorflags = dev->SR1 & 0xF00;

    /* Clear flags */
    dev->SR1 = 0;
    dev->SR2 = 0;

    _i2c_stop(dev);
    dev->CR2 &= ~ (CR2_IRQ_BUF | CR2_IRQ_ERR | CR2_IRQ_EVT);
    ii->state = I2C_STATE_ERROR;
}

/****************************************************************/

void
I2C1_EV_IRQHandler(void){
    _i2c_ev_irq( 0 );
}
void
I2C2_EV_IRQHandler(void){
    _i2c_ev_irq( 1 );
}
void
I2C1_ER_IRQHandler(void){
    _i2c_er_irq( 0 );
}
void
I2C2_ER_IRQHandler(void){
    _i2c_er_irq( 1 );
}


