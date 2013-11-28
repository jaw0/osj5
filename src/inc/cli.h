/*
  Copyright (c) 2013
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2013-Nov-28 12:27 (EST)
  Function: 

*/

#ifndef __cli_h__
#define __cli_h__

struct cli_env {
	char prompt[32];
	char a[32], b[32], c[32], d[32];
};


#define UV_TYPE_STR16      1
#define UV_TYPE_STR32      2
#define UV_TYPE_UC         3
#define UV_TYPE_US         4
#define UV_TYPE_UL         5
#define UV_TYPE_UQ         6
#define UV_TYPE_IP         7
#define UV_TYPE_TIME	   8
#define UV_TYPE_ULX        9
#define UV_TYPE_ENV	0x80
#define UV_TYPE_PROC	0x40
#define UV_TYPE_RO	0x20



#endif /* __cli_h__ */
