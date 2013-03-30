/*
  Copyright (c) 2013
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2013-Mar-28 18:18 (EDT)
  Function: ssd1306 monochrome oled display, 128x32 + 128x64, spi + i2c

*/

/* XXX - we currently only support 1 device
   need config features for more */

#include <conf.h>
#include <proc.h>
#include <arch.h>
#include <alloc.h>
#include <nstdio.h>
#include <locks.h>
#include <dev.h>
#include <error.h>
#include <spi.h>
#include <i2c.h>
#include <gpio.h>

#include "font_5x7.h"


#define ORIENT_0	0
#define ORIENT_90	1
#define ORIENT_180	2
#define ORIENT_270	3


int oled_putchar(FILE*, char);

const struct io_fs oled_port_fs = {
    oled_putchar,
    0, //oled_getchar,
    0,
    0,
    0, // oled_status,
    0,
    0,
    0,
    0,
    0,
    0
};

static const char oled64_init[] = {
    0xAE, 0xD5, 0x80, 0xA8, 0x3F, 0xD3, 0x00, 0x40, 0x8D, 0x14, 0x20, 0x00, 0xA1,
    0xC8, 0xDA, 0x12, 0x81, 0xCF, 0xD9, 0xF1, 0xDB, 0x40, 0xA4, 0xA6, 0xAF
};

static const char oled32_init[] = {
    0xAE, 0xD5, 0x80, 0xA8, 0x1F, 0xD3, 0x00, 0x40, 0x8D, 0x14, 0x20, 0x00, 0xA1,
    0xC8, 0xDA, 0x02, 0x81, 0x8F, 0xD9, 0xF1, 0xDB, 0x40, 0xA4, 0xA6, 0xAF
};

static const char oled_origin[] = { 0x00, 0x10, 0x40 };
static const char oled_invert[] = { 0xA7 };
static const char oled_normal[] = { 0xA6 };

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


#define MAXX3ARG 4
struct OLED {
    FILE file;
    int _height;
    int _width;

    int orientation;
    int	height;
    int width;

    int x,y;
    int text_attr;
    int text_scale;

    int x3_argn;
    char x3_arg[MAXX3ARG];
    int x3_mode;
#define GOTESC		0x100
#define GOTBRACK	0x200

    int addr;
    u_char dpybuf[ 128 * OLED_HEIGHT / 8 ];
}  oledinfo[ N_OLED ];



static void _oled_cmds(struct OLED *, const u_char *, int);
static void _oled_flush(struct OLED *);
static void _oled_logo(struct OLED *);


int
oled_init(struct Device_Conf *dev){
    int unit = dev->unit;
    struct OLED *ii = oledinfo + unit;

    bzero(ii, sizeof(struct OLED));

    // parse out conf
    ii->addr = dev->addr;
    ii->_width  = ii->width  = 128;
    ii->_height = ii->height = OLED_HEIGHT;
    ii->text_scale = 1;
#ifdef OLED_UPSIDEDOWN
    ii->orientation = ORIENT_180;
#endif

    finit( & oledinfo[unit].file );
    oledinfo[unit].file.fs = &oled_port_fs;

    gpio_init( OLED_SPI_CS, GPIO_OUTPUT_PP | GPIO_OUTPUT_10MHZ );
    gpio_init( OLED_SPI_DC, GPIO_OUTPUT_PP | GPIO_OUTPUT_10MHZ );
    gpio_set( OLED_SPI_CS );

    // init dev
    if( ii->_height == 64 )
        _oled_cmds( ii, oled64_init, sizeof(oled64_init) );
    else
        _oled_cmds( ii, oled32_init, sizeof(oled32_init) );

    _oled_logo( ii );

#ifdef OLED_BUS_SPI
    bootmsg("%s at spi 0x%x size %dx%d\n", dev->name, ii->addr, ii->_width, ii->_height);
#else
#endif

    return 0;
    return (int) &oledinfo[unit].file;
}


/****************************************************************/


static void
_oled_cmds(struct OLED *ii, const u_char *cmd, int len){

#ifdef OLED_BUS_SPI
    int i, d;
    //for(d=0; d<1000000; d++) asm("nop");

    for(i=0; i<len; i++){
        //for(d=0; d<100000; d++) asm("nop");
        spi_write1(&spicf_cmd, cmd[i]);
        //for(d=0; d<100000; d++) asm("nop");
    }
#else
    // RSN - i2c
#endif
}

