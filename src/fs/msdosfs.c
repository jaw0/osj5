/*
  Copyright (c) 2011
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2011-Dec-06 13:08 (EST)
  Function: 
 
  $Id$

*/

#include <sys/types.h>
#include <stdarg.h>
#include <conf.h>
#include <fs.h>
#include <error.h>
#include <msdosfs.h>



int msdosfs_close(FILE *f);
int msdosfs_read(FILE* f, char* buf, int len);
int msdosfs_write(FILE* f, const char* buf, int len);
int msdosfs_getchar(FILE *f);
int msdosfs_putchar(FILE *f, char c);
int msdosfs_status(FILE *f);
int msdosfs_seek(FILE *f, long, int);
long msdosfs_tell(FILE *f);
int msdosfs_flush(FILE *f);
int msdosfs_stat(FILE *f, struct stat *s);
int msdosfs_ioctl(FILE *f, int, void*);

struct MSDOSFS {
    struct MountEntry *me;
    u_int	fat_type;	// 16 or 32
    u_int	bytes_per_sec;
    u_int	secs_per_clust;
    u_int	num_fat;
    u_int	tot_secs;
    u_int	fat_start_sec;
    u_int	root_start_sec;
    u_int	data_start_sec;
    u_int	next_free_clust;
    u_int 	root_entries;

};


const struct io_fs msdosfs_iofs = {
    msdosfs_putchar,
    msdosfs_getchar,
    msdosfs_close,
    msdosfs_flush,	/* flush */
    msdosfs_status,
    msdosfs_read,
    msdosfs_write,
    0, 0, 		/* bread, bwrite */
    msdosfs_seek,
    msdosfs_tell,
    msdosfs_stat,
    msdosfs_ioctl
};

static u_int32_t
get(const u_char *buf, int len){
    switch(len){
    case 4:
        return ( buf[0] | (buf[1]<<8) | (buf[2]<<16) | (buf[3]<<24) );
    case 2:
        return ( buf[0] | (buf[1]<<8) );
    case 1:
        return buf[0];
    }
    return -1;
}

static void
set(u_char *buf, int len, u_int32_t val){
    switch(len){
    case 4:
        buf[0] = val; buf[1] = val>>8; buf[2] = val>>16; buf[3] = val>>24;
        break;
    case 2:
        buf[0] = val; buf[1] = val>>8;
        break;
    }
}

#define GET(b,f)	get((u_char*)&b->f, sizeof(b->f))
#define SET(b,f,v)	(sizeof(b->f) == 1 ? (b->f = v) : set((u_char*)&b->f, sizeof(b->f), v))

static int
valid_bpb(struct MSDOSFS_BPB *bpb){
    int v;

    v = GET(bpb, BytesPerSec);
    kprintf("bps %x\n", v);
    if( v != 512 && v != 1024 && v != 2048 && v != 4096 ) return 0;
    v = GET(bpb, SecPerClust);
    kprintf("spc %x\n", v);
    if( v & (v-1) ) return 0;	// is it a power of 2

    return 1;
}

static void
xdump( u_char *start, u_char *end ){

    while( start < end ){
        kprintf("%02.2X", *start);
        if( (int)start % 4 == 3 ) kprintf(" ");
        start ++;
    }
    kprintf("\n");
}

static offset_t
clust2sec(struct MSDOSFS *msfs, u_long clust){
    return (clust - 2) * msfs->secs_per_clust + msfs->data_start_sec;
}

