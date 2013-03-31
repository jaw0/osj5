/*
  Copyright (c) 2013
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2013-Mar-28 18:18 (EDT)
  Function: ssd1306 monochrome oled display, 128x32 + 128x64, spi + i2c

*/

/* XXX - we currently only support 1 device
   need config features for more */

extern "C" {
# include <conf.h>
# include <proc.h>
# include <arch.h>
# include <alloc.h>
# include <nstdio.h>
};
extern "C" {
# include <locks.h>
# include <dev.h>
# include <error.h>
# include <spi.h>
};
extern "C" {
# include <i2c.h>
# include <gpio.h>
# include <gfxdpy.h>
# include <strings.h>
};

#define SSD1306_I2C_ADDR	0x3C

int oled_putchar(FILE*, char);
int oled_getchar(FILE*);
int oled_noop(FILE*);
int oled_status(FILE*);
int oled_flush(FILE*);

const struct io_fs oled_port_fs = {
    oled_putchar,
    oled_getchar,
    oled_noop,	// close
    oled_flush,
    oled_status,
    0,
    0,
    0,
    0,
    0,
    0
};

static const u_char oled64_init[] = {
    0xAE, 0xD5, 0x80, 0xA8, 0x3F, 0xD3, 0x00, 0x40, 0x8D, 0x14, 0x20, 0x00, 0xA1,
    0xC8, 0xDA, 0x12, 0x81, 0xCF, 0xD9, 0xF1, 0xDB, 0x40, 0xA4, 0xA6, 0xAF
};

static const u_char oled32_init[] = {
    0xAE, 0xD5, 0x80, 0xA8, 0x1F, 0xD3, 0x00, 0x40, 0x8D, 0x14, 0x20, 0x00, 0xA1,
    0xC8, 0xDA, 0x02, 0x81, 0x8F, 0xD9, 0xF1, 0xDB, 0x40, 0xA4, 0xA6, 0xAF
};

static const u_char oled_origin[] = { 0x00, 0x10, 0x40 };
static const u_char oled_invert[] = { 0xA7 };
static const u_char oled_normal[] = { 0xA6 };

#ifdef OLED_BUS_SPI
static const struct SPIConf spicf_cmd = {
    0,
    0,
    400000,
    2, { OLED_SPI_CS, OLED_SPI_DC }
};

static const struct SPIConf spicf_dpy = {
    0,
    0,
    400000,
    2, { OLED_SPI_CS, OLED_SPI_DC | 0x80 }
};
#endif


//****************************************************************

class OLED : public GFXdpy {
public:
    FILE file;
    int  addr;
    u_char dpybuf[ 128 * OLED_HEIGHT / 8 ];

    virtual void flush(void);
    virtual void _set_pixel(int, int, int);
    virtual int  _get_pixel(int, int);
    virtual void clear_screen(void);

}  oledinfo[ N_OLED ];



static void _oled_cmds(OLED *, const u_char *, int);
static void _oled_flush(OLED *);
static void _oled_logo(OLED *);

//****************************************************************

extern "C" int
oled_init(struct Device_Conf *dev){
    int unit = dev->unit;
    OLED *ii = oledinfo + unit;

    ii->init();

    // parse out conf
    ii->addr    = dev->addr;
    ii->_width  = ii->width  = 128;
    ii->_height = ii->height = OLED_HEIGHT;

#ifdef OLED_UPSIDEDOWN
    ii->set_orientation( GFX_ORIENT_180 );
#endif

    finit( & oledinfo[unit].file );
    oledinfo[unit].file.fs = &oled_port_fs;
    ii->file.d  = (void*)ii;

#ifdef OLED_BUS_SPI
    gpio_init( OLED_SPI_CS, GPIO_OUTPUT_PP | GPIO_OUTPUT_10MHZ );
    gpio_init( OLED_SPI_DC, GPIO_OUTPUT_PP | GPIO_OUTPUT_10MHZ );
    gpio_set( OLED_SPI_CS );
#endif

    // init dev
    if( ii->_height == 64 )
        _oled_cmds( ii, oled64_init, sizeof(oled64_init) );
    else
        _oled_cmds( ii, oled32_init, sizeof(oled32_init) );

    _oled_logo( ii );

#ifdef OLED_BUS_SPI
    bootmsg("%s at spi%d size %dx%d\n", dev->name, ii->addr, ii->_width, ii->_height);
#else
    bootmsg("%s at i2c%d size %dx%d\n", dev->name, ii->addr, ii->_width, ii->_height);
#endif

    return (int) &oledinfo[unit].file;
}


