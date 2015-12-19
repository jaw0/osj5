/*
  Copyright (c) 2015
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2015-Dec-13 18:00 (EST)
  Function: crypto

*/

#include <conf.h>
#include <proc.h>
#include <stm32.h>
#include <userint.h>
#include <crypto.h>

#define SR_BUSY	(1<<4)
#define SR_OFNE	(1<<2)
#define SR_IFNF	(1<<1)

static int crypto_blksz;
static int crypto_inbuf;
static int crypto_bufsz;
static int crypto_insz;

int
crypto_init(void){
    RCC->AHB2ENR |= 1<<4;
    return 0;
}

static void
_reset_crypto(void){

    CRYP->CR &= ~0xC3FC;
    CRYP->CR |= (2 << 6);	// byte-mode
    CRYP->CR |= 1<<14;		// flush fifo

    crypto_inbuf = 0;
    crypto_bufsz = 0;
    crypto_insz  = 0;
}

static void
_set_key(const u_char *key, int keylen){

    // truncate key to valid size
    // if <128, pad

    if( keylen >= 32 ){
        CRYP->CR |= 2<<8;
    }
    else if( keylen >= 24 ){
        CRYP->CR |= 1<<8;
    }

    int *k = (int*)key;

    if( keylen >= 32 ){
        CRYP->K0LR = __REV( *k ++ );
        CRYP->K0RR = __REV( *k ++ );
    }
    if( keylen >= 24 ){
        CRYP->K1LR = __REV( *k ++ );
        CRYP->K1RR = __REV( *k ++ );
    }
    CRYP->K2LR = __REV( *k ++ );
    CRYP->K2RR = __REV( *k ++ );
    CRYP->K3LR = __REV( *k ++ );
    CRYP->K3RR = __REV( *k ++ );

}

static inline void
_prepare_key(void){

    CRYP->CR |= 7<<3;	// key prepare mode
    CRYP->CR |= 1<<15;	// enable

    // wait for ready
    while( CRYP->SR & 0x10 ){}
}

static void
_set_iv(const u_char *iv, int ivlen){
    int *v = (int*)iv;

    CRYP->IV0LR = __REV( *v ++ );
    CRYP->IV0RR = __REV( *v ++ );

    if( ivlen >= 8 ){
        CRYP->IV1LR = __REV( *v ++ );
        CRYP->IV1RR = __REV( *v ++ );
    }
}

static void _start_crypto(int alg){

    CRYP->CR |= alg << 3;
    CRYP->CR |= 1<<14;	// flush fifo
    CRYP->CR |= 1<<15;	// enable

    switch(alg){
    case CRYPTO_ALG_DES_ECB:
    case CRYPTO_ALG_DES_CBC:
        crypto_blksz = 8;
        break;
    default:
        crypto_blksz = 16;
        break;
    }
}

void
crypto_encrypt_start(int alg, const u_char *key, int keylen, const u_char *iv, int ivlen){

    _reset_crypto();
    _set_key(key, keylen);
    _set_iv(iv, ivlen);
    _start_crypto(alg);
}

void
crypto_decrypt_start(int alg, const u_char *key, int keylen, const u_char *iv, int ivlen){

    _reset_crypto();
    _set_key(key, keylen);
    if( alg == CRYPTO_ALG_AES_ECB || alg == CRYPTO_ALG_AES_CBC ){
        _prepare_key();
    }
    _set_iv(iv, ivlen);
    CRYP->CR |= 1<<2;	// decrypt mode
    _start_crypto(alg);
}


static inline void
_wait_for_infifo(void){
    while( !(CRYP->SR & SR_IFNF) ){}
}


// append any reults to output
#define PROCESS_RESULTS()	\
    while( CRYP->SR & SR_OFNE ){	\
        int c = CRYP->DOUT;		\
        if( outlen ){			\
            *dst++ = c;			\
            outlen -= 4;		\
            nout += 4;			\
        }				\
    }


