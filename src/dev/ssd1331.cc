/*
  Copyright (c) 2013
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2013-Mar-28 18:18 (EDT)
  Function: ssd1331 color oled display, 96x64 + 128x64, spi

*/

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
# include <error.h>
# include <gfxdpy.h>
# include <strings.h>
};

#define CONF_FLAG_UPSDOWN	0x1
#define CONF_FLAG_HEIGHT32	0x2


int ssd1331_putchar(FILE*, char);
int ssd1331_getchar(FILE*);
int ssd1331_noop(FILE*);
int ssd1331_status(FILE*);
int ssd1331_flush(FILE*);

const struct io_fs ssd1331_port_fs = {
    ssd1331_putchar,
    ssd1331_getchar,
    ssd1331_noop,	// close
    ssd1331_flush,
    ssd1331_status,
    0,
    0,
    0,
    0,
    0,
    0
};

static const u_char ssd1331_dpy_init[] = {
    0xAE, 0xA0, 0x72/*0x76?*/, 0xA1, 0x0, 0xA2, 0, 0xA4, 0xA8, 0x3f, 0xAD, 0x8E,
    0xB0, 0x0B, 0xB1, 0x31, 0xB3, 0xF0, 0x8A, 0x64, 0x8B, 0x78, 0x8C, 0x64, 0xBB,
    0x3A, 0xBE, 0x3E, 0x87, 0x06, 0x81, 0x91, 0x82, 0x50, 0x83, 0x7D, 0xAF
};


static const u_char ssd1331_origin[] = { 0x15, 0, 95, 0x75, 0, 63 };
static const u_char ssd1331_invert[] = { 0xA7 };
static const u_char ssd1331_normal[] = { 0xA4 };


//****************************************************************

class SSD1331 : public GFXdpy {
public:
    FILE 	file;
    int  	port;
    int		speed;
    bool	flag_upsdown;

    struct SPIConf spicf_dpy;
    struct SPIConf spicf_cmd;

    u_short dpybuf[ 96 * 64 ];

    virtual void flush(void);
    virtual void _set_pixel(int, int, int);
    virtual int  _get_pixel(int, int);
    virtual void clear_screen(void);
    virtual void set_colors(void);

}  ssd1331info[ N_SSD1331 ];



static void _ssd1331_cmds(SSD1331 *, const u_char *, int);
static void _ssd1331_flush(SSD1331 *);
static void _ssd1331_logo(SSD1331 *);

//****************************************************************

extern "C" int
ssd1331_init(struct Device_Conf *dev){
    int unit = dev->unit;
    SSD1331 *ii = ssd1331info + unit;

    ii->init();

    // parse out conf
    ii->flag_upsdown = dev->flags & CONF_FLAG_UPSDOWN;

    ii->port    = dev->port & 0x7F;		// spi or i2c device number
    ii->speed	= dev->baud;
    ii->_width  = ii->width  = 96;
    ii->_height = ii->height = 64;

    if( ii->flag_upsdown )
        ii->set_orientation( GFX_ORIENT_180 );

    finit( & ssd1331info[unit].file );
    ssd1331info[unit].file.fs = &ssd1331_port_fs;
    ii->file.d  = (void*)ii;

#ifdef USE_SPI
    ii->spicf_cmd.unit  = ii->spicf_dpy.unit  = ii->port;
    ii->spicf_cmd.speed = ii->spicf_dpy.speed = ii->speed;
    ii->spicf_cmd.nss   = ii->spicf_dpy.nss   = 2;
    ii->spicf_cmd.ss[0] = ii->spicf_dpy.ss[0] = dev->arg[0];
    ii->spicf_cmd.ss[1] = ii->spicf_dpy.ss[1] = dev->arg[1];
    ii->spicf_dpy.ss[1] |= 0x80;

# if defined(PLATFORM_STM32F1)
    gpio_init( dev->arg[0], GPIO_OUTPUT_PP | GPIO_OUTPUT_10MHZ );
    gpio_init( dev->arg[1], GPIO_OUTPUT_PP | GPIO_OUTPUT_10MHZ );
# elif defined(PLATFORM_STM32F4)
    gpio_init( dev->arg[0], GPIO_OUTPUT | GPIO_PUSH_PULL | GPIO_SPEED_25MHZ );
    gpio_init( dev->arg[1], GPIO_OUTPUT | GPIO_PUSH_PULL | GPIO_SPEED_25MHZ );
# else
#  error "unknown platform"
# endif

    gpio_set( dev->arg[0] );
#else
    PANIC("spi cot configured");
#endif


    // init dev
    _ssd1331_cmds( ii, ssd1331_dpy_init, sizeof(ssd1331_dpy_init) );

    _ssd1331_logo( ii );

    bootmsg("%s at spi%d size %dx%d color\n", dev->name, ii->port, ii->_width, ii->_height);

    return (int) &ssd1331info[unit].file;
}


