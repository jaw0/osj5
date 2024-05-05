/*
  Copyright (c) 2013
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2013-Mar-24 21:07 (EDT)
  Function: new spi (stm32{u5,h5,h7})

*/

#include <conf.h>
#include <proc.h>
#include <arch.h>
#include <locks.h>
#include <dev.h>
#include <error.h>
#include <clock.h>
#include <stm32.h>
#include <dma.h>
#include <spi.h>
#include <gpio.h>
#include <nvic.h>
#include <spi_impl.h>
#include <userint.h>


#ifdef SPI_TRACE
# define TRACE
#endif
#include <trace.h>


#define SPI_STATE_DISABLED          0
#define SPI_STATE_IDLE              1
#define SPI_STATE_XFER_DONE         2
#define SPI_STATE_DMA_DONE	    3
#define SPI_STATE_BUSY              4
#define SPI_STATE_ERROR             -1

#ifndef DMA_MIN_SIZE
#  define DMA_MIN_SIZE	64
#endif

struct SPIInfo spiinfo[ N_SPI ];

static int  _set_speed(struct SPIInfo *, int);
static void _msg_next(struct SPIInfo *);
static void irq_spidma_handler( struct SPIInfo *, uint32_t );

int
spi_init(struct Device_Conf *dev){
    int unit = dev->unit;
    struct SPIInfo *ii = spiinfo + unit;
    SPI_TypeDef *addr;

    bzero(ii, sizeof(struct SPIInfo));

    _spi_dev_init(dev, ii);
    addr = ii->addr;

    addr->CFG2 |= SPI_CFG2_SSM | SPI_CFG2_MASTER | SPI_CFG2_AFCNTR;
    addr->CFG2 |= SPI_CFG2_MASTER; // QQQ - must be done again?
    addr->CR1  |= SPI_CR1_SSI;

    int speed = _set_speed(ii, dev->baud);

#ifdef USE_DMA
    ii->dmareq.chan     = -1;
    ii->dmareq.irqipl   = IPL_DISK;
    ii->dmareq.prio     = DMA_PRIO_LOW_M;
    ii->dmareq.callback = irq_spidma_handler;
    ii->dmareq.cbarg    = ii;
    ii->dmareq.port_rx = & ii->addr->RXDR;
    ii->dmareq.port_tx = & ii->addr->TXDR;

    dma_alloc( & ii->dmareq );
#endif

    ii->name  = dev->name;
    ii->state = SPI_STATE_IDLE;

    trace_init();


    bootmsg("%s at io 0x%x dma %d/%d+%d speed %dkHz clock %dkHz\n",
            dev->name, ii->addr, ii->dmareq.chan, ii->dmareq.req_rx, ii->dmareq.req_tx,
            speed/1000, ii->clock/1000);

    return 0;
}

static int
_set_speed(struct SPIInfo *ii, int speed){
    SPI_TypeDef *dev = ii->addr;
    int cspeed = ii->clock / 2;
    int clkdiv = 0;

    // NB - can also use HSI16, MSIK as src, for slower clk

    while( clkdiv < 7 && cspeed > speed ){
        cspeed /= 2;
        clkdiv ++;
    }

    dev->CFG1 &= ~(7 << 28);
    dev->CFG1 |= clkdiv << 28;

    trace_crumb2("spi", "set-speed", clkdiv, cspeed);
    return cspeed;
}


/****************************************************************/

// init CS pins
int
spi_cf_init(const struct SPIConf *cf){
    int i, p;

    for(i=0; i<cf->nss; i++){
        p = cf->ss[i] & 0xFF;

        gpio_init( p, SPIGPIO_CONF );
    }

    gpio_set( cf->ss[0] & 0xFF );

    return 0;
}


// set/clear cs pins
static void
_spi_cspins(const struct SPIConf *cf, int on){
    int nss = cf->nss;
    const short *ss = cf->ss;

    trace_crumb2("spi", "cspins", on, nss);
    while(nss--){
        int s = *ss ++;
        int m = (s & SPI_SS_INV) ? 1 : 0;	// hi bit = on/off

        trace_crumb2("spi", "pin", s, m);

        if( on == m )
            gpio_set( s & 0xFF );
        else
            gpio_clear( s & 0xFF );

    }
}


static inline int
_spi_drain_rx(SPI_TypeDef *dev){
    int sr, c;
    int n = 16;

    while(n-- > 0){
        sr = dev->SR;
        if( sr & SPI_SR_RXP ){
            c = dev->RXDR;
        }else{
            return 0;
        }
    }
}

