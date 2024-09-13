/*
  Copyright (c) 2015
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2015-Dec-13 18:00 (EST)
  Function: aes crypto

*/

#include <conf.h>
#include <proc.h>
#include <stm32.h>
#include <crypto.h>
//#include <dma.h>
#include <alloc.h>
#include <userint.h>

// NB - some devices have the "crypto" device, some have the "aes" device (not compatible)
// NB - DMA does not work as documented

// #define USE_AES_DMA

#define SR_BUSY	(1<<4)
#define SR_OFNE	(1<<2)
#define SR_IFNF	(1<<1)

#define SR_CCF  (1<<0)
#define CR_CCF  (1<<7)

static int crypto_blksz;
static int crypto_inbuf;
static int crypto_bufsz;
static int crypto_insz;
static int crypto_aadsz;
static int crypto_outpend;
static int crypto_outlen;
static u_long* crypto_outbuf;

#define DMASTRO	DMA2_Stream5
#define DMASTRI	DMA2_Stream6
#define DMACHAN	2

int
aes_init(void){

#ifdef PLATFORM_STM32U5
    RCC->AHB2ENR1 |= 1<<16;
#else
    // F7
    RCC->AHB2ENR |= 1<<4;
#endif
    return 0;
}

static void
_reset_crypto(void){

#ifdef PLATFORM_STM32U5
    AES->CR  &= ~ 0xFF0D787F;
#else
    AES->CR  &= ~ 0x57FFF;
#endif
    AES->CR |= 2 << 1; // byte mode

    crypto_inbuf   = 0;
    crypto_bufsz   = 0;
    crypto_insz    = 0;
    crypto_outpend = 0;
}

static void
_wait_ccf(){
    while( !(AES->SR & SR_CCF) ){
        __asm("nop");
    }

#ifdef PLATFORM_STM32U5
    AES->ICR |= 1;
#else
    // F7
    AES->CR |= CR_CCF;
#endif
}

static void
_wait_nbusy(){
    while( AES->SR & SR_BUSY ){
        __asm("nop");
    }
}

static void
_wait_keyvalid(){
    while( !(AES->SR & (1<<7)) ){
        __asm("nop");
    }
}

// 128 bit or 256 bit only
static void
_set_key(const u_char *key, int keylen){

    // truncate key to valid size
    // if <128, pad

    if( keylen >= 32 ){
        AES->CR |= 1 << 18; // 256 bit key
    }

    if( key ){
        int *k = (int*)key;

        if( keylen >= 32 ){
            AES->KEYR7 = __REV( *k ++ );
            AES->KEYR6 = __REV( *k ++ );
            AES->KEYR5 = __REV( *k ++ );
            AES->KEYR4 = __REV( *k ++ );
        }

        AES->KEYR3 = __REV( *k ++ );
        AES->KEYR2 = __REV( *k ++ );
        AES->KEYR1 = __REV( *k ++ );
        AES->KEYR0 = __REV( *k ++ );
    }else{
        AES->CR |= 2 << 24; // shared from SAES
    }
#ifdef PLATFORM_STM32U5
    _wait_keyvalid();
#endif
}

static inline void
_prepare_key(int alg){

    AES->CR |= 1 << 3; // key prepare mode
    AES->CR |= 1; // enable

    _wait_ccf();
}

static inline void
_set_iv(const u_char *iv, int ivlen){
    int *v = (int*)iv;

    AES->IVR3 = __REV( *v ++ );
    AES->IVR2 = __REV( *v ++ );
    AES->IVR1 = __REV( *v ++ );
    AES->IVR0 = __REV( *v ++ );
}

static void
_start_crypto(int alg){

    AES->CR |= (alg & 3) << 5;
    AES->CR |= (alg >>2) << 16;
    AES->CR |= 1; // enable

    crypto_blksz = 16;
}

#ifdef USE_AES_DMA
static inline void
_xwait_for_indma(void){
    if( DMASTRI->CR & 1 )
        while( !(DMA2->HISR & (1<<21)) ){} // transfer complete, stream 6
}

static inline void
_xwait_for_outdma(void){
    if( DMASTRO->CR & 1 )
        while( !(DMA2->HISR & (1<<11)) ){} // transfer complete, stream 5
}

