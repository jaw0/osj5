/*
  Copyright (c) 2013
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2013-Mar-31 10:54 (EDT)
  Function: graphic display
*/

extern "C" {
# include <conf.h>
# ifdef USE_NSTDIO
#  include <proc.h>
#  include <nstdio.h>
#else
#  include <stdio.h>
# endif
#include <stdint.h>
};

#include <gfxdpy.h>
#include <font.h>

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
extern "C" int  strcasecmp(const char*, const char*);


#define GOTESC		0x100
#define GOTBRACK	0x200
#define GOTTEXT		0x400
#define FLAGMINUS	1
#define FLAGDIGIT	2
#define ABS(x)		((x)<0 ? -(x) : (x))


//****************************************************************

int
font_height(const Font *f){
    return (f->lineheight ? f->lineheight : f->height);
}


void
GFXdpy::init(void){
    x3_argn = x3_mode = 0;
    xx_text_n = 0;
    reset();

#ifdef USE_NSTDIO
    finit( & file );
    file.fs = &gfxdpy_port_fs;
    file.d  = (void*)this;
    file.codepage = CODEPAGE_GFXDPY;
#endif
#ifdef GFXDPY_BEEPS
    volume = 127;
#endif

}

void
GFXdpy::reset(void){
    orientation = 0;
    cx = cy = sx = sy = 0;
    text_attr = text_flags = 0;
    text_scale = 1;
    residue = 0;
    font = fonts[0];
    text_height = font_height(font) * text_scale;
    text_fg  = 7;
    text_bg  = 0;
    set_colors();
}

void
GFXdpy::bound_pos(void){
    if( cx < 0 ) cx = 0;
    if( cy < 0 ) cy = 0;
    if( cx > width - 1 ) cx = width  - 1;
    if( cy > height - 1) cy = height - 1;
}

bool
GFXdpy::set_font(int f){
    font = fonts[ f % N_FONT ];
    text_height = font_height(font) * text_scale;
    return 1;
}

bool
GFXdpy::set_font(const Font *f){
    font = f;
    text_height = font_height(font) * text_scale;
    return 1;
}

const Font *
find_font(const char *name){
    short i;

    for(i=0; i<N_FONT; i++){
        if( !strcasecmp(name, fonts[i]->name) ){
            return fonts[i];
        }
    }
    // not found
    return 0;
}

const Font *
find_font(int w, int h){
    short i;

    for(i=0; i<N_FONT; i++){
        if( (fonts[i]->width == w) && (fonts[i]->lineheight == h) ){
            return fonts[i];
        }
    }
    // not found
    return 0;
}

void
list_fonts(void){
    // report to stdout

    short i;

    for(i=0; i<N_FONT; i++){
        printf("%3d %2d x %2d  %s\n", i,
               fonts[i]->width, fonts[i]->lineheight, fonts[i]->name);

    }
}

bool
GFXdpy::set_font(const char *name){
    short i;

    const Font *f = find_font(name);
    if(f){
        font = f;
        text_height = font_height(font) * text_scale;
        return 1;
    }
    return 0;
}
bool
GFXdpy::set_font(int w, int h){
    short i;

    const Font *f = find_font(w, h);
    if(f){
        font = f;
        text_height = font_height(font) * text_scale;
        return 1;
    }
    return 0;
}

void
GFXdpy::_set_pos(int x, int y){
    cx = x;
    cy = y;
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

    int sb = text_height - (height - cy);

    for(y=0; y<height; y++){
        for(x=0; x<width; x++){
            int pix = get_pixel(x, y + sb);
            set_pixel(x, y, pix);
        }
    }

    cy -= sb;
}

