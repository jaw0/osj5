/*
  Copyright (c) 1998
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Function: text editor
*/


#include <conf.h>
#include <alloc.h>
#include <nstdio.h>
#include <proc.h>
#include <fs.h>
#include <userint.h>

#ifndef USE_CLI
#error "editor requires feature CLI"
#endif

#define BUFSIZ	256

struct Line {
    char line[256];
    struct Line *next, *prev;
};

struct Buffer {
    struct Line *firstline, *lastline, *currline;
    int nlines, currno;
    struct Line *mark[26];
};

char *
getaddr(const char *buf, struct Buffer *file, int *addrno, struct Line **addro){
    struct Line *addr;
    int relp=0;
    int fromend=0;
    int adrn, n, distcurr;
    char *p = (char*)buf;

    if( *p == '$' ){
        *p++;
        if( *p == '-' ){
            fromend = file->nlines;
        }else{
            *addro  = file->lastline;
            *addrno = file->nlines;
            return p;
        }
    }
    if( *p == '\'' ){
        struct Line *l;
        p++;
        *addrno = 0;
        *addro = 0;
        if( *p < 'a' || *p > 'z' ){
            /* error */
            return (char*)buf;
        }
        addr = file->mark[ *p - 'a' ];
        if( !addr ){
            /* no mark */
            return (char*)buf;
        }
        adrn = 1;
        for(l=file->firstline; l && l != addr; l=l->next)
            adrn ++;

        p++;
        if( *p == '+' || *p == '-' ){
            fromend = adrn;
        }else{
            *addrno = adrn;
            *addro = addr;
            return p;
        }
    }

    if( *p == '+' ){
        relp = 1;
        p++;
    }
    if( *p == '-' ){
        relp = -1;
        p++;
    }
    if( *p == '.' ){
        p++;
        *addro  = file->currline;
        *addrno = file->currno;
        return p;
    }
    if( *p == '^' ){
        p++;
        if( file->currline ){
            *addro = file->currline->prev;
            *addrno = file->currno -1;
        }else{
            *addro = file->currline;
            *addrno = file->currno;
        }
        return p;
    }

    adrn = 0;
    while( *p >='0' && *p <= '9' ){
        adrn *= 10;
        adrn += *p - '0';
        p++;
    }

    if( relp && !adrn )
        adrn = 1;

    if( fromend ){
        if( relp < 0 )
            adrn = fromend - adrn;
        else
            adrn = fromend + adrn;
        relp = 0;
        fromend = 0;
    }

    if( relp ){
        if( relp < 0 ){
            adrn = file->currno - adrn;
        }else{
            adrn = file->currno + adrn;
        }
        relp = 0;
    }

    *addrno = adrn;

#if 1
    distcurr = adrn - file->currno;
    if( distcurr < 0 ) distcurr = - distcurr;

    if( adrn < file->nlines - adrn && adrn < distcurr ){
        /* closest to start */
        addr = file->firstline;
        relp = 1;
        n = adrn - 1;
    }
    else if( file->nlines - adrn < adrn && file->nlines - adrn < distcurr ){
        /* closest to end */
        addr = file->lastline;
        relp = -1;
        n = file->nlines - adrn;
    }
    else if( adrn < file->currno ){
        addr = file->currline;
        relp = -1;
        n = file->currno - adrn;
    }else{
        addr = file->currline;
        relp = 1;
        n = adrn - file->currno;
    }
#else
    addr = file->firstline;
    relp = 1;
    n = adrn - 1;
#endif

    if( n < 0 )
        addr = 0;
    while( n-- && addr ){
        addr = (relp>0) ? addr->next : addr->prev;
    }

    *addro = addr;
    return p;
}

#define DEF_DOTDOT				\
    if( naddr == 1 ){                           \
        adr2 = adr1;                            \
        adrn2 = adrn1;                          \
        naddr++;                                \
    }                                           \
    if( naddr != 2){                            \
        adr1 = adr2 = file.currline;            \
        adrn1 = adrn2 = file.currno;            \
        naddr = 2;                              \
    }

