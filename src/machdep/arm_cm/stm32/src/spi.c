/*
  Copyright (c) 2013
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2013-Mar-24 21:07 (EDT)
  Function: stm32 spi using dma

*/

#include <conf.h>
#include <proc.h>
#include <arch.h>
#include <locks.h>
#include <dev.h>
#include <error.h>
#include <clock.h>
#include <spi.h>
#include <gpio.h>
#include <stm32.h>
#include <nvic.h>
#include <spi_impl.h>

#ifdef SPI_TRACE
# define TRACE
#endif
#include <trace.h>


#define CR1_CRCEN	0x2000
#define CR1_SSM		0x200
#define CR1_SSI		0x100
#define CR1_SPE		0x40
#define CR1_MSTR	0x4

#define CR2_TXEIE	0x80
#define CR2_RXNEIE	0x40
#define CR2_ERRIE	0x20
#define CR2_TXDMAEN	0x2
#define CR2_RXDMAEN	0x1

#define SR_BSY		0x80
#define SR_TXE		0x2
#define SR_RXNE		0x1

// stm32f1
#define DMACCR_MINC	0x80
#define DMACCR_DIR_M2P	0x10	// 0: periph=>mem, 1: mem=>periph
#define DMACCR_TEIE	0x8
#define DMACCR_TCIE	0x2
#define DMACCR_EN	0x1

// stm32f4
#define DMASCR_MINC	(1<<10)
#define DMASCR_DIR_M2P  (1<<6)
#define DMASCR_PFCTRL	(1<<5)
#define DMASCR_TEIE	4
#define DMASCR_TCIE	16
#define DMASCR_EN	1


#define SPI_STATE_DISABLED          0
#define SPI_STATE_IDLE              1
#define SPI_STATE_XFER_DONE         2
#define SPI_STATE_DMA_DONE	    3
#define SPI_STATE_BUSY              4
#define SPI_STATE_ERROR             -1

#ifndef DMA_MIN_SIZE
#  define DMA_MIN_SIZE	64
#endif

static char dma_idle_source = 0xFF;
static char dma_idle_sink;

struct SPIInfo spiinfo[ N_SPI ];

static int  _set_speed(struct SPIInfo *, int);
static void _msg_next(struct SPIInfo *);


int
spi_init(struct Device_Conf *dev){
    int unit = dev->unit;
    struct SPIInfo *ii = spiinfo + unit;
    SPI_TypeDef *addr;

    bzero(ii, sizeof(struct SPIInfo));

    _spi_dev_init(unit, ii);
    addr = ii->addr;

    addr->CR1 |= CR1_SSM | CR1_MSTR;

    int speed = _set_speed(ii, dev->baud);

    //nvic_enable( ii->irq,  IPL_DISK );

    ii->name  = dev->name;
    ii->state = SPI_STATE_IDLE;

    trace_init();

    bootmsg("%s at io 0x%x irq %d dma %d+%d speed %dkHz clock %d\n",
            dev->name, ii->addr, ii->irq, ii->dmanrx, ii->dmantx, speed/1000, ii->clock/1000);

    return 0;
}