/****************************************************************/


static void
_ssd1331_cmds(SSD1331 *ii, const u_char *cmd, int len){
    int i;

    spi_msg m;
    m.mode = SPIMO_WRITE;
    m.dlen = len;
    m.data = (char*)cmd;

    spi_xfer(& ii->spicf_cmd, 1, &m, 1000000);
}

// flush display buffer to device
void
SSD1331::flush(void){
    spi_msg m;

    m.mode = SPIMO_WRITE;
    m.dlen = sizeof(ssd1331_origin);
    m.data = (char*)ssd1331_origin;
    spi_xfer(& spicf_cmd, 1, &m, 100000);

    m.mode = SPIMO_WRITE;
    m.dlen = sizeof(dpybuf);
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
SSD1331::set_colors(void){

    u_char fg = text_fg | ((text_attr & ATTR_FAINT) ? 0 : 8) | ((text_attr & ATTR_BRIGHT) ? 0x10 : 0);
    u_char bg = text_bg; // QQQ - bg attrs?

    color_fg = color_palette[fg];
    color_bg = color_palette[bg];
}

// R(5) G(6) B(5)
static inline u_short
color24to16(int c){
    return ((c>>3) & 0x1F)	 // B
        |  ((c>>5) & (0x3F<<5))  // G
        |  ((c>>8) & (0x1f<<11)) // R
        ;
}

static inline int
color16to24(u_short c){
    u_char r = (c>>11) & 0x1F;
    u_char g = (c>>5)  & 0x3F;
    u_char b = c & 0x1F;

    r = (r<<3) | (r>>2);
    g = (g<<2) | (g>>4);
    b = (b<<3) | (b>>2);

    return (r<<16) | (g<<8) | b;
}

//****************************************************************

void
SSD1331::_set_pixel(int px, int py, int val){
    dpybuf[ py * _width + px ] = val;
}

int
SSD1331::_get_pixel(int px, int py){
    return dpybuf[ py * _width + px ];
}

void
SSD1331::clear_screen(void){
    bzero(dpybuf, sizeof(dpybuf));
}

//****************************************************************

static void
_ssd1331_puts(SSD1331 *ii, const char *s){

    while( *s )
        ii->putchar(*s ++);
}

extern "C" void
ssd13310_puts(const char *s){
    SSD1331 *ii = ssd1331info;
    while( *s )
        ii->putchar(*s ++);
}

static void
_ssd1331_logo(SSD1331 *ii){
    extern const char *ident;
    int i;

#if 0
    _ssd1331_puts(ii, "\e[11m");

    ii->text_attr = ATTR_REVERSE;
    for(i=0; i<24; i++){
        ii->color_fg = color_palette[i];
        _ssd1331_puts(ii, " ");
    }
    _ssd1331_puts(ii, "\r\n");
    ii->text_attr = 0;
    ii->set_colors();
#else
    int x, y;
    for(y=0; y<64; y++)
        for(x=0; x<24; x++){
            ii->dpybuf[ y * 96 + x + 72 ] = color_palette[ (x/8) * 8 + y/8 ];
        }

#endif
    _ssd1331_puts(ii, "\e[17mOS/J5\r\n\e[15m" );
    _ssd1331_puts(ii, ident);
    _ssd1331_puts(ii, "\r\nstarting...\r\n\e[0m");

    ii->flush();
}

/*****************************************************************/

int
ssd1331_putchar(FILE *f, char ch){
    SSD1331 *ii = (SSD1331*)f->d;

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
ssd1331_flush(FILE *f){
    SSD1331 *ii = (SSD1331*)f->d;

    ii->flush();
}

int
ssd1331_getchar(FILE *f){
    return -1;
}

int
ssd1331_noop(FILE*f){
    return 1;
}

int
ssd1331_status(FILE*f){
    return FST_O;
}

/****************************************************************/
