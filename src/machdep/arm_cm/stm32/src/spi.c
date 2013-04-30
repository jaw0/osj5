/*
  Copyright (c) 2013
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2013-Mar-24 21:07 (EDT)
  Function: stm32 spi using dma + sd card

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

//#define VERBOSE


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

#define DMACCR_MINC	0x80
#define DMACCR_DIR	0x10	// 0: periph=>mem, 1: mem=>periph
#define DMACCR_TEIE	0x8
#define DMACCR_TCIE	0x2
#define DMACCR_EN	0x1

#define SPI_STATE_DISABLED          0
#define SPI_STATE_IDLE              1
#define SPI_STATE_XFER_DONE         2
#define SPI_STATE_DMA_DONE	    3
#define SPI_STATE_BUSY              4
#define SPI_STATE_ERROR             -1


#define DMA_MIN_SIZE	4


static u_long cur_crumb = 0;
static char dma_idle_source = 0xFF;
static char dma_idle_sink;


#ifdef VERBOSE
struct crumb {
    const char *event;
    int arg0;
    int arg1;
};

#define NR_CRUMBS       128
static struct crumb crumbs[NR_CRUMBS];

static inline void
_spi_drop_crumb(const char *event, u_long arg0, u_long arg1) {
    //if (cur_crumb < NR_CRUMBS) {
        struct crumb *crumb = &crumbs[cur_crumb++ % NR_CRUMBS];
        crumb->event = event;
        crumb->arg0 = arg0;
        crumb->arg1 = arg1;
        //}
}
#define SPI_CRUMB(event, arg0, arg1) _spi_drop_crumb(event, (u_long)arg0, (u_long)arg1)
#else
#define SPI_CRUMB(event, arg0, arg1)
#endif


struct SPIInfo {
    const char		*name;
    SPI_TypeDef 	*addr;
    DMA_Channel_TypeDef *rxdma, *txdma;
    int 	  	irq;
    int			clock;

    lock_t		lock;
    int			state;
    u_long		errorflags;

    // currently doing:
    spi_msg		*msg;
    int			num_msg;
    const struct SPIConf	*cf;

} spiinfo[ N_SPI ];


static int set_speed(struct SPIInfo *, int);
static void _msg_next(struct SPIInfo *);




int
spi_init(struct Device_Conf *dev){
    int unit = dev->unit;
    struct SPIInfo *ii = spiinfo + unit;
    SPI_TypeDef *addr;
    int dmairq, dman;

    bzero(ii, sizeof(struct SPIInfo));

#if defined(PLATFORM_STMF1)
    switch(unit){
    case 0:
        // on ahb2, dma1 chan2+3
        // CLK = A5, MISO = A6, MOSI = A7
        ii->addr      = addr = SPI1;
        ii->irq       = IRQ_SPI1;
        ii->rxdma     = DMA_Channel2;
        ii->txdma     = DMA_Channel3;
        ii->clock     = APB2CLOCK;
        dmairq        = IRQ_DMA1_CHANNEL2;
        dman          = 2;
        RCC->APB2ENR |= 1;	// AFI
        RCC->APB2ENR |= 1<<12;	// spi
        gpio_init( GPIO_A5, GPIO_AF_OUTPUT_PP | GPIO_OUTPUT_50MHZ );
        gpio_init( GPIO_A6, GPIO_INPUT_FLOATING );
        gpio_init( GPIO_A7, GPIO_AF_OUTPUT_PP | GPIO_OUTPUT_50MHZ );
        break;
    case 1:
        // on ahb1, dma1 chan 4+5
        // CLK = B13, MISO = B14, MOSI = B15
        ii->addr      = addr = SPI2;
        ii->irq       = IRQ_SPI2;
        ii->rxdma     = DMA_Channel4;
        ii->txdma     = DMA_Channel5;
        ii->clock     = APB1CLOCK;
        dmairq        = IRQ_DMA1_CHANNEL4;
        dman          = 4;
        RCC->APB2ENR |= 1;	// AFI
        RCC->APB1ENR |= 1<<14;	// spi
        gpio_init( GPIO_B13, GPIO_AF_OUTPUT_PP | GPIO_OUTPUT_50MHZ );
        gpio_init( GPIO_B14, GPIO_INPUT_FLOATING );
        gpio_init( GPIO_B15, GPIO_AF_OUTPUT_PP | GPIO_OUTPUT_50MHZ );
        break;
    default:
        // ...
        PANIC("invalid spi device");
    }

    RCC->AHBENR |= 1;	// DMA1

#elif defined(PLATFORM_STM32F4)
    switch(unit){
    case 0:
        // on ahb2, dma1 chan2+3
        // CLK = A5, MISO = A6, MOSI = A7
        ii->addr      = addr = SPI1;
        ii->irq       = IRQ_SPI1;
        ii->rxdma     = DMA_Channel2;
        ii->txdma     = DMA_Channel3;
        ii->clock     = APB2CLOCK;
        dmairq        = IRQ_DMA1_CHANNEL2;
        dman          = 2;
        RCC->APB2ENR |= 1<<12;	// spi
        gpio_init( GPIO_A5, GPIO_AF(5) | GPIO_PUSH_PULL | GPIO_OUTPUT_50MHZ );
        gpio_init( GPIO_A6, GPIO_AF(5) );
        gpio_init( GPIO_A7, GPIO_AF(5) | GPIO_PUSH_PULL | GPIO_OUTPUT_50MHZ );
        break;
    case 1:
        // on ahb1, dma1 chan 4+5
        // CLK = B13, MISO = B14, MOSI = B15
        ii->addr      = addr = SPI2;
        ii->irq       = IRQ_SPI2;
        ii->rxdma     = DMA_Channel4;
        ii->txdma     = DMA_Channel5;
        ii->clock     = APB1CLOCK;
        dmairq        = IRQ_DMA1_CHANNEL4;
        dman          = 4;
        RCC->APB1ENR |= 1<<14;	// spi
        gpio_init( GPIO_B13, GPIO_AF(5) | GPIO_PUSH_PULL | GPIO_OUTPUT_50MHZ );
        gpio_init( GPIO_B14, GPIO_AF(5) );
        gpio_init( GPIO_B15, GPIO_AF(5) | GPIO_PUSH_PULL | GPIO_OUTPUT_50MHZ );
        break;
    case 2:
        // on ahb1, dma1 chan 4+5
        // CLK = B3, MISO = B4, MOSI = B5
        ii->addr      = addr = SPI3;
        ii->irq       = IRQ_SPI3;
        ii->rxdma     = DMA_Channel4;
        ii->txdma     = DMA_Channel5;
        ii->clock     = APB1CLOCK;
        dmairq        = IRQ_DMA1_CHANNEL4;
        dman          = 4;
        RCC->APB1ENR |= 1<<15;	// spi
        gpio_init( GPIO_B3, GPIO_AF(6) | GPIO_PUSH_PULL | GPIO_OUTPUT_50MHZ );
        gpio_init( GPIO_B4, GPIO_AF(6) );
        gpio_init( GPIO_B5, GPIO_AF(6) | GPIO_PUSH_PULL | GPIO_OUTPUT_50MHZ );
        break;
    default:
        // ...
        PANIC("invalid spi device");
    }

    RCC->AHB1ENR |= 1<<21;	// DMA1

#endif

    addr->CR1 |= CR1_SSM | CR1_SSI | CR1_MSTR;
    addr->CR2 &= ~0xE7;

    int speed = set_speed(ii, dev->baud);

    nvic_enable( ii->irq,  IPL_DISK );
    nvic_enable( dmairq,   IPL_DISK );	// rx
    nvic_enable( dmairq+1, IPL_DISK );	// tx

    ii->name  = dev->name;
    ii->state = SPI_STATE_IDLE;

    bootmsg("%s at io 0x%x irq %d dma %d+%d speed %dkHz\n",
            dev->name, ii->addr, ii->irq, dman, dman+1, speed/1000);

    return 0;
}

static int
set_speed(struct SPIInfo *ii, int speed){
    SPI_TypeDef *dev   = ii->addr;
    int cspeed = ii->clock / 2;
    int clkdiv = 0;

    while( clkdiv < 7 && cspeed > speed ){
        cspeed /= 2;
        clkdiv ++;
    }

    dev->CR1 &= ~(7 << 3);
    dev->CR1 |= clkdiv << 3;

    SPI_CRUMB("set-speed", cspeed, 0);
    return cspeed;
}


/****************************************************************/

