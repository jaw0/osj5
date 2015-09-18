/*
  Copyright (c) 2013
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2013-Mar-31 12:55 (EDT)
  Function: fonts
*/

#ifndef __font_h__
#define __font_h__

struct Font {
    const char *name;
    char  type;
    char  height;	// height in pixels
    char  width;	// width in pixels
    char  bytescol;	// height in bytes
    char  numcol;	// width in columns
    short startchar;
    short lastchar;
    unsigned char data[];
};
// type=1 => fixed length encodingf, monospaced fonts

// for type=2 variable length encoded proportional fonts
// NB - cursor will advance by xoff+xpad+numcol
struct FontGlyph {
    char  reclen;	// glyph size not including this field (0 => empty glyph)
    char  xoff     : 4;
    char  xpad     : 4;
    char  yoff     : 4;
    char  bytescol : 4;
    char  numcol;
    unsigned char data[];
};


#endif /* __font_h__ */
