/*
  Copyright (c) 2013
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2013-Mar-28 18:18 (EDT)
  Function: ssd1322 grayscale oled display, 256x64, spi

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

static const ssdCmd ssd1322_dpy_init[] = {
    CMD1( 0xFD, 0x12),		       // set command lock
    CMD0( 0xAE ),                      // display off
    CMD1( 0xB3, 0x91),                 // set clock rate
    CMD1( 0xCA, 0x3F),                 // set mux ratio
    CMD1( 0xA1, 0),                    // start line; 0x60 for 128x96
    CMD1( 0xA2, 0),                    // display offset
    CMD2( 0xA0, 0x14, 0x11),           // set remap/com
    CMD1( 0xB5, 0),                    // set gpio
    CMD1( 0xAB, 0x1),                  // function select - external vdd
    CMD2( 0xB4, 0xA0, 0xFD),	// QQQ undoc, in sample code, vsl?
    CMD1( 0xB1, 0xE2),                 // phase length
    CMD1( 0xB6, 0x8),                  // precharge2
    CMD1( 0xBB, 0x1F),		       // precharge
    CMD1( 0xBE, 0x07),		       // vcom
    CMD1( 0xC1, 0x7F),		       // contrast
    CMD1( 0xC7, 0xF),                  // contrast master

    CMD2(0xD1, 0x82, 0x20),	  // QQQ undoc, in sample code, enhancer?

    CMD0( 0xB9 ),		       // default grayscale
    CMD0( 0xA6 ),                      // normal display
    CMD0( 0xAF ),                      // display on
    CMD0( 0xA9),  		       // exit partial display

};


static const ssdCmd ssd1322_origin[] = {
    CMD2(0x15, 0x1C, 0x5B),           // set columns
    CMD2(0x75, 0, 0x3F),              // set rows
};
static const ssdCmd ssd1322_invert[] = {
    CMD0( 0xA7),
};
static const ssdCmd ssd1322_normal[] = {
    CMD0( 0xA6),
};
static const ssdCmd ssd1322_sleep[] = {
    CMD0( 0xAE),
};
static const ssdCmd ssd1322_awake[] = {
    CMD0( 0xAF),
};
static const ssdCmd ssd1322_display[] = {
    CMD0( 0x5C),
};


//****************************************************************

class SSD1322 : public GFXdpy {
public:
    int  	port;
    int		speed;
    bool	flag_upsdown;

    struct SPIConf spicf_dpy;
    struct SPIConf spicf_cmd;

    u_char *dpybuf;

    virtual void flush(void);
    virtual void _set_pixel(int, int, int);
    virtual int  _get_pixel(int, int);
    virtual int  get_color(int);
    virtual void clear_screen(void);
    virtual void set_colors(void);
    virtual u_char* get_buffer(void) { return (u_char*)dpybuf; }
    virtual bool is_color(void){ return 1; }
    virtual void set_sleep(bool);

}  ssd1322info[ N_SSD1322 ];



static void _ssd1322_cmds(SSD1322 *, const struct ssdCmd *, int);
static void _ssd1322_flush(SSD1322 *);
static void _ssd1322_logo(SSD1322 *);
static void _ssd1322_gamma(SSD1322 *);

//****************************************************************

extern "C" int
ssd1322_init(struct Device_Conf *dev){
    int unit = dev->unit;
    SSD1322 *ii = ssd1322info + unit;

    ii->init();

    // parse out conf
    ii->flag_upsdown = dev->flags & CONF_FLAG_UPSDOWN;

    ii->port    = dev->port & 0x7F;		// spi or i2c device number
    ii->speed	= dev->baud;
    ii->_width  = ii->width  = 256;
    ii->_height = ii->height = 64;

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

    // 4bit grayscale
    ii->dpybuf = (u_char*)((int)alloc(ii->_width * ii->_height / 2 + 32) & ~0x1F);

    // delay
    usleep( 10000 );
    // init dev
    _ssd1322_cmds( ii, ssd1322_dpy_init, ELEMENTSIN(ssd1322_dpy_init) );

    _ssd1322_gamma( ii );

#ifdef PROJECT_SPLASH
    extern void PROJECT_SPLASH( GFXdpy * );
    PROJECT_SPLASH( ii );
#else
    _ssd1322_logo( ii );
#endif

    bootmsg("%s ssd1322 at spi%d size %dx%d gray\n", dev->name, ii->port, ii->_width, ii->_height);

    return (int) &ssd1322info[unit].file;
}


/****************************************************************/

