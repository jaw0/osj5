/*
  Copyright (c) 2011
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2011-Dec-11 23:51 (EST)
  Function: startup

*/

#include <conf.h>
#include <proc.h>
#include <bootflags.h>

#ifndef STANDALONE
void
start(void){
    struct Proc proc0;

    init(&proc0);

#ifdef PROJECT_MAIN
    extern void PROJECT_MAIN(void);
    PROJECT_MAIN();
#endif

#ifdef USE_CLI
# if defined(USE_FILESYS) & defined(MOUNT_ROOT) & defined(STARTUPFILE)
    if( !(bootflags & BOOT_NORC) )
        run_script( MOUNT_ROOT STARTUPFILE );
# endif

    proc0.name = "shell";
    extern void shell(void);
    shell();
#endif

    while(1) yield();
}
#endif
