/*
  Copyright (c) 2013
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2013-Mar-31 12:55 (EDT)
  Function: fonts
*/

#ifndef __font_h__
#define __font_h__

class Font {
public:
    int height;
    int width;
    int startchar;
    int lastchar;
    int byteschar;
    const unsigned char *data;

    int get_charld(int, int) const;
};



#endif /* __font_h__ */