static void
_xstart_in_dma(u_char *in, int inlen){

    AES->CR |= 1 << 11; // dma in en

    DMASTRI->CR  &= (0xF<<28) | (1<<20);	// zero CR
    DMA2->HIFCR  |= 0x3D << 16;			// clear ints

    DMASTRI->PAR   = & AES->DINR;
    DMASTRI->M0AR  = in;
    DMASTRI->NDTR  = inlen >> 2;

    DMASTRI->CR   |= (DMACHAN << 25)
        | (2<<16)		// high prio
        | (2<<13) | (2<<11)	// 32 bit->32 bit
        | (1<<10)		// inc mem
        | (1<<6)		// mem->dev
        ;

    printf("dma in ndtr %d\n", DMASTRI->NDTR);

    DMASTRI->CR   |= 1;		// enable
}

static void
_xstart_out_dma(u_char *out, int outlen){

    AES->CR |= 1 << 12; // dma out en

    DMASTRO->CR = 0;
    DMASTRO->CR   &= (0xF<<28) | (1<<20);	// zero CR
    DMA2->HIFCR  |= 0x3D<<6;			// clear ints

    DMASTRO->PAR   = & AES->DOUTR;
    DMASTRO->M0AR  = out;
    DMASTRO->NDTR  = outlen >> 2;

    DMASTRO->CR   |= (DMACHAN << 25)
        | (3<<16)		// highest prio
        | (2<<13) | (2<<11)	// 32 bit->32 bit
        | (1<<10)		// inc mem
        ;

    printf("dma out ndtr %d\n", DMASTRO->NDTR);
    
    DMASTRO->CR   |= 1;		// enable

}

static inline void
_xstop_out_dma(void){

    printf("/dma out ndtr %d\n", DMASTRO->NDTR);
    DMASTRO->CR   &= ~1;
}

static inline void
_xstop_in_dma(void){

    printf("/dma in ndtr %d\n", DMASTRI->NDTR);
    DMASTRI->CR   &= ~1;
}
#endif

void
crypto_encrypt_start(int alg, const u_char *key, int keylen, const u_char *iv, int ivlen, u_char *out, int outlen){

    _reset_crypto();
    _set_key(key, keylen);
    _set_iv(iv, ivlen);
    crypto_outbuf = out;
    crypto_outlen = outlen;
    _start_crypto(alg);
}

void
crypto_decrypt_start(int alg, const u_char *key, int keylen, const u_char *iv, int ivlen, u_char *out, int outlen){

    _reset_crypto();
    AES->CR |= (1 << 3);
    _set_key(key, keylen);

    if( alg == CRYPTO_ALG_AES_ECB || alg == CRYPTO_ALG_AES_CBC ){
        _prepare_key(alg);
    }

    AES->CR &= ~1;
    AES->CR &= ~(3<<3);
    AES->CR |= 2<<3;	// decrypt mode

    _set_iv(iv, ivlen);
    crypto_outbuf = out;
    crypto_outlen = outlen;
    _start_crypto(alg);

}

void
crypto_set_output(u_char *out, int outlen){
    crypto_outbuf = out;
    crypto_outlen = outlen;
}

static void
_crypto_output(){

    _wait_ccf();
    if( (crypto_outbuf == 0) || (crypto_outlen < 16) ){
        int x;
        x = AES->DOUTR;
        x = AES->DOUTR;
        x = AES->DOUTR;
        x = AES->DOUTR;
    }else{
        *crypto_outbuf ++ = AES->DOUTR;
        *crypto_outbuf ++ = AES->DOUTR;
        *crypto_outbuf ++ = AES->DOUTR;
        *crypto_outbuf ++ = AES->DOUTR;
        crypto_outlen  -= 16;
    }
    crypto_outpend -= 16;
}

static inline void
_crypto_maybe_output(){

    if( crypto_outpend != 16 ) return;
    _crypto_output();
}

void
crypto_one_block(const u_long *in, u_long *out){

    AES->DINR = *in ++;
    AES->DINR = *in ++;
    AES->DINR = *in ++;
    AES->DINR = *in ++;
    _wait_ccf();
    *out ++ = AES->DOUTR;
    *out ++ = AES->DOUTR;
    *out ++ = AES->DOUTR;
    *out ++ = AES->DOUTR;

    crypto_outpend = 0;
    crypto_insz += 16;
}

