/*
  Copyright (c) 2013
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2013-Mar-31 10:54 (EDT)
  Function: graphic display
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

int gfxdpy_putchar(FILE*, char);
int gfxdpy_getchar(FILE*);
int gfxdpy_noop(FILE*);
int gfxdpy_status(FILE*);
int gfxdpy_flush(FILE*);
int gfxdpy_ioctl(FILE*, int, void*);

const struct io_fs gfxdpy_port_fs = {
    gfxdpy_putchar,
    gfxdpy_getchar,
    gfxdpy_noop,	// close
    gfxdpy_flush,
    gfxdpy_status,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    gfxdpy_ioctl,
};

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


#define GOTESC		0x100
#define GOTBRACK	0x200

#define FLAGMINUS	1

//****************************************************************

void
GFXdpy::init(void){
    orientation = cx = cy = text_attr = text_flags = x3_argn = x3_mode = 0;
    text_scale = 1;
    font = fonts + 0;
    text_fg  = 7;
    text_bg  = 0;
    set_colors();

    finit( & file );
    file.fs = &gfxdpy_port_fs;
    file.d  = (void*)this;
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

void
GFXdpy::scroll_horiz(int ya, int yz, int dx){
    int x;

    if( dx > 0 ){
        for( ; ya<yz; ya++){
            for(x=0; x<width-dx; x++){
                int pix = get_pixel(x+dx, ya);
                set_pixel(x, ya, pix);
            }
            for(x=width-dx; x<width; x++)
                set_pixel(x, ya, color_bg);
        }
    }else{
        dx = - dx;
        for( ; ya<yz; ya++){
            for(x=width-1; x>=dx; x--){
                int pix = get_pixel(x-dx, ya);
                set_pixel(x, ya, pix);
            }
            for(x=0; x<dx; x++)
                set_pixel(x, ya, color_bg);
        }
    }
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

    if( px >= _width || py >= _height || px < 0 || py < 0 ) return color_bg;
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
            if( text_attr & ATTR_REVERSE ) pix = ! pix;

            pix = pix ? color_fg : color_bg;
            set_pixel(x + cx, y + cy, pix );
        }
    }
}


void
GFXdpy::putchar(int ch){

    /* minimal X3.64 support */
    /* RSN - DEC ReGIS graphics */
    if( x3_mode == GOTESC ){
        if( ch == '[' ){
            x3_mode  = GOTBRACK;
            x3_argn  = 0;
            x3_flags = 0;
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
    case '-' | GOTBRACK:
        x3_flags |= FLAGMINUS;
        goto done;
    case '0' | GOTBRACK: case '1' | GOTBRACK: case '2' | GOTBRACK: case '3' | GOTBRACK:
    case '4' | GOTBRACK: case '5' | GOTBRACK: case '6' | GOTBRACK: case '7' | GOTBRACK:
    case '8' | GOTBRACK: case '9' | GOTBRACK:
        x3_arg[ x3_argn ] *= 10;
        x3_arg[ x3_argn ] += (ch - '0') * ((x3_flags & FLAGMINUS) ? -1 : 1);
        goto done;

    case 'A' | GOTBRACK:	// up
        if( !x3_arg[0] ) x3_arg[0] = 1;
        cy -= x3_arg[0] * text_scale * font->height;
        if( cy < 0 ) cy = 0;
        break;
    case 'B' | GOTBRACK:	// down
        if( !x3_arg[0] ) x3_arg[0] = 1;
        cy += x3_arg[0] * text_scale * font->height;
        if( cy > height - text_scale * font->height ) cy = height - text_scale * font->height;
        break;
    case 'C' | GOTBRACK:	// right
        if( !x3_arg[0] ) x3_arg[0] = 1;
        cx += x3_arg[0] * text_scale * font->width;
        if( cx > width - text_scale * font->width ) cx = width - text_scale * font->width;
        break;
    case 'D' | GOTBRACK:	// left
        if( !x3_arg[0] ) x3_arg[0] = 1;
        cx -= x3_arg[0] * text_scale * font->width;
        if( cx < 0 ) cx = 0;
        break;
    case 'E' | GOTBRACK:	// line down
        if( !x3_arg[0] ) x3_arg[0] = 1;
        cy += x3_arg[0] * text_scale * font->height;
        if( cy > height - text_scale * font->height ) cy = height - text_scale * font->height;
        cx = 0;
    case 'F' | GOTBRACK:	// line up
        if( !x3_arg[0] ) x3_arg[0] = 1;
        cy -= x3_arg[0] * text_scale * font->height;
        if( cy < 0 ) cy = 0;
        cx = 0;
    case 'G' | GOTBRACK:	// set column (0 based, not 1 based); negative -> from right
        if( x3_arg[0] < 0 )
            cx = width - x3_arg[0] * font->width  * text_scale;
        else
            cx = x3_arg[0] * font->width  * text_scale;

        if( cx < 0 ) cx = 0;
        if( cx > width - text_scale * font->width ) cx = width - text_scale * font->width;
        break;

    case 'J' | GOTBRACK:	// clear screen
        // RSN - animated wipes
        clear_screen();
        cx = cy = 0;
        break;

    case 'H' | GOTBRACK: 	// move cursor (0 based, not 1 based)
        cx = x3_arg[0] * font->width  * text_scale;
        cy = x3_arg[1] * font->height * text_scale;
        break;

    case 'm' | GOTBRACK:
        switch(x3_arg[0]){
        case 0:	 // reset
            text_attr = 0;
            font      = fonts;
            text_fg   = 7;
            text_bg   = 0;
            set_colors();
            break;
        case 1:
            text_attr |= ATTR_BRIGHT;
            set_colors();
            break;
        case 2:
            text_attr |= ATTR_FAINT;
            set_colors();
            break;
        case 4:  text_attr |= ATTR_ULINE;	break;
        case 7:  text_attr |= ATTR_REVERSE;	break;
        case 9:  text_attr |= ATTR_STRIKE;	break;
        case 22:
            text_attr &= ~(ATTR_FAINT | ATTR_BRIGHT);
            set_colors();
            break;
        case 24: text_attr &= ~ATTR_ULINE;	break;
        case 27: text_attr &= ~ATTR_REVERSE;	break;
        case 29: text_attr &= ~ATTR_STRIKE;	break;

        case 30: case 31: case 32: case 33: case 34:
        case 35: case 36: case 37:
            text_fg = x3_arg[0] - 30;
            set_colors();
            break;
        case 40: case 41: case 42: case 43: case 44:
        case 45: case 46: case 47:
            text_bg = x3_arg[0] - 40;
            set_colors();
            break;

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
        // scale+flags - non-standard
        text_scale = x3_arg[0];
        text_flags = x3_arg[1];
        if( text_scale < 1 ) text_scale = 1;
        break;

    case '<' | GOTBRACK:
        // scroll left by arg, move cursor to right edge (not standard)
        if( !x3_arg[0] ) x3_arg[0] = 1;
        scroll_horiz(cy, cy + text_scale * font->height, x3_arg[0] * text_scale * font->width);
        cx = width - text_scale * font->width;
        break;

    case '>' | GOTBRACK:
        // scroll right by arg, move cursor to left edge (not standard)
        if( !x3_arg[0] ) x3_arg[0] = 1;
        scroll_horiz(cy, cy + text_scale * font->height, - x3_arg[0] * text_scale * font->width);
        cx = 0;
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
        if( cy > height - text_scale * font->height ){
            scroll();
        }
        if( (cx > width - text_scale * font->width) && text_flags & GFX_FLAG_AUTOSHIFT ){
            scroll_horiz(cy, cy + text_scale * font->height, text_scale * font->width);
        }

        render_glyph(ch);
        cx += text_scale * font->width;
        break;
    }

    x3_mode = 0;


done:
    return;
}

void
GFXdpy::set_sleep(bool sleep){}

u_char *
GFXdpy::get_buffer(void){ return 0; }

/****************************************************************/

int
gfxdpy_putchar(FILE *f, char ch){
    GFXdpy *ii = (GFXdpy*)f->d;

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
gfxdpy_flush(FILE *f){
    GFXdpy *ii = (GFXdpy*)f->d;

    ii->flush();
}

int
gfxdpy_getchar(FILE *f){
    return -1;
}

int
gfxdpy_noop(FILE*f){
    return 1;
}

int
gfxdpy_status(FILE*f){
    return FST_O;
}


int
gfxdpy_ioctl(FILE* f, int cmd, void* a){
    GFXdpy *ii = (GFXdpy*)f->d;

    if( ((cmd >> 8) & 0xFF) != 'g' )
        return -1;

    switch( cmd & 0xFF ){
    case 'g':		/* get */
        return (int) ii;
        break;
    case 's':
        ii->set_sleep( a ? 1 : 0 );
        break;
    case 'b':
        return (int) ii->get_buffer();
    default:
        return -1;
    }
}


/****************************************************************/

void flush(void){}
void set_pixel(int, int, int){}
int  get_pixel(int, int){ return 0; }
void clear_screen(void) {}

/****************************************************************/

extern "C" {

void
c_gfxdpy_set_pixel(GFXdpy *g, int x, int y, int v){
    g->set_pixel(x,y,v);
}

int
c_gfxdpy_get_pixel(GFXdpy *g, int x, int y){
    return g->get_pixel(x,y);
}

void
c_gfxdpy_flush(GFXdpy *g){
    g->flush();
}

}
