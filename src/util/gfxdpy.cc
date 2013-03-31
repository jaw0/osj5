/*
  Copyright (c) 2013
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2013-Mar-31 10:54 (EDT)
  Function: 
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
# include <gfxdpy.h>
# include <strings.h>
};

// XXX
#include "../dev/font_ucs_9x15.h"
#ifndef FONT_STARTCHAR
# define FONT_STARTCHAR 0
#endif


#define FLAG_AUTOFLUSH	1

#define ATTR_REVERSE	1
#define ATTR_ULINE	2
#define ATTR_STRIKE	4
#define ATTR_FAINT	8

#define GOTESC		0x100
#define GOTBRACK	0x200


//****************************************************************

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

    int fh = text_scale * FONT_GLYPH_HEIGHT;
    int sb = fh - (height - cy);

    for(y=0; y<height; y++){
        for(x=0; x<width; x++){
            int pix = get_pixel(x, y + sb);
            set_pixel(x, y, pix);
        }
    }

    cy -= sb;
}

void
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

int
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

void
GFXdpy::render_glyph(int ch){
    int x, y;

    int h = text_scale * FONT_GLYPH_HEIGHT;

    if( ch >= sizeof(font)/FONT_GLYPH_WIDTH/sizeof(font[0]) ) ch = 0;
    if( ch < FONT_STARTCHAR ) ch = FONT_STARTCHAR;

    ch -= FONT_STARTCHAR;

    for(x=0; x<text_scale * FONT_GLYPH_WIDTH; x++){
        int gl = font[ch * FONT_GLYPH_WIDTH + x / text_scale ];
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

            set_pixel(x + cx + text_scale * FONT_GLYPH_WIDTH, y + cy, pix);
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
        break;

    case 'H' | GOTBRACK:
        cx = x3_arg[0] * FONT_GLYPH_WIDTH  * text_scale;
        cy = x3_arg[1] * FONT_GLYPH_HEIGHT * text_scale;
        break;

    case 'm' | GOTBRACK:
        switch(x3_arg[0]){
        case 0:	 text_attr  = 0;		break;	// reset
        case 2:  text_attr |= ATTR_FAINT;	break;
        case 4:  text_attr |= ATTR_ULINE;	break;
        case 7:  text_attr |= ATTR_REVERSE;	break;
        case 9:  text_attr |= ATTR_STRIKE;	break;
        case 22: text_attr &= ~ATTR_FAINT;	break;
        case 24: text_attr &= ~ATTR_ULINE;	break;
        case 27: text_attr &= ~ATTR_REVERSE;	break;
        case 29: text_attr &= ~ATTR_STRIKE;	break;
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
        cx -= text_scale * FONT_GLYPH_WIDTH;
        if( cx < 0 ) cx = 0;
        break;
    case '\r':
        cx = 0;
        break;
    case '\n':
        cy += text_scale * FONT_GLYPH_HEIGHT;
        break;
    default:
        if( cy >= height - FONT_GLYPH_HEIGHT ){
            scroll();
        }

        render_glyph(ch);
        cx += text_scale * (FONT_GLYPH_WIDTH + 1);
        break;
    }

    x3_mode = 0;

#if 0
    // autowrap?
    if( cx >= width ){
        cx = 0;
        cy += text_scale * FONT_GLYPH_HEIGHT;
    }
#endif


done:
    return;
}



void flush(void){}
void set_pixel(int, int, int){}
int  get_pixel(int, int){ return 0; }
void clear_screen(void) {}


