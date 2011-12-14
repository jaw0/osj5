/*
  Copyright (c) 2011
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2011-Dec-05 12:42 (EST)
  Function:

  $Id$

*/

#include <sys/types.h>
#include <sys/param.h>
#include <conf.h>
#include <arch.h>
#include <nstdio.h>
#include <proc.h>
#include <alloc.h>
#include <dev.h>
#include <fs.h>
#include <bootflags.h>

extern struct Device_Conf all_devices[];
extern int n_devs;
extern void kflush(int);
extern void init_ddb(void);

extern const char *version;

void
autoconfig(void){
    int i;
    FILE *f;

    for(i=0; i<n_devs; i++){
        if( all_devices[i].init )
            f = (FILE*)( (all_devices[i].init)( all_devices + i ));
#ifdef USE_FILESYS
        if( all_devices[i].name && f > 0 )
            /* mount device in dev: */
            mount( f, all_devices[i].name, 1, 0);
#endif

    }
}

void
init(proc_t proc){
    char buf[64];
    int i;

    splhigh();

    /* machdep initialization */
    init_hw();
    init_ints();

    /* spit out banner */
    kprintf("%s", version);

    kprintf("bootflags = 0x%x\n", bootflags);

#ifdef USE_DDB
    init_ddb();
#endif

    autoconfig();

    kflush(0);	/* flush buffered output */

#ifdef USE_PROC
    init_proc(proc);
#endif

}