/****************************************************************/


static void
_oled_cmds(OLED *ii, const u_char *cmd, int len){
    int i;

#ifdef OLED_BUS_SPI

    for(i=0; i<len; i++){
        spi_write1(&spicf_cmd, cmd[i]);
    }
#else
    i2c_msg m;
    m.slave = SSD1306_I2C_ADDR;
    m.clen  = 2;
    m.dlen  = 0;
    m.cdata[0] = 0;

    for(i=0; i<len; i++){
        m.cdata[1] = cmd[i];
        i2c_write1(ii->addr, &m);
    }

#endif
}

void
OLED::flush(void){

#ifdef OLED_BUS_SPI
    if( currproc ){
        spi_xfer(&spicf_dpy, sizeof(dpybuf), (char*) dpybuf, 1000000);
    }else{
        int i;
        for(i=0; i<sizeof(dpybuf); i++)
            spi_write1(&spicf_dpy, dpybuf[i]);
    }
#else
    i2c_msg m;
    m.slave = SSD1306_I2C_ADDR;
    m.clen = 1;
    m.cdata[0] = 0x40;
    m.dlen = sizeof(dpybuf);
    m.data = (char*)dpybuf;

    if( currproc ){
        i2c_xfer(addr, 1, &m, 1000000);
    }else{
        i2c_write1(addr, &m);
    }
#endif
}

//****************************************************************

void
OLED::_set_pixel(int px, int py, int val){

    if( val )
        dpybuf[ (py / 8) * _width + px ] |= 1 <<(py & 7);
    else
        dpybuf[ (py / 8) * _width + px ] &= ~( 1 <<(py & 7) );

}

int
OLED::_get_pixel(int px, int py){

    int pl = dpybuf[ (py / 8) * _width + px ];
    return (pl & (1<<(py&7))) ? 1 : 0;
}

void
OLED::clear_screen(void){
    bzero(dpybuf, sizeof(dpybuf));
}

//****************************************************************

static void
_oled_puts(OLED *ii, const char *s){

    while( *s )
        ii->putchar(*s ++);
}

extern "C" void
oled0_puts(const char *s){
    OLED *ii = oledinfo;
    while( *s )
        ii->putchar(*s ++);
}

static void
_oled_logo(OLED *ii){
    extern const char *ident;

#if OLED_HEIGHT == 64
    _oled_puts(ii, "\e[16m\e[2sOS/J5\r\n\e[0s" );
#else
    _oled_puts(ii, "\e[16mOS/J5      \x8F\r\n\e[10m" );
#endif
    _oled_puts(ii, ident);
    _oled_puts(ii, "\r\nstarting...\r\n\e[0m");

    ii->flush();
}

/*****************************************************************/

int
oled_putchar(FILE *f, char ch){
    OLED *ii = (OLED*)f->d;

    ii->putchar(ch);

    if( ii->text_flags & GFX_FLAG_AUTOFLUSH || ch == '\n' )
        ii->flush();

    return 1;
}

int
oled_flush(FILE *f){
    OLED *ii = (OLED*)f->d;

    ii->flush();
}

int
oled_getchar(FILE *f){
    return -1;
}

int
oled_noop(FILE*f){
    return 1;
}

int
oled_status(FILE*f){
    return FST_O;
}

/****************************************************************/

#if 0

bitmap(){

}

scroll_horiz()
scroll_vert()
draw_(filled)_shape()
invert()
set_rotatation()
height, width,
set_cursor(x, y)

#endif