static int
_set_speed(struct SPIInfo *ii, int speed){
    SPI_TypeDef *dev   = ii->addr;
    int cspeed = ii->clock / 2;
    int clkdiv = 0;

    while( clkdiv < 7 && cspeed > speed ){
        cspeed /= 2;
        clkdiv ++;
    }

    dev->CR1 &= ~(7 << 3);
    dev->CR1 |= clkdiv << 3;

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
_spi_rxtx1(SPI_TypeDef *dev, int val){
    int sr, c;

    // wait until ready
    while(1){
        sr = dev->SR;
        if( sr & SR_TXE  ) break;
    }

    trace_crumb2("spi", "rxtx1", sr, val);
    PUT_DR(dev, val);

    while(1){
        sr = dev->SR;
        if( sr & SR_RXNE ){
            c = GET_DR(dev);
            trace_crumb2("spi", "rxtx1", sr, c);
            return c;
        }
    }
}

static inline int
_spi_tx1(SPI_TypeDef *dev, int val){
    int sr, c;

    // wait until ready
    while(1){
        sr = dev->SR;
        if( sr & SR_TXE  ) break;
    }

    trace_crumb1("spi", "tx1", sr);
    PUT_DR(dev, val);

    return 0;
}

static inline int
_spi_rx1(SPI_TypeDef *dev){
    int sr, c;

    while(1){
        sr = dev->SR;
        if( sr & SR_RXNE ){
            c = GET_DR(dev);
            trace_crumb2("spi", "rx1/rx", sr, c);
            return c;
        }

        if( sr & SR_TXE ){
            trace_crumb1("spi", "rx1/tx", sr);
            PUT_DR(dev, 0xFF);
        }

    }
}

static inline int
_spi_drain_rx(SPI_TypeDef *dev){
    int sr, c;
    int n = 16;

    while(n-- > 0){
        sr = dev->SR;
        if( sr & SR_RXNE ){
            c = GET_DR(dev);
        }else{
            return 0;
        }
    }
}

/****************************************************************/

#ifdef DMA_TYPE_1
# if defined(STM32L4PLUS)
static inline void _dma_csel(struct SPIInfo *ii) {

}

# elif defined(PLATFORM_STM32L4)
// L4 has an extra step - set the channel select
static inline void _dma_csel(struct SPIInfo *ii) {
    char b;
    DMA_Request_TypeDef *dmar;

    if( ii->dma == DMA1 ){
        dmar = DMA1_CSELR;
    }else{
        dmar = DMA2_CSELR;
    }

    b = (ii->dmanrx - 1) << 2;
    dmar->CSELR &= 0xF << b;
    dmar->CSELR |= ii->dmachan << b;

    b = (ii->dmantx - 1) << 2;
    dmar->CSELR &= ~(0xF << b);
    dmar->CSELR |= ii->dmachan << b;

}
# else
static inline void _dma_csel(struct SPIInfo *ii) {}
# endif

static inline void
_disable_irq_dma(struct SPIInfo *ii){
    SPI_TypeDef *dev = ii->addr;

    dev->CR2 &= ~( CR2_TXEIE | CR2_RXNEIE | CR2_TXDMAEN | CR2_RXDMAEN );
    ii->rxdma->CCR &= ~(DMACCR_EN | DMACCR_TEIE | DMACCR_TCIE );
    ii->txdma->CCR &= ~(DMACCR_EN | DMACCR_TEIE | DMACCR_TCIE );
}

static void
_dma_conf(DMAC_T *dmac, char *pdev, char *addr, int len, u_long flags){

    dmac->CPAR  = (u_long) pdev;
    dmac->CMAR  = (u_long) addr;
    dmac->CNDTR = len ? len : 65535;
    dmac->CCR  &= ~ (DMACCR_DIR_M2P | DMACCR_MINC);
    dmac->CCR  |= flags | (len ? DMACCR_TEIE | DMACCR_TCIE : 0);
    dmac->CCR  |= DMACCR_EN;
}


static void
_dma_enable_read(struct SPIInfo *ii){
    SPI_TypeDef *dev = ii->addr;

    trace_crumb0("spi", "en-dma/r");
    // rx dma to buffer; tx dummy
    _dma_conf( ii->rxdma, (char*)& dev->DR, ii->msg->data, ii->msg->dlen, DMACCR_MINC );
    _dma_conf( ii->txdma, (char*)& dev->DR, &dma_idle_source, 0, DMACCR_DIR_M2P );
    _dma_csel(ii);

    dev->CR2 |= CR2_TXDMAEN | CR2_RXDMAEN;
}

static void
_dma_enable_write(struct SPIInfo *ii){
    SPI_TypeDef *dev = ii->addr;

    trace_crumb0("spi", "en-dma/w");
    // tx dma from buffer, rx discard
    _dma_conf( ii->txdma, (char*)& dev->DR, ii->msg->data, ii->msg->dlen, DMACCR_MINC | DMACCR_DIR_M2P );
    _dma_conf( ii->rxdma, (char*)& dev->DR, &dma_idle_sink, 0, 0 );
    _dma_csel(ii);

    dev->CR2 |= CR2_TXDMAEN | CR2_RXDMAEN;
}

/****************************************************************/

#elif defined(DMA_TYPE_2)

static inline int
_dma_isr_clear_irqs(DMA_TypeDef *dma, int dman){
    int isr;
    int pos = (dman & 3) * 8 - (dman & 1) * 2;	// not aligned

    if( dman > 3 ){
        isr = (dma->HISR >> pos) & 0x3F;
        dma->HIFCR = (0x3D << pos);
    }else{
        isr = (dma->LISR >> pos) & 0x3F;
        dma->LIFCR = (0x3D << pos);
    }

    return isr;
}

static inline void
_disable_irq_dma(struct SPIInfo *ii){
    SPI_TypeDef *dev = ii->addr;

    dev->CR2 &= ~( CR2_TXEIE | CR2_RXNEIE | CR2_TXDMAEN | CR2_RXDMAEN );
    ii->rxdma->CR &= ~(DMASCR_EN | DMASCR_TEIE | DMASCR_TCIE);
    ii->txdma->CR &= ~(DMASCR_EN | DMASCR_TEIE | DMASCR_TCIE);
}

static void
_dma_conf(DMAC_T *dmac, int chan, char *pdev, char *addr, int len, u_long flags){

    dmac->PAR   = (u_long) pdev;
    dmac->M0AR  = (u_long) addr;
    dmac->NDTR  = len ? len : 65535;
    dmac->CR   &= ~1;	// clear EN first
    dmac->CR   &= (0xF<<28) | (1<<20);
    dmac->CR   |= flags | (len ? DMASCR_TEIE | DMASCR_TCIE : 0) | (chan << 25);

    dmac->CR   |= DMASCR_EN;

}

static void
_dma_enable_read(struct SPIInfo *ii){
    SPI_TypeDef *dev = ii->addr;

    trace_crumb0("spi", "en-dma/r");
    dcache_flush(ii->msg->data, ii->msg->dlen);
    // rx dma to buffer; tx dummy
    int plx = splhigh();
#ifndef PLATFORM_STM32F7
    // is needed  - F411
    // not needed - tested F413, F7
    _dma_isr_clear_irqs( ii->dma, ii->dmanrx );
    _dma_isr_clear_irqs( ii->dma, ii->dmantx );
#endif
    _dma_conf( ii->rxdma, ii->dmachan, (char*)& dev->DR, ii->msg->data, ii->msg->dlen, DMASCR_MINC );
    _dma_conf( ii->txdma, ii->dmachan, (char*)& dev->DR, &dma_idle_source, 0, DMASCR_DIR_M2P );

    dev->CR2 |= CR2_TXDMAEN | CR2_RXDMAEN;
    splx(plx);
}

static void
_dma_enable_write(struct SPIInfo *ii){
    SPI_TypeDef *dev = ii->addr;

    trace_crumb0("spi", "en-dma/w");
    dcache_flush(ii->msg->data, ii->msg->dlen);
    // tx dma from buffer, rx discard
    int plx = splhigh();
#ifndef PLATFORM_STM32F7
    _dma_isr_clear_irqs( ii->dma, ii->dmanrx );
    _dma_isr_clear_irqs( ii->dma, ii->dmantx );
#endif
    _dma_conf( ii->txdma, ii->dmachan, (char*)& dev->DR, ii->msg->data, ii->msg->dlen, DMASCR_MINC | DMASCR_DIR_M2P );
    _dma_conf( ii->rxdma, ii->dmachan, (char*)& dev->DR, &dma_idle_sink, 0, 0 );

    dev->CR2 |= CR2_TXDMAEN | CR2_RXDMAEN;
    splx(plx);
}

#else
#  error "unknown dma type"
#endif

/****************************************************************/

static inline void
_spi_enable_irq(struct SPIInfo *ii){
    SPI_TypeDef *dev = ii->addr;

    trace_crumb0("spi", "irq-en");
    dev->CR2 |= CR2_TXEIE | CR2_RXNEIE;
}

static inline void
_spi_conf_enable(const struct SPIConf *cf, struct SPIInfo *ii){
    SPI_TypeDef *dev   = ii->addr;

    if( cf->speed ) _set_speed(ii, cf->speed);
    dev->CR1 |= CR1_MSTR | CR1_SSI;
}

static inline void
_spi_conf_disable(const struct SPIConf *cf, struct SPIInfo *ii){
    SPI_TypeDef *dev   = ii->addr;

    _disable_irq_dma(ii);
    dev->CR1  &= ~ (CR1_SPE | CR1_CRCEN);

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

/****************************************************************/

static inline int
_msg_until(struct SPIInfo *ii){
    spi_msg *m = ii->msg;
    int count = 0;

    //proc_trace_add("spi/until", m->dlen);

    while( m->dlen -- > 0 ){
        int c = m->response = _spi_rxtx1( ii->addr, 0xFF );
        int r = m->until(c);

        if( r ==  1 ){
            trace_crumb2("spi", "got", c, count);
            return 0;	// got it. done.
        }
        if( r == -1 ) break;    // error
#if 1
        spl0();

        if( !(++count % 10) ) yield();

#else
        if( /* (m->mode == SPIMO_UNTIL_SLOW) && */ (count++ > 10) ){
            yield();
            count = 0;
        }

        if( (m->mode == SPIMO_UNTIL) && (count++ > 100) ){
            yield();
            count = 0;
        }
#endif
    }

    // failed
    trace_crumb1("spi", "until-fail", ii->addr->SR); // m->response, count);
    ii->state = SPI_STATE_ERROR;
    return 1;
}

static void
_msg_dma_wait(struct SPIInfo *ii){
    int plx;

    trace_crumb0("spi", "msg-dma-wait");
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
            return;
        }
    }

}

