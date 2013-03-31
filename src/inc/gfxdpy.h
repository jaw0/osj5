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

#define GFX_FLAG_AUTOFLUSH	1


#define MAXX3ARG 4

class GFXdpy {
public:
    int _height;
    int _width;
    int text_flags;

public:
    int orientation;
    int	height;
    int width;

private:
    int cx,cy;
    int text_attr;
    int text_scale;

    int  x3_argn;
    char x3_arg[MAXX3ARG];
    int  x3_mode;


public:
    virtual void flush(void);
    virtual void _set_pixel(int, int, int);
    virtual int  _get_pixel(int, int);
    virtual void clear_screen(void);


    void init(void){ orientation = cx = cy = text_attr = text_flags = x3_argn = x3_mode = 0; text_scale = 1; }
    void set_pixel(int, int, int);
    int  get_pixel(int, int);
    void set_orientation(int);
    void scroll(void);
    void render_glyph(int);
    void putchar(int);

};

#endif /* __gfxdpy_h__ */
