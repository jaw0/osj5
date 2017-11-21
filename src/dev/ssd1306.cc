/*
  Copyright (c) 2013
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2013-Mar-28 18:18 (EDT)
  Function: ssd1306 monochrome oled display, 128x32 + 128x64, spi + i2c

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
#include <userint.h>
};

#define SSD1306_I2C_ADDR	0x3C

#define CONF_FLAG_UPSDOWN	0x1
#define CONF_FLAG_HEIGHT32	0x2


static const u_char ssd1306_64_init[] = {
//    0xAE, 0xD5, 0x80, 0xA8, 0x3F, 0xD3, 0x00, 0x40, 0x8D, 0x14, 0x20, 0x00, 0xA1,
//    0xC8, 0xDA, 0x12, 0x81, 0xCF, 0xD9, 0xF1, 0xDB, 0x40, 0xA4, 0xA6, 0xAF

0xAE,           	// off
0xD5, 0x80,     	// clock
0xA8, 0x3F,     	// mux ratio
0x20, 0x00,     	// horiz addr mode
0x00, 0x10,             // column start = 0
0x22, 0x00, 0x07,       // page start/end
0x21, 0x00, 0x7f,       // column start/end
0xb0,                   // page start
0x40,           	// dpy start 0
0xD3, 0x00,     	// dpy offset
0xA1,           	// seg remap
0xC8,           	// com out dir
0xDA, 0x12,     	// com pins
0x81, 0xCF,     	// contrast
0xD9, 0xF1,     	// precharge
0xDB, 0x40,     	// vcom level
0xA4,           	// resume from ram
0xA6,           	// normal dpy
0x8D, 0x14,     	// charge pump
0xAF                    // on
};

static const u_char ssd1306_32_init[] = {
0xAE,           	// off
0xD5, 0x80,     	// clock
0xA8, 0x1F,     	// mux ratio
0x20, 0x00,     	// horiz addr mode
0x00, 0x10,             // column start = 0
0x22, 0x00, 0x03,       // page start/end
0x21, 0x00, 0x7f,       // column start/end
0xb0,                   // page start
0x40,           	// dpy start 0
0xD3, 0x00,     	// dpy offset
0xA1,           	// seg remap
0xC8,           	// com out dir
0xDA, 0x02,     	// com pins
0x81, 0x8F,     	// contrast
0xD9, 0xF1,     	// precharge
0xDB, 0x40,     	// vcom level
0xA4,           	// resume from ram
0xA6,           	// normal dpy
0x8D, 0x14,     	// charge pump
0xAF                    // on
};

static const u_char ssd1306_origin[] = { 0x00, 0x10, 0x40 };
static const u_char ssd1306_invert[] = { 0xA7 };
static const u_char ssd1306_normal[] = { 0xA6 };
static const u_char ssd1306_sleep[]  = { 0xAE };
static const u_char ssd1306_awake[]  = { 0xAF };


//****************************************************************

class SSD1306 : public GFXdpy {
public:
    int  	addr;
    int  	port;
    int		speed;
    bool	flag_32high;
    bool	flag_upsdown;
    bool	flag_spi;

    struct SPIConf spicf_dpy;
    struct SPIConf spicf_cmd;

    u_char *dpybuf;

    virtual void flush(void);
    virtual void _set_pixel(int, int, int);
    virtual int  _get_pixel(int, int);
    virtual void clear_screen(void);
    virtual void set_colors(void);
    virtual void set_sleep(bool);
    virtual u_char* get_buffer(void) { return dpybuf; }
    virtual bool is_color(void) { return 0; }

}  ssd1306info[ N_SSD1306 ];



static void _ssd1306_cmds(SSD1306 *, const u_char *, int);
static void _ssd1306_flush(SSD1306 *);
static void _ssd1306_logo(SSD1306 *);

//****************************************************************

extern "C" int
ssd1306_init(struct Device_Conf *dev){
    int unit = dev->unit;
    SSD1306 *ii = ssd1306info + unit;

    ii->init();

    // parse out conf
    ii->flag_32high  = dev->flags & CONF_FLAG_HEIGHT32;
    ii->flag_upsdown = dev->flags & CONF_FLAG_UPSDOWN;
    ii->flag_spi     = dev->port  & 0x80;	// high-bit => use spi

    ii->addr    = dev->addr;			// i2c slave addr
    ii->port    = dev->port & 0x7F;		// spi or i2c device number
    ii->speed	= dev->baud;
    ii->_width  = ii->width  = 128;
    ii->_height = ii->height = ii->flag_32high ? 32 : 64;

    if( ! ii->addr ) ii->addr = SSD1306_I2C_ADDR;
    if( ii->flag_upsdown )
        ii->set_orientation( GFX_ORIENT_180 );

    if( ii->flag_spi ){
#ifdef USE_SPI
        ii->spicf_cmd.unit  = ii->spicf_dpy.unit  = ii->port;
        ii->spicf_cmd.speed = ii->spicf_dpy.speed = ii->speed;
        ii->spicf_cmd.nss   = ii->spicf_dpy.nss   = 2;
        ii->spicf_cmd.ss[0] = ii->spicf_dpy.ss[0] = dev->arg[0];
        ii->spicf_cmd.ss[1] = ii->spicf_dpy.ss[1] = dev->arg[1];
        ii->spicf_dpy.ss[1] |= SPI_SS_INV;

        spi_cf_init( & ii->spicf_cmd );
        spi_cf_init( & ii->spicf_dpy );
#else
        PANIC("spi not configured");
#endif
    }else{
#ifndef USE_I2C
        PANIC("i2c not configured");
#endif
    }

    ii->dpybuf = (u_char*)alloc(ii->_width * ii->_height / 8);

    // init dev
    if( ii->_height == 64 )
        _ssd1306_cmds( ii, ssd1306_64_init, sizeof(ssd1306_64_init) );
    else
        _ssd1306_cmds( ii, ssd1306_32_init, sizeof(ssd1306_32_init) );

#ifdef PROJECT_SPLASH
    extern void PROJECT_SPLASH( GFXdpy * );
    PROJECT_SPLASH( ii );
#else
    _ssd1306_logo( ii );
#endif

    if( ii->flag_spi )
        bootmsg("%s at spi%d size %dx%d\n", dev->name, ii->port, ii->_width, ii->_height);
    else
        bootmsg("%s at i2c%d size %dx%d\n", dev->name, ii->port, ii->_width, ii->_height);


    return (int) &ssd1306info[unit].file;
}


/****************************************************************/


