/*
  Copyright (c) 1998
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 1998
  Function:

  $Id$

*/


#include <conf.h>
#include <nstdio.h>
#include <proc.h>
#include <error.h>

static const char * const bad_f = "invalid FILE*";

/* initialize file */
int finit(FILE *f){
    int i;

    if( !f )
        PANIC(bad_f);

    f->ungotc  = 0;
    f->flags   = 0;
    f->prevout = 0;
    f->dupped  = 0;
    f->flags |= F_ICRNL | F_ONLRET;

    f->d = 0;

    for(i=0; i<sizeof(f->cchars); i++)
        f->cchars[i] = 0;
    f->ccpid = 0;

    return 1;
}

/* dup file */
FILE *dup(FILE *f){
    FILE *n;

    if( !f )
        PANIC(bad_f);
    n = (FILE*)alloc(sizeof(FILE));
    bcopy(f, n, sizeof(FILE));
    n->dupped = f;
    return n;
}

void fsetcchar(FILE *f, int i, int c){

    if( !f ) f = STDIN;
    while( f->dupped ){ f = f->dupped; }
    f->ccpid = (proc_t)currproc;
    f->cchars[i] = c;
}

int putchar(char c){
    return fputc(c, STDOUT);
}
int getchar(void){
    return fgetc(STDIN);
}
/* puts includes \n, fputs does not. */
void puts(const char *mesg ){
    while( *mesg )
        putchar( *mesg++ );
    putchar('\n');
}
void fputs(const char *mesg, FILE *f){
    while( *mesg )
        fputc( *mesg++, f);
}

char *fgets(char *s, int n, FILE *f){
    char *ss = s;
    int c;

    while( --n && (c=fgetc(f)) != -1 && c != '\n' && c != '\r' ){
        *ss++ = c;
    }
    *ss = 0;
    return (s == ss && f->flags & F_EOF) ? 0 : s;
}

int ungetc(char c, FILE *f){

    if( !f )
        PANIC(bad_f);
    f->ungotc = c;
    f->flags |= F_UNGOT;

    return 1;
}

int fgetc(FILE *f){
    int c;

    if( !f || !f->fs )
        PANIC(bad_f);
    if( !f->fs->getc ) return -1;
    if( f->flags & F_UNGOT ){
        f->flags &= ~F_UNGOT;
        return f->ungotc;
    }
    if( f->flags & F_EOF )
        return -1;
    c = (f->fs->getc)(f);
    if( f->flags & F_ISTRIP )
        c &= 0x7F;
    if( c=='\n' && f->flags & F_INLCR )
        c = '\r';
    else if( c=='\r' ){
        if( f->flags & F_ICRNL )
            c = '\n';
        if( f->flags & F_IGNCR )
            c = fgetc(f);
    }
    if( f->flags & F_ECHO )
        fputc(c, f);
    return c;
}

int fputc(char c, FILE *f){

    if( !f || !f->fs )
        PANIC(bad_f);
    if(  !f->fs->putc ) return -1;
    if( f->flags & F_OSTRIP )
        c &= 0x7F;
    if( c=='\n' ){
        if( f->prevout != '\r' && f->flags & F_ONLRET )
            (f->fs->putc)(f, '\r');
        if( f->flags & F_ONLCR )
            c = '\r';
    }else if( c=='\r' ){
        if( f->flags & F_OCRNL )
            c = '\n';
        if( f->flags & F_ONOCR )
            return 1;
    }else if( f->flags & F_ECHOCTL ){
        if( c && c <= 27 && c != 8 ){
            f->prevout = c;
            (f->fs->putc)(f, '^');
            if( c == 27 )
                return (f->fs->putc)(f, '$');
            return (f->fs->putc)(f, c + 'A' - 1);
        }
    }
    f->prevout = c;
    return (f->fs->putc)(f, c);
}

int fflush(FILE *f){

    if( !f || !f->fs )
        PANIC(bad_f);
    if( !f->fs->flush ) return -1;
    return (f->fs->flush)(f);
}

int fstatus(FILE *f){

    if( !f || !f->fs || !f->fs->status )
        PANIC(bad_f);
    return (f->fs->status)(f);
}


int fwrite(FILE *f, const char *b, int n){
    int r = 0;

    if(!f || !f->fs)
        PANIC(bad_f);
    if(f->fs->write)
        return (f->fs->write)(f,b,n);

    /* else iterate putc */
    while(n){
        r = fputc(*b, f);
        b++;
        n--;
    }

    return r;
}

int fread(FILE *f, char *b, int n){
    int c;

    if(!f || !f->fs)
        PANIC(bad_f);
    if(f->fs->read)
        return (f->fs->read)(f,b,n);
    /* getc one char */
    if( n > 1 ){
        c = fgetc(f);
        if( c >= 0 ){
            *b = c;
            return 1;
        }
        return -1;
    }
    return 0;
}

int
fbread(FILE *f, char *b, int len, offset_t pos){

    if(!f || !f->fs || !f->fs->bread)
        PANIC(bad_f);

    return f->fs->bread(f,b,len,pos);
}

int fbwrite(FILE *f, const char *b, int len, offset_t pos){

    if(!f || !f->fs || !f->fs->bwrite)
        PANIC(bad_f);

    return f->fs->bwrite(f,b,len,pos);
}


int fclose(FILE *f){

    if( !f || !f->fs )
        PANIC(bad_f);
    if( f->fs->close )
        return (f->fs->close)(f);
    return 0;
}

int fseek(FILE *f, long off, int how){

    if( !f || !f->fs  )
        PANIC(bad_f);

    if( !f->fs->seek ){
        return -1;
    }
    return (f->fs->seek)(f, off, how);
}

long ftell(FILE *f){

    if( !f || !f->fs  )
        PANIC(bad_f);

    if( !f->fs->tell ){
        return -1;
    }
    return (f->fs->tell)(f);
}

int fstat(FILE *f, struct stat *s){

    if( !f || !f->fs  )
        PANIC(bad_f);

    bzero(s, sizeof(struct stat));

    if( !f->fs->stat ){
        return -1;
    }
    return (f->fs->stat)(f, s);
}

int fioctl(FILE *f, int c, void *a){

    if( !f || !f->fs  )
        PANIC(bad_f);

    if( !f->fs->ioctl ){
        kprintf("fioctl %x unimplemented for %x\n", c, f);
        return -1;
    }
    return (f->fs->ioctl)(f, c, a);
}

