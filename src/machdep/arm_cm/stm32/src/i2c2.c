/*
  Copyright (c) 2018
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2018-Mar-12 20:36 (EDT)
  Function: "new" i2c device

*/


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

#include <stm32.h>
#include <i2c_impl.h>

#ifdef I2C_TRACE
# define TRACE
#endif
#include <trace.h>


#define CFFLAGS_ALTPINS	3	// 2 bits of flags - alt set of pins


#define CR1_PE		1
#define CR1_TXIE	2
#define CR1_RXIE	4
#define CR1_NACKIE	16
#define CR1_STOPIE	32
#define CR1_TCIE	64
#define CR1_ERRIE	128

#define CR2_RDWRN	(1<<10)
#define CR2_RELOAD	(1<<24)
#define CR2_AUTOEND	(1<<25)
#define CR2_START	(1<<13)

#define SR_TXIS		2
#define SR_RXNE		4
#define SR_NACK		(1<<4)
#define SR_STOP		(1<<5)
#define SR_TC		(1<<6)
#define SR_TCR		(1<<7)
#define SR_NACK		(1<<4)


#define I2C_STATE_DISABLED          0
#define I2C_STATE_IDLE              1
#define I2C_STATE_XFER_DONE         2
#define I2C_STATE_BUSY              3
#define I2C_STATE_ERROR             -1



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

    i2c_pins_init( i, altpins );

    switch(i){
    case 0:
        i2cinfo[i].addr = addr = I2C1;
        i2cinfo[i].irq  = I2C1_EV_IRQn;
        break;
    case 1:
        i2cinfo[i].addr = addr = I2C2;
        i2cinfo[i].irq  = I2C2_EV_IRQn;
        break;
#ifdef I2C3
    case 2:
        i2cinfo[i].addr = addr = I2C3;
        i2cinfo[i].irq  = I2C3_EV_IRQn;
        break;
#endif
#ifdef I2C4
    case 3:
        i2cinfo[i].addr = addr = I2C4;
        i2cinfo[i].irq  = I2C4_EV_IRQn;
        break;
#endif
    default:
        PANIC("invalid i2c device");
    }
    int speed = dev->baud;
    if( !speed ) speed = 100000;

    addr->CR1 = 0;

    speed = i2c_set_speed(i, speed);

    i2cinfo[i].state = I2C_STATE_IDLE;
    nvic_enable( i2cinfo[i].irq,     IPL_I2C );
    nvic_enable( i2cinfo[i].irq + 1, IPL_I2C );

    trace_init();

    bootmsg("%s at io 0x%x irq %d speed %dkHz\n", dev->name, i2cinfo[i].addr, i2cinfo[i].irq, speed/1000);
    return 0;
}

int
i2c_set_speed(int unit, int speed){
    if( unit >= N_I2C ) return -1;

    struct I2CInfo *ii = i2cinfo + unit;
    I2C_TypeDef *addr   = ii->addr;

    int psc  = (APB1CLOCK / speed) >> 8;
    if( psc > 15 ) psc = 15;

    int iclk = APB1CLOCK / (psc + 1);
    int sync = iclk / 4000000;		// ~250ns - analog filter delay
    int tcyc = iclk / speed;

    int hi = 0, lo = 0, dadel = 0, cldel = 0;

    if( speed > 400000 ){
        // fast plus
        hi = (88 * tcyc) >> 8;
        cldel = iclk / 20000000;	// >= 50ns

    }else if( speed > 100000 ){
        // fast
        hi = (81 * tcyc) >> 8;
        cldel = iclk / 10000000;	// >= 100ns
        dadel = 1 + iclk / 20000000;	// ~ Tfall - Tfilter ~= 50ns

    }else{
        // standard
        hi = (115 * tcyc) >> 8;
        cldel = iclk / 4000000;		// >= 250us
        dadel = 1 + iclk / 20000000;	// ~ Tfall - Tfilter ~= 50ns
    }

    lo = tcyc - hi - sync;

    if( hi > 256 ) hi = 256;
    if( lo > 256 ) lo = 256;
    if( cldel > 15 ) cldel = 15;
    if( dadel > 15 ) dadel = 15;

    speed = iclk / (hi + lo + sync);

    addr->TIMINGR = (psc << 28)
        | (cldel << 20)
        | (dadel << 16)
        | ((hi - 1) << 8)
        | (lo - 1)
        ;

    return speed;
}


/****************************************************************/

static inline int
_msg_len(i2c_msg *m){
    return m->clen + m->dlen;
}

