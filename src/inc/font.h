/*
  Copyright (c) 2013
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2013-Mar-31 12:55 (EDT)
  Function: fonts
*/

#ifndef __font_h__
#define __font_h__

struct FontMetric {
    signed char xadj;
};

struct Font {
    const char *name;
    char  type;
    char  height;	// height in pixels
    char  width;	// width in pixels
    char  bytescol;	// height in bytes
    char  numcol;	// width in columns
    short startchar;
    short lastchar;
    const struct FontMetric *metrics;
    unsigned char data[];
};



#endif /* __font_h__ */