/****************************************************************/

static inline void
_spi_conf_enable(const struct SPIConf *cf, struct SPIInfo *ii){
    SPI_TypeDef *dev   = ii->addr;

    if( cf->speed ) _set_speed(ii, cf->speed);
    dev->IFCR = 0x3F8; // clear all flags
}

static inline void
_spi_conf_disable(const struct SPIConf *cf, struct SPIInfo *ii){
    SPI_TypeDef *dev   = ii->addr;

    trace_crumb1("spi", "spi-off", dev->SR);
}

static void
_spi_conf_start(const struct SPIConf *cf, struct SPIInfo *ii){

    _spi_cspins(cf, 1);
    _spi_conf_enable(cf, ii);
}

static void
_spi_conf_done(const struct SPIConf *cf, struct SPIInfo *ii){

    _spi_conf_disable(cf, ii);
    // restore cs pins
    _spi_cspins(cf, 0);
}

static void
_dma_wait(struct SPIInfo *ii){
    int plx;

    trace_crumb0("spi", "dma-wait");
    while( 1 ){
        asleep( ii, ii->name );
        if( ii->state != SPI_STATE_BUSY ){
            aunsleep();
            return;
        }
        await( -1, get_time() - ii->timeout );

        if( ii->timeout && get_time() > ii->timeout ){
            trace_crumb0("spi", "timeout");
            ii->state = SPI_STATE_ERROR;
#ifdef USE_DMA
            dma_reset( & ii->dmareq );
#endif
            return;
        }
    }

}

static inline void
_spi_write_data(SPI_TypeDef *dev, int len, const char *data){

    while(len){
        while( (dev->SR & SPI_SR_TXP) == 0 ) {
            __asm("nop");
        }
        uint32_t sr = dev->SR;
        *(__IO char*)&(dev->TXDR) = *data;
        trace_crumb2("spi", "+wr", sr, dev->SR);
        data ++;
        len --;
    }
}

static inline void
_spi_read_data(SPI_TypeDef *dev, int len, char *data){

    while(len){
        while( dev->SR & SPI_SR_RXP == 0 ) {
            __asm("nop");
        }
        uint32_t sr = dev->SR;
        *data = *(__IO char*)&(dev->RXDR);
        trace_crumb2("spi", "+rd", sr, dev->SR);
        data ++;
        len --;
    }
}

static void
_spi_write(struct SPIInfo *ii, int len, const char *data){
    SPI_TypeDef *dev   = ii->addr;

    dev->CFG2 &= ~(3<<17); 	// clear COMM
    dev->CFG2 |= 1<<17;		// simplex transmit

    trace_crumb1("spi", "wr", len);

    while(len){
        int l = len;
        if( l > ii->maxtsize ) l = ii->maxtsize;
        len -= l;

        dev->CR2 = l;
        dev->CR1 |= SPI_CR1_SPE;	// enable
        dev->CR1 |= SPI_CR1_CSTART;

#ifdef USE_DMA
        if( l >= DMA_MIN_SIZE ){
            trace_crumb1("spi", "wr/dma", l);
            dev->CFG1 |= SPI_CFG1_TXDMAEN;
            dma_m2p( &ii->dmareq, data, l );
            _dma_wait(ii);
        }else{
            _spi_write_data(dev, l, data);
        }
#else
        _spi_write_data(dev, l, data);
#endif
        data += l;
    }

    trace_crumb1("spi", ".wr", dev->SR);
    while( (dev->SR & SPI_SR_EOT) == 0 ){
        __asm("nop");
    }
    trace_crumb1("spi", "/wr", dev->SR);

    dev->CR1  &= ~SPI_CR1_SPE;
}

static void
_spi_read(struct SPIInfo *ii, int len, char *data){
    SPI_TypeDef *dev   = ii->addr;

    dev->CFG2 &= ~(3<<17); 	// clear COMM
    dev->CFG2 |= 2<<17;		// simplex receive

    trace_crumb1("spi", "rd", len);

    while(len){
        int l = len;
        if( l > ii->maxtsize ) l = ii->maxtsize;
        len -= l;

        dev->CR2 = l;
        dev->CR1 |= SPI_CR1_SPE;	// enable
        dev->CR1 |= SPI_CR1_CSTART;

#ifdef USE_DMA
        if( l >= DMA_MIN_SIZE ){
            trace_crumb1("spi", "rd/dma", l);
            dev->CFG1 |= SPI_CFG1_RXDMAEN;
            dma_p2m( &ii->dmareq, data, l );
            _dma_wait(ii);
        }else{
            _spi_read_data(dev, l, data);
        }
#else
        _spi_read_data(dev, l, data);
#endif
        data += l;
    }

    dev->CR1  &= ~SPI_CR1_SPE;
}