void
crypto_add(const u_long *in, int inlen){

    // finish any buffered input
    //printf("+ bufsz %d; insz %d; len %d\n", crypto_bufsz, crypto_insz, inlen);
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
            _crypto_maybe_output();
            AES->DINR     = crypto_inbuf;
            crypto_inbuf = 0;
            crypto_bufsz = 0;
            crypto_inbuf = 0;
            crypto_insz += 4;
            crypto_outpend += 4;
        }
    }

    for(; inlen > 3; inlen -= 4){
        _crypto_maybe_output();
        AES->DINR = *in ++;
        crypto_insz +=4;
        crypto_outpend += 4;
    }

    // save remaining partial
    if( inlen ){
        u_char *buf = (u_char*)&crypto_inbuf + crypto_bufsz;
        crypto_bufsz += inlen;

        u_char *src = (u_char*)in;
        for( ; inlen; inlen--){
            *buf++ = *src++;
        }
    }

    //printf("+ insz %d\n", crypto_insz);
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
        case 1: crypto_inbuf |= pl << 8;  // and fall through
        case 2: crypto_inbuf |= pl << 16; // and fall through
        case 3: crypto_inbuf |= pl << 24;
            break;
        }

        _crypto_maybe_output();
        AES->DINR  = crypto_inbuf;
        crypto_insz += 4;
        crypto_outpend += 4;
        len += 4 - crypto_bufsz;
        crypto_inbuf = 0;
        crypto_bufsz = 0;
    }

    // pad?
    if( len ){
        crypto_inbuf = use_pkcs ? 0x01010101 * pl : 0;
        for( ; len < crypto_blksz; len += 4 ){
            _crypto_maybe_output();
            AES->DINR  = crypto_inbuf;
            crypto_insz += 4;
            crypto_outpend += 4;
        }
    }


}

int
crypto_final(void){

    _crypto_flush_input(1);
    _crypto_maybe_output();

    AES->CR &= ~1;	// disable

    return crypto_insz;
}


void
crypto_gcm_start(const u_char *key, int keylen, const u_char *iv, int ivlen){

    _reset_crypto();
    _set_key(key, keylen);
    _set_iv(iv, ivlen);
    // IV = iv<96 bits> . counter<32 bits> : counter starts at 2
    AES->IVR0 = 2;

    AES->CR &= ~(3 << 1); // clear datatype
    AES->CR |= 3 << 5; 	// GCM Mode
    AES->CR |= 1;	// enable

    _wait_ccf();

    AES->CR |= (2 << 1); // byte mode

    // AAD phase
    AES->CR |= 1 << 13; // CCMPH = header phase (1)
    AES->CR |= 1;	// enable

    crypto_blksz = 16;
    crypto_aadsz = 0;
    crypto_outbuf = 0;
    crypto_outlen = 0;
}

void
crypto_gcm_encrypt_start(const u_char *key, int keylen, const u_char *iv, int ivlen){
    crypto_gcm_start(key, keylen, iv, ivlen);
}

void
crypto_gcm_decrypt_start(const u_char *key, int keylen, const u_char *iv, int ivlen){

    _reset_crypto();

    _set_key(key, keylen);
    _set_iv(iv, ivlen);
    // IV = iv<96 bits> . counter<32 bits> : counter starts at 2
    AES->IVR0 = 2;

    // (only) when using an SAES shared key, this needs to be done now:
    AES->CR |= 2<<3;	// decrypt mode

    AES->CR &= ~(3 << 1); // clear datatype
    AES->CR |= 3 << 5; 	// GCM Mode
    AES->CR |= 1;	// enable

    _wait_ccf();

    AES->CR |= (2 << 1); // byte mode

    // AAD phase
    AES->CR |= 1 << 13; // CCMPH = header phase (1)
    AES->CR |= 1;	// enable

    crypto_blksz = 16;
    crypto_aadsz = 0;
    crypto_outbuf = 0;
    crypto_outlen = 0;
}



void
crypto_gcm_encrypt(u_char *out, int outlen){

    crypto_aadsz  = crypto_insz + crypto_bufsz;
    // printf(">>e aadsz %d\n", crypto_aadsz);

    _crypto_flush_input(0);
    _crypto_maybe_output();

    crypto_insz   = 0;
    crypto_outbuf = out;
    crypto_outlen = outlen;
    crypto_outpend = 0;

    AES->CR &= ~ (3<<13);
    AES->CR |= 2 << 13; // CCMPH = payload phase (2)
    _wait_nbusy();

}

