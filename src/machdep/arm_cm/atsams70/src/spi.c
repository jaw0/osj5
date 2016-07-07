/*
  Copyright (c) 2016
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2016-Jul-03 11:28 (EDT)
  Function: atsam spi

*/

#include <conf.h>
#include <proc.h>
#include <arch.h>
#include <locks.h>
#include <dev.h>
#include <error.h>
#include <misc.h>
#include <spi.h>
#include <gpio.h>
#include <atsam.h>
#include <nvic.h>
#include <pmc.h>
#include <xdma.h>

//#define SPIVERBOSE

#ifdef SPIVERBOSE
#  define CRUMBS	"spi"
#endif
#include <crumbs.h>


#define SPI_STATE_DISABLED          0
#define SPI_STATE_IDLE              1
#define SPI_STATE_XFER_DONE         2
#define SPI_STATE_DMA_DONE	    3
#define SPI_STATE_BUSY              4
#define SPI_STATE_ERROR             -1

#define DMA_MIN_SIZE	64


static char dma_idle_source = 0xFF;
static char dma_idle_sink;


struct SPIInfo {
    const char		*name;
    Spi 		*addr;
    u_char 	  	irq;
    u_char		dmairx, dmaitx;
    u_char		dmacrx, dmactx;

    lock_t		lock;
    int			state;
    u_long		errorflags;

    // currently doing:
    spi_msg		*msg;
    int			num_msg;
    const struct SPIConf	*cf;
    utime_t		timeout;

} spiinfo[ N_SPI ];


static void _msg_next(struct SPIInfo *);
static void _dma_handler(void*);


int
spi_init(struct Device_Conf *dev){
    int unit = dev->unit;
    struct SPIInfo *ii = spiinfo + unit;
    Spi *addr;

    bzero(ii, sizeof(struct SPIInfo));

    switch(unit){
    case 0:
        ii->addr      = addr = SPI0;
        ii->irq       = SPI0_IRQn;
        ii->dmaitx    = 1;
        ii->dmairx    = 2;
        pmc_enable( ID_SPI0 );

        gpio_init( GPIO_D20, GPIO_AF_B );	// MISO
        gpio_init( GPIO_D21, GPIO_AF_B );	// MOSI
        gpio_init( GPIO_D22, GPIO_AF_B );	// SCK
        break;
    case 1:
        ii->addr      = addr = SPI1;
        ii->irq       = SPI1_IRQn;
        ii->dmaitx    = 1;
        ii->dmairx    = 2;
        pmc_enable( ID_SPI1 );

        gpio_init( GPIO_C26, GPIO_AF_C );	// MISO
        gpio_init( GPIO_C27, GPIO_AF_C );	// MOSI
        gpio_init( GPIO_C24, GPIO_AF_C );	// SCK
        break;
    default:
        // ...
        PANIC("invalid spi device");
    }

    ii->dmactx = dma_alloc( (dma_handler_t)_dma_handler, (int)ii );
    ii->dmacrx = dma_alloc( (dma_handler_t)_dma_handler, (int)ii );

    addr->SPI_CR = SPI_CR_SWRST;
    addr->SPI_MR = SPI_MR_MSTR | (0xFF<<24); // maximum dlybcs
    // addr->SPI_CR = 1<<30;	// FIFO enable?
    addr->SPI_CR = SPI_CR_SPIEN;

    nvic_enable( ii->irq,  IPL_DISK );

    ii->name  = dev->name;
    ii->state = SPI_STATE_IDLE;

    bootmsg("%s at io 0x%x irq %d dma %d+%d\n",
            dev->name, ii->addr, ii->irq, ii->dmaitx, ii->dmairx);

    return 0;
}

/****************************************************************/

static void
_spi_dump_crumb(void){
    DUMP_CRUMBS();
}

void spi_dump_crumb(){_spi_dump_crumb();}

// map gpio pin to chip select
static const struct {
    int   gpio;
    char  unit, ss;
    short gpcf;
} _pins2ss[] = {
    { GPIO_B2,  0, 0, GPIO_AF_D },
    { GPIO_A31, 0, 1, GPIO_AF_A },
    { GPIO_D25, 0, 1, GPIO_AF_B },
    { GPIO_D12, 0, 2, GPIO_AF_C },
    { GPIO_D29, 0, 3, GPIO_AF_B },

    { GPIO_C25, 1, 0, GPIO_AF_C },
    { GPIO_C28, 1, 1, GPIO_AF_C },
    { GPIO_C29, 1, 2, GPIO_AF_C },
    { GPIO_C30, 1, 3, GPIO_AF_C },
    { GPIO_D0,  1, 1, GPIO_AF_C },
    { GPIO_D1,  1, 2, GPIO_AF_C },
    { GPIO_D2,  1, 3, GPIO_AF_C },
};


