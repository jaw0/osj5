/*
  Copyright (c) 2013
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2013-Mar-28 18:18 (EDT)
  Function: ssd1351 color oled display, 128x128, spi

*/

extern "C" {
# include <conf.h>
# include <proc.h>
# include <arch.h>
# include <alloc.h>
# include <misc.h>
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
# include <userint.h>
};

#define CONF_FLAG_UPSDOWN	0x1

struct ssdCmd {
    u_char cmd;
    u_char narg;
    u_char arg[4];
};

#define CMD0(c)			{c, 0}
#define CMD1(c,a0)		{c, 1, {a0}}
#define CMD2(c,a0,a1)		{c, 2, {a0,a1}}
#define CMD3(c,a0,a1,a2)	{c, 3, {a0,a1,a2}}
#define CMD4(c,a0,a1,a2,a3)	{c, 4, {a0,a1,a2,a3}}

static const ssdCmd ssd1351_dpy_init[] = {
    CMD1( 0xFD, 0x12),		       // set command lock
    CMD1( 0xFD, 0xB1),		       // set command lock
    CMD0( 0xAE ),                      // display off
    CMD1( 0xB3, 0xF1),                 // set clock rate
    CMD1( 0xCA, 0x7F),                 // set mux ratio
    CMD1( 0xA0, 0x74),                 // set remap
    CMD2( 0x15, 0, 0x7F),              // set columns
    CMD2( 0x75, 0, 0x7F),              // set rows
    CMD1( 0xA1, 0),                    // start line; 0x60 for 128x96
    CMD1( 0xA2, 0),                    // display offset

    CMD1( 0xB5, 0),                    // set gpio
    CMD1( 0xAB, 0x1),                  // function select
    CMD1( 0xB1, 0x32),                 // precharge
    CMD1( 0xBE, 0x5),                  // vcomh
    CMD3( 0xC1, 0xC8, 0x80, 0xC8),     // contrast abc
    CMD1( 0xC7, 0xF),                  // contrast master
    CMD3( 0xB4, 0xA0, 0xB5, 0x55),     // set vsl
    CMD1( 0xB6, 0x1),                  // precharge2
    CMD0( 0xA6 ),                       // normal display

    CMD0( 0xAF ),                       // display on
};


static const ssdCmd ssd1351_origin[] = {
    CMD2(0x15, 0, 0x7F),              // set columns
    CMD2(0x75, 0, 0x7F),              // set rows
};
static const ssdCmd ssd1351_invert[] = {
    CMD0( 0xA7),
};
static const ssdCmd ssd1351_normal[] = {
    CMD0( 0xA6),
};
static const ssdCmd ssd1351_sleep[] = {
    CMD0( 0xAE),
};
static const ssdCmd ssd1351_awake[] = {
    CMD0( 0xAF),
};
static const ssdCmd ssd1351_display[] = {
    CMD0( 0x5C),
};


//****************************************************************

class SSD1351 : public GFXdpy {
public:
    int  	port;
    int		speed;
    bool	flag_upsdown;

    struct SPIConf spicf_dpy;
    struct SPIConf spicf_cmd;

    u_short *dpybuf;

    virtual void flush(void);
    virtual void _set_pixel(int, int, int);
    virtual int  _get_pixel(int, int);
    virtual int  get_color(int);
    virtual void clear_screen(void);
    virtual void set_colors(void);
    virtual u_char* get_buffer(void) { return (u_char*)dpybuf; }
    virtual bool is_color(void){ return 1; }
    virtual void set_sleep(bool);

}  ssd1351info[ N_SSD1351 ];



static void _ssd1351_cmds(SSD1351 *, const struct ssdCmd *, int);
static void _ssd1351_flush(SSD1351 *);
static void _ssd1351_logo(SSD1351 *);

//****************************************************************

extern "C" int
ssd1351_init(struct Device_Conf *dev){
    int unit = dev->unit;
    SSD1351 *ii = ssd1351info + unit;

    ii->init();

    // parse out conf
    ii->flag_upsdown = dev->flags & CONF_FLAG_UPSDOWN;

    ii->port    = dev->port & 0x7F;		// spi or i2c device number
    ii->speed	= dev->baud;
    ii->_width  = ii->width  = 128;
    ii->_height = ii->height = 128;

    if( ii->flag_upsdown )
        ii->set_orientation( GFX_ORIENT_180 );

#ifdef USE_SPI
    ii->spicf_cmd.unit  = ii->spicf_dpy.unit  = ii->port;
    ii->spicf_cmd.speed = ii->spicf_dpy.speed = ii->speed;

    ii->spicf_cmd.nss   = 2;
    ii->spicf_cmd.ss[0] = dev->arg[0];
    ii->spicf_cmd.ss[1] = dev->arg[1];

    ii->spicf_dpy.nss   = 2;
    ii->spicf_dpy.ss[0] = dev->arg[0];
    ii->spicf_dpy.ss[1] = dev->arg[1] | SPI_SS_INV;

    spi_cf_init( & ii->spicf_cmd );
    spi_cf_init( & ii->spicf_dpy );

#else
    PANIC("spi not configured");
#endif

    ii->dpybuf = (u_short*)((int)alloc(ii->_width * ii->_height * 2 + 32) & ~0x1F);

    // init dev
    _ssd1351_cmds( ii, ssd1351_dpy_init, ELEMENTSIN(ssd1351_dpy_init) );

#ifdef PROJECT_SPLASH
    extern void PROJECT_SPLASH( GFXdpy * );
    PROJECT_SPLASH( ii );
#else
    _ssd1351_logo( ii );
#endif

    bootmsg("%s at spi%d size %dx%d color\n", dev->name, ii->port, ii->_width, ii->_height);

    return (int) &ssd1351info[unit].file;
}


