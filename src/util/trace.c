/*
  Copyright (c) 2018
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2018-Apr-19 23:49 (EDT)
  Function: tracing

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
#define LRT_MARK_START	5
#define LRT_MARK_STOP	6

#ifndef TRACE_BUFSIZE
# define TRACE_BUFSIZE 8192
#endif

#ifndef TRACE_CLOCK
# define TRACE_CLOCK get_hrtime
#endif
extern utime_t TRACE_CLOCK();


struct trace_info {
    const char *tag;
    const char *msg;
    int when;
    short type;
    short len;
};


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
    va_start(ap,fmt);

    if( !logbuf ) return;
    // if( logmode == LOGMO_OFF ) return;

    if( !ROOMFOR(64) ) return;	// XXX ~

    int plx = splhigh();
    struct trace_info *ti = (struct trace_info*)(logbuf + logpos);
    ti->type = LRT_MSG;
    ti->when = TRACE_CLOCK();

    u_char *p = (u_char*)(ti + 1);

    int l = vxprintf( printffnc, &p, fmt, ap);
    // remove newline
    if( logbuf[logpos + l + 2 - 1] == '\n' ) l --;

    ti->len = l;

    logpos += SPACEFOR(l);
    splx(plx);
}

void
trace_data(const char *tag, const char *evt, int len, const char *dat){

    if( !logbuf ) return;
    if( !ROOMFOR(len + sizeof(struct trace_info)) ) return;

    int plx = splhigh();
    struct trace_info *ti = (struct trace_info*)(logbuf + logpos);
    ti->type = LRT_DATA;
    ti->tag  = tag;
    ti->msg  = evt;
    ti->when = TRACE_CLOCK();
    ti->len  = len;

    u_char *p = (u_char*)(ti + 1);
    memcpy(p, dat, len);

    logpos += SPACEFOR(len);
    splx(plx);

}

void
trace_fdata(const char *tag, const char *fmt, int narg, ...){
    va_list ap;

    if( !logbuf ) return;
    if( !ROOMFOR(SPACEFOR(narg * sizeof(int))) ) return;

    va_start(ap, narg);

    int plx = splhigh();
    struct trace_info *ti = (struct trace_info*)(logbuf + logpos);
    ti->type = LRT_FDATA;
    ti->tag  = tag;
    ti->msg  = fmt;
    ti->when = TRACE_CLOCK();
    ti->len  = narg * sizeof(int);

    int *p = (int *)(ti + 1);
    memcpy(p, ap, narg * sizeof(int));

    logpos += SPACEFOR(narg * sizeof(int));
    splx(plx);

}

void
trace_crumb(const char *tag, const char *evt, int narg, ...){
    va_list ap;
    va_start(ap, narg);

#ifdef TRACE_ALSO2_ITMSWO
    itm_trace_crumb( TRACE_ALSO2_ITMSWO, tag, evt, narg, ap);
#endif

    if( !logbuf ) return;
    if( !ROOMFOR(SPACEFOR(narg * sizeof(int))) ) return;

    int plx = splhigh();
    struct trace_info *ti = (struct trace_info*)(logbuf + logpos);
    ti->type = LRT_CRUMB;
    ti->tag  = tag;
    ti->msg  = evt;
    ti->when = TRACE_CLOCK();
    ti->len  = narg * sizeof(int);

    int *p = (int *)(ti + 1);
    memcpy(p, ap, narg * sizeof(int));

    logpos += SPACEFOR(narg * sizeof(int));
    splx(plx);
}

void
trace_mark_start(const char *tag){
    va_list ap;

    if( !logbuf ) return;
    if( !ROOMFOR(0) ) return;

    int plx = splhigh();
    struct trace_info *ti = (struct trace_info*)(logbuf + logpos);
    ti->type = LRT_MARK_START;
    ti->tag  = tag;
    ti->when = TRACE_CLOCK();
    ti->len  = 0;
    ti->msg  = 0;

    logpos += SPACEFOR(0);
    splx(plx);
}

void
trace_mark_stop(const char *tag){
    va_list ap;

    if( !logbuf ) return;
    if( !ROOMFOR(0) ) return;

    int plx = splhigh();
    struct trace_info *ti = (struct trace_info*)(logbuf + logpos);
    ti->type = LRT_MARK_STOP;
    ti->tag  = tag;
    ti->when = TRACE_CLOCK();
    ti->len  = 0;
    ti->msg  = 0;

    logpos += SPACEFOR(0);
    splx(plx);
}


/****************************************************************/

void
trace_init(void){

#ifdef TRACE_ALSO2_ITMSWO
    itm_port_enable( TRACE_ALSO2_ITMSWO );
#endif

    if( logbuf ) return;

    int plx = splhigh();
    logbuf  = malloc(TRACE_BUFSIZE);
    logsize = TRACE_BUFSIZE;
    splx(plx);
}

void
trace_reset(void){

    int plx = splhigh();
    logpos = 0;
    splx(plx);
}

int
trace_size(void){
    return logpos;
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

    vprintf(ti->msg, ti+1);

}

static void
trace_dpy_crumb(struct trace_info *ti){
    int i;
    int *d = (int*)(ti+1);

    printf("%s", ti->msg);

    for(i=0; i*sizeof(int)<ti->len; i++ ){
        printf(" %x", d[i]);
    }
}

void
trace_dump(int markflag, const char *filter){

    int p = 0;
    int z = logpos;
    int inmark = 0;
    unsigned int wh;

    for(p=0; p<z; ){
        struct trace_info *ti = (struct trace_info *)(logbuf + p);

        if( !filter || !strcmp(filter, ti->tag) ){

            if( ti->type == LRT_MARK_START ) inmark = 1;
            if( !markflag || inmark ){

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

                case LRT_MARK_START:
                    printf("start {");
                    break;

                case LRT_MARK_STOP:
                    printf("stop }");
                    inmark = 0;
                    break;
                }

                printf("\n");
            }
        }

        p += SPACEFOR(ti->len);
    }
}

DEFUN(trace, "trace")
{
    const char *filt = 0;
    int resetp = 0;
    int markp = 0;

    if( (argc > 1) && !strcmp(argv[1], "-r") ){
        resetp = 1;
        argc--;
        argv++;
    }
    if( (argc > 1) && !strcmp(argv[1], "-m") ){
        markp = 1;
        argc--;
        argv++;
    }
    if( argc > 1 ){
        filt = argv[1];
    }

    trace_dump(markp, filt);

    if( resetp ) trace_reset();

    return 0;
}