void
crypto_gcm_decrypt(u_char *out, int outlen){

    crypto_aadsz  = crypto_insz + crypto_bufsz;
    // printf(">>d aadsz %d\n", crypto_aadsz);

    _crypto_flush_input(0);
    _crypto_maybe_output();

    crypto_insz   = 0;
    crypto_outbuf = out;
    crypto_outlen = outlen;
    crypto_outpend = 0;

    AES->CR &= ~ (3<<13);
    AES->CR |= 2 << 13; // CCMPH = payload phase (2)
    AES->CR |= 2 << 3;  // decrypt
    _wait_nbusy();

}

int
crypto_gcm_final(u_char *out, int outlen){

    if( (AES->CR & (3 <<13)) == (1 << 13) ){
        // gmac mode - no payload
        crypto_gcm_encrypt(0, 0);
    }else{
        _crypto_flush_input(1);
    }
    _crypto_maybe_output();
    _wait_nbusy();

    // printf("final aadsz %d, insz %d; CR %x, SR %x\n", crypto_aadsz, crypto_insz, AES->CR, AES->SR);

    AES->CR |= 3 << 13;  // CCMPH = final phase (3)
    AES->CR &= ~(3<<3);  // dir = encrypt

    // write lengths (bits)
#ifdef PLATFORM_STM32U5
    AES->DINR = 0;
    AES->DINR = crypto_aadsz << 3;
    AES->DINR = 0;
    AES->DINR = crypto_insz << 3;
#else
    // F7 - ignores the swap setting?
    AES->DINR = 0;
    AES->DINR = __REV( crypto_aadsz << 3 );
    AES->DINR = 0;
    AES->DINR = __REV( crypto_insz << 3 );
#endif

    printf("aadsz %d, insz %d\n", crypto_aadsz, crypto_insz);

    // wait for it
    _wait_ccf();

    // read mac from DOUT x4
    int *dst = (u_long*)out;
    dst[0] = AES->DOUTR;
    dst[1] = AES->DOUTR;
    dst[2] = AES->DOUTR;
    dst[3] = AES->DOUTR;

    AES->CR &= ~1;	// disable
}



