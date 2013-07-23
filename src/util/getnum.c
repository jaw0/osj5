/*
  Copyright (c) 1998
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 1998
  Function: text to number, etc.
*/


#include <get.h>


static unsigned char
vallof(char c){

    if(c>='0' && c<='9') return c - '0';
    if(c>='a' && c<='z') return c - 'a' + 0xa;
    if(c>='A' && c<='Z') return c - 'A' + 0xA;

    return 255;
}

static int
islegit(int base, char c){

    if( vallof(c) < base ) return 1;
    return 0;
}

long
atoi(const char *a){
    return strtol(a, 0, 10);
}

long
strtol(const char *buf, const char **ptr, int base){
    long val=0;
    int i=0, neg=0;

    if( !base ){
        if( buf[0] != '0' )
            base = 10;
        else{
            if( buf[1] == 'x' || buf[1] == 'X' ){
                base = 16;
                buf += 2;
            }else
                base = 8;
        }
    }

    while( !islegit(base, buf[i])){
        if( buf[i]=='-') neg = 1;
        i++;
    }
    while( islegit(base, buf[i]))
        val = (val * base) + vallof(buf[i++]);

    if( ptr )
        *ptr = buf + i;

    return neg?-val:val;
}

long long
strtoq(const char *buf, const char **ptr, int base){
    long long val=0;
    int i=0, neg=0;

    if( !base ){
        if( buf[0] != '0' )
            base = 10;
        else{
            if( buf[1] == 'x' || buf[1] == 'X' ){
                base = 16;
                buf += 2;
            }else
                base = 8;
        }
    }

    while( !islegit(base, buf[i])){
        if( buf[i]=='-') neg = 1;
        i++;
    }
    while( islegit(base, buf[i]))
        val = (val * base) + vallof(buf[i++]);

    if( ptr )
        *ptr = buf + i;

    return neg?-val:val;
}

long
atoi_base(int base, const char *buf){
    return strtol(buf, 0, base);
}

