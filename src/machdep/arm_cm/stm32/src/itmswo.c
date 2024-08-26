/*
  Copyright (c) 2024
  Author: Jeff Weisberg <tcp4me.com!jaw>
  Created: 2024-Aug-25 16:50 (EDT)
  Function: ITM SWO output

*/

#include <conf.h>
#include <nstdio.h>
#include <ioctl.h>
#include <proc.h>
#include <arch.h>
#include <error.h>
#include <misc.h>
#include <dev.h>
#include <bootflags.h>
#include <clock.h>
#include <stm32.h>
#include <stdarg.h>

#define ITM_BAUD_DEFAULT 2000000

int itm_putchar(FILE*, char);
int itm_getchar(FILE*);
int itm_write(FILE*, const char *, int);

const struct io_fs itm_port_fs = {
    itm_putchar,
    itm_getchar,
    0, // close
    0, // flush
    0, // status
    0, // read
    itm_write,
    0, // bread
    0, // bwrite
    0, // seek
    0, // tell
    0, // stat
    0, // ioctl
};

struct ITMswo {
    FILE file;
};
static struct ITMswo itm[ N_ITMSWO ];

int
itmswo_init(struct Device_Conf *dev){
    int i     = dev->unit;
    int speed = dev->baud;
    if( !speed ) speed = ITM_BAUD_DEFAULT;


    bzero( &itm[i], sizeof(struct ITMswo));
    finit( & itm[i].file );
    itm[i].file.fs = &itm_port_fs;
    itm[i].file.codepage = CODEPAGE_UTF8;
    itm[i].file.d  = (void*)&itm[i];


    int psc = SYSCLOCK / speed - 1;

    // CoreDebug->DEMCR = CoreDebug_DEMCR_TRCENA_Msk; // enable trace in core debug

    TPI->ACPR = psc;
    TPI->SPPR = 2;		// 2=NRZ, 1=manchester
    TPI->FFCR = TPI_FFCR_TrigIn_Msk;

    ITM->LAR = 0xC5ACCE55; 	// unlock access
    ITM->TCR = ITM_TCR_TRACEBUSID_Msk | ITM_TCR_SWOENA_Msk | ITM_TCR_SYNCENA_Msk | ITM_TCR_ITMENA_Msk
        | ITM_TCR_TSENA_Msk;
    ITM->TPR = 0;		// allow unpriv access
    ITM->TER = 1; 		// enable port 0

    DWT->CTRL = 0x400003FE;

    return (int) &itm[i].file;
}

void
itm_port_enable(int port){
    ITM->TER |= 1 << port;
}

int
itm_port_putchar(int port, int ch){

    // ITM enabled ?
    if( (ITM->TCR & ITM_TCR_ITMENA_Msk) == 0 ) return;

    // port enabled ?
    if( (ITM->TER & (1<<port)) == 0 ) return;

    int maxwait = 1000;
    while(--maxwait && (ITM->PORT[0U].u32 == 0) ){
        __asm("nop");
    }

    ITM->PORT[port].u8 = ch;
    return 1;
}

int
itm_getchar(FILE *f){
    tsleep( 0, 0, "itm/in", 0 );
    return 0;
}


int
itm_putchar(FILE *f, char ch){
    itm_port_putchar(0, ch);
}

int
itm_write(FILE *f, const char *buf, int len){
    int i;

    for(i=0; i<len; i++){
        itm_port_putchar(0, *buf);
        buf++;
    }

    return len;
}

static int
kprintffnc_itm(void *a, char c){
    itm_port_putchar( (int)a, c );
}

void
itm_printf(int port, const char *fmt, ...){
    va_list ap;

    va_start(ap,fmt);
    vxprintf(kprintffnc_itm, port, fmt, ap);
}

void
itm_vprintf(int port, const char *fmt, va_list ap){
    vxprintf(kprintffnc_itm, port, fmt, ap);
}

static void
_putstr(int port, const char *s){
    while(*s){
        itm_port_putchar(port, *s);
        s ++;
    }
}

static void
_putnum(int port, uint32_t n){
    int i, c;

    for(i=7; i>=0; i--){
        c = 0xF<<(i<<2);
        c += '0';
        if( c > '9' ) c += 'A' - '0';
        itm_port_putchar(port, c);
    }
}

// option TRACE_ALSO2_ITMSWO 30
void
itm_trace_crumb(int port, const char *tag, const char *evt, int narg, uint32_t *ap){
    int i;

    _putstr(port, tag);
    itm_port_putchar(port, ' ');
    _putstr(port, evt);

    for(i=0; i<narg; i++){
        itm_port_putchar(port, ' ');
        _putnum(port, ap[i]);
    }

    itm_port_putchar(port, '\n');

}

void
itm_panic(const char *msg, int line, const char *file){

    itm_port_enable( 31 );
    itm_printf(31, "\nPANIC: %s at line %d of %s\n*** halting ***\n", msg, line, file);

}
