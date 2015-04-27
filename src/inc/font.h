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
    char  height;
    char  width;
    char  byteschar;
    short startchar;
    short lastchar;
    const unsigned char data[];
};



#endif /* __font_h__ */
