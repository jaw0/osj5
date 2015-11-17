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

// #define SPIVERBOSE


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


#define DMA_MIN_SIZE	64


static u_long cur_crumb = 0;
static char dma_idle_source = 0xFF;
static char dma_idle_sink;


#ifdef SPIVERBOSE
struct crumb {
    const char *event;
    int when;
    int arg0;
    int arg1;
};

#define NR_CRUMBS       128
static struct crumb crumbs[NR_CRUMBS];

static inline void
_spi_drop_crumb(const char *event, u_long arg0, u_long arg1) {
    struct crumb *crumb = &crumbs[cur_crumb % NR_CRUMBS];
    crumb->event = event;
    crumb->when  = get_hrtime();
    crumb->arg0  = arg0;
    crumb->arg1  = arg1;
    cur_crumb++;
}
#define SPI_CRUMB(event, arg0, arg1) _spi_drop_crumb(event, (u_long)arg0, (u_long)arg1)
#else
#define SPI_CRUMB(event, arg0, arg1)
#endif

#if defined(PLATFORM_STM32F1) || defined(PLATFORM_STM32L1)
typedef DMA_Channel_TypeDef DMAC_T;
#elif defined(PLATFORM_STM32F4)
typedef DMA_Stream_TypeDef DMAC_T;
#endif


struct SPIInfo {
    const char		*name;
    SPI_TypeDef 	*addr;
    DMAC_T 		*rxdma, *txdma;

    DMA_TypeDef		*dma;
    u_char		dmachan;

    u_char		dmanrx, dmantx;
    u_char 	  	irq;
    int			clock;

    lock_t		lock;
    int			state;
    u_long		errorflags;

    // currently doing:
    spi_msg		*msg;
    int			num_msg;
    const struct SPIConf	*cf;
    utime_t		timeout;

} spiinfo[ N_SPI ];


static int  _set_speed(struct SPIInfo *, int);
static void _msg_next(struct SPIInfo *);



