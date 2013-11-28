
/*
  Copyright 1998,1999,2000,2001 Jeff Weisberg <jaw@tcp4me.com>
  see the file LICENSE for details
*/

#ifndef __userint_h__
#define __userint_h__

#include <misc.h>
#include <cli.h>

/* functions */
#define DEFUN(name, docstr)	int CONCAT(ui_f_, name)(int argc, char** argv, struct cli_env *env)
#define DEFALIAS(name, aname)	/* */


/* vars */
#define DEFVAR(proto, name, init, type, docstr) proto name = init;


#endif /* __userint_h__ */

