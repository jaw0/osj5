/*
  Copyright (c) 2013
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2013-Mar-24 21:07 (EDT)
  Function: spi using dma1

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

#define VERBOSE


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


static u_long cur_crumb = 0;

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
    if (cur_crumb < NR_CRUMBS) {
        struct crumb *crumb = &crumbs[cur_crumb++];
        crumb->event = event;
        crumb->arg0 = arg0;
        crumb->arg1 = arg1;
    }
}
#define SPI_CRUMB(event, arg0, arg1) _spi_drop_crumb(event, arg0, arg1)
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

} spiinfo[ N_SPI ];


static int set_speed(struct SPIInfo *, int);



int
spi_init(struct Device_Conf *dev){
    int unit = dev->unit;
    struct SPIInfo *ii = spiinfo + unit;
    SPI_TypeDef *addr;
    int dmairq, dman;

    bzero(spiinfo+unit, sizeof(struct SPIInfo));

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
        gpio_init( GPIO_A7, GPIO_AF_OUTPUT_OD | GPIO_OUTPUT_50MHZ );
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
        gpio_init( GPIO_B15, GPIO_AF_OUTPUT_OD | GPIO_OUTPUT_50MHZ );
        break;
    default:
        // ...
        PANIC("invalid spi device");
    }

    RCC->AHBENR |= 1;	// DMA1

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
    dev->CR1 |= clkdiv;

    return cspeed;
}


/****************************************************************/

static void
_irq_spidma_handler(int unit, int dman, DMA_Channel_TypeDef *dmac){
    struct SPIInfo *ii = spiinfo + unit;
    SPI_TypeDef *dev   = ii->addr;

    SPI_CRUMB("dma-irq", dman, DMA->ISR);

    // get status, clear irq
    int pos = 4 * (dman - 1);
    int isr = (DMA->ISR >> pos) & 0xF;

    // disable irq
    dmac->CCR  &= ~( DMACCR_TEIE | DMACCR_TCIE );
    // clear irq
    DMA->IFCR &= ~ (0xF<<pos);

    if( isr & 8 ){
        // error - done
        SPI_CRUMB("dma-err", 0, 0);
        ii->state = SPI_STATE_ERROR;
        ii->errorflags = -1; // QQQ
        wakeup( ii );
    }
    else if( isr & 2 ){
        // finished - wait for TXE
        SPI_CRUMB("dma-done", 0, 0);
        dev->CR2 |= CR2_TXEIE;
        ii->state = SPI_STATE_DMA_DONE;
    }
}

static void
_irq_spi_handler(int unit){
    struct SPIInfo *ii = spiinfo + unit;
    SPI_TypeDef *dev   = ii->addr;

    int sr = dev->SR;
    SPI_CRUMB("spi-irq", unit, sr);

    if( sr & SR_TXE ){
        // done(ish)
        SPI_CRUMB("spi-txe", 0, 0);

        dev->CR2 &= ~( CR2_TXEIE | CR2_ERRIE );	// disable irq

        if( ii->state != SPI_STATE_XFER_DONE ){
            ii->state = SPI_STATE_XFER_DONE;
            wakeup( ii );
        }
    }
    // NB: since we are running half-duplex,
    // there are always OVR+UDR errors. ignore.

}


void SPI1_IRQHandler(void){ _irq_spi_handler(0); }
void SPI2_IRQHandler(void){ _irq_spi_handler(1); }
// the handlers are named 0-6. everything else uses 1-7
void DMA1_Stream1_IRQHandler(void){ _irq_spidma_handler(0, 2, DMA_Channel2); }
void DMA1_Stream2_IRQHandler(void){ _irq_spidma_handler(0, 3, DMA_Channel3); }
void DMA1_Stream3_IRQHandler(void){ _irq_spidma_handler(1, 4, DMA_Channel4); }
void DMA1_Stream4_IRQHandler(void){ _irq_spidma_handler(1, 5, DMA_Channel5); }

/****************************************************************/