int
spi_init(struct Device_Conf *dev){
    int unit = dev->unit;
    struct SPIInfo *ii = spiinfo + unit;
    SPI_TypeDef *addr;
    int dmairqrx, dmairqtx, dmanrx, dmantx;

    bzero(ii, sizeof(struct SPIInfo));

#if defined(PLATFORM_STM32F1)
    switch(unit){
    case 0:
        // on ahb2, dma1 chan2+3
        // CLK = A5, MISO = A6, MOSI = A7
        ii->addr      = addr = SPI1;
        ii->irq       = IRQ_SPI1;
        ii->dma       = DMA;
        ii->rxdma     = DMA_Channel2;
        ii->txdma     = DMA_Channel3;
        ii->clock     = APB2CLOCK;
        dmairqrx      = IRQ_DMA1_CHANNEL2;
        dmairqtx      = IRQ_DMA1_CHANNEL3;
        ii->dmanrx    = 2;
        ii->dmantx    = 3;
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
        ii->dma       = DMA;
        ii->rxdma     = DMA_Channel4;
        ii->txdma     = DMA_Channel5;
        ii->clock     = APB1CLOCK;
        dmairqrx      = IRQ_DMA1_CHANNEL4;
        dmairqtx      = IRQ_DMA1_CHANNEL5;
        ii->dmanrx    = 4;
        ii->dmantx    = 5;
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
        // on ahb2, dma2 chan2+3
        // CLK = A5, MISO = A6, MOSI = A7
        ii->addr      = addr = SPI1;
        ii->irq       = IRQ_SPI1;
        ii->rxdma     = DMA2_Stream2;
        ii->txdma     = DMA2_Stream3;
        ii->dma	      = DMA2;
        ii->clock     = APB2CLOCK;
        dmairqrx      = IRQ_DMA2_STREAM2;
        dmairqtx      = IRQ_DMA2_STREAM3;
        ii->dmanrx    = 2;
        ii->dmantx    = 3;
        ii->dmachan   = 3;
        RCC->APB2ENR |= 1<<12;	// spi
        RCC->AHB1ENR |= 1<<22;	// DMA2
        gpio_init( GPIO_A5, GPIO_AF(5) | GPIO_PUSH_PULL | GPIO_SPEED_50MHZ );
        gpio_init( GPIO_A6, GPIO_AF(5) | GPIO_PULL_UP );
        gpio_init( GPIO_A7, GPIO_AF(5) | GPIO_PUSH_PULL | GPIO_SPEED_50MHZ );
        break;
    case 1:
        // on ahb1, dma1 chan 3+4
        // CLK = B13, MISO = B14, MOSI = B15
        ii->addr      = addr = SPI2;
        ii->irq       = IRQ_SPI2;
        ii->rxdma     = DMA1_Stream3;
        ii->txdma     = DMA1_Stream4;
        ii->dma	      = DMA1;
        ii->clock     = APB1CLOCK;
        dmairqrx      = IRQ_DMA1_STREAM3;
        dmairqtx      = IRQ_DMA1_STREAM4;
        ii->dmanrx    = 3;
        ii->dmantx    = 4;
        ii->dmachan   = 0;
        RCC->APB1ENR |= 1<<14;	// spi
        RCC->AHB1ENR |= 1<<21;	// DMA1
        gpio_init( GPIO_B13, GPIO_AF(5) | GPIO_PUSH_PULL | GPIO_SPEED_50MHZ );
        gpio_init( GPIO_B14, GPIO_AF(5) | GPIO_PULL_UP );
        gpio_init( GPIO_B15, GPIO_AF(5) | GPIO_PUSH_PULL | GPIO_SPEED_50MHZ );
        break;
    case 2:
        // on ahb1, dma1 chan 2+5
        // CLK = B3, MISO = B4, MOSI = B5
        ii->addr      = addr = SPI3;
        ii->irq       = IRQ_SPI3;
        ii->rxdma     = DMA1_Stream2;
        ii->txdma     = DMA1_Stream5;
        ii->dma	      = DMA1;
        ii->clock     = APB2CLOCK;
        dmairqrx      = IRQ_DMA1_STREAM2;
        dmairqtx      = IRQ_DMA1_STREAM5;
        ii->dmanrx    = 2;
        ii->dmantx    = 5;
        ii->dmachan   = 0;
        RCC->APB1ENR |= 1<<15;	// spi
        RCC->AHB1ENR |= 1<<21;	// DMA1
        gpio_init( GPIO_B3, GPIO_AF(6) | GPIO_PUSH_PULL | GPIO_SPEED_50MHZ );
        gpio_init( GPIO_B4, GPIO_AF(6) | GPIO_PULL_UP );
        gpio_init( GPIO_B5, GPIO_AF(6) | GPIO_PUSH_PULL | GPIO_SPEED_50MHZ );
        break;
    default:
        // ...
        PANIC("invalid spi device");
    }
#elif defined(PLATFORM_STM32L1)
    switch(unit){
    case 0:
        // on ahb2, dma1 chan2+3
        // CLK = A5, MISO = A6, MOSI = A7
        ii->addr      = addr = SPI1;
        ii->irq       = IRQ_SPI1;
        ii->rxdma     = DMA1_Channel2;
        ii->txdma     = DMA1_Channel3;
        ii->dma       = DMA1;
        ii->clock     = APB2CLOCK;
        dmairqrx      = IRQ_DMA1_CHANNEL2;
        dmairqtx      = IRQ_DMA1_CHANNEL3;
        ii->dmanrx    = 2;
        ii->dmantx    = 3;
        RCC->APB2ENR |= 1<<12;	// spi
        RCC->AHBENR  |= 1<<24;	// DMA1
        gpio_init( GPIO_A5, GPIO_AF(5) | GPIO_PUSH_PULL | GPIO_SPEED_HIGH );
        gpio_init( GPIO_A6, GPIO_AF(5) | GPIO_PULL_UP );
        gpio_init( GPIO_A7, GPIO_AF(5) | GPIO_PUSH_PULL | GPIO_SPEED_HIGH );
        break;
    case 1:
        // on ahb1, dma1 chan 3+4
        // CLK = B13, MISO = B14, MOSI = B15
        ii->addr      = addr = SPI2;
        ii->irq       = IRQ_SPI2;
        ii->rxdma     = DMA1_Channel4;
        ii->txdma     = DMA1_Channel5;
        ii->dma       = DMA1;
        ii->clock     = APB1CLOCK;
        dmairqrx      = IRQ_DMA1_CHANNEL4;
        dmairqtx      = IRQ_DMA1_CHANNEL5;
        ii->dmanrx    = 4;
        ii->dmantx    = 5;
        RCC->APB1ENR |= 1<<14;	// spi
        RCC->AHBENR  |= 1<<24;	// DMA1
        gpio_init( GPIO_B13, GPIO_AF(5) | GPIO_PUSH_PULL | GPIO_SPEED_HIGH );
        gpio_init( GPIO_B14, GPIO_AF(5) | GPIO_PULL_UP );
        gpio_init( GPIO_B15, GPIO_AF(5) | GPIO_PUSH_PULL | GPIO_SPEED_HIGH );
        break;
    case 2:
        // on ahb1, dma2 chan 1+2
        // CLK = B3, MISO = B4, MOSI = B5
        ii->addr      = addr = SPI3;
        ii->irq       = IRQ_SPI3;
        ii->rxdma     = DMA2_Channel1;
        ii->txdma     = DMA2_Channel2;
        ii->dma       = DMA2;
        ii->clock     = APB1CLOCK;
        dmairqrx      = IRQ_DMA2_CHANNEL1;
        dmairqtx      = IRQ_DMA2_CHANNEL2;
        ii->dmanrx    = 1;
        ii->dmantx    = 2;
        RCC->APB1ENR |= 1<<15;	// spi
        RCC->AHBENR  |= 1<<25;	// DMA2
        gpio_init( GPIO_B3, GPIO_AF(6) | GPIO_PUSH_PULL | GPIO_SPEED_HIGH );
        gpio_init( GPIO_B4, GPIO_AF(6) | GPIO_PULL_UP );
        gpio_init( GPIO_B5, GPIO_AF(6) | GPIO_PUSH_PULL | GPIO_SPEED_HIGH );
        break;
    default:
        // ...
        PANIC("invalid spi device");
    }
#else
#  error "unknown platform"
#endif

    addr->CR1 |= CR1_SSM | /*CR1_SSI | */ CR1_MSTR;
    addr->CR2 &= ~0xE7;

    int speed = _set_speed(ii, dev->baud);

    nvic_enable( ii->irq,  IPL_DISK );
    nvic_enable( dmairqrx, IPL_DISK );
    nvic_enable( dmairqtx, IPL_DISK );

    ii->name  = dev->name;
    ii->state = SPI_STATE_IDLE;

    bootmsg("%s at io 0x%x irq %d dma %d+%d speed %dkHz\n",
            dev->name, ii->addr, ii->irq, ii->dmanrx, ii->dmantx, speed/1000);

    return 0;
}