static void
_ssd1306_cmds(SSD1306 *ii, const u_char *cmd, int len){
    int i;

    if( ii->flag_spi ){
#ifdef USE_SPI
        spi_msg m;
        m.mode = SPIMO_WRITE;
        m.dlen = len;
        m.data = (char*)cmd;

        spi_xfer(& ii->spicf_cmd, 1, &m, 100000);
#endif
    }else{
#ifdef USE_I2C
        i2c_msg m;
        m.slave = SSD1306_I2C_ADDR;
        m.clen  = 2;
        m.dlen  = 0;
        m.cdata[0] = 0;

        for(i=0; i<len; i++){
            m.cdata[1] = cmd[i];
            i2c_write1(ii->port, &m);
        }
#endif
    }
}

// flush display buffer to device
void
SSD1306::flush(void){

    if( flag_spi ){
#ifdef USE_SPI
        spi_msg m;
        m.mode = SPIMO_WRITE;
        m.dlen = _height * _width / 8;
        m.data = (char*)dpybuf;

        spi_xfer(& spicf_dpy, 1, &m, 100000);
#endif
    }else{
#ifdef USE_I2C
        i2c_msg m;
        m.slave = SSD1306_I2C_ADDR;
        m.clen = 1;
        m.cdata[0] = 0x40;
        m.dlen = _height * _width / 8;
        m.data = (char*)dpybuf;

        if( currproc ){
            i2c_xfer(port, 1, &m, 1000000);
        }else{
            i2c_write1(port, &m);
        }
#endif
    }
}

//****************************************************************

void
SSD1306::set_colors(void){
    color_bg = 0;
    color_fg = (text_attr & ATTR_FAINT) ? 0x7f7f7f : 0xffffff;
}

void
SSD1306::_set_pixel(int px, int py, int val){

    if( val && !(val & 0x808080) ){
        // dither
        if( (px+py)&1 ) val = 0;
    }

    if( val )
        dpybuf[ (py / 8) * _width + px ] |= 1 <<(py & 7);
    else
        dpybuf[ (py / 8) * _width + px ] &= ~( 1 <<(py & 7) );

}

int
SSD1306::_get_pixel(int px, int py){

    int pl = dpybuf[ (py / 8) * _width + px ];
    return (pl & (1<<(py&7))) ? 0xFFFFFF : 0;
}

void
SSD1306::clear_screen(void){
    bzero(dpybuf, _height * _width / 8);
}

void
SSD1306::set_sleep(bool sleep){
    _ssd1306_cmds( this, sleep ? ssd1306_sleep : ssd1306_awake, 1 );
}

//****************************************************************

static void
_ssd1306_puts(SSD1306 *ii, const char *s){

    while( *s )
        ii->putchar(*s ++);
}

extern "C" void
ssd13060_puts(const char *s){
    SSD1306 *ii = ssd1306info;

    while( *s )
        ii->putchar(*s ++);
    ii->flush();
}

static void
_ssd1306_logo(SSD1306 *ii){

    ii->clear_screen();

    if( ii->flag_32high ){
        _ssd1306_puts(ii, "\e[17mOS/J5       \x8F\r\n\e[15m" );
        _ssd1306_puts(ii, ident);
        _ssd1306_puts(ii, "\r\n\e[0m");
    }else{
        _ssd1306_puts(ii, "\e[16m\e[2sOS/J5\r\n\e[0s" );
        _ssd1306_puts(ii, ident);
        _ssd1306_puts(ii, "\r\nstarting...\r\n\e[0m");
    }
    ii->flush();
}

/*****************************************************************/

#ifdef KTESTING
extern "C" int atoi(const char*);
extern "C"
DEFUN(initoled, "reinit oled")
{
    if( argc < 2 ) return 0;

    int unit = atoi(argv[1]);
    SSD1306 *ii = ssd1306info + unit;

    printf("oled %d init\n", unit);

    if( ii->_height == 64 )
        _ssd1306_cmds( ii, ssd1306_64_init, sizeof(ssd1306_64_init) - 1 );
    else
        _ssd1306_cmds( ii, ssd1306_32_init, sizeof(ssd1306_32_init) - 1 );

    _ssd1306_logo( ii );

    sleep(2);
    _ssd1306_cmds( ii, ssd1306_awake, 1 );

    ii->flush();

    return 0;
}

extern "C"
DEFUN(oledtest, "test")
{
    // unit 0
    SSD1306 *ii = ssd1306info;

    while(1){
        _ssd1306_logo( ii );
        usleep(1000);
    }
}

#endif
