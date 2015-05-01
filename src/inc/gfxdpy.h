/*
  Copyright (c) 2013
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2013-Mar-31 10:48 (EDT)
  Function: graphic display
*/
#ifndef __gfxdpy_h__
#define __gfxdpy_h__



#define GFX_ORIENT_0	0
#define GFX_ORIENT_90	1
#define GFX_ORIENT_180	2
#define GFX_ORIENT_270	3

#define GFX_FLAG_AUTOFLUSH	1	// flush display every character
#define GFX_FLAG_AUTOSHIFT	2	// left scroll line


#define MAXX3ARG 4

#define ATTR_REVERSE	1
#define ATTR_ULINE	2
#define ATTR_STRIKE	4
#define ATTR_FAINT	8
#define ATTR_BRIGHT	16


class Font;

typedef unsigned char u_char;
typedef signed   char s_char;
#undef putchar

class GFXdpy {
public:
#ifdef USE_NSTDIO
    FILE   file;
#endif
    short  _height;		// display physical size
    short  _width;
    short  height;		// effective size in this orientation
    short  width;

    u_char orientation;		// GFX_ORIENT_*
    u_char text_flags;		// GFX_FLAG_*
    u_char text_scale;		// scale factor for text
    u_char text_attr;		// ATTR_*

    u_char text_fg,  text_bg;	// ANSI code
    int	   color_fg, color_bg;	// rgb

private:
    short  cx,cy;		// current cursor position

    // putchar ansi x3.64 state
    s_char x3_arg[MAXX3ARG];
    char   x3_argn;
    u_char x3_flags;
    short  x3_mode;

    const Font *font;		// current font

public:
    virtual void flush(void) = 0;
    virtual void _set_pixel(int, int, int) = 0;
    virtual int  _get_pixel(int, int) = 0;
    virtual void clear_screen(void) = 0;
    virtual void set_colors(void) = 0;
    virtual void set_sleep(bool);
    virtual u_char* get_buffer(void);
    virtual bool is_color(void) = 0;

    void init(void);
    void set_pixel(int, int, int);
    int  get_pixel(int, int);
    void set_orientation(int);
    void scroll(void);
    void scroll_horiz(int,int,int);
    void scroll_vert(int,int,int);
    void render_glyph(int);
    void putchar(int);
    void puts(const char *);
    void get_pos(int*, int*);
    void set_pos(int, int);
    void set_font(int);
    void set_font(const Font*);
    bool set_font(const char *);
    static const Font* find_font(const char *);

    void hline(int,int, int,int, int);

    void line(int,int, int,int, int, unsigned p=0xFFFFFFFF);
    void rect(int,int, int,int, int, unsigned p=0xFFFFFFFF);
    void rect_filled(int,int, int,int, int);
    void triangle(int,int, int,int, int,int, int, unsigned p=0xFFFFFFFF);
    void triangle_filled(int,int, int,int, int,int, int);

    // RSN: drawing: arc, circle, ellipse, ...
};

#endif /* __gfxdpy_h__ */
