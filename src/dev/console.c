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
extern FILE *pcterm_port;
#endif
#ifdef USE_SERIAL
extern FILE *serial0_port;
#endif
#ifdef PLATFORM_EMUL
extern FILE *emulcon_port;
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

#ifdef CONSOLE_ON
#  ifndef DEVPREFIX
#     define DEVPREFIX "dev:"
#  endif
    // try to use specified device
    f = fopen(DEVPREFIX CONSOLE_ON, "w");
    n = CONSOLE_ON;
    if( !f ) kprintf("console: cannot attach %s\n", DEVPREFIX CONSOLE_ON);
#endif

    if( !f ){

#ifdef USE_SERIAL
        f = serial0_port;
        n = "serial";
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

    }

    if( ! f ){
        return 0;
    }

    console_port  = f;
    f->flags |= F_ICRNL | F_ONLRET;
    kconsole_port = dup(f);

    kconsole_port->flags |= F_NONBLOCK;

    bootmsg("console installed on %s\n", n);

    return 0;
}

int
set_console(const char *file){
    FILE *f;

    f = fopen(file, "w");
    if( !f ){
        kprintf("console: cannot attach %s\n", file);
        return -1;
    }

    int plx = splhigh();
    fclose( console_port );
    fclose( kconsole_port );

    console_port = f;
    kconsole_port = dup(f);
    kconsole_port->flags |= F_NONBLOCK;
    splx(plx);

    bootmsg("console installed on %s\n", file);

    return 0;
}