// init CS pins
int
spi_cf_init(struct SPIConf *cf){
    int i, ok=0;

    // ss[0] - index of primary ss
    for(i=0; i<ELEMENTSIN(_pins2ss); i++){
        if( cf->ss[0] != _pins2ss[i].gpio ) continue;

        if( cf->unit != _pins2ss[i].unit ){
            PANIC("SPI SS pin not available on requested device");
        }

        cf->_ss = _pins2ss[i].ss;
        gpio_init( _pins2ss[i].gpio, _pins2ss[i].gpcf );

        // set speed
        int scbr = periph_clock_freq() / cf->speed;
        if( scbr > 255 ) scbr = 255;
        if( scbr < 1  )  scbr = 1;
        spiinfo[ cf->unit ].addr->SPI_CSR[ cf->_ss ] = (scbr << 8) | SPI_CSR_CSAAT | SPI_CSR_NCPHA;
#ifdef SPIVERBOSE
        bootmsg("spi%d/ss%d speed %d\n", cf->unit, cf->_ss, periph_clock_freq() / scbr);
#endif
        ok = 1;
    }

    if( !ok ){
        PANIC("requested SPI SS pin is not valid as a SS pin");
    }

    for(i=1; i<cf->nss; i++){
        gpio_init( cf->ss[i], GPIO_OUTPUT | GPIO_PUSH_PULL );
    }

    return 0;
}

// set/clear cs pins
static void
_spi_cspins(const struct SPIConf *cf, int on){
    int nss = cf->nss - 1;
    const char *ss = cf->ss + 1;
    Spi *dev = spiinfo[ cf->unit ].addr;

    DROP_CRUMB("cspins", on, 0);

    if( on ){
        uint32_t mr = dev->SPI_MR;
        mr &= ~SPI_MR_PCS_Msk;
        uint32_t pcs = 0x0F ^ (1 << cf->_ss);
        mr |= pcs << SPI_MR_PCS_Pos;
        dev->SPI_MR = mr;
    }else{
        dev->SPI_CR = SPI_CR_LASTXFER;
    }

    while(nss--){
        int s = *ss ++;
        int m = (s & 0x80) ? 1 : 0;	// hi bit = on/off

        if( on == m )
            gpio_set( s & 0x7F );
        else
            gpio_clear( s & 0x7F );
    }
}

static inline int
_spi_rxtx1(Spi *dev, int val, int lastp){
    int sr, c;

    // wait until ready
    while(1){
        sr = dev->SPI_SR;
        if( sr & SPI_SR_TDRE  )     break;
        if( sr & SPI_SR_TXEMPTY )   break;
    }

    dev->SPI_TDR = val & 0xFF;
    if( lastp )
        dev->SPI_CR = SPI_CR_LASTXFER;

    while(1){
        sr = dev->SPI_SR;
        if( sr & SPI_SR_RDRF )      break;
    }

    c = dev->SPI_RDR;
    return c & 0xFF;
}

/****************************************************************/

static void
_spi_conf_start(const struct SPIConf *cf, struct SPIInfo *ii){

    _spi_cspins(cf, 1);
}

static void
_spi_conf_done(const struct SPIConf *cf, struct SPIInfo *ii){

    _spi_cspins(cf, 0);
}

/****************************************************************/

