/*
  Copyright (c) 2015
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2015-Dec-13 18:00 (EST)
  Function: hashing

*/

#include <conf.h>
#include <proc.h>
#include <stm32.h>
#include <userint.h>


static int hash_inbuf;
static int hash_bufsz;
static int hash_outlen;
static u_char *hmac_key;
static int hmac_key_len;

int
hash_init(void){

    RCC->AHB2ENR |= 1<<5;
    return 0;
}

void
hash_md5_start(void){

    HASH->CR     = 1<<7;
    HASH->CR    |= (2<<4);	// byte mode
    HASH->CR    |= 1<<2;	// init
    HASH->STR &= ~0x11F;
    hash_outlen  = 16;
}


void
hash_sha1_start(void){

    HASH->CR     = 0;
    HASH->CR    |= (2<<4);	// byte mode
    HASH->CR    |= 1<<2;	// init
    HASH->STR &= ~0x11F;
    hash_outlen  = 24;
}

static inline void
_hash_wait_ready(void){
    // wait until done
    while( HASH->SR & 8 ){}
}

static void
_hmac_add_key(void){
    short klen = hmac_key_len;
    int *k     = (int*)hmac_key;

    HASH->STR &= ~0x11F;
    while(klen >= 4){
        HASH->DIN = *k;
        k ++;
        klen -= 4;
    }
    if( klen ){
        HASH->STR |= klen * 8;
        HASH->DIN  = *k;
    }

    HASH->STR |= 1<<8;
    _hash_wait_ready();
}


static inline void
_hmac_start(void){
    _hmac_add_key();
    HASH->STR &= ~0x11F;
}

void
hmac_md5_start(const u_char *key, int keylen){
    HASH->CR      = (1<<7) | (1<<6);
    if( keylen > 64 ) HASH->CR |= 1<<16;	// long key
    HASH->CR     |= (2<<4);	// byte mode
    HASH->CR     |= 1<<2;	// init
    hash_outlen   = 16;
    hmac_key      = key;
    hmac_key_len  = keylen;
    _hmac_start();
}

void
hmac_sha1_start(const u_char *key, int keylen){
    HASH->CR      = (1<<6);
    if( keylen > 64 ) HASH->CR |= 1<<16;	// long key
    HASH->CR     |= (2<<4);	// byte mode
    HASH->CR     |= 1<<2;	// init
    hash_outlen   = 24;
    hmac_key      = key;
    hmac_key_len  = keylen;
    _hmac_start();
}

void
hash_add(const u_char *in, int inlen){
    short i;

    // add existing partial block
    if( hash_bufsz ){
        u_char *buf = (u_char*)&hash_inbuf + hash_bufsz;
        short add  = 4 - hash_bufsz;
        if( add > inlen ) add = inlen;

        for( ; add; add--){
            *buf++ = *in++;
            inlen --;
        }

        hash_bufsz += add;

        if( hash_bufsz >= 4 ){
            HASH->DIN  = hash_inbuf;
            hash_bufsz = 0;
            hash_inbuf = 0;
        }
    }

    while(inlen >= 4){
        HASH->DIN = *(int*)in;
        in += 4;
        inlen -= 4;
    }

    // save remaining partial
    if( inlen ){
        u_char *buf = (u_char*)&hash_inbuf + hash_bufsz;
        hash_bufsz += inlen;

        for( ; inlen; inlen--){
            *buf++ = *in++;
        }
    }
}

static void
_hash_add_final(void){

    HASH->STR &= ~0x11F;

    // add remaining partial
    if( hash_bufsz ){
        HASH->DIN  = hash_inbuf;
        HASH->STR |= hash_bufsz * 8;
    }

    HASH->STR |= 1<<8;
    _hash_wait_ready();
}

static inline void
_hash_copy_out(u_char *out, int outlen){

    if( outlen > hash_outlen ) outlen = hash_outlen;

    short i;
    outlen >>= 2;
    int *dst = (int*)out;
    for(i=0; i<outlen; i++)
        dst[i] = __REV(HASH->HR[i]);

}

void
hash_finish(u_char *out, int outlen){

    _hash_add_final();
    _hash_copy_out(out, outlen);
}

void
hmac_finish(u_char *out, int outlen){

    _hash_add_final();
    _hmac_add_key();
    _hash_copy_out(out, outlen);
}


#ifdef KTESTING
// 512B -> 12usec
DEFUN(hashtiming, "test hash timing")
{
    char buf[32];

    yield();
    utime_t t0 = get_hrtime();

    hash_md5_start();
    hash_add( &buf, 512 );
    hash_finish(buf, sizeof(buf));

    utime_t t1 = get_hrtime();
    printf("hash %d usec\n", (int)(t1-t0));

    return 0;
}


DEFUN(hashtest, "test")
{
    char buf[32];

    hash_md5_start();
    hash_add("what do ya want for nothing?", 28); // d03cb659cbf9192dcd066272249f8412
    hash_finish(buf, sizeof(buf));
    hexdump(buf, 16);

    // test vectors from RFC 2202
    hmac_md5_start("Jefe", 4);
    hash_add("what do ya want for nothing?", 28); // 750c783e6ab0b503eaa86e310a5db738
    hmac_finish(buf, sizeof(buf));
    hexdump(buf, 16);

    hmac_sha1_start("Jefe", 4);
    hash_add("what do ya want for nothing?", 28); // effcdf6ae5eb2fa2d27416d5f184df9c259a7c79
    hmac_finish(buf, sizeof(buf));
    hexdump(buf, 20);

    return 0;
}

#endif