void
GFXdpy::scroll_horiz(int xa, int ya, int xz,int yz, int dx){
    int x;

    if( dx > 0 ){
        for( ; ya<=yz; ya++){
            for(x=xa; x<=xz-dx; x++){
                int pix = get_pixel(x+dx, ya);
                set_pixel(x, ya, pix);
            }
            for(x=xz-dx; x<xz; x++)
                set_pixel(x, ya, color_bg);
        }
    }else{
        dx = - dx;
        for( ; ya<=yz; ya++){
            for(x=xz; x>=xa+dx; x--){
                int pix = get_pixel(x-dx, ya);
                set_pixel(x, ya, pix);
            }
            for(x=xa; x<xa+dx; x++)
                set_pixel(x, ya, color_bg);
        }
    }
}

void
GFXdpy::scroll_vert(int xa, int ya, int xz, int yz, int dy){
    int y;

    if( dy > 0 ){
        for( ; xa<=xz; xa++){
            for(y=ya; y<=yz-dy; y++){
                int pix = get_pixel(xa, y+dy);
                set_pixel(xa, y, pix);
            }
            for(y=yz-dy; y<yz; y++)
                set_pixel(xa, y, color_bg);
        }
    }else{
        dy = - dy;
        for( ; xa<=xz; xa++){
            for(y=yz; y>=ya+dy; y--){
                int pix = get_pixel(xa, y-dy);
                set_pixel(xa, y, pix);
            }
            for(y=ya; y<ya+dy; y++)
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

    if( (px >= _width) || (py >= _height) || (px < 0) || (py < 0) ) return;
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

int
GFXdpy::get_color(int rgb){
    return rgb;
}

inline unsigned int
get_charld(const Font *f, int ch, int x) {

    if( ch < f->startchar ) return 0;
    if( ch > f->lastchar  ) return 0;
    ch -= f->startchar;

    int e = ch * f->numcol + x;

    switch( f->bytescol ){
    case 1:
        return f->data[e];
    case 2:
        return ((uint16_t*)f->data)[e];
    case 4:
        return ((uint32_t*)f->data)[e];
    }
}

void
GFXdpy::set_blank_pixel(int x, int y, int h) {
    int pix = 0;
    if( text_attr & ATTR_ULINE  && y == h-1) pix = 1;
    if( text_attr & ATTR_STRIKE && y == h/2) pix = 1;

    if( (residue == 0) || pix ){
        if( text_attr & ATTR_REVERSE ) pix = ! pix;
        pix = pix ? color_fg : color_bg;
        set_pixel(x, y, pix );
    }
}

// new compressed format
int
GFXdpy::render_glyph2(int ch){
    char x, y, xx, yy;
    signed char xadj=0;
    char h = text_scale * font->height;

    const struct FontData *fd = 0;
    const u_char *cd=0;
    char l0=font->width*text_scale, r0=0, ncol=0;

    if( (ch <= font->lastchar) && (ch >= font->startchar) ){
        ch -= font->startchar;
        fd = font->fdata + ch;
    }
    if( fd ){
        l0 = fd->l0 * text_scale;
        r0 = fd->r0 * text_scale;
        xadj = fd->xadj * text_scale;
        ncol = fd->ncol;
        cd = font->data + fd->pos;
    }

    // pad left side 0s
    for(x=0; x<l0; x++){
        for(y=0; y<h; y++){
            if( residue == 0 )
                set_blank_pixel(x + cx, y + cy, h );
        }
        if( residue > 0 ) residue --;
    }

    // run length encoded data
    x = 0;
    y = 0;
    short pos=0, done=0, size=ncol * font->height;

    for(pos=0; done<size; pos++){
        uint8_t run   = cd[ pos ];
        uint8_t zeros = run >> 3;
        uint8_t ones  = run & 7;
        char m, n;

        for(m=0; m<2; m++){
            char l = m ? ones : zeros;
            for(n=0; n<l; n++){
                char x0 = x * text_scale + l0;
                for(xx=x0; xx<x0+text_scale; xx++){
                    char y0 = y * text_scale;
                    for(yy=y0; yy<y0+text_scale; yy++){

                        int pix = m;
                        if( text_attr & ATTR_ULINE  && yy == h-1) pix = 1;
                        if( text_attr & ATTR_STRIKE && yy == h/2) pix = 1;

                        // do not re-erase overlapping proportionally spaced glyphs
                        if( (residue == 0) || pix ){
                            if( text_attr & ATTR_REVERSE ) pix = ! pix;
                            pix = pix ? color_fg : color_bg;

                            set_pixel(xx + cx, yy + cy, pix );
                        }

                    }
                }


                done ++;
                y ++;
                if( y >= font->height ){
                    y = 0;
                    x ++;
                }

            }
        }
    }

    // pad right side 0s
    char x0 = l0 + ncol * text_scale;

    for(x=0; x<r0; x++){
        for(y=0; y<h; y++){
            set_blank_pixel(x0 + x + cx, y + cy, h );
        }
    }

    residue = -xadj;
    return x0 + r0 + xadj;
}

void
GFXdpy::render_glyph(int ch){
    int x, y;

    int h = text_scale * font->height;

    for(x=0; x<text_scale * font->width; x++){
        unsigned int gl = get_charld(font, ch, x / text_scale);

        for(y=0; y<h; y++){
            int pix = gl & (1<<(y/text_scale));
            if( text_attr & ATTR_ULINE  && y == h-1) pix = 1;
            if( text_attr & ATTR_STRIKE && y == h/2) pix = 1;

            // do not re-erase overlapping proportionally spaced glyphs
            if( (residue == 0) || pix ){
                if( text_attr & ATTR_REVERSE ) pix = ! pix;
                pix = pix ? color_fg : color_bg;
                set_pixel(x + cx, y + cy, pix );
            }
        }

        if( residue > 0 ) residue --;
    }
}

int
glyph_width(const Font *f, int ch){
    int w = f->width;

    if( ch < f->startchar ) return 0;
    if( ch > f->lastchar  ) return 0;

    ch -= f->startchar;

    if( f->fdata ){
        return f->fdata[ch].l0 + f->fdata[ch].r0 + f->fdata[ch].ncol + f->fdata[ch].xadj;
    }
    if( f->metrics ){
        w += f->metrics[ch].xadj;
    }
    return w;
}

void
GFXdpy::putchar(int ch){

    /* minimal X3.64 support */
    /* RSN - DEC ReGIS graphics, tek4014, ...? */
    if( x3_mode == GOTESC ){
        if( ch == '[' ){
            x3_mode  = GOTBRACK;
            x3_argn  = 0;
            x3_flags = 0;
            xx_text_n  = 0;
            bzero( x3_arg, sizeof(x3_arg) );
            bzero( xx_text, MAXXTEXT+1 );
            goto done;
        }else{
            x3_mode = 0;
            ch = GOTESC | ch;
        }
    }

    /* text arg: esc[50;`text;51x */
    if( (x3_mode & GOTTEXT) && (ch != ';') ){
        if( xx_text_n < MAXXTEXT ){
            xx_text[ xx_text_n ++ ] = ch;
        }
        goto done;
    }

    /* keep argn accurate - make sure e[0X -> argn=1 */
    if( (x3_flags & FLAGDIGIT) && (ch != ';') && (ch < '0' || ch > '9') && (ch != '-') ){
        x3_flags &= ~FLAGDIGIT;
        x3_argn ++;
    }

    switch( ch | x3_mode ){
    case '\e':
        x3_mode = GOTESC;
        goto done;
    case ';' | GOTBRACK:
        x3_argn ++;
        x3_flags &= ~FLAGMINUS;
        x3_mode  &= ~GOTTEXT;
        if( x3_argn >= MAXX3ARG ) x3_argn = MAXX3ARG - 1;
        goto done;
    case '-' | GOTBRACK:
        x3_flags |= FLAGMINUS;
        x3_flags |= FLAGDIGIT;
        goto done;
    case '0' | GOTBRACK: case '1' | GOTBRACK: case '2' | GOTBRACK: case '3' | GOTBRACK:
    case '4' | GOTBRACK: case '5' | GOTBRACK: case '6' | GOTBRACK: case '7' | GOTBRACK:
    case '8' | GOTBRACK: case '9' | GOTBRACK:
        x3_arg[ x3_argn ] *= 10;
        x3_arg[ x3_argn ] += (ch - '0') * ((x3_flags & FLAGMINUS) ? -1 : 1);
        x3_flags |= FLAGDIGIT;
        goto done;

    case ';' | GOTBRACK | GOTTEXT:
        if( xx_text_n && (xx_text[xx_text_n-1] == '`')){
            // remove trailing `
            xx_text[ --xx_text_n ] = 0;
        }
        x3_mode  &= ~GOTTEXT;
        goto done;
    case '`' | GOTBRACK:
        x3_mode |= GOTTEXT;
        goto done;

    case 'A' | GOTBRACK:	// up
        if( !x3_arg[0] ) x3_arg[0] = 1;
        cy -= x3_arg[0] * text_height;
        if( cy < 0 ) cy = 0;
        break;
    case 'B' | GOTBRACK:	// down
        if( !x3_arg[0] ) x3_arg[0] = 1;
        cy += x3_arg[0] * text_height;
        if( cy > height - text_height ) cy = height - text_height;
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
        cy += x3_arg[0] * text_height;
        if( cy > height - text_height ) cy = height - text_height;
        cx = 0;
    case 'F' | GOTBRACK:	// line up
        if( !x3_arg[0] ) x3_arg[0] = 1;
        cy -= x3_arg[0] * text_height;
        if( cy < 0 ) cy = 0;
        cx = 0;
    case 'G' | GOTBRACK:	// set column (0 based, not 1 based); negative -> from right
        cx = x3_arg[0] * font->width  * text_scale;
        if( cx < 0 ) cx = width + cx;
        if( cx < 0 ) cx = 0;
        if( cx > width - text_scale * font->width ) cx = width - text_scale * font->width;
        break;

    case 'H' | GOTBRACK: 	// move cursor (0 based, not 1 based); negative -> from right/bottom
        cy = x3_arg[0] * text_height;
        cx = x3_arg[1] * font->width  * text_scale;
        if( cx < 0 ) cx = width  + cx;
        if( cy < 0 ) cy = height + cy;
        break;

    case 'h' | GOTBRACK: 	// private mode settings (non-standard)
        switch(x3_arg[0]){
        case 0:
            if( x3_argn )	// esc[0;h but not esc[h
                reset();
            break;
        case 1:			// set orientation
            set_orientation(x3_arg[1]);
            break;
        case 2:			// set scale factor
            text_scale = x3_arg[1];
            if( text_scale < 1 ) text_scale = 1;
            text_height = font_height(font) * text_scale;
            break;
        case 3:
            text_flags |= GFX_FLAG_AUTOFLUSH;
            break;
        case 4:
            text_flags &= ~GFX_FLAG_AUTOFLUSH;
            break;
        case 5:
            text_flags |= GFX_FLAG_AUTOSHIFT;
            break;
        case 6:
            text_flags &= ~GFX_FLAG_AUTOSHIFT;
            break;
        case 7:
            if( x3_argn )
                text_height = x3_arg[1];
            break;

        default:
#ifdef GFXDPY_CSIH_HANDLER
            extern GFXDPY_CSIH_HANDLER(GFXdpy*, int, const short*, const char*);
            GFXDPY_CSIH_HANDLER(this, x3_argn, x3_arg, xx_text);
#endif
            break;
        }
        break;

    case 'J' | GOTBRACK:	// clear screen
        if( !x3_argn ) x3_arg[0] = 2; // default clear all
        switch( x3_arg[0] ){
        case 0:
            rect_filled(0, 0, width-1, cy-1, color_bg);
            break;
        case 1:
            rect_filled(0, cy, width-1, height-1, color_bg);
            break;
        case 2:
            clear_screen();
            if( ! x3_argn ) cx = cy = 0;	// no arg - go home
            break;
        }
        break;

    case 'K' | GOTBRACK:	// clear line
        switch( x3_arg[0] ){
        case 0: // erase to right
            rect_filled(cx, cy, width-1, cy+text_scale*font_height(font)-1, color_bg);
            break;
        case 1: // erase to left
            rect_filled(0, cy, cx, cy+text_scale*font_height(font)-1, color_bg);
            break;
        case 2: // erase line
            rect_filled(0, cy, width-1, cy+text_scale*font_height(font)-1, color_bg);
            break;
        }
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
            if( x3_argn == 4 ){
                // esc[30;R;G;B;m
                color_fg = ((x3_arg[1] & 0xFF) << 16) | ((x3_arg[2] & 0xFF) << 8) | (x3_arg[3] & 0xFF);
            }else{
                text_fg = x3_arg[0] - 30;
                set_colors();
            }
            break;
        case 40: case 41: case 42: case 43: case 44:
        case 45: case 46: case 47:
            if( x3_argn == 4 ){
                // esc[40;R;G;B;m
                color_bg = ((x3_arg[1] & 0xFF) << 16) | ((x3_arg[2] & 0xFF) << 8) | (x3_arg[3] & 0xFF);
            }else{
                text_bg = x3_arg[0] - 40;
                set_colors();
            }
            break;

        case 10: case 11: case 12: case 13: case 14:
        case 15: case 16: case 17: case 18: case 19:
            // set font with non-standard extensions
            // esc[10m
            // esc[10;123m	- font by index
            // esc[10;8;6m	- font by size
            // esc[10;`name;m	- font by name

            if( xx_text[0] )
                set_font( xx_text );
            else if( x3_argn == 3)
                set_font( x3_arg[1], x3_arg[2] );
            else if( x3_argn > 1 )
                set_font( x3_arg[1] );
            else
                set_font( x3_arg[0] - 10 );
            break;
        }
        break;

#ifdef GFXDPY_BEEPS
    case '\a':
        beep(880, volume, 100000 );
        break;

    case 'p' | GOTBRACK:
        // esc[123p		- set volume
        // esc[`eg#eg#ab;p 	- play

        if( xx_argn ) volume = x3_arg[0];
        if( xx_text[0] ) play( volume, xx_text );
        break;

#endif

#if 0 // -> esc[h
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
#endif

    case 'r' | GOTBRACK:
        // RSN - set scroll region esc[top;bot;r
        break;

    case 'S' | GOTBRACK:
        // scroll up; chars or 0;pixels
        if( !x3_argn ) x3_arg[0] = 1;
        if( !x3_arg[1] ) x3_arg[1] = 1;
        if( x3_arg[0] == 0 ){
            scroll_vert(0, 0, width, height, x3_arg[1]);
        }else{
            scroll_vert(0, 0, width, height, x3_arg[0] * text_height);
        }
        break;

    case 's' | GOTBRACK:
        // save cursor pos
        sx = cx;
        sy = cy;
        break;

    case 'T' | GOTBRACK:
        // scroll down; chars or 0;pixels
        if( !x3_argn ) x3_arg[0] = 1;
        if( !x3_arg[1] ) x3_arg[1] = 1;
        if( x3_arg[0] == 0 ){
            scroll_vert(0, 0, width, height, -x3_arg[1]);
        }else{
            scroll_vert(0, 0, width, height, -x3_arg[0] * text_height);
        }
        break;

    case 'u' | GOTBRACK:
        // restore cursor pos
        cx = sx;
        cy = sy;
        bound_pos();
        break;

    case '=' | GOTBRACK: 	// move cursor, by pixels
        cy = x3_arg[0];
        cx = x3_arg[1];
        if( cx < 0 ) cx = width  + cx;
        if( cy < 0 ) cy = height + cy;
        bound_pos();
        break;

    case '?' | GOTBRACK:
        // report queries - non-standard
        // esc[`param;?
        x3report();
        break;

    case '*' | GOTBRACK:
        // graphics - non-standard
        x3draw();
        break;

    case '<' | GOTBRACK:
        // scroll left by arg, move cursor to right edge (not standard)
        // chars or 0;pixels
        if( !x3_argn ) x3_arg[0] = 1;
        if( !x3_arg[1] ) x3_arg[1] = 1;
        if( x3_arg[0] == 0 ){
            scroll_horiz(cy, cy + text_scale * font_height(font), x3_arg[1]);
        }else{
            scroll_horiz(cy, cy + text_scale * font_height(font), x3_arg[0] * text_scale * font->width);
        }
        cx = width - text_scale * font->width;
        break;

    case '>' | GOTBRACK:
        // scroll right by arg, move cursor to left edge (not standard)
        // chars or 0;pixels
        if( !x3_argn ) x3_arg[0] = 1;
        if( !x3_arg[1] ) x3_arg[1] = 1;
        if( x3_arg[0] == 0 ){
            scroll_horiz(cy, cy + text_scale * font_height(font), - x3_arg[1]);
        }else{
            scroll_horiz(cy, cy + text_scale * font_height(font), - x3_arg[0] * text_scale * font->width);
        }
        cx = 0;
        break;

    case '\b':
        cx -= text_scale * font->width;
        residue = 0;
        if( cx < 0 ) cx = 0;
        break;
    case '\r':
        cx = 0;
        residue = 0;
        break;
    case '\n':
        cy += text_height;
        residue = 0;
        break;
    default:

        if( cy > height - text_height ){
            scroll();
        }
        if( (cx > width - text_scale * font->width) && (text_flags & GFX_FLAG_AUTOSHIFT) ){
            scroll_horiz(cy, cy + text_scale * font_height(font), text_scale * font->width);
            cx -= text_scale * font->width;
        }

        if( font->fdata ){
            cx += render_glyph2(ch);
        }else{
            render_glyph(ch);
            int gw = text_scale * glyph_width(font, ch);
            cx += gw;
            residue = text_scale * font->width - gw;
        }

        break;
    }

    x3_mode = 0;


done:
    return;
}

/****************************************************************/

void
GFXdpy::x3report(void){

    if( !strcmp(xx_text, "fonts") ){
        list_fonts();
        return;
    }
    if( !strcmp(xx_text, "font") ){
        printf("%2d x %2d  %s\n", font->width, font->lineheight, font->name);
        return;
    }
    if( !strcmp(xx_text, "x") ){
        printf("%d\n", cx);
        return;
    }
    if( !strcmp(xx_text, "y") ){
        printf("%d\n", cy);
        return;
    }
    if( !strcmp(xx_text, "width") ){
        printf("%d\n", width);
        return;
    }
    if( !strcmp(xx_text, "height") ){
        printf("%d\n", height);
        return;
    }

    printf("unknown?\n");
}

struct DrawParam {
    const char *name;
    char has_rad;
    char has_patt;	// optionally specify a line pattern
    char is_onept;
};
static const DrawParam draw_param[] = {
    { "m",   0, 0, 1 }, // move
    { "l",   0, 1, 0 }, // line
    { "c",   1, 0, 1 }, // circle
    { "cf",  1, 0, 1 }, // circle filled
    { "r",   0, 1, 0 }, // rect
    { "rf",  0, 1, 0 }, // rect, filled
    { "rr",  1, 1, 0 }, // rect, rounded
    { "rrf", 1, 1, 0 }, // rect, rounded, filled
    {}, // end sentinal
};


#define PATTERN(x) ( (x) | ((x)<< 16) )
void
GFXdpy::x3draw(void){
    unsigned pattern = 0xFFFFFFFF;
    unsigned color   = color_fg;
    short x0=0,y0=0,x1=0,y1=0, rad=0;
    char abs1=0, abs2=0, move=0, op=0;

    // esc[x;y`op;*
    // esc[x;y;x;y`op;*
    // op prefix: +-@.
    //   +  relative position
    //   @  absolute position
    //   -  position relative to 1st point
    //   .  update position

    // esc[7m = reverse color
    if( text_attr & ATTR_REVERSE ) color = color_bg;

    // parse op string
    if( xx_text[0] == '@' ) abs1 = '@';
    if( xx_text[1] == '@' ) abs2 = '@';
    if( xx_text[1] == '-' ) abs2 = '-';  // rel to x0,y0; eg. width,height

    for(op=0; xx_text[op]; op++){
        switch( xx_text[op] ){
        case '.':
        case '>':	// move only x
        case '^':	// move only y
            move = xx_text[op]; break;
        case '-':	// relative to x0,y0
        case '+':	// relative
        case '@':	// absolute
            break;
        default:
            goto breakfor;
        }
    }
breakfor:

    const struct DrawParam *dp=0;
    char i;
    for(i=0; draw_param[i].name; i++){
        if( !strcmp(draw_param[i].name, xx_text+op) )
            dp = draw_param +i;
    }

    if( !dp ) return;


    char reqd = 0;
    if( dp->is_onept == 0 ) reqd += 2;
    if( dp->has_rad ) reqd ++;
    char optd = reqd;
    if( dp->has_patt ) optd ++;

    if( x3_argn > optd ){
        // more coords
        if( x3_argn > (reqd+2) ) pattern = PATTERN(x3_arg[reqd+2]);
        if( dp->is_onept ){
            x0=x1=x3_arg[0];
            y0=y1=x3_arg[1];
            rad=x3_arg[2];
        }else{
            x0=x3_arg[0];
            y0=x3_arg[1];
            x1=x3_arg[2];
            y1=x3_arg[3];
            rad=x3_arg[4];
        }
    }else{
        // minimal coords
        if( x3_argn > (reqd) ) pattern = PATTERN(x3_arg[reqd]);

        if( dp->is_onept ){
            rad = x3_arg[0];
        }else{
            x1=x3_arg[0];
            y1=x3_arg[1];
            rad=x3_arg[2];
        }
    }

    if( !abs1 ){
        x0 += cx;
        y0 += cy;
    }
    if( abs2 == 0 ){
        x1 += cx;
        y1 += cy;
    }
    if( abs2 == '-' ){
        x1 += x0;
        y1 += y0;
    }

#if 0
    fprintf(stderr, "> %d, %s (%d,%d,%d,%d) cur (%d %d)\n",
            x3_argn, xx_text, x3_arg[0], x3_arg[1], x3_arg[2], x3_arg[3], cx, cy);

    fprintf(stderr, "> %s (%d,%d,%d,%d) r %d, p %x, a %d,%d, r %d, o %d, ->%d\n",
            dp->name, x0,y0,x1,y1, rad, pattern, abs1, abs2, reqd, optd, move);
#endif

    if( !strcasecmp(xx_text+op, "m") ){
        move = '.';
    }
    if( !strcasecmp(xx_text+op, "l") ){
        line(x0,y0, x1,y1, color, pattern);
    }
    if( !strcasecmp(xx_text+op, "c") ){
        circle(x0, y0, rad, color);
    }
    if( !strcasecmp(xx_text+op, "cf") ){
        circle_filled(x0, y0, rad, color);
    }
    if( !strcasecmp(xx_text+op, "r") ){
        rect(x0,y0,x1,y1, color, pattern);
    }
    if( !strcasecmp(xx_text+op, "rf") ){
        rect_filled(x0,y0,x1,y1, color);
    }
    if( !strcasecmp(xx_text+op, "rr") ){
        rrect(x0,y0,x1,y1, rad, color, pattern);
    }
    if( !strcasecmp(xx_text+op, "rrf") ){
        rrect_filled(x0,y0,x1,y1, rad, color);
    }

    if( dp->is_onept ){
        x1 = x0;
        y1 = y0;
    }

    // update current position
    switch( move ){
    case '.':
        cx = x1;
        cy = y1;
        break;
    case '>':
        cx = x1;
        break;
    case '^':
        cy = y1;
        break;
    }

    bound_pos();
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

    //printf(">>> line %d %d %d %d, %x %x\n", x0,y0,x1,y1, color, pattern);
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
GFXdpy::rrect(int x0, int y0, int x1, int y1, int r, int color, unsigned pattern){

    line(x0+r,y0, x1-r,y0, color, pattern);
    line(x0+r,y1, x1-r,y1, color, pattern);
    line(x0,y0+r, x0,y1-r, color, pattern);
    line(x1,y0+r, x1,y1-r, color, pattern);

    circle(x0+r, y0+r, r, color, 4 );	// top left
    circle(x0+r, y1-r, r, color, 2 );	// bottom left
    circle(x1-r, y0+r, r, color, 8 );	// top right
    circle(x1-r, y1-r, r, color, 1 );	// bottom right
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
GFXdpy::rrect_filled(int x0, int y0, int x1, int y1, int r, int color){

    circle_filled(x0+r,y0+r, r, color, x1-x0-2*r, 1); 	// top
    rect_filled(x0, y0+r, x1, y1-r, color); 		// middle
    circle_filled(x0+r,y1-r, r, color, x1-x0-2*r, 2); 	// bottom
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
        // avoid a single disconected corner point
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

// based on:
//   https://en.wikipedia.org/wiki/Midpoint_circle_algorithm
void
GFXdpy::circle(int x0, int y0, int r, int color, int sects){
    short x = r;
    short y = 0;
    short d2 = 1 - x;

    while( y <= x ){

        if( sects & 1 ){
            set_pixel( x + x0,  y + y0, color);
            set_pixel( y + x0,  x + y0, color);
        }
        if( sects & 2 ){
            set_pixel(-x + x0,  y + y0, color);
            set_pixel(-y + x0,  x + y0, color);
        }
        if( sects & 4 ){
            set_pixel(-x + x0, -y + y0, color);
            set_pixel(-y + x0, -x + y0, color);
        }
        if( sects & 8 ){
            set_pixel( x + x0, -y + y0, color);
            set_pixel( y + x0, -x + y0, color);
        }

        y++;

        if( d2 <= 0 ){
            d2 += 2 * y + 1;
        }else{
            x --;
            d2 += 2 * (y - x) + 1;
        }
    }
}

void
GFXdpy::circle_filled(int x0, int y0, int r, int color, int wid, int sects){
    short x = r;
    short y = 0;
    short d2 = 1 - x;

    while( y <= x ){
        if( sects & 1 ){
            hline( -x + x0, -y + y0, x + x0 + wid, -y + y0, color );
            hline( -y + x0, -x + y0, y + x0 + wid, -x + y0, color );
        }

        if( sects & 2 ){
            hline( -x + x0,  y + y0, x + x0 + wid,  y + y0, color );
            hline( -y + x0,  x + y0, y + x0 + wid,  x + y0, color );
        }
        
        y++;

        if( d2 <= 0 ){
            d2 += 2 * y + 1;
        }else{
            x --;
            d2 += 2 * (y - x) + 1;
        }
    }
}

void
GFXdpy::bitblit(const u_char *img, int x0, int y0, int w, int h, int color){
    short i,j;
    char b=0;

    for(j=0; j<h; j++){
        if( b ){
            // skip padding
            img ++;
            b = 0;
        }
        for(i=0; i<w; i++){
            int c = (*img & (1<<b)) ? color : 0;
            set_pixel(x0+i, y0+j, c);
            b ++;
            if( b > 7 ){
                img ++;
                b = 0;
            }
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
