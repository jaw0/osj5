/*
  Copyright (c) 2018
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2018-Apr-19 23:49 (EDT)
  Function: 

*/

#include <conf.h>
#include <proc.h>
#include <userint.h>
#include <nstdio.h>
#include <stdarg.h>
#include <error.h>
#include <userint.h>


static char *logbuf = 0;
static int logsize  = 0;
static int logpos   = 0;
static int logmode  = 0;

#define ROOMFOR(x)	(logpos < logsize - (x))
#define SPACEFOR(x)	(((x) + sizeof(struct trace_info) + 3) & ~3)

#define LRT_VERSN	0
#define LRT_MSG		1
#define LRT_DATA	2
#define LRT_FDATA	3
#define LRT_CRUMB	4


struct trace_info {
    const char *tag;
    const char *msg;
    int when;
    short type;
    short len;
};


/****************************************************************/

static inline void
_lock(void){
    irq_disable();
}

static inline void
_unlock(void){
    irq_enable();
}

/****************************************************************/

static int
printffnc(char **a, char c){

    **a = c;
    (*a) ++;

    return 1;
}

// NB - try to keep messages short
void
trace_msgf(const char *fmt, ...){
    va_list ap;

    if( !logbuf ) return;
    // if( logmode == LOGMO_OFF ) return;

    if( !ROOMFOR(64) ) return;	// XXX ~

    _lock();
    struct trace_info *ti = (struct trace_info*)(logbuf + logpos);
    ti->type = LRT_MSG;
    ti->when = get_hrtime();

    u_char *p = (u_char*)(ti + 1);

    va_start(ap,fmt);
    int l = vprintf( printffnc, &p, fmt, ap);
    // remove newline
    if( logbuf[logpos + l + 2 - 1] == '\n' ) l --;

    ti->len = l;

    logpos += SPACEFOR(l);
    _unlock();
}

void
trace_data(const char *tag, const char *evt, int len, const char *dat){

    if( !logbuf ) return;
    if( !ROOMFOR(len + sizeof(struct trace_info)) ) return;

    _lock();
    struct trace_info *ti = (struct trace_info*)(logbuf + logpos);
    ti->type = LRT_DATA;
    ti->tag  = tag;
    ti->msg  = evt;
    ti->when = get_hrtime();
    ti->len  = len;

    u_char *p = (u_char*)(ti + 1);
    memcpy(p, dat, len);

    logpos += SPACEFOR(len);
    _unlock();

}

void
trace_fdata(const char *tag, const char *fmt, int narg, ...){
    va_list ap;

    if( !logbuf ) return;
    if( !ROOMFOR(SPACEFOR(narg * sizeof(int))) ) return;

    va_start(ap, narg);

    _lock();
    struct trace_info *ti = (struct trace_info*)(logbuf + logpos);
    ti->type = LRT_FDATA;
    ti->tag  = tag;
    ti->msg  = fmt;
    ti->when = get_hrtime();
    ti->len  = narg * sizeof(int);

    int *p = (int *)(ti + 1);
    memcpy(p, ap, narg * sizeof(int));

    logpos += SPACEFOR(narg * sizeof(int));
    _unlock();

}

void
trace_crumb1(const char *tag, const char *evt, int d1){

    if( !logbuf ) return;
    if( !ROOMFOR( SPACEFOR(sizeof(int))) ) return;

    _lock();
    struct trace_info *ti = (struct trace_info*)(logbuf + logpos);
    ti->type = LRT_CRUMB;
    ti->tag  = tag;
    ti->msg  = evt;
    ti->when = get_hrtime();
    ti->len  = sizeof(int);

    int *p = (int *)(ti + 1);
    p[0] = d1;

    logpos += SPACEFOR( sizeof(int));
    _unlock();
}


void
trace_crumb2(const char *tag, const char *evt, int d1, int d2){

    if( !logbuf ) return;
    if( !ROOMFOR( SPACEFOR(2*sizeof(int))) ) return;

    _lock();
    struct trace_info *ti = (struct trace_info*)(logbuf + logpos);
    ti->type = LRT_CRUMB;
    ti->tag  = tag;
    ti->msg  = evt;
    ti->when = get_hrtime();
    ti->len  = 2 * sizeof(int);

    int *p = (int *)(ti + 1);
    p[0] = d1;
    p[1] = d2;

    logpos += SPACEFOR( 2 * sizeof(int));
    _unlock();
}

void
trace_crumb3(const char *tag, const char *evt, int d1, int d2, int d3){

    if( !logbuf ) return;
    if( !ROOMFOR( 3*SPACEFOR(2*sizeof(int))) ) return;

    _lock();
    struct trace_info *ti = (struct trace_info*)(logbuf + logpos);
    ti->type = LRT_CRUMB;
    ti->tag  = tag;
    ti->msg  = evt;
    ti->when = get_hrtime();
    ti->len  = 3 * sizeof(int);

    int *p = (int *)(ti + 1);
    p[0] = d1;
    p[1] = d2;
    p[2] = d3;

    logpos += SPACEFOR( 3 * sizeof(int));
    _unlock();
}

/****************************************************************/

void
trace_init(int bufsize){

    if( logbuf ) return;

    _lock();
    logbuf  = malloc(bufsize);
    logsize = bufsize;
    _unlock();
}

void
trace_reset(void){

    _lock();
    logpos = 0;
    _unlock();
}

static void
trace_dpy_msg(struct trace_info *ti){
    int i;

    char *d = (char*)(ti + 1);

    for(i=0; i<ti->len; i++){
        putchar( d[i] );
    }

}

static void
trace_dpy_data(struct trace_info *ti){
    printf("%s %*H", ti->msg, ti->len, ti+1);
}

static void
trace_dpy_fdata(struct trace_info *ti){

    printfv(ti->msg, ti+1);

}

static void
trace_dpy_crumb(struct trace_info *ti){
    int i;
    int *d = (int*)(ti+1);

    printf("%s ", ti->msg);

    for(i=0; i*sizeof(int)<ti->len; i++ ){
        printf("%x ", d[i]);
    }
}

void
trace_dump(void){

    int p = 0;
    int z = logpos;
    unsigned int wh;

    for(p=0; p<z; ){
        struct trace_info *ti = (struct trace_info *)(logbuf + p);

        // when, tag
        if( !p ) wh = ti->when;
        unsigned int dt = ti->when - wh;
        wh = ti->when;

        printf("%8d %-8s ", dt, ti->tag);

        switch( ti->type ){
        case LRT_MSG:
            trace_dpy_msg(ti);
            break;
        case LRT_DATA:
            trace_dpy_data(ti);
            break;
        case LRT_FDATA:
            trace_dpy_fdata(ti);
            break;
        case LRT_CRUMB:
            trace_dpy_crumb(ti);
            break;

        }

        printf("\n");
        p += SPACEFOR(ti->len);
    }
}