static void
_oled_flush(struct OLED *ii){

    if( currproc ){
        spi_xfer(&spicf_dpy, sizeof(ii->dpybuf), ii->dpybuf, 1000000);
    }else{
        int i;
        for(i=0; i<sizeof(ii->dpybuf); i++)
            spi_write1(&spicf_dpy, ii->dpybuf[i]);
    }
}

static void
_oled_set_orientation(struct OLED *ii, int orient){

    ii->orientation = orient;
    switch( orient ){
    case ORIENT_0:
    case ORIENT_180:
        ii->width  = ii->_width;
        ii->height = ii->_height;
        break;
    case ORIENT_90:
    case ORIENT_270:
        ii->width  = ii->_height;
        ii->height = ii->_width;
        break;
    }
}

static void
_oled_scroll(struct OLED *ii){
    u_char *db = ii->dpybuf;
    int i;

    int rowb  = ii->text_scale * ii->_width * FONT_GLYPH_HEIGHT / 8;
    int rows  = ii->text_scale * ii->_height / FONT_GLYPH_HEIGHT;
    int charb = rowb / rows;


    switch( ii->orientation ){
    case ORIENT_0:
        // slide up + clear bottom
        bcopy( db + rowb, db, rowb * (rows - 1) );
        bzero( db + rowb * (rows - 1), rowb );
        break;

    case ORIENT_180:
        bcopy( db, db + rowb, rowb * (rows - 1) );
        bzero( db, rowb );
        break;

    case ORIENT_90:
        bcopy( db + charb, db, rowb * rows - charb );
        for(i=0; i<rows; i++)
            bzero( db + rowb * (i + 1) - charb, charb );
        break;

    case ORIENT_270:
        bcopy( db, db + charb, rows * rowb - charb );
        for(i=0; i<rows; i++)
            bzero( db + rowb * i, charb );
        break;
    }
}

static inline void
_oled_set_pixel(struct OLED *ii, int x, int y, int val){
    int px, py;

    switch( ii->orientation ){
    case ORIENT_0:
        px = x; py = y;
        break;
    case ORIENT_90:
        py = x;
        px = ii->_width - y - 1;
	break;
    case ORIENT_180:
        px = ii->_width - x - 1;
        py = ii->_height - y - 1;
        break;
    case ORIENT_270:
        px = y;
        py = ii->_height - x - 1;
        break;
    }

    if( px >= ii->_width || py >= ii->_height ) return;

    if( val )
        ii->dpybuf[ (py / 8) * ii->_width + px ] |= 1 <<(py & 7);
    else
        ii->dpybuf[ (py / 8) * ii->_width + px ] &= ~( 1 <<(py & 7) );

}

static void
_oled_render_glyph(struct OLED *ii, int ch){
    int x, y;

    // optimize the common case
    if( ii->orientation == ORIENT_0 && ii->text_scale == 1 && FONT_GLYPH_HEIGHT == 8 && !(ii->y & 7) ){
        for(x=0; x<ii->text_scale * FONT_GLYPH_WIDTH; x++){
            int gl = font[ch * FONT_GLYPH_WIDTH + x / ii->text_scale ];
            if( ii->text_attr ) gl = ~gl;

            ii->dpybuf[ ii->y/8 * ii->width + x + ii->x ] = gl;
        }

        ii->dpybuf[ ii->y/8 * ii->width + x + ii->x + FONT_GLYPH_WIDTH ] = ii->text_attr ? 0xFF : 0;
        return;
    }

    for(x=0; x<ii->text_scale * FONT_GLYPH_WIDTH; x++){
        int gl = font[ch * FONT_GLYPH_WIDTH + x / ii->text_scale ];
        for(y=0; y<ii->text_scale * FONT_GLYPH_HEIGHT; y++){
            int pix = gl & (1<<(y/ii->text_scale));
            if( ii->text_attr ) pix = ! pix;

            _oled_set_pixel(ii, x + ii->x, y + ii->y, pix);
        }
    }

    // blank gutter
    int pix = ii->text_attr ? 1 : 0;
    for(x=0; x<ii->text_scale; x++){
        for(y=0; y<ii->text_scale * FONT_GLYPH_HEIGHT; y++){
            _oled_set_pixel(ii, x + ii->x + ii->text_scale * FONT_GLYPH_WIDTH, y + ii->y, pix);
        }
    }
}

