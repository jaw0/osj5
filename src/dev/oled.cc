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
# include <locks.h>
# include <dev.h>
# include <error.h>
# include <spi.h>
# include <i2c.h>
# include <gpio.h>
# include <gfxdpy.h>
# include <strings.h>
};

#define SSD1306_I2C_ADDR	0x3C

#define CONF_FLAG_UPSDOWN	0x1
#define CONF_FLAG_HEIGHT32	0x2


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


//****************************************************************

class OLED : public GFXdpy {
public:
    FILE 	file;
    int  	addr;
    int  	port;
    int		speed;
    bool	flag_32high;
    bool	flag_upsdown;
    bool	flag_spi;

    struct SPIConf spicf_dpy;
    struct SPIConf spicf_cmd;

    // the 128x32 needs to be sent 128x64
    // use a full size buffer, or send twice?
    u_char dpybuf[ 128 * 64 / 8 ];

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

    finit( & oledinfo[unit].file );
    oledinfo[unit].file.fs = &oled_port_fs;
    ii->file.d  = (void*)ii;

    if( ii->flag_spi ){
        ii->spicf_cmd.unit  = ii->spicf_dpy.unit  = ii->port;
        ii->spicf_cmd.speed = ii->spicf_dpy.speed = ii->speed;
        ii->spicf_cmd.nss   = ii->spicf_dpy.nss   = 2;
        ii->spicf_cmd.ss[0] = ii->spicf_dpy.ss[0] = dev->arg[0];
        ii->spicf_cmd.ss[1] = ii->spicf_dpy.ss[1] = dev->arg[1];
        ii->spicf_dpy.ss[1] |= 0x80;

        gpio_init( dev->arg[0], GPIO_OUTPUT_PP | GPIO_OUTPUT_10MHZ );
        gpio_init( dev->arg[1], GPIO_OUTPUT_PP | GPIO_OUTPUT_10MHZ );
        gpio_set( dev->arg[0] );
    }

    // init dev
    if( ii->_height == 64 )
        _oled_cmds( ii, oled64_init, sizeof(oled64_init) );
    else
        _oled_cmds( ii, oled32_init, sizeof(oled32_init) );

    _oled_logo( ii );

    if( ii->flag_spi )
        bootmsg("%s at spi%d size %dx%d\n", dev->name, ii->port, ii->_width, ii->_height);
    else
        bootmsg("%s at i2c%d size %dx%d\n", dev->name, ii->port, ii->_width, ii->_height);


    return (int) &oledinfo[unit].file;
}


/****************************************************************/


static void
_oled_cmds(OLED *ii, const u_char *cmd, int len){
    int i;

    if( ii->flag_spi ){
        spi_msg m;
        m.mode = SPIMO_WRITE;
        m.dlen = len;
        m.data = (char*)cmd;

        spi_xfer(& ii->spicf_cmd, 1, &m, 100000);

    }else{

        i2c_msg m;
        m.slave = SSD1306_I2C_ADDR;
        m.clen  = 2;
        m.dlen  = 0;
        m.cdata[0] = 0;

        for(i=0; i<len; i++){
            m.cdata[1] = cmd[i];
            i2c_write1(ii->port, &m);
        }
    }
}

// flush display buffer to device
void
OLED::flush(void){

    if( flag_spi ){
        spi_msg m;
        m.mode = SPIMO_WRITE;
        m.dlen = sizeof(dpybuf);
        m.data = (char*)dpybuf;

        spi_xfer(& spicf_dpy, 1, &m, 100000);

    }else{
        i2c_msg m;
        m.slave = SSD1306_I2C_ADDR;
        m.clen = 1;
        m.cdata[0] = 0x40;
        m.dlen = sizeof(dpybuf);
        m.data = (char*)dpybuf;

        if( currproc ){
            i2c_xfer(port, 1, &m, 1000000);
        }else{
            i2c_write1(port, &m);
        }
    }
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

    if( ii->flag_32high ){
        _oled_puts(ii, "\e[17mOS/J5     \x8F\r\n\e[15m" );
        _oled_puts(ii, ident);
        _oled_puts(ii, "\r\n\e[0m");
    }else{
        _oled_puts(ii, "\e[16m\e[2sOS/J5\r\n\e[0s" );
        _oled_puts(ii, ident);
        _oled_puts(ii, "\r\nstarting...\r\n\e[0m");
    }
    ii->flush();
}

/*****************************************************************/

int
oled_putchar(FILE *f, char ch){
    OLED *ii = (OLED*)f->d;

    if( ch == 0x0B ){
        ii->flush();
        return 1;
    }

    ii->putchar(ch);

    if( (ii->text_flags & GFX_FLAG_AUTOFLUSH) || (ch == '\n') )
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