/****************************************************************/

static inline int
_msg_until(struct SPIInfo *ii){
    spi_msg *m = ii->msg;
    int count = 0;

    while( m->dlen -- > 0 ){
        uint8_t c;

        _spi_read(ii, 1, &c);
        m->response = c;

        int r = m->until(c);

        if( r ==  1 ){
            trace_crumb2("spi", "got", c, count);
            return 0;	// got it. done.
        }
        if( r == -1 ) break;    // error

        spl0();

        if( !(++count % 10) ) yield();

    }

    // failed
    trace_crumb1("spi", "until-fail", ii->addr->SR); // m->response, count);
    ii->state = SPI_STATE_ERROR;
    return 1;
}


static inline int
_msg_read(struct SPIInfo *ii){
    spi_msg *m = ii->msg;
    int i;

    _spi_read(ii, m->dlen, m->data);

    return 0;
}

static inline int
_msg_write(struct SPIInfo *ii){
    spi_msg *m = ii->msg;
    int i;

    _spi_write(ii, m->dlen, m->data);

    return 0;
}


static int
_msg_do(struct SPIInfo *ii){
    spi_msg *m = ii->msg;
    int i;

    trace_crumb2("spi", "msg-do", m->mode, m->dlen);
    proc_trace_add("spi/do", m->mode);

    m->response = 0;
    ii->state = SPI_STATE_BUSY;

    switch(m->mode){
    case SPIMO_READ:
        _msg_read(ii);
        break;
    case SPIMO_WRITE:
        _msg_write(ii);
        break;
    case SPIMO_UNTIL:
    case SPIMO_UNTIL_SLOW:
        _msg_until(ii);
        break;
    case SPIMO_FUNC:
        trace_crumb0("spi", "func");
        m->until(m->data);
        break;

    case SPIMO_PINSON:
    case SPIMO_PINSOFF:
        _spi_cspins(ii->cf, (m->mode == SPIMO_PINSON));
        // fall thru
    case SPIMO_DELAY:
        for(i=0; i<m->dlen; i++)
            _spi_write( ii, 1, &i );
        break;
    case SPIMO_FINISH:
        // nop?
        break;
    }

    return 0;
}

static void
irq_spidma_handler( struct SPIInfo *ii, uint32_t dma_sr ){

    trace_crumb1("spi", "dma!", dma_sr);

    if( dma_sr & DMA_SR_ERROR_MASK )
        ii->state = SPI_STATE_ERROR;
    else
        ii->state = SPI_STATE_DMA_DONE;

    wakeup( ii );

}


void
spi_clear(const struct SPIConf * cf){
    struct SPIInfo *ii = spiinfo + cf->unit;
    SPI_TypeDef *dev   = ii->addr;
    int i;

    // enable device, pins
    _spi_conf_done(cf, ii);
    usleep(10000);
    _spi_conf_start(cf, ii);

    dev->CR1  |= SPI_CR1_SPE;	// enable

    _spi_drain_rx(dev);

    // disable device, pins
    _spi_conf_done(cf, ii);
    dev->CR1  &= ~SPI_CR1_SPE;	// enable
    usleep(10000);
}

int
spi_set_speed(const struct SPIConf * cf, int speed){
    struct SPIInfo *ii = spiinfo + cf->unit;
    return _set_speed(ii, speed);
}

int
spi_reg_read_nl(const struct SPIConf * cf, int reg, int n, char *dst, int timeout){
    if( cf->unit >= N_SPI ) return -1;

    struct SPIInfo *ii = spiinfo + cf->unit;
    SPI_TypeDef *dev   = ii->addr;

    // enable device, pins
    trace_crumb1("spi", "read/start", cf->unit);
    _spi_conf_start(cf, ii);

    _spi_drain_rx( ii->addr );
    _spi_write(ii, 1, &reg);
    trace_crumb1("spi", "tx", reg);

    _spi_read(ii, n, dst);

    // disable device, pins
    _spi_conf_done(cf, ii);

    trace_crumb2("spi", "done", ii->state, dev->SR);

    return 0;

}