static void
_oled_putchar(struct OLED *ii, int ch){

    /* minimal X3.64 support */
    if( ii->x3_mode == GOTESC ){
        if( ch == '[' ){
            ii->x3_mode = GOTBRACK;
            ii->x3_argn = 0;
            bzero( ii->x3_arg, MAXX3ARG );
            return;
        }else{
            ii->x3_mode = 0;
            ch = 0x80 | ch;
        }
    }

    switch( ch | ii->x3_mode ){
    case '\e':
        ii->x3_mode = GOTESC;
        goto done;
    case ';' | GOTBRACK:
        ii->x3_argn ++;
        if( ii->x3_argn >= MAXX3ARG ) ii->x3_argn = MAXX3ARG - 1;
        goto done;
    case '0' | GOTBRACK: case '1' | GOTBRACK: case '2' | GOTBRACK: case '3' | GOTBRACK:
    case '4' | GOTBRACK: case '5' | GOTBRACK: case '6' | GOTBRACK: case '7' | GOTBRACK:
    case '8' | GOTBRACK: case '9' | GOTBRACK:
        ii->x3_arg[ ii->x3_argn ] *= 10;
        ii->x3_arg[ ii->x3_argn ] += ch - '0';
        goto done;

    case 'J' | GOTBRACK:
        bzero(ii->dpybuf, sizeof(ii->dpybuf));
        break;

    case 'H' | GOTBRACK:
        ii->x = ii->x3_arg[0] * FONT_GLYPH_WIDTH  * ii->text_scale;
        ii->y = ii->x3_arg[1] * FONT_GLYPH_HEIGHT * ii->text_scale;

        break;

    case 'm' | GOTBRACK:
        ii->text_attr = ( ii->x3_arg[0] == 7 ) ? 1 : 0;
        break;

    case 'r' | GOTBRACK:
        // rotation - non-standard
        _oled_set_orientation(ii, ii->x3_arg[0]);
        break;

    case 's' | GOTBRACK:
        // scale - non-standard
        ii->text_scale = ii->x3_arg[0];
        if( ii->text_scale < 1 ) ii->text_scale = 1;
        break;

    case '\b':
        ii->x -= ii->text_scale * FONT_GLYPH_WIDTH;
        if( ii->x < 0 ) ii->x = 0;
        break;
    case '\r':
        ii->x = 0;
        break;
    case '\n':
        ii->y += ii->text_scale * FONT_GLYPH_HEIGHT;
        break;
    default:
        _oled_render_glyph(ii, ch);
        ii->x += ii->text_scale * (FONT_GLYPH_WIDTH + 1);
        break;
    }

    ii->x3_mode = 0;

    if( ii->x >= ii->width ){
        ii->x = 0;
        ii->y += ii->text_scale * FONT_GLYPH_HEIGHT;
    }

    if( ii->y >= ii->height ){
        _oled_scroll(ii);
        ii->y -= ii->text_scale * FONT_GLYPH_HEIGHT;
    }

done:
    return;
}

static void
_oled_puts(struct OLED *ii, const char *s){

    while( *s )
        _oled_putchar(ii, *s ++);
}

static void
_oled_logo(struct OLED *ii){
    extern const char *ident;

    // memset(ii->dpybuf, 0x10, sizeof(ii->dpybuf));
    // _oled_flush(ii);
    // memset(ii->dpybuf, 0, sizeof(ii->dpybuf));

    _oled_puts(ii, "\e[2sOS/J5    \e[7m \e[0m\r\n\e[0s" );
    _oled_puts(ii, ident);
    _oled_puts(ii, "\r\nstarting...\r\n");
    _oled_flush(ii);
}

/*****************************************************************/
void
oled_flush(int unit){
    struct OLED *ii = oledinfo + unit;

    _oled_flush(ii);
}


/****************************************************************/

int
oled_putchar(FILE *f, char ch){
    struct OLED *ii;
    ii = (struct OLED*)f->d;

    _oled_putchar(ii, ch);
    _oled_flush(ii);
    return 1;
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