int
crypto_add(const u_char *in, int inlen, u_char *out, int outlen){
    short nout = 0;
    int *dst   = (int*)out;

    PROCESS_RESULTS();

    // finish any buffered input
    if( crypto_bufsz ){
        u_char *buf = (u_char*)&crypto_inbuf + crypto_bufsz;
        short add   = 4 - crypto_bufsz;
        if( add > inlen ) add = inlen;

        for( ; add; add--){
            *buf++ = *in++;
            inlen --;
        }

        crypto_bufsz += add;

        if( crypto_bufsz >= 4 ){
            _wait_for_infifo();
            CRYP->DR     = crypto_inbuf;
            crypto_bufsz = 0;
            crypto_inbuf = 0;
            crypto_insz += 4;
        }
    }

    while(inlen >= 4){
        if( CRYP->SR & SR_OFNE ){
            int c = CRYP->DOUT;
            if( outlen ){
                *dst++ = c;
                outlen -= 4;
                nout += 4;
            }
        }
        if( !(CRYP->SR & SR_IFNF) ) continue;

        CRYP->DR = *(int*)in;
        in    += 4;
        inlen -= 4;
        crypto_insz += 4;
    }

    // save remaining partial
    if( inlen ){
        u_char *buf = (u_char*)&crypto_inbuf + crypto_bufsz;
        crypto_bufsz += inlen;

        for( ; inlen; inlen--){
            *buf++ = *in++;
        }
    }

    PROCESS_RESULTS();

    return nout;
}

int
crypto_final(u_char *out, int outlen){
    short nout = 0;
    int *dst   = (int*)out;

    PROCESS_RESULTS();

    // apply pkcs7 padding only if padding is needed
    // (caller should pad if they care)
    short len = (crypto_insz + crypto_bufsz) % crypto_blksz;
    u_char pl = len ? crypto_blksz - len : 0;

    if( crypto_bufsz ){
        switch( crypto_bufsz ){
        case 3: crypto_inbuf |= pl << 16; // and fall through
        case 2: crypto_inbuf |= pl << 8;  // and fall through
        case 1: crypto_inbuf |= pl;
            break;
        }

        _wait_for_infifo();
        CRYP->DR  = crypto_inbuf;
        crypto_insz += 4;
        len -= crypto_bufsz;
    }

    // pad?
    if( len ){
        crypto_inbuf = 0x01010101 * pl;
        for( ; len > 0; len -= 4 ){
            PROCESS_RESULTS();
            _wait_for_infifo();
            CRYP->DR  = crypto_inbuf;
        }
    }

    PROCESS_RESULTS();
    while( CRYP->SR & SR_BUSY ){}
    PROCESS_RESULTS();

    CRYP->CR &= ~(1<<15);	// disable
    return nout;
}

#ifdef KTESTING
static const u_char zero128[16]  = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
static const u_char azero128[16] = { 'a',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
static const u_char azero256[32] = { 'a',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
static const u_char azero[32]    = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                                   'a',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

// 24usec
static u_char crbuf[512];
DEFUN(cryptotiming, "test crypto timing")
{
    int n = 0;

    yield();
    int t0 = get_hrtime();

    crypto_encrypt_start( CRYPTO_ALG_AES_CBC, azero256, 32, azero128, 16);
    utime_t t1 = get_hrtime();
    n += crypto_add(crbuf, 512, crbuf, 512);
    utime_t t2 = get_hrtime();
    n += crypto_final(crbuf + n, sizeof(crbuf) - n );

    utime_t t3 = get_hrtime();
    printf("aes256 %d %d %d usec\n", (int)(t1-t0), (int)(t2-t1), (int)(t3-t2));

    return 0;
}

DEFUN(cryptotest, "crypto test")
{
    char buf[32];
    int n,i;

#if 0 //ok
    crypto_encrypt_start( CRYPTO_ALG_AES_CBC, azero128, 16, azero128, 16);
    n += crypto_add(zero128, 16, buf,   sizeof(buf) );
    n += crypto_add(zero128, 16, buf+n, sizeof(buf) - n);
    n += crypto_final(buf + n, sizeof(buf) - n );
    hexdump( buf, n );

    crypto_encrypt_start( CRYPTO_ALG_AES_CBC, "abcdefghijklmnop", 16, azero128, 16);
    n = crypto_add(zero128, 16, buf,   sizeof(buf) );
    n += crypto_final(buf + n, sizeof(buf) - n );
    hexdump( buf, n );

    crypto_encrypt_start( CRYPTO_ALG_AES_CBC, "abcdefghijklmnop", 16, "0123456789abcdef", 16);
    n = crypto_add(zero128, 16, buf,   sizeof(buf) );
    n += crypto_final(buf + n, sizeof(buf) - n );
    hexdump( buf, n );

#endif

    crypto_encrypt_start( CRYPTO_ALG_AES_CBC, azero256, 32, azero128, 16);
    n = crypto_add(zero128, 16, buf,   sizeof(buf) );
    n += crypto_final(buf + n, sizeof(buf) - n );
    hexdump( buf, n );

    return 0;
}

#endif