int
spi_reg_read(const struct SPIConf * cf, int reg, int n, char *dst, int timeout){
    if( cf->unit >= N_SPI ) return -1;

    struct SPIInfo *ii = spiinfo + cf->unit;
    SPI_TypeDef *dev   = ii->addr;

    if( currproc ){
        int r = sync_tlock(&ii->lock, "spi.L", timeout);
        if( !r ) return SPI_XFER_TIMEOUT;
    }

    int plx = splproc();
    spi_reg_read_nl(cf, reg, n, dst, timeout);
    splx(plx);

    ii->state = SPI_STATE_IDLE;
    if( currproc )
        sync_unlock( &ii->lock );

    return 0;

}

int
spi_write(const struct SPIConf * cf, int n, char *src, int timeout){
    if( cf->unit >= N_SPI ) return -1;

    struct SPIInfo *ii = spiinfo + cf->unit;
    SPI_TypeDef *dev   = ii->addr;
    ii->timeout = timeout ? get_time() + timeout : 0;

    if( currproc ){
        int r = sync_tlock(&ii->lock, "spi.L", timeout);
        if( !r ) return SPI_XFER_TIMEOUT;
    }

    // enable device, pins
    trace_crumb1("spi", "write/start", cf->unit);
    int plx = splproc();
    _spi_conf_start(cf, ii);

    _spi_drain_rx( ii->addr );

    _spi_write(ii, n, src);

    // disable device, pins
    _spi_conf_done(cf, ii);
    splx(plx);

    trace_crumb1("spi", "done", ii->state);

    ii->state = SPI_STATE_IDLE;
    if( currproc )
        sync_unlock( &ii->lock );

    return 0;

}

int
spi_xfer(const struct SPIConf * cf, int nmsg, spi_msg *msgs, int timeout){
    if( cf->unit >= N_SPI ) return -1;
    if( !nmsg ) return 0;

    struct SPIInfo *ii = spiinfo + cf->unit;
    SPI_TypeDef *dev   = ii->addr;
    int verbose=1;

    if( msgs[0].mode & 0x80 ){
        verbose = 1;
        msgs[0].mode &= ~0x80;
    }

    if( currproc ){
        int r = sync_tlock(&ii->lock, "spi.L", timeout);
        if( !r ) return SPI_XFER_TIMEOUT;
    }

    trace_crumb1("spi", "start", nmsg);

    ii->cf        = cf;
    ii->msg       = msgs;
    ii->num_msg   = nmsg;
    ii->state     = SPI_STATE_BUSY;
    ii->timeout   = timeout ? get_time() + timeout : 0;

    // enable device, pins
    _spi_conf_start(cf, ii);
    trace_crumb1("spi", "spi-on", cf->unit);

    while( ii->num_msg > 0 ){
        int plx = splproc();
        _msg_do( ii );
        splx(plx);
        if( ii->state == SPI_STATE_ERROR ){
            trace_crumb0("spi", "error");
            break;
        }
        ii->num_msg --;
        if( ii->msg ) ii->msg ++;
    }

    if( ii->num_msg == 0 && ii->state != SPI_STATE_ERROR )
        ii->state = SPI_STATE_XFER_DONE;


    // disable device, pins
    _spi_conf_done(cf, ii);

    trace_crumb1("spi", "done", ii->state);


    int r;
    switch(ii->state){
    case SPI_STATE_XFER_DONE:	r = SPI_XFER_OK;	break;
    case SPI_STATE_ERROR:	r = SPI_XFER_ERROR;	break;
    default:			r = SPI_XFER_TIMEOUT;	break;
    }

    ii->state = SPI_STATE_IDLE;
    if( currproc )
        sync_unlock( &ii->lock );

    return r;
}

/****************************************************************/

#ifdef KTESTING
DEFUN(spitest, "test")
{
    struct SPIInfo *ii = spiinfo + 0;

    ii->addr->IFCR = 0x3F8; // clear all flags

    //while(1){
    _spi_write( ii, 32, &ii );
    printf(".");
    //}

    return 0;
}


DEFUN(spiinfo, "test")
{
    struct SPIInfo *ii = spiinfo + 0;
    SPI_TypeDef *dev   = ii->addr;

    printf("spi@ %08x\n", dev);
    printf("CR1  %08x\n", dev->CR1);
    printf("CR2  %08x\n", dev->CR2);
    printf("CFG1 %08x\n", dev->CFG1);
    printf("CFG2 %08x\n", dev->CFG2);
    printf("SR   %08x\n", dev->SR);

    return 0;
}
#endif

