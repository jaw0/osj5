

#include <sys/types.h>
#include <proc.h>
#include <arch.h>
#include <msgs.h>
#include <bootflags.h>

#define INTERVAL	250000

void sighandler();
void shell();
void reapkids();

long k_paddr = 0;


void
init_signals(void){

	signal(14, sighandler);
	ualarm( PROC_TIME, PROC_TIME );
}

asm("sighandler:\n"
    "pushl $0\n"
    "call sigsetmask\n"
    "pushl $32\n");
PUSHALOT();
asm("call intr_handler");
POPALOT();
asm("addl $8, %esp\n");
asm("cmpb $0, yieldflag");
asm("je 1f");
asm("cmpb $0, cpl");
asm("jne 1f");
asm("movb $0, yieldflag");
asm("call _yield");
asm("1:");
asm("ret");


void
bar(){
	printf("bar\n");
}

void
dotboy(){

    currproc->name = "dotboy";
    while(1){
        write(2, ".", 1);
        usleep(1000);
    }
}

main(){
	struct Proc proc0;
	struct Catch cf;
  	cpl = 1;
        // bootflags = BOOT_SINGLE;
	init_signals();
        init(&proc0);

	CATCHF(cf, MSG_DEADKID, reapkids);

        //start_proc(1024, dotboy);
        //sleep(5000);

#if 0        
	if( !fork(1024)){
		struct Catch cf;
		
		currproc->name = "ball";
		
		while(1){
			CATCHL(cf, 1234, caught);
			usleep(10000);
			throw(1234, 17);
			printf("dropped the ball\n");
			if(0){
			  caught:
				printf("caught %d\n", cf.retval);
			}
		}
		UNCATCH(cf);
		exit(0);
	}

	if( !fork(1024)){
		currproc->name = "bangboy";
		while(1){
			usleep(3700);
			write(2, "!", 1);

		}
	}

	if( !fork(1024)){
		int i;
		currproc->name = "hog";
		while(1){
			i ++;
			
		}
	}
#endif
	shell();
	exit(0);
}

