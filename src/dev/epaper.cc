/*
  Copyright (c) 2015
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2015-Mar-21 12:10 (EDT)
  Function: sharp memory display

*/

extern "C" {
# include <conf.h>
# include <misc.h>
# include <proc.h>
# include <arch.h>
# include <alloc.h>
# include <nstdio.h>
# include <locks.h>
# include <dev.h>
# include <error.h>
# include <spi.h>
# include <i2c.h>
# include <gpio.h>
# include <error.h>
# include <gfxdpy.h>
# include <strings.h>
};

#define CONF_FLAG_ROTATE	0x3	// bottom 2 bits

// args: CSio, DCio, width, height


//****************************************************************

class EPAPER : public GFXdpy {
public:
    int  	port;
    int		speed;
    int		bufsize;
    bool	vcom;

    struct SPIConf spicf_dpy;

    u_char *dpybuf;

    virtual void flush(void);
    virtual void _set_pixel(int, int, int);
    virtual int  _get_pixel(int, int);
    virtual void clear_screen(void);
    virtual void set_colors(void);
    virtual u_char* get_buffer(void) { return dpybuf; }
    virtual bool is_color(void){ return 0; }

private:
    int  _addr(int, int);
    void _initbuf(void);
}  epaperinfo[ N_EPAPER ];



static void _epaper_cmds(EPAPER *, const u_char *, int);
static void _epaper_flush(EPAPER *);
static void _epaper_logo(EPAPER *);
static void _init_dpy(EPAPER *);

//****************************************************************

extern "C" int
epaper_init(struct Device_Conf *dev){
    int unit = dev->unit;
    EPAPER *ii = epaperinfo + unit;

    ii->init();

    // parse out conf

    ii->port    = dev->port & 0x7F;		// spi device number
    ii->speed	= dev->baud;
    ii->_width  = ii->width  = dev->arg[2];
    ii->_height = ii->height = dev->arg[3];

    if( dev->flags & CONF_FLAG_ROTATE )
        ii->set_orientation( dev->flags & CONF_FLAG_ROTATE );

    ii->spicf_dpy.unit  = ii->port;
    ii->spicf_dpy.speed = ii->speed;
    ii->spicf_dpy.nss   = 1;

    // CS is active high
    ii->spicf_dpy.ss[0] = dev->arg[0] | 0x80;	// arg[0] = CS


#if defined(PLATFORM_STM32F1)
    gpio_init( dev->arg[0], GPIO_OUTPUT_PP | GPIO_OUTPUT_10MHZ );
#elif defined(PLATFORM_STM32F4)
    gpio_init( dev->arg[0], GPIO_OUTPUT | GPIO_PUSH_PULL | GPIO_SPEED_25MHZ );
#endif
    gpio_clear( dev->arg[0] );

    // allocate extra space per row to store addr + trailers
    ii->bufsize = ii->_width * ii->_height / 8 + 2 * ii->_height + 2;
    ii->dpybuf  = (u_char*)alloc( ii->bufsize );
    ii->vcom    = 0;

    _init_dpy( ii );

#ifdef PROJECT_SPLASH
    extern void PROJECT_SPLASH( GFXdpy * );
    PROJECT_SPLASH( ii );
#else
    _epaper_logo( ii );
#endif

    bootmsg("%s at spi%d size %dx%d\n", dev->name, ii->port, ii->_width, ii->_height);

    return (int) &epaperinfo[unit].file;
}


/****************************************************************/

static char _initbuf[] = { 0x20, 0, 0 };
void
_init_dpy( EPAPER *ii ){
    spi_msg m;

    // send clear
    m.mode = SPIMO_WRITE;
    m.dlen = 3;
    m.data = _initbuf;
    spi_xfer(& ii->spicf_dpy, 1, &m, 100000);
}

void
EPAPER::_initbuf(void){
    // init addr + trailer info
    int i;

    for(i=0; i<_height; i++){
        short r = i;
        // reverse bits
        r = ((r >> 1) & 0x55) | ((r & 0x55) << 1);
        r = ((r >> 2) & 0x33) | ((r & 0x33) << 2);
        r = ((r >> 4) & 0x0F) | ((r & 0x0F) << 4);

        // fill in trailer
        // and row number (bits reversed)
        dpybuf[ i * (width/8 + 2) ]     = 0;
        dpybuf[ i * (width/8 + 2) + 1 ] = r;
    }
    // final trailer
    dpybuf[ bufsize - 1 ] = 0;
    dpybuf[ bufsize - 2 ] = 0;
}

// flush display buffer to device
void
EPAPER::flush(void){
    spi_msg m;

    _initbuf();
    dpybuf[0] = 0x80 | (vcom ? 0x40 : 0);
    vcom = !vcom;

    m.mode = SPIMO_WRITE;
    m.dlen = bufsize;
    m.data = (char*)dpybuf;

    spi_xfer(& spicf_dpy, 1, &m, 100000);
}

//****************************************************************

void
EPAPER::set_colors(void){
    color_bg = 0;
    color_fg = (text_attr & ATTR_FAINT) ? 0x7f7f7f : 0xffffff;
}

int
EPAPER::_addr(int x, int y){

    // space for addr, trailers, etc
    return y * (_width/8 + 2) + x/8 + 2;
}

void
EPAPER::_set_pixel(int px, int py, int val){

    if( val && !(val & 0x808080) ){
        // dither
        if( (px+py)&1 ) val = 0;
    }
    short p = _addr(px, py);
    short b = 7 - (px & 7);	// bit reversed

    // color reversed
    if( val )
        dpybuf[ p ] &= ~(1 << b);
    else
        dpybuf[ p ] |= 1 << b;
}

int
EPAPER::_get_pixel(int px, int py){
    short p = _addr(px, py);
    short b = 7 - (px & 7);	// bit reversed
    int  pl = dpybuf[ p ] & (1<<b);

    return pl ? 0 : 0xFFFFFF;
}

extern "C" void memset(void*, int, int);
void
EPAPER::clear_screen(void){
    memset(dpybuf, 0xFF, bufsize);
}

//****************************************************************

static void
_epaper_puts(EPAPER *ii, const char *s){

    while( *s )
        ii->putchar(*s ++);
}

extern "C" void
epaper0_puts(const char *s){
    EPAPER *ii = epaperinfo;
    while( *s )
        ii->putchar(*s ++);
}

static void
_epaper_logo(EPAPER *ii){

    ii->clear_screen();
#if 1
    _epaper_puts(ii, "\e[16m\e[2sOS/J5\r\n\e[0s" );
    _epaper_puts(ii, ident);
    _epaper_puts(ii, "\r\nstarting...\r\n\e[0m");
#else
    int i,j;

    for(j=0; j<ii->_height; j++)
        for(i=0; i<ii->_width; i++)
            if( i & 1 ){
                ii->_set_pixel(i,j, 0xFFFFFF);
            }else{
                ii->_set_pixel(i,j, 0);
            }

#endif
    ii->flush();
}

/*****************************************************************/