/****************************************************************/

static void
_ssd1351_cmds(SSD1351 *ii, const struct ssdCmd *cmd, int len){
    spi_msg m[3];
    int i, j;

    for(i=0; i<len; i++, cmd++){

        m[0].mode = SPIMO_WRITE;
        m[0].dlen = 1;
        m[0].data = (char*)&cmd->cmd;

        spi_xfer(& ii->spicf_cmd, 1, m, 100000);

        if( cmd->narg == 0 ) continue;

        // device requires wiggling C/D in the middle of the command
        m[0].mode = SPIMO_WRITE;
        m[0].dlen = cmd->narg;
        m[0].data = (char*)cmd->arg;

        spi_xfer(& ii->spicf_dpy, 1, m, 100000);

    }

}

// flush display buffer to device
void
SSD1351::flush(void){
    spi_msg m;

    _ssd1351_cmds(this, ssd1351_origin,  ELEMENTSIN(ssd1351_origin));
    _ssd1351_cmds(this, ssd1351_display, ELEMENTSIN(ssd1351_display));

    m.mode = SPIMO_WRITE;
    m.dlen = _height * _width * 2;
    m.data = (char*)dpybuf;
    spi_xfer(& spicf_dpy, 1, &m, 100000);
}

//****************************************************************
// R5g6b5 - byte-swapped

#define RGB16(r,g,b) \
    (r & 0xF8) | ((b & 0xF8)<<5) | (g>>5) | ((g & 0xE0)<<8)


// faint, normal, bright, other
// Black Red Green Yellow Blue Magenta Cyan White
static u_short color_palette[] = {
    0,                  RGB16(128,0,0),     RGB16(0,128,0),     RGB16(127,127,0),   RGB16(0,0,127),     RGB16(127,0,127),   RGB16(0,127,127),   RGB16(96,96,96),
    0,                  RGB16(235,0,0),     RGB16(0,205,0),     RGB16(205,205,0),   RGB16(0,0,235),     RGB16(192,0,192),   RGB16(0,160,160),   RGB16(160,160,160),
    RGB16(32,32,32),    RGB16(255,85,85),   RGB16(85,255,85),   RGB16(255,255,85),  RGB16(85,85,255),   RGB16(255,85,255),  RGB16(85,255,255),  0xFFFF,
    RGB16(128,128,128), RGB16(255,192,192), RGB16(144,238,144), RGB16(255,255,224), RGB16(173,216,230), RGB16(255,224,255), RGB16(224,255,255), 0xFFFF,
};

void
SSD1351::set_colors(void){

    u_char fg = text_fg | ((text_attr & ATTR_FAINT) ? 0 : 8) | ((text_attr & ATTR_BRIGHT) ? 0x10 : 0);
    u_char bg = text_bg; // QQQ - bg attrs?

    color_fg = color_palette[fg];
    color_bg = color_palette[bg];
}


int
SSD1351::get_color(int rgb){
    int r = (rgb>>16) & 0xFF;
    int g = (rgb>>8) & 0xFF;
    int b = (rgb) & 0xFF;

    return RGB16(r,g,b);
}

//****************************************************************

void
SSD1351::_set_pixel(int px, int py, int val){
    dpybuf[ py * _width + px ] = val;
}

int
SSD1351::_get_pixel(int px, int py){
    return dpybuf[ py * _width + px ];
}

void
SSD1351::clear_screen(void){
    bzero(dpybuf, _height * _width * 2 );
}
void
SSD1351::set_sleep(bool sleep){
    _ssd1351_cmds( this, sleep ? ssd1351_sleep : ssd1351_awake, 1 );
}

//****************************************************************

static void
_ssd1351_puts(SSD1351 *ii, const char *s){

    while( *s )
        ii->putchar(*s ++);
}

extern "C" void
ssd13510_puts(const char *s){
    SSD1351 *ii = ssd1351info;

    while( *s )
        ii->putchar(*s ++);
    ii->flush();
}

static void
_ssd1351_logo(SSD1351 *ii){
    int i;

    int x, y;
    int x0 = ii->width - 32;

    ii->clear_screen();

    for(y=0; y<64; y++)
        for(x=0; x<32; x++){
            ii->set_pixel(x + x0, y, color_palette[ ((x/8) * 8 + y/8) & 0x1f ] );
        }

    _ssd1351_puts(ii, "\e[17mOS/J5\r\n\e[15m" );
    _ssd1351_puts(ii, ident);
    _ssd1351_puts(ii, "\r\nstarting...\r\n\e[0m");

    ii->flush();
}

/*****************************************************************/