static void
_spi_dump_crumb(void){
    int i;

#ifdef VERBOSE
    for(i=0; i<cur_crumb; i++){
        printf("[spi] %s\t%x %x\n", crumbs[i].event, crumbs[i].arg0, crumbs[i].arg1);
    }
#endif
}


// set/clear cs pins
static void
_spi_cspins(int nss, char *ss, int on){

    while(nss--){
        int s = *ss ++;
        int m = (s & 0x80) ? 1 : 0;	// hi bit = on/off

        if( s == m )
            gpio_set( s & 0x7F );
        else
            gpio_clear( s & 0x7F );
    }
}
/****************************************************************/

static inline void
_dma_start(struct SPIInfo *ii, int read, int len, char *data){
    SPI_TypeDef *dev   = ii->addr;
    DMA_Channel_TypeDef *dmac = read ? ii->rxdma : ii->txdma;

    printf("dma %s %x\n", (read?"rx":"tx"), dmac);
    dmac->CPAR  = (u_long) & dev->DR;
    dmac->CMAR  = (u_long) data;
    dmac->CNDTR = len;
    dmac->CCR  |= DMACCR_MINC | DMACCR_TEIE | DMACCR_TCIE;

    if( read )
        dmac->CCR &= ~ DMACCR_DIR;
    else
        dmac->CCR |= DMACCR_DIR;

    dmac->CCR |= DMACCR_EN;
}

static inline void
_devs_disable(struct SPIInfo *ii){
    // disable spi+dma
    SPI_TypeDef *dev   = ii->addr;

    dev->CR1  &= ~ (CR1_SPE | CR1_CRCEN);
    dev->CR2  &= ~ (CR2_TXDMAEN | CR2_RXDMAEN);

    ii->rxdma->CCR &= ~ DMACCR_EN;
    ii->txdma->CCR &= ~ DMACCR_EN;
}

int
spi_xfer(int unit, int flags, int nss, char *ss, int len, char *data, int timeo){
    struct SPIInfo *ii = spiinfo + unit;
    SPI_TypeDef *dev   = ii->addr;
    int i = 0;

    if( unit >= N_SPI ) return -1;

#ifdef VERBOSE
    printf("spi xfer waiting, state %x\n", ii->state);
#endif
    cur_crumb = 0;

    sync_lock(&ii->lock, "spi.L");

    if( ii->state != SPI_STATE_IDLE ){
        // reset ?
    }

    ii->state = SPI_STATE_BUSY;

#ifdef VERBOSE
    printf("spi xfer starting, %d bytes\n", len);
#endif

    // enable cs pins
    _spi_cspins(nss, ss, 1);
    // start up dma
    dev->CR2 |= (flags & SPI_FLAG_READ) ? CR2_RXDMAEN : CR2_TXDMAEN;
    _dma_start( ii, flags & SPI_FLAG_READ, len, data );

    if( flags & SPI_FLAG_CRC7 ) dev->CR1 |= CR1_CRCEN;
    dev->CR1 |= CR1_SPE | CR1_MSTR | CR1_SSI;	// and go!

    int x = tsleep( ii, -1, ii->name, timeo );

    int r;
    switch(ii->state){
    case SPI_STATE_XFER_DONE:	r = SPI_XFER_OK;	break;
    case SPI_STATE_ERROR:	r = ii->errorflags;	break;
    default:			r = SPI_XFER_TIMEOUT;	break;
    }

    if( (flags & SPI_FLAG_READ) && (flags & SPI_FLAG_CRC7) ){
        int crc = dev->DR;
        // check crc?
    }

#ifdef VERBOSE
    printf("spi xfer finishing\n");
#endif

    // wait !busy ( ~ 7 bit times from the txe-irq )
    while( dev->SR & SR_BSY ) ;
    _devs_disable(ii);

    // restore cs pins
    _spi_cspins(nss, ss, 0);

#ifdef VERBOSE
    _spi_dump_crumb();
    printf("spi xfer done %d\n\n", ii->state);
#endif

    ii->state = SPI_STATE_IDLE;
    sync_unlock( &ii->lock );

    return r;
}

