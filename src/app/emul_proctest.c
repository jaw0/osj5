

#include <proc.h>

void
runtest(void){

    currproc->prio = 15;
    while(1){}

}

void
proctest(void){

    start_proc( 1024, runtest, "test1" );
    //start_proc( 1024, runtest, "test2" );
}