static void
_spi_dump_crumb(void){
    int i;

#ifdef VERBOSE
    int st = (cur_crumb > NR_CRUMBS) ? cur_crumb - NR_CRUMBS : 0;
    for(i=st; i<cur_crumb; i++){
        int n = i % NR_CRUMBS;
        kprintf("[spi] %s\t%x %x\n", crumbs[n].event, crumbs[n].arg0, crumbs[n].arg1);
    }
#endif
}


// set/clear cs pins
static void
_spi_cspins(const struct SPIConf *cf, int on){
    int nss = cf->nss;
    const char *ss = cf->ss;

    SPI_CRUMB("cspins", on, 0);
    while(nss--){
        int s = *ss ++;
        int m = (s & 0x80) ? 1 : 0;	// hi bit = on/off

        if( on == m )
            gpio_set( s & 0x7F );
        else
            gpio_clear( s & 0x7F );
#ifdef VERBOSE
        // kprintf("pin %x %s\n", (s & 0x7f), (on==m)?"on":"off");
#endif
    }
}


/****************************************************************/

static inline void
_spi_enable_irq(struct SPIInfo *ii){
    SPI_TypeDef *dev = ii->addr;

    SPI_CRUMB("irq-en", 0, 0);
    dev->CR2 |= CR2_TXEIE | CR2_RXNEIE;
}