#ifdef KTESTING
static const u_char zero128[16]  ATTR_ALIGNED = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
static const u_char azero128[16] ATTR_ALIGNED = { 'a',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
static const u_char azero256[32] ATTR_ALIGNED = { 'a',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
static const u_char test1[32]    ATTR_ALIGNED = {
    0x8a, 0x18, 0x2a, 0xdc,  0xe7, 0xd1, 0x80, 0x72,  0xed, 0x6a, 0x21, 0x5e,  0x4c, 0x85, 0xeb, 0x4b,
    0x0d, 0xae, 0x2e, 0xcd,  0x9b, 0x59, 0x01, 0xbc,  0xc2, 0x8b, 0x9c, 0x7a,  0x15, 0x2b, 0xab, 0xe4 };


static u_char aesbuf[32] ATTR_ALIGNED;


DEFUN(aestest, 0)
{

    memset(aesbuf, 0xAA, 32);
    //_start_out_dma(aesbuf, 16);

    _reset_crypto();
    _set_key(azero256, 32);
    _set_iv( azero128, 16);
    _start_crypto(CRYPTO_ALG_AES_CBC);
    printf("aes %x cr %x; buf %x\n", AES, AES->CR, aesbuf);

    AES->DINR = 0;
    AES->DINR = 0;
    AES->DINR = 0;
    AES->DINR = 0;
    _wait_ccf();

    int r[4];
    r[0] = AES->DOUTR;
    r[1] = AES->DOUTR;
    r[2] = AES->DOUTR;
    r[3] = AES->DOUTR;

    // 8A18.2ADC.E7D1.8072.ED6A.215E.4C85.EB4B
    printf("%16,.4H\n", r);
    printf("cr %x, sr %x\n", AES->CR, AES->SR);
    _reset_crypto();
    // ok!

    return 0;
}

#ifdef USE_AES_DMA
DEFUN(aestest2, 0)
{

    memset(aesbuf, 0xAA, 32);

    _reset_crypto();
    _set_key(azero256, 32);
    _set_iv( azero128, 16);

    AES->CR |= (CRYPTO_ALG_AES_CBC & 3) << 5;
    AES->CR |= (CRYPTO_ALG_AES_CBC >>2) << 16;

    // _start_crypto(CRYPTO_ALG_AES_CBC);
    printf("aes %x cr %x; buf %x\n", AES, AES->CR, aesbuf);
    usleep(10000);

    // configure dma in

    DMASTRI->CR  &= (0xF<<28) | (1<<20);	// zero CR
    DMA2->HIFCR  |= 0x3D << 16;			// clear ints

    DMASTRI->PAR   = & AES->DINR;
    DMASTRI->M0AR  = zero128;
    DMASTRI->NDTR  = 16 >> 2;

    DMASTRI->CR   |= (DMACHAN << 25)
        | (2<<16)		// high prio
        | (2<<13) | (2<<11)	// 32 bit->32 bit
        | (1<<10)		// inc mem
        | (1<<6)		// mem->dev
        ;

    printf("dma in ndtr %d\n", DMASTRI->NDTR);


    // configure dma out

    DMASTRO->CR = 0;
    DMASTRO->CR   &= (0xF<<28) | (1<<20);	// zero CR
    DMA2->HIFCR  |= 0x3D<<6;			// clear ints

    DMASTRO->PAR   = & AES->DOUTR;
    DMASTRO->M0AR  = aesbuf;
    DMASTRO->NDTR  = 16 >> 2;

    DMASTRO->CR   |= (DMACHAN << 25)
        | (3<<16)		// highest prio
        | (2<<13) | (2<<11)	// 32 bit->32 bit
        | (1<<10)		// inc mem
        ;

    printf("dma out ndtr %d\n", DMASTRO->NDTR);
    
    
    printf("dma in  ndtr %d; out ndtr %d; hisr %x\n", DMASTRI->NDTR, DMASTRO->NDTR, DMA2->HISR);

#define XX_A    AES->CR |= 1; // enable
#define XX_B    DMASTRI->CR   |= 1; DMASTRO->CR   |= 1;		// enable
#define XX_C    AES->CR |= 1 << 11; AES->CR |= 1 << 12; // dma in, out en
#define XX_C2   AES->CR |= 1 << 12; AES->CR |= 1 << 11; // dma out, in en

    // ok:
    //XX_C; XX_B; XX_A; // sometimes
    //XX_A; XX_C; XX_B; // sometimes
    //XX_A; XX_B; XX_C; // no

    //XX_C; XX_A; XX_B; // no
    //XX_B; XX_A; XX_C; // sometimes
    //XX_B; XX_C; XX_A; // sometimes

    //XX_C2; XX_B; XX_A; // sometimes
    //XX_A; XX_C2; XX_B; // sometimes
    //XX_A; XX_B; XX_C2; // no

    //XX_C2; XX_A; XX_B; // no
    //XX_B; XX_A; XX_C2; // sometimes
    //XX_B; XX_C2; XX_A; // no

    //_wait_for_outdma();

    sleep(1);
    printf("cr %x sr %x\n", AES->CR, AES->SR);
    printf("/dma in  ndtr %d; out ndtr %d; hisr %x\n", DMASTRI->NDTR, DMASTRO->NDTR, DMA2->HISR);
    printf("%32,.4H\n", aesbuf);

    AES->CR &= ~1;
    
    return 0;
}
#endif


// 62usec
DEFUN(cryptotiming, "test crypto timing")
{
    u_char *crbuf = alloc(512);
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

    crypto_encrypt_start( CRYPTO_ALG_AES_CBC, azero256, 32, azero128, 16, buf, sizeof(buf));
    crypto_add(zero128, 16 );
    crypto_add(zero128, 16 );
    crypto_final( );
    printf("%32,.4H\n", buf);

    memset(buf, 0xAA, 32);
    crypto_decrypt_start( CRYPTO_ALG_AES_CBC, azero256, 32, azero128, 16, buf, sizeof(buf));
    crypto_add(test1, 32 );
    crypto_final( );
    printf("%x: %32,.4H\n", buf, buf);


    return 0;

    // expect
    //   8A18.2ADC.E7D1.8072.ED6A.215E.4C85.EB4B.0DAE.2ECD.9B59.01BC.C28B.9C7A.152B.ABE4
    //   0000.0000.0000.0000.0000.0000.0000.0000.0000.0000.0000.0000.0000.0000.0000.0000


    // F415:
    // 8A18.2ADC.E7D1.8072.ED6A.215E.4C85.EB4B.0DAE.2ECD.9B59.01BC.C28B.9C7A.152B.ABE4
    // E084.9364.64B4.C4BC.E146.917B.C176.DBC9.D51E.480E.1B32.CC77.CFEA.0D9A.C517.0737 (?)

}

DEFUN(gcmtest, "crypto test")
{
    char buf[32];
    char mac[16];
    int n,i;

    bzero(buf, sizeof(buf));

    crypto_gcm_start(azero128, 16, zero128, 16);
    // AAD
    crypto_add(azero128, 16 );

    crypto_gcm_encrypt(buf, sizeof(buf));
    // plaintext
    crypto_add(azero128, 16 );
    crypto_add(azero128, 16 );
    crypto_gcm_final(mac, 16);
    printf("aad %d, in %d\n", crypto_aadsz, crypto_insz);

    printf("%32,.4H\n", buf);
    printf("%16,.4H\n", mac);
    sleep(1);
    
    // expect:
    // 3BC0.9531.C63C.8370.768A.8469.B7F0.E391.C770.677C.8C22.8DB2.396A.2ECB.8BEA.0E7B
    // 395B.25BC.AE7C.8BDB.867B.55B7.4CB8.DB3F

    // and decrypt
    crypto_gcm_start(azero128, 16, zero128, 16);
    // AAD
    crypto_add(azero128, 16 );

    crypto_gcm_decrypt(buf, sizeof(buf));
    // cryptotext
    crypto_add(buf, 32);
    crypto_gcm_final(mac, 16);
    printf("aad %d, in %d\n", crypto_aadsz, crypto_insz);

    printf("%32,.4H\n", buf);
    printf("%16,.4H\n", mac);

    // expect original plaintext, same tag:
    // 6100.0000.0000.0000.0000.0000.0000.0000.6100.0000.0000.0000.0000.0000.0000.0000
    // 395B.25BC.AE7C.8BDB.867B.55B7.4CB8.DB3F

    return 0;
}

DEFUN(gmactest, "crypto test")
{
    char buf[32];
    char mac[16];

    bzero(buf, sizeof(buf));

    crypto_gcm_start(zero128, 16, zero128, 16);
    crypto_add(zero128, 16);
    crypto_gcm_final(mac, 16);

    // expect:
    // 21C2.EB20.CD22.14DB.DF34.C9B8.2ECB.7ED2
    printf("%16,.4H\n", mac);

    return 0;
}

DEFUN(gmactest2, "test")
{

    AES->CR = 0;	// reset
    AES->CR |= 3 << 5; 	// CHMOD = GCM Mode
    AES->CR |= 2 << 1;  // byte mode

    // set key + iv to all 0s
    AES->KEYR3 = 0;
    AES->KEYR2 = 0;
    AES->KEYR1 = 0;
    AES->KEYR0 = 0;

    AES->IVR3 = 0;
    AES->IVR2 = 0;
    AES->IVR1 = 0;
    AES->IVR0 = 2; // init counter to 2 (per RM0456 Table 466)

    AES->CR |= 1;	// enable
    _wait_ccf();


    // AAD phase
    AES->CR |= 1 << 13; // CCMPH = header phase (1)
    AES->CR |= 1;	// enable

    // add AAD data
    AES->DINR = 0;
    AES->DINR = 0;
    AES->DINR = 0;
    AES->DINR = 0;


    _wait_ccf();


    // crypto_gcm_final(mac, 16);
    // skip payload phase
    // AES->CR &= ~ (3<<13);
    // AES->CR |= 2 << 13; // CCMPH = payload phase (2)
    // _wait_nbusy();


    AES->CR |= 3 << 13;  // CCMPH = final phase (3)
    AES->CR &= ~(3<<3);  // dir = encrypt

    // write lengths (bits)
    AES->DINR = 0;
    AES->DINR = 128; // ok=128; __REV( 128 );
    AES->DINR = 0;
    AES->DINR = 0;

    // wait for it
    _wait_ccf();

    // read mac from DOUT x4
    uint32_t dst[4];
    dst[0] = AES->DOUTR;
    dst[1] = AES->DOUTR;
    dst[2] = AES->DOUTR;
    dst[3] = AES->DOUTR;

    AES->CR &= ~1;	// disable


    printf("%16,.4H\n", dst);
    return 0;
}

#endif