static void
_ssd1322_cmds(SSD1322 *ii, const struct ssdCmd *cmd, int len){
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

static void
_ssd1322_gamma(SSD1322 *ii){
    spi_msg m[3];

    // printf "%d, ", (($_ / 15.0) ** 2.2) * 180 for (0 .. 15)
    const u_char gamma[16] = { 0, 1, 2, 5, 9, 16, 23, 33, 45, 58, 73, 90, 110, 131, 154, 180 };

    m[0].mode = SPIMO_WRITE;
    m[0].dlen = 1;
    m[0].data = "\xB8"; // set gray table

    m[1].mode = SPIMO_WRITE;
    m[1].dlen = 15;
    m[1].data = (char*)gamma + 1; // 1 .. 15

    m[2].mode = SPIMO_WRITE;
    m[2].dlen = 1;
    m[2].data = "\x0"; // enable gray table

    spi_xfer(& ii->spicf_cmd, 1, m,   100000);
    spi_xfer(& ii->spicf_dpy, 1, m+1, 100000);
    spi_xfer(& ii->spicf_cmd, 1, m+2, 100000);

}

// flush display buffer to device
void
SSD1322::flush(void){
    spi_msg m;

    _ssd1322_cmds(this, ssd1322_origin,  ELEMENTSIN(ssd1322_origin));
    _ssd1322_cmds(this, ssd1322_display, ELEMENTSIN(ssd1322_display));

    m.mode = SPIMO_WRITE;
    m.dlen = _height * _width / 2;
    m.data = (char*)dpybuf;
    spi_xfer(& spicf_dpy, 1, &m, 100000);
}

//****************************************************************

// black, normal, faint, bright, other
static u_char color_palette[] = { 0, 0xB, 0x4, 0xF, 0x8 };

void
SSD1322::set_colors(void){

    u_char fg = ((text_attr & ATTR_FAINT) ? 2 : 1) + ((text_attr & ATTR_BRIGHT) ? 2 : 0);
    u_char bg = 0;

    color_fg = color_palette[fg];
    color_bg = color_palette[bg];
}


int
SSD1322::get_color(int rgb){
    int r = (rgb>>16) & 0xFF;
    int g = (rgb>>8) & 0xFF;
    int b = (rgb) & 0xFF;

    return (g + ((r + b)>>1)) >> 5;
}

//****************************************************************

// QQQ - pixels are interleaved: 1L, 1H, 0L, 0H, 3L, 3H, 2L, 2H

static inline int
pix_idx(int py, int px, int w){
    int p = py * w + px;
    return p ;
}

void
SSD1322::_set_pixel(int px, int py, int val){

    val &= 0xF;
    int p = pix_idx(py, px, _width) >> 1;

    if( (px & 1) == 0 ){
        dpybuf[ p ] &= 0x0F;
        dpybuf[ p ] |= ( val << 4 );
    }else{
        dpybuf[ p ] &= 0xF0;
        dpybuf[ p ] |= val;
    }
}

int
SSD1322::_get_pixel(int px, int py){
    int p = pix_idx( py, px, _width) >> 1;
    int x = dpybuf[ p ];

    if( (px & 1) == 0)
        return (x >> 4) & 0xF;
    return x & 0xF;
}

void
SSD1322::clear_screen(void){
    bzero(dpybuf, _height * _width / 2 );
}
void
SSD1322::set_sleep(bool sleep){
    _ssd1322_cmds( this, sleep ? ssd1322_sleep : ssd1322_awake, 1 );
}

//****************************************************************

static void
_ssd1322_puts(SSD1322 *ii, const char *s){

    while( *s )
        ii->putchar(*s ++);
}

extern "C" void
ssd13220_puts(const char *s){
    SSD1322 *ii = ssd1322info;

    while( *s )
        ii->putchar(*s ++);
    ii->flush();
}

static void
_ssd1322_logo(SSD1322 *ii){
    int i;

    int x, y;
    int x0 = ii->width - 32;

    ii->clear_screen();

    for(y=0; y<64; y++)
        for(x=0; x<32; x++){
            ii->set_pixel(x + x0, y, x0>>1);
        }

    _ssd1322_puts(ii, "\e[17mOS/J5\r\n\e[15m" );
    _ssd1322_puts(ii, ident);
    _ssd1322_puts(ii, "\r\nstarting...\r\n\e[0m");

    ii->flush();
}

/*****************************************************************/

