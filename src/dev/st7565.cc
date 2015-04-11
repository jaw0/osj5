/*
  Copyright (c) 2013
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2013-Aug-26 22:18 (EDT)
  Function: st7565 monochrome lcd display, 128x32 + 128x64, on spi

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

#define CONF_FLAG_UPSDOWN	0x1
#define CONF_FLAG_HEIGHT32	0x2

#define CMD_SET_PAGE  		0xB0
#define CMD_SET_COLUMN_HI  	0x10
#define CMD_SET_COLUMN_LO  	0x00


static const u_char st7565_init_dat[] = {
    0xA0, 0xAE, 0xC0, 0xA2, 0x2F, 0x21, 0x81, 0x3F,
};


//****************************************************************

class ST7565 : public GFXdpy {
public:
    int  	port;
    int		speed;
    bool	flag_32high;
    bool	flag_upsdown;

    struct SPIConf spicf_dpy;
    struct SPIConf spicf_cmd;

    u_char *dpybuf;

    virtual void flush(void);
    virtual void _set_pixel(int, int, int);
    virtual int  _get_pixel(int, int);
    virtual void clear_screen(void);
    virtual void set_colors(void);
    virtual u_char* get_buffer(void) { return dpybuf; }
    virtual bool is_color(void){ return 0; }

}  st7565info[ N_ST7565 ];



static void _st7565_cmds(ST7565 *, const u_char *, int);
static void _st7565_flush(ST7565 *);
static void _st7565_logo(ST7565 *);

//****************************************************************

extern "C" int
st7565_init(struct Device_Conf *dev){
    int unit = dev->unit;
    ST7565 *ii = st7565info + unit;

    ii->init();

    // parse out conf
    ii->flag_32high  = dev->flags & CONF_FLAG_HEIGHT32;
    ii->flag_upsdown = dev->flags & CONF_FLAG_UPSDOWN;

    ii->port    = dev->port & 0x7F;		// spi device number
    ii->speed	= dev->baud;
    ii->_width  = ii->width  = 128;
    ii->_height = ii->height = ii->flag_32high ? 32 : 64;

    if( ii->flag_upsdown )
        ii->set_orientation( GFX_ORIENT_180 );

    ii->spicf_cmd.unit  = ii->spicf_dpy.unit  = ii->port;
    ii->spicf_cmd.speed = ii->spicf_dpy.speed = ii->speed;
    ii->spicf_cmd.nss   = ii->spicf_dpy.nss   = 2;
    ii->spicf_cmd.ss[0] = ii->spicf_dpy.ss[0] = dev->arg[0];	// arg[0] = nCS
    ii->spicf_cmd.ss[1] = ii->spicf_dpy.ss[1] = dev->arg[1];	// arg[1] = nC/D
    ii->spicf_dpy.ss[1] |= 0x80;

#if defined(PLATFORM_STM32F1)
    gpio_init( dev->arg[0], GPIO_OUTPUT_PP | GPIO_OUTPUT_10MHZ );
    gpio_init( dev->arg[1], GPIO_OUTPUT_PP | GPIO_OUTPUT_10MHZ );
#elif defined(PLATFORM_STM32F4)
    gpio_init( dev->arg[0], GPIO_OUTPUT | GPIO_PUSH_PULL | GPIO_SPEED_25MHZ );
    gpio_init( dev->arg[1], GPIO_OUTPUT | GPIO_PUSH_PULL | GPIO_SPEED_25MHZ );
#endif
    gpio_set( dev->arg[0] );

    ii->dpybuf = (u_char*)alloc(ii->_width * ii->_height / 8);

    // init dev
    _st7565_cmds( ii, st7565_init_dat, sizeof(st7565_init_dat) );

#ifdef PROJECT_SPLASH
    extern void PROJECT_SPLASH( GFXdpy * );
    PROJECT_SPLASH( ii );
#else
    _st7565_logo( ii );
#endif

    bootmsg("%s at spi%d size %dx%d\n", dev->name, ii->port, ii->_width, ii->_height);


    return (int) &st7565info[unit].file;
}


/****************************************************************/


static void
_st7565_cmds(ST7565 *ii, const u_char *cmd, int len){
    int i;
    spi_msg m;

    m.mode = SPIMO_WRITE;
    m.dlen = len;
    m.data = (char*)cmd;

    spi_xfer(& ii->spicf_cmd, 1, &m, 100000);
}

// flush display buffer to device
void
ST7565::flush(void){
    spi_msg m;
    char cmd[4];
    int p;

    for(p=0; p<_height/8; p++){
        cmd[0] = CMD_SET_PAGE | p;
        cmd[1] = CMD_SET_COLUMN_HI;
        cmd[2] = CMD_SET_COLUMN_LO;
        _st7565_cmds(this, (const u_char*)cmd, 3);

        m.mode = SPIMO_WRITE;
        m.dlen = 128;
        m.data = (char*)dpybuf + p * 128;

        spi_xfer(& spicf_dpy, 1, &m, 100000);
    }
}

//****************************************************************

void
ST7565::set_colors(void){
    color_bg = 0;
    color_fg = (text_attr & ATTR_FAINT) ? 0x7f7f7f : 0xffffff;
}

void
ST7565::_set_pixel(int px, int py, int val){

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
ST7565::_get_pixel(int px, int py){

    int pl = dpybuf[ (py / 8) * _width + px ];
    return (pl & (1<<(py&7))) ? 0xFFFFFF : 0;
}

void
ST7565::clear_screen(void){
    bzero(dpybuf, _height * _width / 8);
}

//****************************************************************

static void
_st7565_puts(ST7565 *ii, const char *s){

    while( *s )
        ii->putchar(*s ++);
}

extern "C" void
st75650_puts(const char *s){
    ST7565 *ii = st7565info;
    while( *s )
        ii->putchar(*s ++);
}

static void
_st7565_logo(ST7565 *ii){

    ii->clear_screen();

    if( ii->flag_32high ){
        _st7565_puts(ii, "\e[17mOS/J5       \x8F\r\n\e[15m" );
        _st7565_puts(ii, ident);
        _st7565_puts(ii, "\r\n\e[0m");
    }else{
        _st7565_puts(ii, "\e[16m\e[2sOS/J5\r\n\e[0s" );
        _st7565_puts(ii, ident);
        _st7565_puts(ii, "\r\nstarting...\r\n\e[0m");
    }
    ii->flush();
}

/*****************************************************************/
