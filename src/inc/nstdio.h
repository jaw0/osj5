
/*
  Copyright 1998,1999,2000,2001 Jeff Weisberg <jaw@tcp4me.com>
  see the file LICENSE for details
*/

/* $Id: nstdio.h,v 1.11 2001/10/31 18:09:12 jaw Exp $ */

#ifndef __nstdio_h__
#define __nstdio_h__

#include <sys/types.h>

struct FILE;
struct stat;

typedef long long offset_t;

struct io_fs {
	int  (*putc)(struct FILE*, char);
	int  (*getc)(struct FILE*);
	int  (*close)(struct FILE*);
	int  (*flush)(struct FILE*);
	int  (*status)(struct FILE*);
	int  (*read)(struct FILE*, char*, int);
	int  (*write)(struct FILE*, const char*, int);
        int  (*bread)(struct FILE*, char*, int, offset_t);
        int  (*bwrite)(struct FILE*, const char*, int, offset_t);
	int  (*seek)(struct FILE*, long, int);
	long (*tell)(struct FILE*);
	int  (*stat)(struct FILE*, struct stat*);
	int  (*ioctl)(struct FILE*, int, void*);
};

typedef struct FILE {
	u_long flags;
#define	F_UNGOT		1	/* for ungetc */
#define F_NONBLOCK	2	/* non-blocking output */
#define F_EOF		4	/* nothing left to read */
#define	F_IGNCR		8	/* strip \r on input */
#define F_INLCR		0x10	/* map \n -> \r on input */
#define F_ICRNL		0x20	/* map \r -> \n on input */
#define F_ISTRIP	0x40	/* strip high bit on input */
#define	F_ONLCR		0x80	/* map \n -> \r on output */
#define F_OCRNL		0x100	/* map \r -> \n on output */
#define F_ONLRET	0x200	/* map \n -> \r\n on output */
#define F_ONOCR		0x400	/* drop \r on output */
#define F_OSTRIP	0x800	/* strip high bit on output */
#define F_ECHO		0x1000	/* echo input to output */
#define F_ECHOCTL	0x2000	/* output ctl chars as ^X */
#define F_IGNCTL	0x4000  /* ignore control chars */

	char   ungotc;           /* for ungetc */
	char   prevout;          /* previous output char - for stateful translations */
        u_char codepage;	 /* character set */
#define CODEPAGE_BINARY 0	 /* binary, raw, or unknown */
#define CODEPAGE_7ASCII	1	 /* normal 7-bit ascii */
#define CODEPAGE_GFXDPY	2	 /* the fonts used by gfxdpy.c */
#define CODEPAGE_UTF8   3	 /* utf-8 */
#define CODEPAGE_LATIN1 4	 /* iso-8859-1 */
#define CODEPAGE_PC437  5	 /* the fonts built into the PC video (pcterm.c) */


	const  struct io_fs *fs; /* functions */
        struct FILE *dupped;	 /* original F if dupped */
	void   *d;               /* type specific data */
        char   cchars[4];        /* special chars to trap */
        struct Proc *ccpid;      /* pid to send msg to for above chars */

} FILE;

struct stat {
	/* dev, ino, mode, nlink, uid, gid, size, atime, mtime, ctime, blksize, blocks */
	struct MountEntry *dev;
	u_long mode;

	offset_t size;
	time_t ctime;
	int blksize;
	u_long flags;
#define SSF_BLKWRITE	1	/* writes must be sector sized, device will autoerase - eg. Atmel flash */
#define SSF_NOERASE	2	/* need not be erased, eg RAM */
#define SSF_READONLY	4	/* read-only */
#define SSF_SPECIAL	8	/* special device */
#define SSF_BIGERASE	16	/* can only erase entire device */
};

struct io_line_state {
    int  rate;
    char stopbits;
    char databits;
    char parity;
};

struct io_connect {
    void *warg, *marg;
    int asksize;
    int  (*write)(void*, const char*, int);
    int  (*more)(void*, int avail);
    int  (*conf)(void*, int brk, struct io_line_state*);
};


struct MountEntry;
extern FILE *fopen(const char *, const char *);
extern FILE *dev_open(const char *, const char *, const char *);
extern FILE *me_open(struct MountEntry *, const char *, const char *);
extern int finit(FILE*);
extern int fputc(char, FILE*);
extern int fgetc(FILE*);
extern int ungetc(char, FILE*);
extern int fflush(FILE*);
extern int fstatus(FILE*);
#define FST_I	1		/* input is available */
#define FST_O	2		/* ok to send */

extern FILE* dup(FILE*);
extern int putchar(char);
extern int getchar(void);

extern void puts(const char*);
extern void putByte(u_char);
extern void putWord(u_short);
extern u_char getByte(void);
extern u_short getWord(void);
extern int fclose(FILE *);
extern int fread(FILE*, char*, int);
extern int fwrite(FILE*, const char*, int);
extern int fbread(FILE*, char*, int, offset_t);
extern int fbwrite(FILE*, const char*, int, offset_t);
extern int fseek(FILE*, long, int);	/* 0=from begining; 1=from current; 2=from end */
extern long ftell(FILE*);
extern int fstat(FILE*, struct stat *);
extern int fioctl(FILE*, int, void*);

extern char *getline(char*, int, int);
extern char *fgets(char*, int, FILE*);
extern void fsetcchar(FILE *, int, int);

extern FILE *console_port, *kconsole_port;
extern volatile struct Proc *currproc;

extern void printf(const char *, ...);
extern void fprintf(FILE*, const char *, ...);
extern int  snprintf(char *, int, const char*, ...);
extern void kprintf(const char *, ...);
extern void bootmsg(const char *, ...);
extern int  fioconnect(FILE*, FILE*, struct io_connect*);

#if defined(USE_PROC) && defined(USE_NSTDIO)
#  define STDIN		currproc->stdin
#  define STDOUT	currproc->stdout
#  define STDERR	currproc->stderr
#else
#  define STDIN		kconsole_port
#  define STDOUT	kconsole_port
#  define STDERR	kconsole_port
#endif

/* flags for getline2 */
#define GLF_USEBUF	1
#define GLF_HIST	2
#define GLF_LEFT	4
#define GLF_STARS	8


#endif  /* __nstdio_h__ */