int
msdosfs_init(MountEntry *me){

    // read bpb
    struct MSDOSFS_BPB *bpb = (struct MSDOSFS_BPB*)alloc(512);
    fbread(me->fdev, (char*)bpb, 512, 0);
    xdump((u_char*)bpb, (u_char*)(bpb + 1));

    // validate
    if(!valid_bpb(bpb)){
        free((char*)bpb, 512);
        DIAG("invalid bpb. cannot mount");
        return -1;
    }

    struct MSDOSFS *msfs = (struct MSDOSFS *)alloc(sizeof(struct MSDOSFS));

    msfs->me = me;

    // figure out
    msfs->bytes_per_sec   = GET(bpb, BytesPerSec);
    msfs->secs_per_clust  = GET(bpb, SecPerClust);
    msfs->num_fat	  = GET(bpb, NumFATs);
    msfs->tot_secs	  = GET(bpb, TotSec16);
    if(!msfs->tot_secs)    msfs->tot_secs	= GET(bpb, TotSec32);

    msfs->root_entries 	  = GET(bpb, RootDirCnt);

    int res_secs = GET(bpb, ResSecCnt);
    int fat_secs = GET(bpb, FATSec16);
    if( !fat_secs ) fat_secs = GET(bpb, FATSec32);

    // math copied from MS spec
    int root_secs  = ((msfs->root_entries * 32) + (msfs->bytes_per_sec - 1)) / msfs->bytes_per_sec;
    int data_secs  = msfs->tot_secs - (res_secs + (msfs->num_fat * fat_secs) + root_secs);
    int data_clust = data_secs / msfs->secs_per_clust;

    msfs->data_start_sec = res_secs + (msfs->num_fat * fat_secs) + root_secs;
    msfs->fat_start_sec  = res_secs;

    if( data_clust < 4085 ){
        msfs->fat_type = 12;
    }else if( data_clust < 65525 ){
        msfs->fat_type = 16;
    }else{
        msfs->fat_type = 32;
    }

    if( msfs->fat_type == 32 ){
        // check fs ver
        msfs->root_start_sec = clust2sec(msfs, GET(bpb, RootClust));
    }else{
        msfs->root_start_sec = res_secs + (msfs->num_fat * fat_secs);
    }

    kprintf("msdosfs FAT%d, %d s, %d B/s %d s/c\n",
            msfs->fat_type, msfs->tot_secs, msfs->bytes_per_sec, msfs->secs_per_clust);

    
    // msfs->next_free_clust;

}

int
msdosfs_unmount(MountEntry *me){


    // fat32 - update fsinfo
}


// nstdio funcs
FILE * msdosfs_open(MountEntry *me, const char *name){}
int msdosfs_close(FILE *f){ }
int msdosfs_read(FILE* f, char* buf, int len){}
int msdosfs_write(FILE* f, const char* buf, int len){}
int msdosfs_getchar(FILE *f){}
int msdosfs_putchar(FILE *f, char c){}
int msdosfs_status(FILE *f){}
int msdosfs_seek(FILE *f, long pos, int wh){}
long msdosfs_tell(FILE *f){}
int msdosfs_flush(FILE *f){}
int msdosfs_stat(FILE *f, struct stat *s){}
int msdosfs_ioctl(FILE *f, int op, void*d){}

// fs funcs
int msdosfs_dir(MountEntry *me, int how){}
int msdosfs_fchmod(FILE * f, int attr){}
int msdosfs_chmod(MountEntry *me, const char *name, int attr){}
int msdosfs_format(MountEntry *me, char *msdosfsname){}
int msdosfs_deletefile(MountEntry *me, const char *name){}
int msdosfs_renamefile(MountEntry *me, const char *oname, const char *nname){}
int msdosfs_glob(MountEntry *me, const char *pattern, int (*fnc)(const char *, void*), void *args){}

int
msdosfs_ops(int what, MountEntry *me, ...){
    va_list ap;
    char *name;
    FILE *f;
    int n;

    va_start(ap, me);

    switch (what){

    case FSOP_RENAME:
        name = va_arg(ap, char*);
        return msdosfs_renamefile(me, name, va_arg(ap, char*));

    case FSOP_DELETE:
        return msdosfs_deletefile(me, va_arg(ap, char*));

    case FSOP_DIR:
        return msdosfs_dir(me, va_arg(ap, int));

    case FSOP_CHMOD:
        name = va_arg(ap, char*);
        return msdosfs_chmod(me, name, va_arg(ap, int));

    case FSOP_FCHMOD:
        f = va_arg(ap, FILE*);
        return msdosfs_fchmod(f, va_arg(ap, int));

    case FSOP_FORMAT:
        return msdosfs_format(me, va_arg(ap, char*));

    case FSOP_GLOB: {
        char *name = va_arg(ap, char*);
        int (*fnc)(const char *, void*) = va_arg(ap, void*);
        return msdosfs_glob(me, name, fnc, va_arg(ap, void*) );
    }
    default:
        return -1;
    }
}


