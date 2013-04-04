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

#define DMA_MIN_SIZE	8


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

    // currently doing:
    spi_msg		*msg;
    int			num_msg;
    const struct SPIConf	*cf;

} spiinfo[ N_SPI ];


static int set_speed(struct SPIInfo *, int);



int
spi_init(struct Device_Conf *dev){
    int unit = dev->unit;
    struct SPIInfo *ii = spiinfo + unit;
    SPI_TypeDef *addr;
    int dmairq, dman;

    bzero(ii, sizeof(struct SPIInfo));

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
        nvic_clearpending( ii->irq );

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
        kprintf("[spi] %s\t%x %x\n", crumbs[i].event, crumbs[i].arg0, crumbs[i].arg1);
    }
#endif
}


// set/clear cs pins
static void
_spi_cspins(const struct SPIConf *cf, int on){
    int nss = cf->nss;
    const char *ss = cf->ss;

    while(nss--){
        int s = *ss ++;
        int m = (s & 0x80) ? 1 : 0;	// hi bit = on/off

        if( on == m )
            gpio_set( s & 0x7F );
        else
            gpio_clear( s & 0x7F );
#ifdef VERBOSE
        kprintf("pin %x %s\n", (s & 0x7f), (on==m)?"on":"off");
#endif
    }
}


/****************************************************************/

