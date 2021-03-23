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
static int crypto_aadsz;

#define DMASTRO	DMA2_Stream5
#define DMASTRI	DMA2_Stream6
#define DMACHAN	2

int
crypto_init(void){
    RCC->AHB2ENR |= 1<<4;
    RCC->AHB1ENR |= 1<<22;	// DMA2
    return 0;
}

static void
_reset_crypto(void){

    CRYP->CR &= ~0xBC3FC;
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
    CRYP->CR |= 1<<14;	// flush fifo
    CRYP->CR |= 1<<2;	// decrypt mode
    CRYP->CR |= 1<<15;	// enable

    // wait for ready
    while( CRYP->SR & 0x10 ){}

    CRYP->CR &= ~(7<<3);
}

static inline void
_set_iv(const u_char *iv, int ivlen){
    int *v = (int*)iv;

    CRYP->IV0LR = __REV( *v ++ );
    CRYP->IV0RR = __REV( *v ++ );

    if( ivlen >= 8 ){
        CRYP->IV1LR = __REV( *v ++ );
        CRYP->IV1RR = __REV( *v ++ );
    }
}

static void
_start_crypto(int alg){

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

static inline void
_wait_for_indma(void){
    if( DMASTRI->CR & 1 )
        while( !(DMA2->HISR & (1<<21)) ){}
}

static void
_start_in_dma(u_char *in, int inlen){

    CRYP->DMACR |= 1;	// dma in

    DMASTRI->CR  &= (0xF<<28) | (1<<20);	// zero CR
    DMA2->HIFCR  |= 0x3D << 16;			// clear ints

    DMASTRI->PAR   = & CRYP->DR;
    DMASTRI->M0AR  = in;
    DMASTRI->NDTR  = inlen >> 2;

    DMASTRI->CR   |= (DMACHAN << 25)
        | (2<<16)		// high prio
        | (2<<13) | (2<<11)	// 32 bit->32 bit
        | (1<<10)		// inc mem
        | (1<<6)		// mem->dev
        ;

    DMASTRI->CR   |= 1;		// enable
}

static void
_start_out_dma(u_char *out, int outlen){

    CRYP->DMACR &= 3;
    CRYP->DMACR |= 2;	// dma out

    DMASTRO->CR   &= (0xF<<28) | (1<<20);	// zero CR
    DMA2->HIFCR  |= 0x3D<<6;			// clear ints

    DMASTRO->PAR   = & CRYP->DOUT;
    DMASTRO->M0AR  = out;
    DMASTRO->NDTR  = outlen >> 2;

    DMASTRO->CR   |= (DMACHAN << 25)
        | (3<<16)		// highest prio
        | (2<<13) | (2<<11)	// 32 bit->32 bit
        | (1<<10)		// inc mem
        ;

    DMASTRO->CR   |= 1;		// enable

}

static inline void
_stop_out_dma(void){

    DMASTRO->CR   &= ~1;
}

static inline void
_stop_in_dma(void){

    DMASTRI->CR   &= ~1;
}

void
crypto_encrypt_start(int alg, const u_char *key, int keylen, const u_char *iv, int ivlen, u_char *out, int outlen){

    _reset_crypto();
    _set_key(key, keylen);
    _set_iv(iv, ivlen);
    _start_out_dma(out, outlen);
    _start_crypto(alg);
}

void
crypto_decrypt_start(int alg, const u_char *key, int keylen, const u_char *iv, int ivlen, u_char *out, int outlen){

    _reset_crypto();
    _set_key(key, keylen);

    if( alg == CRYPTO_ALG_AES_ECB || alg == CRYPTO_ALG_AES_CBC ){
        _prepare_key();
    }

    CRYP->CR |= 1<<2;	// decrypt mode
    _set_iv(iv, ivlen);
    _start_out_dma(out, outlen);
    _start_crypto(alg);
}

static inline void
_wait_for_infifo(void){
    while( !(CRYP->SR & SR_IFNF) ){}
}


void
crypto_add(const u_char *in, int inlen){

    _wait_for_indma();

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

    if( inlen > 3 ){
        _start_in_dma(in, inlen & ~3);
        crypto_insz += inlen & ~3;
        inlen &= 3;
    }

    // save remaining partial
    if( inlen ){
        u_char *buf = (u_char*)&crypto_inbuf + crypto_bufsz;
        crypto_bufsz += inlen;

        for( ; inlen; inlen--){
            *buf++ = *in++;
        }
    }
}

static void
_crypto_flush_input(int use_pkcs){

    // apply pkcs7 padding only if padding is needed
    // (caller should pad if they care)
    short len = (crypto_insz + crypto_bufsz) % crypto_blksz;
    u_char pl = len ? crypto_blksz - len : 0;

    if( !use_pkcs ) pl = 0; // pad with zero

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
            _wait_for_infifo();
            CRYP->DR  = crypto_inbuf;
            crypto_insz += 4;
        }
    }

}

int
crypto_final(void){

    _wait_for_indma();
    _crypto_flush_input(1);

    while( CRYP->SR & SR_BUSY ){}

    CRYP->CR &= ~(1<<15);	// disable
    _stop_in_dma();
    _stop_out_dma();

    return crypto_insz;
}