static inline int
_msg_read(struct SPIInfo *ii){
    spi_msg *m = ii->msg;
    int i;

    if( m->dlen > DMA_MIN_SIZE ){
        _dma_enable_read(ii);
        _msg_dma_wait(ii);
    }else{
        for(i=0; i<m->dlen; i++)
            m->data[i] = _spi_rxtx1( ii->addr, 0xFF );
    }

    return 0;
}

static inline int
_msg_write(struct SPIInfo *ii){
    spi_msg *m = ii->msg;
    int i;

    if( m->dlen > DMA_MIN_SIZE ){
        _dma_enable_write(ii);
        _msg_dma_wait(ii);
        m->response = dma_idle_sink;
    }else{
        for(i=0; i<m->dlen; i++)
            _spi_rxtx1( ii->addr, m->data[i] );
    }

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
            _spi_rxtx1( ii->addr, 0xFF );
        break;
    case SPIMO_FINISH:
        while( ii->addr->SR & SR_BSY ){
            if( ii->timeout && get_time() > ii->timeout ) break;
        }
        break;
    }

    return 0;
}

void
_irq_spidma_handler(int unit, int dman, DMAC_T *dmac){
    struct SPIInfo *ii = spiinfo + unit;
    SPI_TypeDef *dev   = ii->addr;
    spi_msg *m = ii->msg;

#if defined(DMA_TYPE_1)
    // get status, clear irq
    int pos = 4 * (dman - 1);
    int isr = (ii->dma->ISR >> pos) & 0xF;

    trace_crumb2("spi", "dma-irq", dman, isr);

    // clear irq
    ii->dma->IFCR |= (0xF<<pos);

    if( isr & 8 ){
        // error - done
        trace_crumb0("spi", "dma-err");
        _disable_irq_dma(ii);
        ii->state = SPI_STATE_ERROR;
        wakeup( ii );
        return;
    }

    if( isr & 2 ){
        // dma complete
        if( m && ((u_long)m->data == dmac->CMAR) && ! dmac->CNDTR ){
            trace_crumb1("spi", "dma-done", ii->msg);
            _disable_irq_dma(ii);
            ii->state = SPI_STATE_DMA_DONE;
            wakeup( ii );
        }
    }
#elif defined(DMA_TYPE_2)

    int isr = _dma_isr_clear_irqs( ii->dma, dman );
    trace_crumb2("spi", "dma-irq", dman, isr);

    if( isr & 8 ){
        // error - done
        trace_crumb2("spi", "dma-err", 0, 0);
        _disable_irq_dma(ii);
        ii->state = SPI_STATE_ERROR;
        wakeup( ii );
        return;
    }

    if( isr & 0x20 ){
        // dma complete
        if( m && ((u_long)m->data == dmac->M0AR) && ! dmac->NDTR ){
            trace_crumb1("spi", "dma-done", ii->msg);
            dcache_invalidate(ii->msg->data, ii->msg->dlen);
            _disable_irq_dma(ii);
            ii->state = SPI_STATE_DMA_DONE;
            wakeup( ii );
        }
    }
#else
#  error "unknown dma type"
#endif
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

    dev->CR1 |= CR1_SPE;

    for(i=0; i<16; i++){
        while( !(dev->SR & SR_TXE) ) {}
        dev->DR = 0xFF;
    }

    // disable device, pins
    _spi_conf_done(cf, ii);
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
    dev->CR1 |= CR1_SPE;       // go!

    if( dev->SR & SR_RXNE ) _spi_drain_rx( ii->addr );
    int x = _spi_rxtx1( ii->addr, reg );
    trace_crumb2("spi", "tx", reg, x);

    for(; n>0; n--){
        *dst++ = _spi_rxtx1( ii->addr, 0xFF );
    }

    trace_crumb1("spi", "spi-wait!busy", dev->SR);
    while( dev->SR & SR_BSY ){
        if( ii->timeout && get_time() > ii->timeout ) break;
    }

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
    dev->CR1 |= CR1_SPE;       // go!

    _spi_drain_rx( ii->addr );

    int i;
    for(i=0; i<n; i++){
        int x = _spi_tx1( ii->addr, src[i] );
    }

    trace_crumb1("spi", "spi-wait!busy", dev->SR);
    while( dev->SR & SR_BSY ){
        if( ii->timeout && get_time() > ii->timeout ) break;
    }

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
    dev->CR1 |= CR1_SPE;       // go!

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

    // wait !busy ( ~ 7 bit times from the txe-irq )
    // probably finished during the time it took to get here
    trace_crumb1("spi", "spi-wait!busy", dev->SR);
    while( dev->SR & SR_BSY ){
        if( ii->timeout && get_time() > ii->timeout ) break;
    }

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

// void SPI1_IRQHandler(void){ _irq_spi_handler(0); }
// void SPI2_IRQHandler(void){ _irq_spi_handler(1); }

// the handlers are named 0-6. everything else uses 1-7
// (spi-unit, dma-stream, dmac_t)
#if defined(PLATFORM_STM32F1)
void DMA1_Stream1_IRQHandler(void){ _irq_spidma_handler(0, 2, DMA_Channel2); }
void DMA1_Stream2_IRQHandler(void){ _irq_spidma_handler(0, 3, DMA_Channel3); }
void DMA1_Stream3_IRQHandler(void){ _irq_spidma_handler(1, 4, DMA_Channel4); }
void DMA1_Stream4_IRQHandler(void){ _irq_spidma_handler(1, 5, DMA_Channel5); }
#elif defined(PLATFORM_STM32L1)
void DMA1_Stream1_IRQHandler(void){ _irq_spidma_handler(0, 2, DMA1_Channel2); }
void DMA1_Stream2_IRQHandler(void){ _irq_spidma_handler(0, 3, DMA1_Channel3); }
void DMA1_Stream3_IRQHandler(void){ _irq_spidma_handler(1, 4, DMA1_Channel4); }
void DMA1_Stream4_IRQHandler(void){ _irq_spidma_handler(1, 5, DMA1_Channel5); }
void DMA2_Stream1_IRQHandler(void){ _irq_spidma_handler(2, 1, DMA2_Channel1); }
void DMA2_Stream2_IRQHandler(void){ _irq_spidma_handler(2, 2, DMA2_Channel2); }
#elif defined(PLATFORM_STM32L4)
void DMA1_Stream1_IRQHandler(void){ _irq_spidma_handler(0, 2, DMA1_Channel2); }
void DMA1_Stream2_IRQHandler(void){ _irq_spidma_handler(0, 3, DMA1_Channel3); }
void DMA1_Stream3_IRQHandler(void){ _irq_spidma_handler(1, 4, DMA1_Channel4); }
void DMA1_Stream4_IRQHandler(void){ _irq_spidma_handler(1, 5, DMA1_Channel5); }
void DMA2_Stream1_IRQHandler(void){ _irq_spidma_handler(2, 1, DMA2_Channel1); }
void DMA2_Stream2_IRQHandler(void){ _irq_spidma_handler(2, 2, DMA2_Channel2); }
#elif defined(PLATFORM_STM32F4)
void DMA1_Stream2_IRQHandler(void){ _irq_spidma_handler(2, 2, DMA1_Stream2); }
void DMA1_Stream3_IRQHandler(void){ _irq_spidma_handler(1, 3, DMA1_Stream3); }
void DMA1_Stream4_IRQHandler(void){ _irq_spidma_handler(1, 4, DMA1_Stream4); }
void DMA1_Stream5_IRQHandler(void){ _irq_spidma_handler(2, 5, DMA1_Stream5); }
void DMA2_Stream2_IRQHandler(void){ _irq_spidma_handler(0, 2, DMA2_Stream2); }
void DMA2_Stream3_IRQHandler(void){ _irq_spidma_handler(0, 3, DMA2_Stream3); }
#elif defined(PLATFORM_STM32F7)
void DMA2_Stream0_IRQHandler(void){ _irq_spidma_handler(3, 0, DMA2_Stream0); }
void DMA2_Stream1_IRQHandler(void){ _irq_spidma_handler(3, 1, DMA2_Stream1); }
#else
#  error "unknown platform"
#endif

/****************************************************************/
