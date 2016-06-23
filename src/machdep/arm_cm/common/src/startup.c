
/*
  Copyright (c) 2016
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2016-May-30 14:29 (EDT)
  Function: common arm cortext-m* startup

*/


extern unsigned int _sidata[];
extern unsigned int _sdata[];
extern unsigned int _edata[];
extern unsigned int _sbss[];
extern unsigned int _ebss[];

extern void (*__init_array_start[])(void);
extern void (*__init_array_end[])(void);

extern void start(void);

void
Reset_Handler(void){
    unsigned int *src, *dst;

    /* copy initialized data */
    src = _sidata;
    dst = _sdata;
    while( dst != _edata ) *dst++ = *src++;

    /* zero bss */
    dst = _sbss;
    while( dst != _ebss ) *dst++ = 0;

    /* run C++ constructors */
    void (**f)(void) = __init_array_start;
    while( f != __init_array_end ){
        (*f)();
        f++;
    }

    start();
}