#define DEF_DOTNEXT				\
    if( naddr == 1 ){                           \
        if( adr1 ){                             \
            adr2 = adr1->next;                  \
            adrn2 = adrn1 + 1;                  \
        }else{                                  \
            adr2 = 0;                           \
            adrn2 = 0;                          \
        }                                       \
        naddr++;                                \
    }                                           \
    if( naddr != 2){                            \
        adr1 = file.currline;                   \
        adrn1 = file.currno;                    \
        adr2 = adr1->next;                      \
        adrn2 = adrn1 + 1;                      \
        naddr = 2;                              \
    }

#define DEF_ALL					\
    if( naddr == 1 ){                           \
        adr2 = adr1;                            \
        adrn2 = adrn1;                          \
        naddr++;                                \
    }                                           \
    if( naddr != 2){                            \
        adr1  = file.firstline;                 \
        adrn1 = 1;                              \
        adr2  = file.lastline;                  \
        adrn2 = file.nlines;                    \
        naddr = 2;                              \
    }

#define INSERT_AT_CURR(l)			\
    if( file.currline ){			\
        l->next = file.currline->next;          \
        l->prev = file.currline;                \
        file.currline->next = l;                \
        if( l->next ){                          \
            l->next->prev = l;                  \
        }else{                                  \
            file.lastline = l;                  \
        }                                       \
    }else{					\
        l->prev = 0;                            \
        l->next = file.firstline;               \
        file.firstline = l;                     \
    }                                           \
    file.currno ++;				\
    file.currline = l;                          \
    file.nlines ++;


#define DELETE_LINE(l)				\
    if( l->next ){				\
        l->next->prev = l->prev;                \
    }else{					\
        file.lastline = l->prev;                \
    }                                           \
    if( l->prev ){				\
        l->prev->next = l->next;                \
    }else{					\
        file.firstline = l->next;               \
    }                                           \
	{					\
            int i;				\
            for(i=0;i<26;i++){                  \
                if( file.mark[i] == l )         \
                    file.mark[i] = 0;           \
            }                                   \
	}					\
	file.nlines --;				\
	free(l, sizeof(struct Line));



