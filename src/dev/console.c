/*
  Copyright (c) 1998
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 1998
  Function: console "virtual" device

  $Id$

*/


#include <sys/types.h>
#include <sys/param.h>
#include <nstdio.h>
#include <conf.h>
#include <proc.h>
#include <error.h>
#include <dev.h>
#include <bootflags.h>

#ifdef USE_PCTERM
FILE *pcterm_port;
#endif
#ifdef USE_SERIAL
FILE *serial0_port;
#endif
#ifdef PLATFORM_EMUL
FILE *emulcon_port;
#endif

FILE *console_port=0, *kconsole_port=0;
extern u_long bootflags;

/* RSN have console capable devs register
   console_register(fd, name, prio)
*/

/*
  initialize the console
*/
int
console_init(struct Device_Conf *dev){
    FILE *f=0;
    char *n;

#ifdef USE_SERIAL
    f = serial0_port;
    n = "serial0";
#endif

#ifdef USE_PCTERM
#   ifdef USE_SERIAL
    if( !(bootflags & BOOT_ALTCON) ){
#   endif
        f = pcterm_port;
        n = "pcterm0";
#   ifdef USE_SERIAL
    }
#   endif
#endif

#ifdef PLATFORM_EMUL
    f = emulcon_port;
    n = "emulcon0";
#endif

    if( ! f ){
        return 0;
    }

    console_port  = f;
    kconsole_port = dup(f);

    kconsole_port->flags |= F_NONBLOCK;

    kprintf("console installed on %s\n", n);

    return 0;
}





