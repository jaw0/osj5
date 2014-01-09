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
#define UV_TYPE_FLOAT    0xA

#define UV_TYPE_MASK	 0xFF
#define UV_TYPE_RO	0x100
#define UV_TYPE_PROC	0x200
#define UV_TYPE_ENV	0x400
#define UV_TYPE_CONFIG	0x800

typedef char uv_str16_t[16];
typedef char uv_str32_t[32];

extern void run_script(const char*);
extern int  save_config(const char *);


#endif /* __cli_h__ */
