/*
  Copyright (c) 2013
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2013-Mar-28 18:18 (EDT)
  Function: sh1122 grayscale oled display, 256x64, spi

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

static const ssdCmd sh1122_dpy_init[] = {

    CMD0( 0xAE ),               // display off
    CMD0( 0x40 ),		// Set Display Start Line (0x00~0x7F)
    CMD1( 0x81, 0x80 ),		// Contrast Control Mode Set

    CMD1( 0xA8, 0x3F ),		// Mutiplex Ratio To 64
    CMD0( 0xA0 ),		// Set Segment Re-map (rotation?)
    CMD1( 0xD3, 0x00 ), 	// Set Offset
    CMD0( 0xC0 ),	    	// C0 = scan from COM0 to COM[N-1}; C8=scan From COM[N-1] to COM0

    CMD1( 0xAD, 0x80 ),		// DC-DC voltage and the switch frequency [0x81 = internal DC-DC]
    CMD1( 0xD5, 0x90 ),		// Set Clock as 80 Frames/Sec [0x50]
    CMD1( 0xD9, 0x76 ),	    	// [x28], Set Dis-Charge/Pre-Charge Period
    CMD1( 0xDB, 0x3B ),		// [0x30] Set VCOM Deselect Level Data
    CMD1( 0xDC, 0x1A ),		// [0x1e] Set the segment pad output voltage level at pre-charge stage
    CMD0( 0x30 ),		// Set the discharge voltage level

    CMD1( 0xB0, 0x00 ),		// Row Address Set
    CMD1( 0x10, 0x00 ),		// Column Set

    CMD0( 0xA4 ),               // display on, normal [A5 = all on]
    CMD0( 0xAF ),               // display on

};


static const ssdCmd sh1122_origin[] = {
    CMD1(0x10, 0x00 ),           // set columns
    CMD1(0xB0, 0x00 ),              // set rows
};
static const ssdCmd sh1122_invert[] = {
    CMD0( 0xA7),
};
static const ssdCmd sh1122_normal[] = {
    CMD0( 0xA6),
};
static const ssdCmd sh1122_sleep[] = {
    CMD0( 0xAE),
};
static const ssdCmd sh1122_awake[] = {
    CMD0( 0xAF),
};
static const ssdCmd sh1122_display[] = {
};


//****************************************************************

class SH1122 : public GFXdpy {
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

}  sh1122info[ N_SH1122 ];



static void _sh1122_cmds(SH1122 *, const struct ssdCmd *, int);
static void _sh1122_flush(SH1122 *);
static void _sh1122_logo(SH1122 *);

//****************************************************************

extern "C" int
sh1122_init(struct Device_Conf *dev){
    int unit = dev->unit;
    SH1122 *ii = sh1122info + unit;

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

    // init dev
    _sh1122_cmds( ii, sh1122_dpy_init, ELEMENTSIN(sh1122_dpy_init) );

#ifdef PROJECT_SPLASH
    extern void PROJECT_SPLASH( GFXdpy * );
    PROJECT_SPLASH( ii );
#else
    _sh1122_logo( ii );
#endif

    bootmsg("%s sh1122 at spi%d size %dx%d gray\n", dev->name, ii->port, ii->_width, ii->_height);

    return (int) &sh1122info[unit].file;
}


/****************************************************************/

static void
_sh1122_cmds(SH1122 *ii, const struct ssdCmd *cmd, int len){
    spi_msg m[3];
    int i, j;

    for(i=0; i<len; i++, cmd++){

        m[0].mode = SPIMO_WRITE;
        m[0].dlen = 1;
        m[0].data = (char*)&cmd->cmd;

        spi_xfer(& ii->spicf_cmd, 1, m, 100000);

        if( cmd->narg == 0 ) continue;

        m[0].mode = SPIMO_WRITE;
        m[0].dlen = cmd->narg;
        m[0].data = (char*)cmd->arg;

        spi_xfer(& ii->spicf_cmd, 1, m, 100000);

    }

}

// flush display buffer to device
void
SH1122::flush(void){
    spi_msg m;

    _sh1122_cmds(this, sh1122_origin,  ELEMENTSIN(sh1122_origin));
    _sh1122_cmds(this, sh1122_display, ELEMENTSIN(sh1122_display));

    m.mode = SPIMO_WRITE;
    m.dlen = _height * _width / 2;
    m.data = (char*)dpybuf;
    spi_xfer(& spicf_dpy, 1, &m, 100000);
}

//****************************************************************

// black, normal, faint, bright, other
static u_char color_palette[] = { 0, 0xB, 0x4, 0xF, 0x8 };

void
SH1122::set_colors(void){

    u_char fg = ((text_attr & ATTR_FAINT) ? 2 : 1) + ((text_attr & ATTR_BRIGHT) ? 2 : 0);
    u_char bg = 0;

    color_fg = color_palette[fg];
    color_bg = color_palette[bg];
}


int
SH1122::get_color(int rgb){
    int r = (rgb>>16) & 0xFF;
    int g = (rgb>>8) & 0xFF;
    int b = (rgb) & 0xFF;

    return (g + ((r + b)>>1)) >> 5;
}

//****************************************************************

static inline int
pix_idx(int py, int px, int w){
    int p = py * w + px;
    return p ;
}

void
SH1122::_set_pixel(int px, int py, int val){

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
SH1122::_get_pixel(int px, int py){
    int p = pix_idx( py, px, _width) >> 1;
    int x = dpybuf[ p ];

    if( (px & 1) == 0)
        return (x >> 4) & 0xF;
    return x & 0xF;
}

void
SH1122::clear_screen(void){
    bzero(dpybuf, _height * _width / 2 );
}
void
SH1122::set_sleep(bool sleep){
    _sh1122_cmds( this, sleep ? sh1122_sleep : sh1122_awake, 1 );
}

//****************************************************************

static void
_sh1122_puts(SH1122 *ii, const char *s){

    while( *s )
        ii->putchar(*s ++);
}

extern "C" void
sh11220_puts(const char *s){
    SH1122 *ii = sh1122info;

    while( *s )
        ii->putchar(*s ++);
    ii->flush();
}

static void
_sh1122_logo(SH1122 *ii){
    int i;

    int x, y;
    int x0 = ii->width - 32;

    ii->clear_screen();

    for(y=0; y<64; y++)
        for(x=0; x<32; x++){
            ii->set_pixel(x + x0, y, x0>>1);
        }

    _sh1122_puts(ii, "\e[17mOS/J5\r\n\e[15m" );
    _sh1122_puts(ii, ident);
    _sh1122_puts(ii, "\r\nstarting...\r\n\e[0m");

    ii->flush();
}

/*****************************************************************/
