
/*
  Copyright 1998,1999,2000,2001 Jeff Weisberg <jaw@tcp4me.com>
  see the file LICENSE for details
*/

/* $Id: userint.h,v 1.1 2001/10/31 18:09:14 jaw Exp $ */

#ifndef __userint_h__
#define __userint_h__

#include <misc.h>

struct cli_env {
	char prompt[32];
	char a[32], b[32], c[32], d[32];
};

#define DEFUN(name, docstr)	int CONCAT(ui_f_, name)(int argc, char** argv, struct cli_env *env)
#define DEFALIAS(name, aname)	/* */

#endif /* __userint_h__ */