static inline int
_msg_remaining(i2c_msg *m){
    return m->clen + m->dlen - m->cpos - m->dpos;
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
_msg_done(i2c_msg *m){
    return (m->cpos >= m->clen) && (m->dpos >= m->dlen);
}

/****************************************************************/

static void
i2c_start(struct I2CInfo *ii){
    I2C_TypeDef *dev   = ii->addr;
    i2c_msg *m = ii->msg;

    _msg_init(m);
    int mlen = _msg_len(m);
    int cr1 = CR1_PE | CR1_TCIE | CR1_STOPIE | CR1_NACKIE | CR1_ERRIE;
    int cr2 = CR2_AUTOEND | CR2_START | (m->slave << 1);

    if( mlen > 255 ){
        mlen = 255;
        cr2 |= CR2_RELOAD;
    }

    cr2 |= mlen << 16;

    if( ii->msg->flags & I2C_MSGF_READ ){
        cr1 |= CR1_RXIE;
        cr2 |= CR2_RDWRN;
    }else{
        cr1 |= CR1_TXIE;
    }

    trace_crumb2("i2c", "start", cr1, cr2);
    dev->CR1 = cr1;
    dev->CR2 = cr2;

}


static void
i2c_done(struct I2CInfo *ii){
    I2C_TypeDef *dev   = ii->addr;

    trace_crumb1("i2c", "i2c/done", dev->ISR);
    dev->CR1 &= ~0xFF;
}

static void
i2c_msg_next(struct I2CInfo *ii){

    ii->num_msg --;
    trace_crumb1("i2c", "msg/nxt", ii->num_msg);

    if( ii->num_msg == 0 ){
        ii->state = I2C_STATE_XFER_DONE;
        wakeup(ii);
    }else{
        ii->msg++;
        i2c_start(ii);
    }
}

static void
i2c_ev_irq(struct I2CInfo *ii){
    I2C_TypeDef *dev = ii->addr;
    int sr = dev->ISR;

    // rx, tx, tc, tcr

    trace_crumb1("i2c", "evirq", sr);

    if( sr & SR_TCR ){
        // reload
        int cr2 = dev->CR2 & ~((0xFF<<16) | CR2_RELOAD);
        int len = _msg_remaining(ii->msg);

        if(len > 255){
            cr2 |= (0xFF<<16) | CR2_RELOAD;
        }else{
            cr2 |= len << 16;
        }

        trace_crumb2("i2c", "irq/rld", len, cr2);
        dev->CR2 = cr2;
    }

    if( sr & SR_NACK ){
        trace_crumb0("i2c", "irq/nack");
        ii->errorflags = dev->ISR;
        ii->state = I2C_STATE_ERROR;
        i2c_done(ii);
        wakeup(ii);
        return;
    }

    if( sr & SR_TXIS ){
        // send
        int c = _msg_next( ii->msg );
        trace_crumb1("i2c", "irq/tx", c);
        dev->TXDR = c;
    }
    if( sr & SR_RXNE ){
        // read
        int c = dev->RXDR;
        trace_crumb1("i2c", "irq/rx", c);
        _msg_add( ii->msg, c );
    }
    if( sr & SR_STOP ){
        // done
        trace_crumb0("i2c", "irq/done");
        i2c_done(ii);
        i2c_msg_next(ii);
    }
}

static void
i2c_er_irq(struct I2CInfo *ii){
    I2C_TypeDef *dev = ii->addr;

    trace_crumb1("i2c", "erirq", dev->ISR);
    ii->errorflags = dev->ISR;
    ii->state = I2C_STATE_ERROR;
    i2c_done(ii);
    wakeup(ii);
}

/****************************************************************/

int
i2c_xfer(int unit, int nmsg, i2c_msg *msgs, int timeo){
    if( unit >= N_I2C ) return -1;

    struct I2CInfo *ii = i2cinfo + unit;
    I2C_TypeDef *dev   = ii->addr;
    int i = 0;

    trace_crumb4("i2c", "xfer", unit, nmsg, ii->state, nmsg);

    /* wait for device */
    sync_lock( & ii->lock, "i2c.L" );

    int plx = spldisk();
    ii->msg       = msgs;
    ii->num_msg   = nmsg;
    ii->state     = I2C_STATE_BUSY;

    i2c_start(ii);
    splx(plx);

    utime_t expires = timeo ? get_time() + timeo : 0;

    while( 1 ){
        splproc();
        asleep( ii, "i2c" );
        if( ii->state != I2C_STATE_BUSY ) break;
        await( -1, timeo ? expires - get_time() : 0 );
        if( ii->state != I2C_STATE_BUSY ) break;

        trace_crumb2("i2c", "wake", dev->ISR, ii->state);

        if( expires && get_time() >= expires ){
            trace_crumb1("i2c", "timeout", dev->ISR);
            i2c_done(ii);
            break;
        }
    }

    aunsleep();
    splx(plx);

#ifdef I2C_VERBOSE
    kprintf("i2c xfer done %d\n\n", ii->state);
    kprintf("cr1 %x, cr2 %x, sr %x\n", dev->CR1, dev->CR2, dev->ISR);
#endif

    int r;
    switch(ii->state){
    case I2C_STATE_XFER_DONE:	r = I2C_XFER_OK;	break;
    case I2C_STATE_ERROR:	r = ii->errorflags;	break;
    default:			r = I2C_XFER_TIMEOUT;	break;	// QQQ - reset?
    }


    ii->state = I2C_STATE_IDLE;
    sync_unlock( & ii->lock );

    return r;
}

int
i2c_write1(int unit, i2c_msg *msg){

    return i2c_xfer(unit, 1, msg, 0);
}

/****************************************************************/

void
I2C1_EV_IRQHandler(void){
    i2c_ev_irq( i2cinfo + 0 );
}
void
I2C2_EV_IRQHandler(void){
    i2c_ev_irq( i2cinfo + 1 );
}
void
I2C1_ER_IRQHandler(void){
    i2c_er_irq( i2cinfo + 0 );
}
void
I2C2_ER_IRQHandler(void){
    i2c_er_irq( i2cinfo + 1 );
}


