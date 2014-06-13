/*
  Copyright (c) 1998
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 1998
  Function: initilize system
*/

#include <sys/types.h>
#include <sys/param.h>
#include <conf.h>
#include <arch.h>
#include <misc.h>
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

extern hexdump(const unsigned char *p, int len);

void
autoconfig(void){
    int i;
    FILE *f;

    for(i=0; i<n_devs; i++){
        if( all_devices[i].init )
            f = (FILE*)( (all_devices[i].init)( all_devices + i ));

        if( all_devices[i].name && f > 0 )
            /* mount device in dev: */
            devmount( f, all_devices[i].name );
    }
}

void
init(proc_t proc){

    splhigh();
    irq_disable();

    /* machdep initialization */
    init_hw();
    init_ints();

    /* spit out banner */
    bootmsg("\n%s", version);

    splx(IPL_PROC);
    irq_enable();

    init_hw2();

#ifdef USE_DDB
    init_ddb();
#endif

    autoconfig();

    kflush(0);	/* flush buffered output */

#ifdef PROJECT_INIT
    extern void PROJECT_INIT(void);
    PROJECT_INIT();
#endif

#ifdef USE_PROC
    init_proc(proc);
#endif

}

