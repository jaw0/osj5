/*
  Copyright (c) 2013
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2013-Mar-31 10:54 (EDT)
  Function: graphic display
*/

extern "C" {
# include <conf.h>
# ifdef USE_NSTDIO
#  include <nstdio.h>
# endif
};

#include <gfxdpy.h>
#include <font.h>

#include <stdio.h>
#undef putchar

#ifdef USE_NSTDIO
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
#endif

// add fonts using "font name" in config file
extern const struct Font * const fonts[];

extern "C" void bzero(void*, int);
extern "C" int  strcmp(const char*, const char*);


#define GOTESC		0x100
#define GOTBRACK	0x200
#define FLAGMINUS	1
#define ABS(x)		((x)<0 ? -(x) : (x))


//****************************************************************

void
GFXdpy::init(void){
    orientation = cx = cy = text_attr = text_flags = x3_argn = x3_mode = 0;
    text_scale = 1;
    font = fonts[0];
    text_fg  = 7;
    text_bg  = 0;
    set_colors();

#ifdef USE_NSTDIO
    finit( & file );
    file.fs = &gfxdpy_port_fs;
    file.d  = (void*)this;
    file.codepage = CODEPAGE_GFXDPY;
#endif
}

void
GFXdpy::set_font(int f){
    font = fonts[ f % N_FONT ];
}

void
GFXdpy::set_font(const Font *f){
    font = f;
}

const Font *
GFXdpy::find_font(const char *name){
    short i;

    for(i=0; i<N_FONT; i++){
        if( !strcmp(name, fonts[i]->name) ){
            return fonts[i];
        }
    }
    // not found
    return 0;
}

bool
GFXdpy::set_font(const char *name){
    short i;

    const Font *f = find_font(name);
    if(f){
        font = f;
        return 1;
    }
    return 0;
}

void
GFXdpy::set_pos(int x, int y){
    cx = x;
    cy = y;
    if( cx < 0 ) cx = width  + cx;
    if( cy < 0 ) cy = height + cy;
}

void
GFXdpy::get_pos(int *x, int *y){
    *x = cx;
    *y = cy;
}