DEFUN(ed, "text editor")
DEFALIAS(ed, edit)
DEFALIAS(ed, emacs)
DEFALIAS(ed, vi)
{
    FILE *f;
    struct Buffer file;
    struct Line *l;
    int delta = 0;
    int i;

    for(i=0; i<26; i++)
        file.mark[i] = 0;

    if( argc > 2 ){
        f_error("ed [filename]");
        return -1;
    }

    if( argc == 2 )
        f = fopen(argv[1], "r");
    else
        f = 0;

    char *buf  = alloc(BUFSIZ);
    char *pbuf = alloc(BUFSIZ);

    /* read file in data struct */
    file.firstline = file.lastline = file.currline = 0;
    file.nlines = 0;
    if( f ){
        while( 1 ){
            l = alloc( sizeof(struct Line) );
            l->next = l->prev = 0;
            if( ! fgets(l->line, sizeof(l->line), f) ){
                free(l, sizeof(struct Line) );
                break;
            }

            if( file.currline ){
                file.currline->next = l;
                l->prev = file.currline;
            }else{
                file.firstline = l;
            }
            file.currline = l;
            file.nlines ++;
        }
        file.lastline = file.currline;
        file.currline = file.firstline;
        file.currno = 1;
        fclose(f);
    }

    /******************************************************************/
    /* edit */
    pbuf[0] = 0;
    while( 1 ){
        char *p, *np;
        struct Line *adr1, *adr2, *adr3;
        int adrn1=0, adrn2=0, adrn3=0;
        int naddr=0;

        /* get command */
        printf("ed: ");
        getline2(buf, BUFSIZ, 0, 0);
        /* \n -> repeat previous */
        if( !*buf ){
            strcpy(buf, pbuf);
        }
        strcpy(pbuf, buf);

        /* parse addrs */
        p = buf;

        if( *p == ',' || *p == '%' ){
            adr1 = file.firstline;
            adr2 = file.lastline;
            adrn1 = 1;
            adrn2 = file.nlines;
            naddr = 2;
            p++;
        }else if( *p == ';' ){
            adr1 = file.currline;
            adr2 = file.lastline;
            adrn1 = file.currno;
            adrn2 = file.nlines;
            naddr = 2;
            p++;
        }else{
            np = getaddr(p, &file, &adrn1, &adr1);
            if( np != p ){
                naddr++;
                p = np;
                if( *p ==','){
                    *p++;
                    np = getaddr(p, &file, &adrn2, &adr2);
                    if( np != p ){
                        naddr++;
                        p = np;
                    }
                }
            }
        }

        switch( *p ){
        case '?':
            printf("addr[,addr]cmd[params]\n"
                   "or {,;%}cmd[params]\n"
                   "  addr: nnn, +/-nnn, ., $, ^, 'x\n"
                   "  cmd: \n"
                   "\ta - append text\n"
                   "\tc - change lines\n"
                   "\td - delete lines\n"
                   "\te - edit line\n"
                   "\ti - insert text\n"
                   "\tj - join lines\n"
                   "\tk - set mark\n"
                   "\tl - list lines\n"
                   "\tm - move lines\n"
                   "\tp - print lines\n"
                   "\tn - number lines\n"
                   "\tq - quit\n"
                   "\tr - read lines from file\n"
                   "\tt - transfer lines\n"
                   "\tw - write lines to file\n"
                   "\t= - display line number\n");
            break;

        case '=':
            printf("%d\n", naddr ? adrn1 : file.nlines);
            break;

        case 'a':
        APPEND:
            DEF_DOTDOT;
        file.currline = adr1;	/* 0 is allowed */
        file.currno  = adrn1;

        while(1){
            l = alloc( sizeof(struct Line) );
            l->next = l->prev = 0;

            printf("ed(a): ");
            getline2(l->line, sizeof(l->line), 0, 0);
            if( !strcmp(l->line, ".") ){
                free(l, sizeof(struct Line) );
                break;
            }

            INSERT_AT_CURR(l);
        }
        delta = 1;
        break;

        case 'd':
        case 'c':
            DEF_DOTDOT;
            if( !adr1 || !adr2 ){
                puts("\a?\n");
                break;
            }
            for(l=adr1; l; ){
                struct Line *ll;

                ll = l->next;
                DELETE_LINE(l);
                if( l == adr2 ) break;
                l = ll;
            }

            if( adr2->next ){
                file.currline = adr2->next;
                file.currno   = adrn1;		/* yes, this is correct */
            }else{
                file.currline = file.lastline;
                file.currno = file.nlines;
            }
            if( *p == 'c' ){
                if( file.currline && file.currline->prev ){
                    if( adr2->next ){
                        adr1 = file.currline->prev;
                        adrn1 = file.currno - 1;
                    }else{
                        adr1 = file.lastline;
                        adrn1 = file.nlines;
                    }
                }else{
                    adr1 = 0;
                    adrn1 = 0;
                }
                goto APPEND;
            }
            delta = 1;
            break;

        case 'e':
            DEF_DOTDOT;
            if( !adr1 ){
                puts("\a?\n");
                break;
            }
            getline2(adr1->line, sizeof(adr1->line), -1, 0);
            file.currline = adr1;
            file.currno   = adrn1;
            delta = 1;
            break;

        case 'i':
            DEF_DOTDOT;
            if( !adr1 ){
                puts("\a?\n");
                break;
            }
            if( adr1->prev ){
                adr1 = adr1->prev;
                adrn1 --;
            }else{
                adr1 = 0;
                adrn1 = 0;
            }
            goto APPEND;

        case 'j':
            DEF_DOTNEXT;
            if( !adr1 || adr1 == adr2 ){
                puts("\a?\n");
                break;
            }

            for(l=adr1->next; l;  ){
                struct Line *ll;

                ll = l->next;
                snprintf(buf, BUFSIZ, "%s%s", adr1->line, l->line);
                strncpy(adr1->line, buf, sizeof(adr1->line));
                DELETE_LINE(l);
                if( l == adr2 ) break;
                l = ll;
            }
            file.currline = adr1;
            file.currno   = adrn1;
            delta = 1;
            break;

        case 'k':
            DEF_DOTDOT;
            p++;
            if( !adr1 || *p < 'a' || *p > 'z' ){
                puts("\a?\n");
                break;
            }
            file.mark[ *p - 'a' ] = adr1;
            break;

        case 'l':
            DEF_DOTDOT;
            for(l=adr1; l; l=l->next ){
                char *p;
                for(p=l->line; *p; p++){
                    if( *p<' ' || *p > 126 )
                        printf("\\%03.3o", (int)*p);
                    else
                        putchar(*p);
                }
                putchar('\n');
                file.currline = l;
                file.currno = adrn1;
                adrn1 ++;
                if( l == adr2 ) break;
            }
            break;

        case 'p':
        case 'n':
            DEF_DOTDOT;
            for(l=adr1; l; l=l->next ){
                if( *p == 'n' )
                    printf("%d\t", adrn1);
                printf("%s\n", l->line);
                file.currline = l;
                file.currno = adrn1;
                adrn1 ++;
                if( l == adr2 ) break;
            }
            break;

        case 'm':
        case 't':
            DEF_DOTDOT;
            if( !adr1 ){
                puts("\a?\n");
                break;
            }
            np = getaddr(p+1, &file, &adrn3, &adr3);
            if( np == p+1 || adrn3 >adrn1 && adrn3 < adrn2 )
                break;
            file.currline = adr3;		/* 0 is allowed */
            file.currno  = adrn3;

            for(l=adr1; l; ){
                struct Line *ll, *nl;
                ll = l->next;

                nl = alloc(sizeof(struct Line));
                strcpy(nl->line, l->line);
                INSERT_AT_CURR(nl);

                if( *p == 'm' ){
                    DELETE_LINE(l);
                }
                if( l == adr2 ) break;
                l = ll;
            }
            delta = 1;
            break;

        case 'q':
            if( delta ){
                printf("\abuffer not saved\n");
            }else{
        case 'Q':
            QUIT:
                for(l=file.firstline; l; ){
                    struct Line *ll;
                    ll = l->next;
                    free(l, sizeof(struct Line));
                    l = ll;
                }
                free(buf,  BUFSIZ);
                free(pbuf, BUFSIZ);
                return 0;
            }
            delta = 0;
            break;

        case 'r':
            p++;
            if( *p ){
                while( *p==' ' || *p=='\t' )p++;
                f = fopen(p, "r");
            }else{
                if( argc == 2 )
                    f = fopen(argv[1], "r");
                else{
                    puts("\afile?\n");
                    break;
                }
            }
            if( !f ){
                f_error("cannot open file");
                break;
            }
            if( !naddr ){
                adr1  = file.lastline;
                adrn1 = file.nlines;
            }
            file.currline = adr1;	/* 0 is allowed */
            file.currno  = adrn1;
            while( 1 ){
                l = alloc( sizeof(struct Line) );
                l->next = l->prev = 0;
                if( ! fgets(l->line, sizeof(l->line), f) ){
                    free(l, sizeof(struct Line) );
                    break;
                }
                INSERT_AT_CURR(l);
            }
            fclose(f);
            delta = 1;
            break;

        case 'w':
            p++;
            DEF_ALL;
            if( *p ){
                while( *p==' ' || *p=='\t' )p++;
                f = fopen(p, "w");
            }else{
                if( argc == 2 )
                    f = fopen(argv[1], "w");
                else{
                    puts("\afile?\n");
                    break;
                }
            }
            if( !f ){
                f_error("cannot save file");
                break;
            }

            /* write data */
            for(l=adr1; l; l=l->next){
                fprintf(f, "%s\n", l->line);
                if( l == adr2 ) break;
            }
            fclose(f);
            delta = 0;
            break;

        default:
            printf("\aunknown command\n");
            break;

        }
    }

    /* not reached */
    return 0;
}