void
crypto_gcm_start(const u_char *key, int keylen, const u_char *iv, int ivlen){

    _reset_crypto();
    _set_key(key, keylen);
    _set_iv(iv, ivlen);

    CRYP->CR |= 1<<19;  // GCM mode
    CRYP->CR |= 1<<15;	// enable

    crypto_blksz = 16;

    // wait for it to disable
    while( CRYP->CR & (1<<15) ) {}

    // aad phase
    CRYP->CR |= 1 << 16; // CCMPH = header phase (1)
    CRYP->CR |= 1 << 15; // enable
    crypto_aadsz = 0;
}


void
crypto_gcm_encrypt(u_char *out, int outlen){

    crypto_aadsz = crypto_insz;
    crypto_insz  = 0;
    CRYP->CR &= ~( (1<<15) | (3 << 16)); // disable
    CRYP->CR |= 2 << 16; // CCMPH = payload phase (2)

    _start_out_dma(out, outlen);
    CRYP->CR |= 1 << 15; // enable

}

void
crypto_gcm_decrypt(u_char *out, int outlen){

    crypto_aadsz = crypto_insz;
    crypto_insz  = 0;
    CRYP->CR &= ~( (1<<15) | (3 << 16)); // disable
    CRYP->CR |= 2 << 16; // CCMPH = payload phase (2)
    CRYP->CR |= 1<<2;	// decrypt mode

    _start_out_dma(out, outlen);
    CRYP->CR |= 1 << 15; // enable
}

int
crypto_gcm_final(u_char *out, int outlen){

    if( CRYP->CR & (3 <<16) == (1 << 16) ){
        // gmac mode - no payload
        crypto_aadsz = crypto_insz;
        crypto_insz = 0;

    }else{
        _wait_for_indma();
        _crypto_flush_input(0);
    }

    while( CRYP->SR & SR_BUSY ){}

    _stop_in_dma();
    _stop_out_dma();

    CRYP->CR |= 3 << 16; // CCMPH = final phase (3)
    CRYP->CR &= ~(1<<2); // dir = 0

    // write length
    CRYP->DR = crypto_insz;
    CRYP->DR = 0;
    CRYP->DR = crypto_aadsz;
    CRYP->DR = 0;

    // wait for it
    while( !(CRYP->SR & SR_OFNE) ) {}

    // read mac from DOUT x4
    int *dst = (u_long*)out;
    dst[0] = CRYP->DOUT;
    dst[1] = CRYP->DOUT;
    dst[2] = CRYP->DOUT;
    dst[3] = CRYP->DOUT;
}


#ifdef KTESTING
static const u_char zero128[16]  = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
static const u_char azero128[16] = { 'a',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
static const u_char azero256[32] = { 'a',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
static const u_char test1[32]    = {
    0x8a, 0x18, 0x2a, 0xdc,  0xe7, 0xd1, 0x80, 0x72,  0xed, 0x6a, 0x21, 0x5e,  0x4c, 0x85, 0xeb, 0x4b,
    0x0d, 0xae, 0x2e, 0xcd,  0x9b, 0x59, 0x01, 0xbc,  0xc2, 0x8b, 0x9c, 0x7a,  0x15, 0x2b, 0xab, 0xe4 };

// 11usec
DEFUN(cryptotiming, "test crypto timing")
{
    u_char *crbuf = alloc(512);
    bzero(crbuf, 512);

    yield();
    int t0 = get_hrtime();

    crypto_encrypt_start( CRYPTO_ALG_AES_CBC, azero256, 32, azero128, 16, crbuf, 512);
    crypto_add(crbuf, 512);
    crypto_final( );

    utime_t t1 = get_hrtime();
    printf("aes256 %d usec\n", (int)(t1-t0));

    free(crbuf, 512);
    return 0;
}

DEFUN(cryptotest, "crypto test")
{
    char buf[32];
    int n,i;

    bzero(buf, sizeof(buf));


    // 8a 18 2a dc  e7 d1 80 72  ed 6a 21 5e  4c 85 eb 4b
    crypto_encrypt_start( CRYPTO_ALG_AES_CBC, azero256, 32, azero128, 16, buf, sizeof(buf));
    crypto_add(zero128, 16 );
    crypto_add(zero128, 16 );
    crypto_final( );
    printf("%32,.4H\n", buf);

    memset(buf, 0xAA, 32);
    crypto_decrypt_start( CRYPTO_ALG_AES_CBC, azero256, 32, azero128, 16, buf, sizeof(buf));

    //for(i=0; i<32; i++) crypto_add(test1 + i, 1);

    crypto_add(test1, 32 );

    crypto_final( );
    printf("%32,.4H\n", buf);


    return 0;
}

DEFUN(gcmtest, "crypto test")
{
    char buf[32];
    char mac[16];
    int n,i;

    bzero(buf, sizeof(buf));

    crypto_gcm_start(azero256, 32, azero128, 16);
    // AAD
    crypto_add(zero128, 16 );
    crypto_add(zero128, 16 );

    crypto_gcm_encrypt(buf, sizeof(buf));
    // plaintext
    crypto_add(zero128, 16 );
    crypto_add(zero128, 16 );
    crypto_gcm_final(mac, 16);

    printf("%32,.4H\n", buf);
    printf("%16,.4H\n", mac);

    return 0;
}

#endif