static inline void
_disable_irq_dma(struct SPIInfo *ii){
    SPI_TypeDef *dev = ii->addr;

    dev->CR2 &= ~( CR2_TXEIE | CR2_RXNEIE | CR2_TXDMAEN | CR2_RXDMAEN );
    ii->rxdma->CCR &= ~(DMACCR_EN | DMACCR_TEIE | DMACCR_TCIE );
    ii->txdma->CCR &= ~(DMACCR_EN | DMACCR_TEIE | DMACCR_TCIE );
}

static inline void
_spi_conf_enable(const struct SPIConf *cf, struct SPIInfo *ii){
    SPI_TypeDef *dev   = ii->addr;

    if( cf->speed ) set_speed(ii, cf->speed);
    dev->CR1 |= CR1_MSTR | CR1_SSI;
}

static inline void
_spi_conf_disable(const struct SPIConf *cf, struct SPIInfo *ii){
    SPI_TypeDef *dev   = ii->addr;

    _disable_irq_dma(ii);
    dev->CR1  &= ~ (CR1_SPE | CR1_CRCEN);

    SPI_CRUMB("spi-off", 0, 0);
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


static void
_dma_conf(DMA_Channel_TypeDef *dmac, char *pdev, char *addr, int len, u_long flags){

    dmac->CPAR  = (u_long) pdev;
    dmac->CMAR  = (u_long) addr;
    dmac->CNDTR = len ? len : 65535;
    dmac->CCR  &= ~ (DMACCR_DIR | DMACCR_MINC);
    dmac->CCR  |= flags | (len ? DMACCR_TEIE | DMACCR_TCIE : 0);
    dmac->CCR  |= DMACCR_EN;
}


static void
_dma_enable_read(struct SPIInfo *ii){
    SPI_TypeDef *dev = ii->addr;

    SPI_CRUMB("en-dma/r", 0, 0);
    // rx dma to buffer; tx dummy
    _dma_conf( ii->rxdma, (char*)& dev->DR, ii->msg->data, ii->msg->dlen, DMACCR_MINC );
    _dma_conf( ii->txdma, (char*)& dev->DR, &dma_idle_source, 0, DMACCR_DIR );

    dev->CR2 |= CR2_TXDMAEN | CR2_RXDMAEN;
}

static void
_dma_enable_write(struct SPIInfo *ii){
    SPI_TypeDef *dev = ii->addr;

    SPI_CRUMB("en-dma/w", 0, 0);
    // tx dma from buffer, rx discard
    _dma_conf( ii->txdma, (char*)& dev->DR, ii->msg->data, ii->msg->dlen, DMACCR_MINC | DMACCR_DIR );
    _dma_conf( ii->rxdma, (char*)& dev->DR, &dma_idle_sink, 0, 0 );

    dev->CR2 |= CR2_TXDMAEN | CR2_RXDMAEN;
}

static void
_msg_abort(struct SPIInfo *ii){

    SPI_CRUMB("msg-abort", ii->msg, 0);

    _disable_irq_dma(ii);
    ii->state = SPI_STATE_ERROR;
    wakeup( ii );
}

static void
_msg_start(struct SPIInfo *ii){
    spi_msg *m = ii->msg;

    SPI_CRUMB("msg-start", m, m->mode);

    // configure
    m->response  = 0;

    switch(m->mode){
    case SPIMO_READ:
        if( m->dlen >= DMA_MIN_SIZE ){
            _dma_enable_read(ii);
            return;
        }
        break;
    case SPIMO_WRITE:
        if( m->dlen >= DMA_MIN_SIZE ){
            _dma_enable_write(ii);
            return;
        }
        break;
    case SPIMO_PINSON:
    case SPIMO_PINSOFF:
        _spi_cspins(ii->cf, (m->mode == SPIMO_PINSON));
        if( ! m->dlen ){
            _msg_next(ii);
            return;
        }
        m->mode = SPIMO_DELAY;
        break;
    case SPIMO_DELAY:
    case SPIMO_UNTIL:
    case SPIMO_FINISH:
        break;
    }

    _spi_enable_irq(ii);
}

static void
_msg_next(struct SPIInfo *ii){

    SPI_CRUMB("msg-next", ii->msg, 0);
    ii->num_msg --;
    ii->msg ++;

    if( ii->num_msg <= 0 ){
        // done
        SPI_CRUMB("msg-done", ii->msg, 0);
        ii->msg = 0;
        ii->state = SPI_STATE_XFER_DONE;
        wakeup( ii );
        return;
    }

    _msg_start(ii);
}

static void
_msg_next_msg(struct SPIInfo *ii){

    _disable_irq_dma(ii);

    // final write => finish writing
    if( ii->num_msg == 1 && ii->msg->mode == SPIMO_WRITE ){
        SPI_TypeDef *dev = ii->addr;
        // wait for the TXEI before we shutdown
        SPI_CRUMB("next-finish", 0, 0);
        ii->msg->mode = SPIMO_FINISH;
        dev->CR2 |= CR2_TXEIE;
        return;
    }

    _msg_next(ii);
}


_irq_spidma_handler(int unit, int dman, DMA_Channel_TypeDef *dmac){
    struct SPIInfo *ii = spiinfo + unit;
    SPI_TypeDef *dev   = ii->addr;
    spi_msg *m = ii->msg;


    // get status, clear irq
    int pos = 4 * (dman - 1);
    int isr = (DMA->ISR >> pos) & 0xF;

    SPI_CRUMB("dma-irq", dman, isr);

    // clear irq
    DMA->IFCR &= ~ (0xF<<pos);

    if( isr & 8 ){
        // error - done
        SPI_CRUMB("dma-err", 0, 0);
        _disable_irq_dma(ii);
        _msg_abort(ii);
        return;
    }

    if( isr & 2 ){
        // dma complete
        if( m && ((u_long)m->data == dmac->CMAR) && ! dmac->CNDTR ){
            SPI_CRUMB("dma-done", ii->msg, 0);
            _disable_irq_dma(ii);
            _msg_next_msg(ii);
        }
    }
}

_irq_spi_handler(int unit){
    struct SPIInfo *ii = spiinfo + unit;
    SPI_TypeDef *dev   = ii->addr;
    spi_msg *m = ii->msg;

    int sr = dev->SR;
    int c;

    SPI_CRUMB("spi-irq", unit, sr);

    if( sr & SR_TXE ){
        SPI_CRUMB("spi-txe", m, m->dlen);

        switch( m->mode ){
        case SPIMO_WRITE:
            dev->DR = *m->data++;
            m->dlen --;
            break;
        case SPIMO_FINISH:
            _msg_next_msg(ii);
            return;
        case SPIMO_READ:
        case SPIMO_UNTIL:
        case SPIMO_DELAY:
            // send dummy byte
            dev->DR = 0xFF;
            break;
        }
    }

    if( sr & SR_RXNE ){
        SPI_CRUMB("spi-rxne", ii->msg, 0);

        switch( m->mode ){
        case SPIMO_WRITE:
        case SPIMO_FINISH:
            c = dev->DR;
            break;
        case SPIMO_READ:
            *m->data++ = dev->DR;
            m->dlen --;
            break;
        case SPIMO_UNTIL:
            c = m->response = dev->DR;
            int r = m->until(c);
            switch(r){
            case 0:		// no match. keep trying?
                if( --m->dlen <= 0 ){
                    SPI_CRUMB("until-dlen", 0, 0);
                    _msg_abort(ii);
                    return;
                }
                break;
            case 1:		// got it, continue on
                _msg_next_msg(ii);
                return;
            case -1:		// got an error
                SPI_CRUMB("until-fail", c, r);
                _msg_abort(ii);
                return;
            }
            break;

        case SPIMO_DELAY:
            c = dev->DR;
            m->dlen --;
            break;
        }
    }

    if( m->dlen <= 0 ){
        _msg_next_msg(ii);
        return;
    }

}

void
spi_clear(const struct SPIConf * cf){
    struct SPIInfo *ii = spiinfo + cf->unit;
    SPI_TypeDef *dev   = ii->addr;
    int i;

    // enable device, pins
    int plx = spldisk();
    _spi_conf_done(cf, ii);
    usleep(10000);
    _spi_conf_start(cf, ii);

    dev->CR1 |= CR1_SPE;

    for(i=0; i<16; i++){
        while( !(dev->SR & SR_TXE) ) {}
        dev->DR   = 0xFF;
    }

    // disable device, pins
    _spi_conf_done(cf, ii);
    usleep(10000);
    splx(plx);
}


int
spi_xfer(const struct SPIConf * cf, int nmsg, spi_msg *msgs, int timeout){
    if( cf->unit >= N_SPI ) return -1;
    if( !nmsg ) return 0;

    struct SPIInfo *ii = spiinfo + cf->unit;
    SPI_TypeDef *dev   = ii->addr;

    if( currproc )
        sync_lock(&ii->lock, "spi.L");

    cur_crumb = 0;

#ifdef VERBOSE
    //kprintf("spi xfer2 starting, %d msgs\n", nmsg);
#endif

    ii->cf        = cf;
    ii->msg       = msgs;
    ii->num_msg   = nmsg;
    ii->state     = SPI_STATE_BUSY;

    // enable device, pins
    int plx = spldisk();
    _spi_conf_start(cf, ii);
    SPI_CRUMB("spi-on", 0, 0);
    dev->CR1 |= CR1_SPE;       // go!
    _msg_start(ii);
    splx(plx);

    utime_t expires = timeout ? get_time() + timeout : 0;

    while( ii->state == SPI_STATE_BUSY ){
        if( currproc ){
            tsleep( ii, -1, ii->name, timeout ? expires - get_time() : 0 );
        }
        if( expires && get_time() > expires ){
            SPI_CRUMB("timeout", 0,0);
            break;
        }
    }

    // wait !busy ( ~ 7 bit times from the txe-irq )
    // probably finished during the time it took to get here
    SPI_CRUMB("spi-wait!busy", dev->SR, 0);
    while( dev->SR & SR_BSY ){
        if( expires && get_time() > expires ) break;
    }

    // disable device, pins
    _spi_conf_done(cf, ii);


#ifdef VERBOSE
    if( (ii->state != SPI_STATE_XFER_DONE) ){
        kprintf("spi xfer\n");
        _spi_dump_crumb();
    }
    //kprintf("spi xfer2 done\n");
#endif

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

void SPI1_IRQHandler(void){ _irq_spi_handler(0); }
void SPI2_IRQHandler(void){ _irq_spi_handler(1); }
// the handlers are named 0-6. everything else uses 1-7
void DMA1_Stream1_IRQHandler(void){ _irq_spidma_handler(0, 2, DMA_Channel2); }
void DMA1_Stream2_IRQHandler(void){ _irq_spidma_handler(0, 3, DMA_Channel3); }
void DMA1_Stream3_IRQHandler(void){ _irq_spidma_handler(1, 4, DMA_Channel4); }
void DMA1_Stream4_IRQHandler(void){ _irq_spidma_handler(1, 5, DMA_Channel5); }


/****************************************************************/
