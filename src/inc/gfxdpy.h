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

class GFXdpy {
public:
    FILE 	file;
    short  _height;
    short  _width;
    short  height;
    short  width;

    u_char orientation;
    u_char text_flags;
    u_char text_scale;
    u_char text_attr;

    u_char text_fg,  text_bg;

    int	   color_fg, color_bg;

private:
    short  cx,cy;

    char x3_arg[MAXX3ARG];
    char x3_argn;
    u_char x3_flags;
    short x3_mode;

    const Font *font;

public:
    virtual void flush(void);
    virtual void _set_pixel(int, int, int);
    virtual int  _get_pixel(int, int);
    virtual void clear_screen(void);
    virtual void set_colors(void);
    virtual void set_sleep(bool);

    void init(void);
    void set_pixel(int, int, int);
    int  get_pixel(int, int);
    void set_orientation(int);
    void scroll(void);
    void scroll_horiz(int,int,int);
    void render_glyph(int);
    void putchar(int);

};

#endif /* __gfxdpy_h__ */
