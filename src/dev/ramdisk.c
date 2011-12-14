
/*
  Copyright 1998,1999,2000,2001 Jeff Weisberg <jaw@tcp4me.com>
  see the file LICENSE for details
*/

#ifdef RCSID
static const char *const rcsid
= "@(#)$Id: ramdisk.c,v 1.3 2001/10/31 18:14:42 jaw Exp $";
#endif

#include <sys/types.h>
#include <sys/param.h>
#include <conf.h>
#include <nstdio.h>

int ramdisk_read(FILE*,char*,int);
int ramdisk_write(FILE*,char*,int);
int ramdisk_stat(FILE*, struct stat*);
int ramdisk_seek(FILE*, long, int);
long ramdisk_tell(FILE*);

static const struct io_fs ramdisk_port_fs = {
        0, /* putc */
	0, /* getc */
	0, /* close */
	0, /* flush */
	0, /* status */
	ramdisk_read,
	ramdisk_write,
	ramdisk_bread,
	ramdisk_bwrite,
	ramdisk_seek,
	ramdisk_tell,
	ramdisk_stat,
	0 /* ioctl */
};

static struct Ramdisk_Device {
	FILE f;
	u_long offset;
	u_long size;
	char space[ RAMDISKSIZE ];
	/* size, startaddr, type, ... */
} ramdisk_device[1];

int init_ramdisk(void){
	int i;
	for (i=0; i<1; i++){
		finit( & ramdisk_device[i].f );
		ramdisk_device[i].f.d = (void*)& ramdisk_device[i];
		ramdisk_device[i].f.fs = & ramdisk_port_fs;
		ramdisk_device[i].offset = 0;
		ramdisk_device[i].size = RAMDISKSIZE;
	}

	mount( & ramdisk_device[0].f, RAMDISKNAME );

	return 0;
}

int ramdisk_stat(FILE *f, struct stat *s){

	s->size  = RAMDISKSIZE;
	s->blksize = 512;
	s->flags = 0;
	return 0;
}

int ramdisk_seek(FILE *f, long off, int how){
	struct Ramdisk_Device *d;
	
	d = f->d;

	if( how == 0 ){
		d->offset = off;
	}else if( how == 1 ){
		d->offset += off;
	}else{
		d->offset = d->size - off;
	}
	return 0;
}

long ramdisk_tell(FILE *f){
	struct Ramdisk_Device *d;
	
	d = f->d;

	return d->offset;
}
	

#ifdef PLATFORM_EMUL

/* emulate with a file */

extern int lseek(int, long long, int);

int
ramdisk_read(FILE *f, char *buf, int len){
	struct Ramdisk_Device *d;
	int fd, i;

	d = f->d;

	memcpy(buf, d->space + d->offset, len);

	return len;
}

int
ramdisk_write(FILE *f, char *buf, int len){
	struct Ramdisk_Device *d;
	int fd, i;
	
	d = f->d;

	memcpy(d->space + d->offset, buf, len);

	return len;
}

#else




#endif /* PLATFORM_EMUL */