void
GFXdpy::puts(const char *s){
    while( *s )
        putchar(*s ++);
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

void
GFXdpy::scroll_vert(int xa, int xz, int dy){
    int y;

    if( dy > 0 ){
        for( ; xa<xz; xa++){
            for(y=0; y<height-dy; y++){
                int pix = get_pixel(xa, y+dy);
                set_pixel(xa, y, pix);
            }
            for(y=height-dy; y<height; y++)
                set_pixel(xa, y, color_bg);
        }
    }else{
        dy = - dy;
        for( ; xa<xz; xa++){
            for(y=height-1; y>=dy; y--){
                int pix = get_pixel(xa, y-dy);
                set_pixel(xa, y, pix);
            }
            for(y=0; y<dy; y++)
                set_pixel(xa, y, color_bg);
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
get_charld(const Font *f, int ch, int x) {

    if( ch < f->startchar ) return 0;
    if( ch > f->lastchar  ) return 0;
    ch -= f->startchar;

    int e = ch * f->numcol + x;

    switch( f->bytescol ){
    case 1:
        return f->data[e];
    case 2:
        return ((unsigned short*)f->data)[e];
    case 4:
        return ((unsigned long*)f->data)[e];
    }
}


void
GFXdpy::render_glyph(int ch){
    int x, y;

    int h = text_scale * font->height;

    for(x=0; x<text_scale * font->width; x++){
        int gl = get_charld(font, ch, x / text_scale);

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
        x3_flags &= ~FLAGMINUS;
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
        cx = x3_arg[0] * font->width  * text_scale;
        if( cx < 0 ) cx = width + cx;
        if( cx < 0 ) cx = 0;
        if( cx > width - text_scale * font->width ) cx = width - text_scale * font->width;
        break;

    case 'J' | GOTBRACK:	// clear screen
        // RSN - animated wipes
        clear_screen();
        cx = cy = 0;
        break;

    case 'H' | GOTBRACK: 	// move cursor (0 based, not 1 based); negative -> from right/bottom
        cy = x3_arg[0] * font->height * text_scale;
        cx = x3_arg[1] * font->width  * text_scale;
        if( cx < 0 ) cx = width  + cx;
        if( cy < 0 ) cy = height + cy;
        break;

    case '=' | GOTBRACK: 	// move cursor, by pixels
        cy = x3_arg[0];
        cx = x3_arg[1];
        if( cx < 0 ) cx = width  + cx;
        if( cy < 0 ) cy = height + cy;
        break;

    case 'm' | GOTBRACK:
        switch(x3_arg[0]){
        case 0:	 // reset
            text_attr = 0;
            font      = fonts[0];
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
            set_font( x3_arg[0] - 10 );
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

/****************************************************************/

void
GFXdpy::line(int x0, int y0, int x1, int y1, int color, unsigned pattern){
    short  dx = x1 - x0;
    short  dy = y1 - y0;
    short  ax = ABS(dx) * 2;
    short  ay = ABS(dy) * 2;
    s_char sx = dx < 0 ? -1 : 1;
    s_char sy = dy < 0 ? -1 : 1;
    unsigned i = 1;

    if( ax > ay ){
        short d = ay - (ax>>1);

        while(1){
            if( pattern & i) set_pixel(x0, y0, color);
            i <<= 1;
            if( !i ) i = 1;

            if( x0 == x1 ) break;
            if(d >= 0){
                y0 += sy;
                d -= ax;
            }
            x0 += sx;
            d += ay;
        }
    }else{
        short d = ax - (ay>>1);

        while(1){
            if( pattern & i) set_pixel(x0, y0, color);
            i <<= 1;
            if( !i ) i = 1;

            if( y0 == y1 ) break;
            if( d >= 0 ){
                x0 += sx;
                d -= ay;
            }
            y0 += sy;
            d += ax;
        }
    }
}

void
GFXdpy::rect(int x0, int y0, int x1, int y1, int color, unsigned pattern){
    line(x0,y0, x1,y0, color, pattern);
    line(x0,y1, x1,y1, color, pattern);
    line(x0,y0, x0,y1, color, pattern);
    line(x1,y0, x1,y1, color, pattern);
}

void
GFXdpy::hline(int x0, int y0, int x1, int y1, int color){

    if( x0 < x1 ){
        for( ;x0<=x1; x0++)
            set_pixel(x0,y0, color);
    }else{
        for( ;x1<=x0; x1++)
            set_pixel(x1,y0, color);
    }
}

void
GFXdpy::rect_filled(int x0, int y0, int x1, int y1, int color){
    short i, j;

    for(j=y0; j<=y1; j++){
        for(i=x0; i<=x1; i++){
            set_pixel(i,j, color);
        }
    }
}


void
GFXdpy::triangle(int x0, int y0, int x1, int y1, int x2, int y2, int color, unsigned pattern){
    line(x0,y0, x1,y1, color, pattern);
    line(x0,y0, x2,y2, color, pattern);
    line(x1,y1, x2,y2, color, pattern);
}

#define SWAP(a,b) tmp = a; a = b; b = tmp;

void
GFXdpy::triangle_filled(int x0, int y0, int x1, int y1, int x2, int y2, int color){
    short tmp;

    // roughly based on: http://www-users.mat.uni.torun.pl/~wrona/3d_tutor/tri_fillers.html

    // put points in vertical order
    if( y1 < y0 ){
        SWAP(x0,x1);
        SWAP(y0,y1);
    }
    if( y2 < y1 ){
        SWAP(x1,x2);
        SWAP(y1,y2);
    }
    if( y1 < y0 ){
        SWAP(x0,x1);
        SWAP(y0,y1);
    }

    if( y0 == y2 ){
        // degenerate case
        line(x0,y0, x1,y1, color);
        line(x1,y1, x2,y2, color);
        return;
    }

    short dx1 = x1 - x0;
    short dy1 = y1 - y0;
    short dx2 = x2 - x0;
    short dy2 = y2 - y0;
    short dx3 = x2 - x1;
    short dy3 = y2 - y1;

    if( y0 == y1 ) dx1 = dy1 = 0;
    if( y1 == y2 ) dx3 = dy3 = 0;

    short s=x0, e=x0;
    short es=0, ee=0;
    short y = y0;

    // top half
    while( y <= y1 ){
        // avoid a single disconected corner point when the top is scalene
        if( !((dx1 < 0 && dx2 < 0 || dx1 > 0 && dx2 > 0) && s == e) )
            hline(s,y, e,y, color);

        y++;
        if( dy2 ){
            es += dx2;
            s = x0 + es / dy2;
        }
        if( dy1 ){
            ee += dx1;
            e = x0 + ee / dy1;
        }
    }

    // bottom half
    ee = dx3 * (y - y1);
    es = dx2 * (y - y0);
    s  = x0 + es / dy2;
    e  = x1 + ee / dy3;

    while( y <= y2 ){
        hline(s,y, e,y, color);

        y++;
        if( dy2 ){
            es += dx2;
            s = x0 + es / dy2;
        }
        if( dy3 ){
            ee += dx3;
            e = x1 + ee / dy3;
        }
    }
}

/****************************************************************/

void
GFXdpy::set_sleep(bool sleep){}

u_char *
GFXdpy::get_buffer(void){ return 0; }

/****************************************************************/

#ifdef USE_NSTDIO

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
    case 'f':
        ii->set_font( (const Font*)a );
        return 0;
    case 'F':
        return ii->set_font( (const char*)a );

    default:
        kprintf("invalid ioctl '%x'\n", cmd);
        return -1;
    }
}

#endif

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