int
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

    SPI_CRUMB("set-speed", cspeed, 0);
    return cspeed;
}


/****************************************************************/

static void
_spi_dump_crumb(void){
    int i;

#ifdef SPIVERBOSE
    int st = (cur_crumb > NR_CRUMBS) ? cur_crumb - NR_CRUMBS : 0;
    int wh = crumbs[st].when;

    for(i=st; i<cur_crumb; i++){
        int n = i % NR_CRUMBS;
        unsigned int dt = crumbs[n].when - wh;
        wh = crumbs[n].when;

        kprintf("[spi] %d\t%s\t%x %x\n", dt, crumbs[n].event, crumbs[n].arg0, crumbs[n].arg1);
    }
#endif
}

void spi_dump_crumb(){_spi_dump_crumb();}

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
#ifdef SPIVERBOSE
        // kprintf("pin %x %s\n", (s & 0x7f), (on==m)?"on":"off");
#endif
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

    dev->DR = val;

    while(1){
        sr = dev->SR;
        if( sr & SR_RXNE ){
            c = dev->DR;
            return c;
        }
    }
}

/****************************************************************/

#if defined(PLATFORM_STM32F1) || defined(PLATFORM_STM32L1)

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

    SPI_CRUMB("en-dma/r", 0, 0);
    // rx dma to buffer; tx dummy
    _dma_conf( ii->rxdma, (char*)& dev->DR, ii->msg->data, ii->msg->dlen, DMACCR_MINC );
    _dma_conf( ii->txdma, (char*)& dev->DR, &dma_idle_source, 0, DMACCR_DIR_M2P );

    dev->CR2 |= CR2_TXDMAEN | CR2_RXDMAEN;
}