static inline int
_msg_until(struct SPIInfo *ii){
    spi_msg *m = ii->msg;
    int count = 0;

    //proc_trace_add("spi/until", m->dlen);

    while( m->dlen -- > 0 ){
        int c = m->response = _spi_rxtx1( ii->addr, 0xFF, 0 );
        int r = m->until(c);

        if( r ==  1 ){
            DROP_CRUMB("got", c, count);
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
    DROP_CRUMB("until-fail", ii->addr->SPI_SR, 0);
    ii->state = SPI_STATE_ERROR;
    return 1;
}

static void
_dma_write(struct SPIInfo *ii){
    spi_msg *m = ii->msg;
    int wto = ii->timeout ? ii->timeout - get_time() : 1000000;

    dma_config(ii->dmactx, XDMAF_M2P | XDMAF_MINC | XDMAF_8BIT, ii->dmaitx, & ii->addr->SPI_TDR, m->data, m->dlen );
    dma_config(ii->dmacrx, XDMAF_P2M | XDMAF_8BIT, ii->dmaitx, & ii->addr->SPI_RDR, &dma_idle_sink, m->dlen );
    dma_start(ii->dmactx);
    dma_start(ii->dmacrx);

    DROP_CRUMB("msg-dma-wait", 0, 0 );
    int r = dma_wait_complete(ii->dmactx, ii, -1, wto);
    DROP_CRUMB("msg-dma-woke", r, ii->addr->SPI_SR);

    dma_stop(ii->dmactx);
    dma_stop(ii->dmacrx);

    if( r ) ii->state = SPI_STATE_ERROR;
}

static void
_dma_read(struct SPIInfo *ii){
    spi_msg *m = ii->msg;
    int wto = ii->timeout ? ii->timeout - get_time() : 1000000;

    dma_config(ii->dmacrx, XDMAF_P2M | XDMAF_MINC | XDMAF_8BIT, ii->dmairx, & ii->addr->SPI_RDR, m->data, m->dlen );
    dma_config(ii->dmactx, XDMAF_M2P | XDMAF_8BIT, ii->dmaitx, & ii->addr->SPI_TDR, &dma_idle_source, m->dlen );
    dma_start(ii->dmacrx);
    dma_start(ii->dmactx);

    DROP_CRUMB("msg-dma-wait", 0, 0 );
    int r = dma_wait_complete(ii->dmacrx, ii, -1, wto);
    DROP_CRUMB("msg-dma-woke", r, ii->addr->SPI_SR);

    dma_stop(ii->dmacrx);
    dma_stop(ii->dmactx);

    if( r ) ii->state = SPI_STATE_ERROR;
}


static inline int
_msg_read(struct SPIInfo *ii){
    spi_msg *m = ii->msg;
    int i;

    if( m->dlen >= DMA_MIN_SIZE ){
        _dma_read(ii);
    }else{
        for(i=0; i<m->dlen; i++)
            m->data[i] = _spi_rxtx1( ii->addr, 0xFF, (ii->num_msg == 1) && (i == m->dlen-1) );
    }

    return 0;
}

static inline int
_msg_write(struct SPIInfo *ii){
    spi_msg *m = ii->msg;
    int i;

    DROP_CRUMB("write", m->dlen, ii->addr->SPI_SR);
    if( m->dlen >= DMA_MIN_SIZE ){
        _dma_write(ii);
    }else{
        for(i=0; i<m->dlen; i++)
            _spi_rxtx1( ii->addr, m->data[i], (ii->num_msg == 1) && (i == m->dlen-1) );
    }

    DROP_CRUMB("/write", 0, ii->addr->SPI_SR);

    return 0;
}


static int
_msg_do(struct SPIInfo *ii){
    spi_msg *m = ii->msg;
    int i;

    DROP_CRUMB("msg-do", m->mode, m->dlen);
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
            _spi_rxtx1( ii->addr, 0xFF, 0 );
        break;
    case SPIMO_FINISH:
        ii->addr->SPI_CR = SPI_CR_LASTXFER;
        while( (ii->addr->SPI_SR & SPI_SR_TXEMPTY) == 0 ){
            if( ii->timeout && get_time() > ii->timeout ) break;
        }
        break;
    }

    return 0;
}


int
spi_xfer(const struct SPIConf * cf, int nmsg, spi_msg *msgs, int timeout){
    if( cf->unit >= N_SPI ) return -1;
    if( !nmsg ) return 0;

    struct SPIInfo *ii = spiinfo + cf->unit;
    Spi *dev   = ii->addr;
    int verbose=0;

    if( msgs[0].mode & 0x80 ){
        verbose = 1;
        msgs[0].mode &= ~0x80;
    }

#ifdef SPIVERBOSE
    kprintf("spi xfer: unit %d, speed %d, nss %d, _ss %d, to %d\n", cf->unit, cf->speed, cf->nss, cf->_ss, timeout);
#endif

    if( currproc ){
        int r = sync_tlock(&ii->lock, "spi.L", timeout);
        if( !r ) return SPI_XFER_TIMEOUT;
    }

    RESET_CRUMBS();


    ii->cf        = cf;
    ii->msg       = msgs;
    ii->num_msg   = nmsg;
    ii->state     = SPI_STATE_BUSY;
    ii->timeout   = timeout ? get_time() + timeout : 0;

    // enable device, pins
    _spi_conf_start(cf, ii);
    DROP_CRUMB("spi-on", cf->unit, 0);

    while( ii->num_msg > 0 ){
        int plx = splproc();
        _msg_do( ii );
        splx(plx);
        if( ii->state == SPI_STATE_ERROR ){
            DROP_CRUMB("error", 0,0);
            break;
        }
        ii->num_msg --;
        if( ii->msg ) ii->msg ++;
    }

    if( ii->num_msg == 0 && ii->state != SPI_STATE_ERROR )
        ii->state = SPI_STATE_XFER_DONE;

    // probably finished during the time it took to get here
    DROP_CRUMB("spi-wait!busy", dev->SPI_SR, 0);
    while( 0 ){
        int x;
        int sr = dev->SPI_SR;
        if( (sr & SPI_SR_TXEMPTY) == 0 || (sr && SPI_SR_SPIENS) == 0 ) break;
        if( sr & SPI_SR_RDRF ) x = dev->SPI_RDR;
        if( ii->timeout && get_time() > ii->timeout ) break;
    }

    // disable device, pins
    _spi_conf_done(cf, ii);

    DROP_CRUMB("done", ii->state, 0);

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
static void
_dma_handler(void *ii){

    DROP_CRUMB("dmairq", ii, 0);
    wakeup( ii );
}
