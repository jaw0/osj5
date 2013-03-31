/*
  Copyright (c) 2013
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2013-Mar-31 10:54 (EDT)
  Function: 
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
# include <gfxdpy.h>
# include <strings.h>
};
#include <font.h>

#include <font/ada_5x7.h>
#include <font/ucs_4x6.h>
#include <font/ucs_5x8.h>
#include <font/ucs_6x10.h>
#include <font/ucs_6x12.h>
#include <font/ucs_9x15.h>
#include <font/ucs_10x20.h>

static const Font fonts[] = {
    // default font:
    { font_ucs_5x8_height, font_ucs_5x8_width, font_ucs_5x8_start, font_ucs_5x8_last,
      font_ucs_5x8_size, (unsigned char *)font_ucs_5x8_data },

    { font_ucs_4x6_height, font_ucs_4x6_width, font_ucs_4x6_start, font_ucs_4x6_last,
      font_ucs_4x6_size, (unsigned char *)font_ucs_4x6_data },

    { font_ada_5x7_height, font_ada_5x7_width, font_ada_5x7_start, font_ada_5x7_last,
      font_ada_5x7_size, (unsigned char *)font_ada_5x7_data },

    { font_ucs_5x8_height, font_ucs_5x8_width, font_ucs_5x8_start, font_ucs_5x8_last,
      font_ucs_5x8_size, (unsigned char *)font_ucs_5x8_data },

    { font_ucs_6x10_height, font_ucs_6x10_width, font_ucs_6x10_start, font_ucs_6x10_last,
      font_ucs_6x10_size, (unsigned char *)font_ucs_6x10_data },

    { font_ucs_6x12_height, font_ucs_6x12_width, font_ucs_6x12_start, font_ucs_6x12_last,
      font_ucs_6x12_size, (unsigned char *)font_ucs_6x12_data },

    { font_ucs_9x15_height, font_ucs_9x15_width, font_ucs_9x15_start, font_ucs_9x15_last,
      font_ucs_9x15_size, (unsigned char *)font_ucs_9x15_data },

    { font_ucs_10x20_height, font_ucs_10x20_width, font_ucs_10x20_start, font_ucs_10x20_last,
      font_ucs_10x20_size, (unsigned char *)font_ucs_10x20_data },
};



#define FLAG_AUTOFLUSH	1

#define ATTR_REVERSE	1
#define ATTR_ULINE	2
#define ATTR_STRIKE	4
#define ATTR_FAINT	8

#define GOTESC		0x100
#define GOTBRACK	0x200


//****************************************************************

void
GFXdpy::init(void){
    orientation = cx = cy = text_attr = text_flags = x3_argn = x3_mode = 0;
    text_scale = 1;
    font = fonts + 0;
}

void
GFXdpy::set_orientation(int orient){

    orientation = orient;
    switch( orient ){
    case GFX_ORIENT_0:
    case GFX_ORIENT_180:
        width  = _width;
        height = _height;
        break;
    case GFX_ORIENT_90:
    case GFX_ORIENT_270:
        width  = _height;
        height = _width;
        break;
    }
}

void
GFXdpy::scroll(void){
    int x, y;

    int fh = text_scale * font->height;
    int sb = fh - (height - cy);

    for(y=0; y<height; y++){
        for(x=0; x<width; x++){
            int pix = get_pixel(x, y + sb);
            set_pixel(x, y, pix);
        }
    }

    cy -= sb;
}

inline void
GFXdpy::set_pixel(int x, int y, int val){
    int px, py;

    switch( orientation ){
    case GFX_ORIENT_0:
        px = x; py = y;
        break;
    case GFX_ORIENT_90:
        py = x;
        px = _width - y - 1;
	break;
    case GFX_ORIENT_180:
        px = _width - x - 1;
        py = _height - y - 1;
        break;
    case GFX_ORIENT_270:
        px = y;
        py = _height - x - 1;
        break;
    }

    if( px >= _width || py >= _height || px < 0 || py < 0 ) return;
    _set_pixel(px, py, val);
}

inline int
GFXdpy::get_pixel(int x, int y){
    int px, py;

    switch( orientation ){
    case GFX_ORIENT_0:
        px = x; py = y;
        break;
    case GFX_ORIENT_90:
        py = x;
        px = _width - y - 1;
	break;
    case GFX_ORIENT_180:
        px = _width - x - 1;
        py = _height - y - 1;
        break;
    case GFX_ORIENT_270:
        px = y;
        py = _height - x - 1;
        break;
    }

    if( px >= _width || py >= _height || px < 0 || py < 0 ) return 0;
    return _get_pixel(px, py);
}

inline int
Font::get_charld(int ch, int x) const {

    if( ch < startchar ) return 0;
    if( ch > lastchar  ) return 0;
    ch -= startchar;

    int e = ch * width + x;

    switch( byteschar ){
    case 1:
        return data[e];
    case 2:
        return ((unsigned short*)data)[e];
    case 4:
        return ((unsigned long*)data)[e];
    }
}


void
GFXdpy::render_glyph(int ch){
    int x, y;

    int h = text_scale * font->height;

    for(x=0; x<text_scale * font->width; x++){
        int gl = font->get_charld(ch, x / text_scale);

        for(y=0; y<h; y++){
            int pix = gl & (1<<(y/text_scale));
            if( text_attr & ATTR_ULINE  && y == h-1) pix = 1;
            if( text_attr & ATTR_STRIKE && y == h/2) pix = 1;
            if( text_attr & ATTR_FAINT  && (x+y)&1 ) pix = 0;
            if( text_attr & ATTR_REVERSE ) pix = ! pix;

            set_pixel(x + cx, y + cy, pix);
        }
    }

    // blank gutter
    for(x=0; x<text_scale; x++){
        for(y=0; y<h; y++){
            int pix = 0;
            if( text_attr & ATTR_ULINE  && y == h-1) pix = 1;
            if( text_attr & ATTR_STRIKE && y == h/2) pix = 1;
            if( text_attr & ATTR_REVERSE ) pix = ! pix;

            set_pixel(x + cx + text_scale * font->width, y + cy, pix);
        }
    }
}


void
GFXdpy::putchar(int ch){

    /* minimal X3.64 support */
    if( x3_mode == GOTESC ){
        if( ch == '[' ){
            x3_mode = GOTBRACK;
            x3_argn = 0;
            bzero( x3_arg, MAXX3ARG );
            return;
        }else{
            x3_mode = 0;
            ch = 0x80 | ch;
        }
    }

    switch( ch | x3_mode ){
    case '\e':
        x3_mode = GOTESC;
        goto done;
    case ';' | GOTBRACK:
        x3_argn ++;
        if( x3_argn >= MAXX3ARG ) x3_argn = MAXX3ARG - 1;
        goto done;
    case '0' | GOTBRACK: case '1' | GOTBRACK: case '2' | GOTBRACK: case '3' | GOTBRACK:
    case '4' | GOTBRACK: case '5' | GOTBRACK: case '6' | GOTBRACK: case '7' | GOTBRACK:
    case '8' | GOTBRACK: case '9' | GOTBRACK:
        x3_arg[ x3_argn ] *= 10;
        x3_arg[ x3_argn ] += ch - '0';
        goto done;

    case 'J' | GOTBRACK:
        clear_screen();
        cx = cy = 0;
        break;

    case 'H' | GOTBRACK:
        cx = x3_arg[0] * font->width  * text_scale;
        cy = x3_arg[1] * font->height * text_scale;
        break;

    case 'm' | GOTBRACK:
        switch(x3_arg[0]){
        case 0:	 text_attr  = 0; font = fonts;	break;	// reset
        case 2:  text_attr |= ATTR_FAINT;	break;
        case 4:  text_attr |= ATTR_ULINE;	break;
        case 7:  text_attr |= ATTR_REVERSE;	break;
        case 9:  text_attr |= ATTR_STRIKE;	break;
        case 22: text_attr &= ~ATTR_FAINT;	break;
        case 24: text_attr &= ~ATTR_ULINE;	break;
        case 27: text_attr &= ~ATTR_REVERSE;	break;
        case 29: text_attr &= ~ATTR_STRIKE;	break;

        case 10: case 11: case 12: case 13: case 14:
        case 15: case 16: case 17: case 18: case 19:
            font = fonts + (x3_arg[0] - 10) % ELEMENTSIN(fonts);
        }
        break;

    case 'r' | GOTBRACK:
        // rotation - non-standard
        set_orientation(x3_arg[0]);
        break;

    case 's' | GOTBRACK:
        // scale - non-standard
        text_scale = x3_arg[0];
        if( text_scale < 1 ) text_scale = 1;
        break;

    case '\b':
        cx -= text_scale * font->width;
        if( cx < 0 ) cx = 0;
        break;
    case '\r':
        cx = 0;
        break;
    case '\n':
        cy += text_scale * font->height;
        break;
    default:
        if( cy >= height - font->height ){
            scroll();
        }

        render_glyph(ch);
        cx += text_scale * (font->width + 1);
        break;
    }

    x3_mode = 0;

#if 0
    // autowrap?
    if( cx >= width ){
        cx = 0;
        cy += text_scale * font->height;
    }
#endif


done:
    return;
}



void flush(void){}
void set_pixel(int, int, int){}
int  get_pixel(int, int){ return 0; }
void clear_screen(void) {}


