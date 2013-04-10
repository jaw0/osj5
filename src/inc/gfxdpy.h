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

class Font;

class GFXdpy {
public:
    short _height;
    short _width;
    u_char text_flags;

public:
    u_char orientation;
    short height;
    short width;

private:
    short  cx,cy;
    u_char text_attr;
    u_char text_scale;

    char x3_arg[MAXX3ARG];
    char x3_argn;
    short x3_mode;

    const Font *font;

public:
    virtual void flush(void);
    virtual void _set_pixel(int, int, int);
    virtual int  _get_pixel(int, int);
    virtual void clear_screen(void);


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