static void
_dma_enable_write(struct SPIInfo *ii){
    SPI_TypeDef *dev = ii->addr;

    SPI_CRUMB("en-dma/w", 0, 0);
    // tx dma from buffer, rx discard
    _dma_conf( ii->txdma, (char*)& dev->DR, ii->msg->data, ii->msg->dlen, DMACCR_MINC | DMACCR_DIR_M2P );
    _dma_conf( ii->rxdma, (char*)& dev->DR, &dma_idle_sink, 0, 0 );

    dev->CR2 |= CR2_TXDMAEN | CR2_RXDMAEN;
}

/****************************************************************/

#elif defined(PLATFORM_STM32F4)

static inline int
_dma_isr_clear_irqs(DMA_TypeDef *dma, int dman){
    int isr;
    int pos = (dman & 3) * 8 - (dman & 1) * 2;	// not aligned

    if( dman > 3 ){
        isr = (dma->HISR >> pos) & 0x3F;
        dma->HIFCR |= (0x3D << pos);
    }else{
        isr = (dma->LISR >> pos) & 0x3F;
        dma->LIFCR |= (0x3D << pos);
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

    SPI_CRUMB("en-dma/r", 0, 0);
    // rx dma to buffer; tx dummy
    _dma_isr_clear_irqs( ii->dma, ii->dmanrx );
    _dma_isr_clear_irqs( ii->dma, ii->dmantx );
    _dma_conf( ii->rxdma, ii->dmachan, (char*)& dev->DR, ii->msg->data, ii->msg->dlen, DMASCR_MINC );
    _dma_conf( ii->txdma, ii->dmachan, (char*)& dev->DR, &dma_idle_source, 0, DMASCR_DIR_M2P );

    dev->CR2 |= CR2_TXDMAEN | CR2_RXDMAEN;
}

static void
_dma_enable_write(struct SPIInfo *ii){
    SPI_TypeDef *dev = ii->addr;

    SPI_CRUMB("en-dma/w", 0, 0);
    // tx dma from buffer, rx discard
    _dma_isr_clear_irqs( ii->dma, ii->dmanrx );
    _dma_isr_clear_irqs( ii->dma, ii->dmantx );
    _dma_conf( ii->txdma, ii->dmachan, (char*)& dev->DR, ii->msg->data, ii->msg->dlen, DMASCR_MINC | DMASCR_DIR_M2P );
    _dma_conf( ii->rxdma, ii->dmachan, (char*)& dev->DR, &dma_idle_sink, 0, 0 );

    dev->CR2 |= CR2_TXDMAEN | CR2_RXDMAEN;
}

#else
#  error "unknown platform"
#endif

/****************************************************************/

static inline void
_spi_enable_irq(struct SPIInfo *ii){
    SPI_TypeDef *dev = ii->addr;

    SPI_CRUMB("irq-en", 0, 0);
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

    SPI_CRUMB("spi-off", dev->SR, 0);
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
            SPI_CRUMB("got", c, count);
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
    SPI_CRUMB("until-fail", ii->addr->SR, 0); // m->response, count);
    ii->state = SPI_STATE_ERROR;
    return 1;
}

static void
_msg_dma_wait(struct SPIInfo *ii){
    int plx;

    SPI_CRUMB("msg-dma-wait", 0,0);
    while( 1 ){
        asleep( ii, ii->name );
        if( ii->state != SPI_STATE_BUSY ){
            aunsleep();
            return;
        }
        await( -1, get_time() - ii->timeout );

        if( ii->timeout && get_time() > ii->timeout ){
            SPI_CRUMB("timeout", 0,0);
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

    SPI_CRUMB("msg-do", m->mode, m->dlen);
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


_irq_spidma_handler(int unit, int dman, DMAC_T *dmac){
    struct SPIInfo *ii = spiinfo + unit;
    SPI_TypeDef *dev   = ii->addr;
    spi_msg *m = ii->msg;

#if defined(PLATFORM_STM32F1) || defined(PLATFORM_STM32L1)
    // get status, clear irq
    int pos = 4 * (dman - 1);
    int isr = (ii->dma->ISR >> pos) & 0xF;

    SPI_CRUMB("dma-irq", dman, isr);

    // clear irq
    ii->dma->IFCR |= (0xF<<pos);

    if( isr & 8 ){
        // error - done
        SPI_CRUMB("dma-err", 0, 0);
        _disable_irq_dma(ii);
        ii->state = SPI_STATE_ERROR;
        wakeup( ii );
        return;
    }

    if( isr & 2 ){
        // dma complete
        if( m && ((u_long)m->data == dmac->CMAR) && ! dmac->CNDTR ){
            SPI_CRUMB("dma-done", ii->msg, 0);
            _disable_irq_dma(ii);
            ii->state = SPI_STATE_DMA_DONE;
            wakeup( ii );
        }
    }
#elif defined(PLATFORM_STM32F4)

    int isr = _dma_isr_clear_irqs( ii->dma, dman );
    SPI_CRUMB("dma-irq", dman, isr);

    if( isr & 8 ){
        // error - done
        SPI_CRUMB("dma-err", 0, 0);
        _disable_irq_dma(ii);
        ii->state = SPI_STATE_ERROR;
        wakeup( ii );
        return;
    }

    if( isr & 0x20 ){
        // dma complete
        if( m && ((u_long)m->data == dmac->M0AR) && ! dmac->NDTR ){
            SPI_CRUMB("dma-done", ii->msg, 0);
            _disable_irq_dma(ii);
            ii->state = SPI_STATE_DMA_DONE;
            wakeup( ii );
        }
    }
#else
#  error "unknown platform"
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
        dev->DR   = 0xFF;
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
spi_xfer(const struct SPIConf * cf, int nmsg, spi_msg *msgs, int timeout){
    if( cf->unit >= N_SPI ) return -1;
    if( !nmsg ) return 0;

    struct SPIInfo *ii = spiinfo + cf->unit;
    SPI_TypeDef *dev   = ii->addr;
    int verbose=0;

    if( msgs[0].mode & 0x80 ){
        verbose = 1;
        msgs[0].mode &= ~0x80;
    }

    if( currproc ){
        int r = sync_tlock(&ii->lock, "spi.L", timeout);
        if( !r ) return SPI_XFER_TIMEOUT;
    }

    cur_crumb = 0;

#ifdef SPIVERBOSE
    //kprintf("spi xfer2 starting, %d msgs\n", nmsg);
#endif

    ii->cf        = cf;
    ii->msg       = msgs;
    ii->num_msg   = nmsg;
    ii->state     = SPI_STATE_BUSY;
    ii->timeout   = timeout ? get_time() + timeout : 0;

    // enable device, pins
    _spi_conf_start(cf, ii);
    SPI_CRUMB("spi-on", cf->unit, 0);
    dev->CR1 |= CR1_SPE;       // go!

    while( ii->num_msg > 0 ){
        int plx = splproc();
        _msg_do( ii );
        splx(plx);
        if( ii->state == SPI_STATE_ERROR ){
            SPI_CRUMB("error", 0,0);
            break;
        }
        ii->num_msg --;
        if( ii->msg ) ii->msg ++;
    }

    if( ii->num_msg == 0 && ii->state != SPI_STATE_ERROR )
        ii->state = SPI_STATE_XFER_DONE;

    // wait !busy ( ~ 7 bit times from the txe-irq )
    // probably finished during the time it took to get here
    SPI_CRUMB("spi-wait!busy", dev->SR, 0);
    while( dev->SR & SR_BSY ){
        if( ii->timeout && get_time() > ii->timeout ) break;
    }

    // disable device, pins
    _spi_conf_done(cf, ii);

    SPI_CRUMB("done", ii->state, 0);

#ifdef SPIVERBOSE
    if( verbose || (ii->state != SPI_STATE_XFER_DONE) ){
        kprintf("spi xfer\n");
        _spi_dump_crumb();
    }
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
#elif defined(PLATFORM_STM32F4)
void DMA1_Stream2_IRQHandler(void){ _irq_spidma_handler(2, 2, DMA1_Stream2); }
void DMA1_Stream3_IRQHandler(void){ _irq_spidma_handler(1, 3, DMA1_Stream3); }
void DMA1_Stream4_IRQHandler(void){ _irq_spidma_handler(1, 4, DMA1_Stream4); }
void DMA1_Stream5_IRQHandler(void){ _irq_spidma_handler(2, 5, DMA1_Stream5); }
void DMA2_Stream2_IRQHandler(void){ _irq_spidma_handler(0, 2, DMA2_Stream2); }
void DMA2_Stream3_IRQHandler(void){ _irq_spidma_handler(0, 3, DMA2_Stream3); }
#else
#  error "unknown platform"
#endif

/****************************************************************/
