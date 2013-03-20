/*
  Copyright (c) 2011
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2011-Dec-12 00:00 (EST)
  Function: 
 
  $Id$

*/

#include <conf.h>
#include <proc.h>
#include <arch.h>

void sighandler();
unsigned long bootflags = 0;

int main(int argc, char**argv){ start(); }

void
init_hw(void){

    signal(14, sighandler);
    ualarm( PROC_TIME, PROC_TIME );

}

void init_hw2(void){}

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

