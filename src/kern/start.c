/*
  Copyright (c) 2011
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2011-Dec-11 23:51 (EST)
  Function: startup
 
  $Id$

*/

#include <conf.h>
#include <proc.h>

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
    FILE *f;
    f = fopen( MOUNT_ROOT STARTUPFILE, "r" );
    if( f ){
        fshell(f, 0);
        fclose(f);
    }
# endif

    extern void shell(void);
    shell();
#endif

    while(1) yield();
}