static void
_dma_start(struct SPIInfo *ii, int read, int len, char *data){
    SPI_TypeDef *dev   = ii->addr;
    DMA_Channel_TypeDef *dmac = read ? ii->rxdma : ii->txdma;

    // kprintf("dma %s %x\n", (read?"rx":"tx"), dmac);
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


/****************************************************************/

static inline void
_spi_conf_enable(const struct SPIConf *cf, struct SPIInfo *ii){
    SPI_TypeDef *dev   = ii->addr;

    if( cf->speed ) set_speed(ii, cf->speed);
    if( cf->flags & SPI_FLAG_CRC7 ) dev->CR1 |= CR1_CRCEN;
    dev->CR1 |= CR1_MSTR | CR1_SSI;
}

static inline void
_spi_conf_disable(const struct SPIConf *cf, struct SPIInfo *ii){
    SPI_TypeDef *dev   = ii->addr;

    dev->CR1  &= ~ (CR1_SPE | CR1_CRCEN);
    dev->CR2  &= ~ (CR2_TXDMAEN | CR2_RXDMAEN);

    ii->rxdma->CCR &= ~ DMACCR_EN;
    ii->txdma->CCR &= ~ DMACCR_EN;
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


int
spi_xfer(const struct SPIConf *cf, int len, char *data, int timeo){
    if( cf->unit >= N_SPI ) return -1;

    struct SPIInfo *ii = spiinfo + cf->unit;
    SPI_TypeDef *dev   = ii->addr;
    int flags = cf->flags;
    int i = 0;

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

    _spi_conf_start(cf, ii);
    dev->CR2 |= (flags & SPI_FLAG_READ) ? CR2_RXDMAEN : CR2_TXDMAEN;
    _dma_start( ii, flags & SPI_FLAG_READ, len, data );
    dev->CR1 |= CR1_SPE;	// go!

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
    _spi_dump_crumb();
    printf("spi xfer finishing\n");
#endif

    // wait !busy ( ~ 7 bit times from the txe-irq )
    // probably finished during the time it took to get here
    while( dev->SR & SR_BSY ) ;

    _spi_conf_done(cf, ii);

#ifdef VERBOSE
    printf("spi xfer done %d\n\n", ii->state);
#endif

    ii->state = SPI_STATE_IDLE;
    sync_unlock( &ii->lock );

    return r;
}


// write just one byte. not really worth the irq overhead.
int
spi_write1(const struct SPIConf *cf, int data){
    if( cf->unit >= N_SPI ){
        kprintf("invalid spi unit %d\n", cf->unit);
        return -1;
    }
    struct SPIInfo *ii = spiinfo + cf->unit;
    SPI_TypeDef *dev   = ii->addr;
    int i = 0;

    sync_lock(&ii->lock, "spi.L");

    if( ii->state != SPI_STATE_IDLE ){
        // QQQ
        kprintf("spi busy\n");
        return;
    }

    ii->state = SPI_STATE_BUSY;

#ifdef VERBOSE
    kprintf("spi xfer starting, 1 byte\n");
#endif

    _spi_conf_start(cf, ii);
    dev->CR1 |= CR1_SPE;	// and go!

    while( !(dev->SR & SR_TXE) ) ;		// it should be empty
    dev->DR = data;

#ifdef VERBOSE
    kprintf("spi xfer finishing\n");
#endif

    // wait !busy
    while( dev->SR & SR_BSY ){
        if( currproc ) yield();
    }

    _spi_conf_done(cf, ii);

#ifdef VERBOSE
    kprintf("spi xfer done %d\n\n", ii->state);
#endif

    ii->state = SPI_STATE_IDLE;
    sync_unlock( &ii->lock );

    return 0;
}

/****************************************************************/
#ifdef USE_SDCARD

static int
_spi_tx1(SPI_TypeDef *dev, int val){
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
// same same
#define _spi_rx1(d) _spi_tx1(d, 0xFF)

static void
_spi_tx_cmd(SPI_TypeDef *dev, int cmd, int arg){
    _spi_tx1(dev, cmd | 0x40 );
    _spi_tx1(dev, (arg>>24) & 0xFF );
    _spi_tx1(dev, (arg>>16) & 0xFF );
    _spi_tx1(dev, (arg>> 8) & 0xFF );
    _spi_tx1(dev, (arg)     & 0xFF );
    // CRC need to be correct only for cmd0 + cmd8
    _spi_tx1(dev, (cmd == 8) ? 0x87 : 0x95);
}

static int
_spi_rx_r1(SPI_TypeDef *dev){
    int max = 0xFFFF;
    int sr;

    while( max-- > 0 ){
        int c = _spi_rx1(dev);
        // wait for bit7=0
        if( !(c & 0x80) ) return c;
    }
    return 0xFF;
}

static int
_spi_tx_cmd_rx1(SPI_TypeDef *dev, const struct SPIConf *cf, int cmd, int arg){

    _spi_cspins(cf, 1);
    _spi_tx_cmd(dev, cmd, arg);
    int r = _spi_rx_r1(dev);
    _spi_cspins(cf, 0);
    return r;
}

static int
_spi_tx_cmd_rx5(SPI_TypeDef *dev, const struct SPIConf *cf, int cmd, int arg, char *res){
    int i;

    _spi_cspins(cf, 1);
    _spi_tx_cmd(dev, cmd, arg);
    int r = _spi_rx_r1(dev);

    for(i=0; i<4; i++)
        res[i] = _spi_rx1(dev);
    _spi_cspins(cf, 0);
    return r;
}

_spi_tx_cmd_rx16(SPI_TypeDef *dev, const struct SPIConf *cf, int cmd, int arg, char *res){

    _spi_cspins(cf, 1);
    _spi_tx_cmd(dev, cmd, arg);
    int r = _spi_rx_r1(dev);

    // wait for data-token
    int max = 200;
    while( max-- > 0 ){
        int c = _spi_rx1(dev);
        if( c != 0xFF ) break;
    }

    int i;
    for(i=0; i<16; i++)
        res[i] = _spi_rx1(dev);

    // discard crc
    _spi_rx1(dev);
    _spi_rx1(dev);

    _spi_cspins(cf, 0);
    return r;

}

// initialize card - busy wait
int
spi_sd_init(const struct SPIConf *cf, char *cid, char *csd){
    if( cf->unit >= N_SPI ){
        kprintf("invalid spi unit %d\n", cf->unit);
        return -1;
    }

    struct SPIInfo *ii = spiinfo + cf->unit;
    SPI_TypeDef *dev   = ii->addr;
    int i, res;

    // lock
    sync_lock(&ii->lock, "spi.L");
    int plx = spldisk();
    // enable
    set_speed(ii, 400000);
    _spi_conf_enable(cf, ii);
    dev->CR1 |= CR1_SPE;	// go!
    // pins off
    _spi_cspins(cf, 0);

    // delay: TX 10 * 0xFF
    for(i=0; i<10; i++)
        _spi_tx1(dev, 0xFF);
    // pins on
    _spi_cspins(cf, 1);

    // cmd0
    i = _spi_tx_cmd_rx1(dev, cf, 0, 0);

    if( i == 0xFF ){
        // timed out. no card present
        res = -1;
        goto done;
    }
    kprintf("cmd0 %x\n", i);

    // cmd8 - required to enable v2/HC features (>2GB)
    int rcmd8, isv2=0;

    _spi_tx1(dev, 0xFF);	// delay
    i = _spi_tx_cmd_rx5(dev, cf, 8, 0x1AA, (char*)&rcmd8);
    // no response or invalid cmd => v1.0, else v2.0
    kprintf("cmd8 %x %x\n", i, rcmd8);
    if( (i & 0x7E) == 0 ) isv2 = 1;	// 2.0 yay!
    // RSN - check voltages

    // loop until ready
    //  cmd 55/41 => R1
    int max = 1000;
    while( max-- > 0 ){
        int rcmd41;
        _spi_tx1(dev, 0xFF);	// delay
        i = _spi_tx_cmd_rx1(dev, cf, 55, 0);
        _spi_tx1(dev, 0xFF);	// delay
        i = _spi_tx_cmd_rx1(dev, cf, 41, isv2 ? 0x40000000 : 0);
        if( !(i & 1) ) break;
    }

    if( i ){
        res = -1;
        goto done;
    }

    kprintf("sd41 %x, max %d\n", i, max);

    // cmd 58 => R3
    int ocr;
    for(i=0;i<4;i++)
        _spi_tx1(dev, 0xFF);	// delay

    i = _spi_tx_cmd_rx5(dev, cf, 58, 0, (char*)&ocr);
    // NB - ocr is byte swapped
    kprintf("ocr %x %x\n", i, ocr);
    // OCR - permitted voltages + CCS
    int ishc = 0;
    if( isv2 && (ocr & 0x40) ) ishc = 1;	// HC yay!
    // card is ready

    // CID - 16 bytes, manuf, model, serialno,
    // CSD - 16 bytes, timing, size
    for(i=0;i<16;i++)
        _spi_tx1(dev, 0xFF);	// delay
    i = _spi_tx_cmd_rx16(dev, cf, 10, 0, cid);
    kprintf("cid %x\n", i);
    for(i=0;i<16;i++)
        _spi_tx1(dev, 0xFF);	// delay

    i = _spi_tx_cmd_rx16(dev, cf,  9, 0, csd);

    _spi_tx1(dev, 0xFF);	// delay
    kprintf("csd %x\n", i);

    //hexdump(cid, 16);
    //hexdump(csd, 16);


    res = 0;

  done:
    // pins off
    // disable
    _spi_conf_done(cf, ii);
    splx(plx);
    // unlock
    sync_unlock( &ii->lock );
    return res;
}

#endif

