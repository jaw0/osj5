/*
  Copyright (c) 2024
  Author: Jeff Weisberg <tcp4me.com!jaw>
  Created: 2024-Sep-12 09:19 (EDT)
  Function: SAES

*/

#include <conf.h>
#include <proc.h>
#include <stm32.h>
#include <crypto.h>
#include <alloc.h>
#include <userint.h>

int
saes_init(void){

    RCC->CR |= 1<<14; // SHSI enable
    while( (RCC->CR & (1<<15)) == 0 ) {
        __asm("nop");
    }
    RCC->AHB2ENR1 |= 1<<20; // SAES

    return 0;
}

void
saes_reset(void){

    SAES->CR  &= ~ 0xFF0D187F;
    SAES->CR |= 2 << 1; // byte mode
}


static void
_wait_ccf(){
    while( !(SAES->SR & AES_SR_CCF) ){
        __asm("nop");
    }

    SAES->ICR |= 1;
}

static void
_wait_nbusy(){
    while( SAES->SR & AES_SR_BUSY ){
        __asm("nop");
    }
}

static void
_wait_keyvalid(){
    while( !(SAES->SR & (1<<7)) ){
        __asm("nop");
    }
}

static void
_set_iv(const u_char *iv){
    int *v = (int*)iv;

    SAES->IVR3 = __REV( *v ++ );
    SAES->IVR2 = __REV( *v ++ );
    SAES->IVR1 = __REV( *v ++ );
    SAES->IVR0 = __REV( *v ++ );
}

static void
_set_key(int keysel, int keylen){

    if( keylen >= 32 ){
        SAES->CR |= 1 << 18; // 256 bit key
    }

    SAES->CR |= keysel << 28;

    _wait_keyvalid();
}

static inline void
_prepare_key(){

    SAES->CR |= 1 << 3; // key prepare mode
    SAES->CR |= 1; // enable

    _wait_ccf();
}


int
saes_wrapkey(int keysel, const uint32_t *pkey, const uint32_t *iv, uint32_t *wkey, int len){

    saes_reset();

    SAES->CR &= ~AES_CR_EN; 	// disable
    _wait_nbusy();

    SAES->CR = (1 << 5) 	// CBC
        | (2 << 24)		// key sharing
        ;
    if( len >= 32 ){
        SAES->CR |= 1 << 18; // 256 bit key
    }

    _set_key(keysel, len);
    _set_iv(iv);

    SAES->CR |= 1;		// enable

    while(len){
        SAES->DINR = __REV(*pkey ++);
        SAES->DINR = __REV(*pkey ++);
        SAES->DINR = __REV(*pkey ++);
        SAES->DINR = __REV(*pkey ++);

        _wait_ccf();

        *wkey ++ =  SAES->DOUTR;
        *wkey ++ =  SAES->DOUTR;
        *wkey ++ =  SAES->DOUTR;
        *wkey ++ =  SAES->DOUTR;

        len -= 16;
    }

    return 1;
}


// unwrapped into AES.key
int
saes_unwrapkey(int keysel, const uint32_t *wkey, const uint32_t *iv, int len){

    saes_reset();

    SAES->CR &= ~AES_CR_EN; 	// disable
    _wait_nbusy();

    SAES->CR = (1 << 5) 	// CBC
        | (2 << 24)		// key sharing
        ;
    if( len >= 32 ){
        SAES->CR |= 1 << 18; // 256 bit key
    }

    _set_key(keysel, len);
    _prepare_key();

    SAES->CR &= ~1;
    SAES->CR &= ~(3<<3);
    SAES->CR |= 2<<3;	// decrypt mode
    _set_iv(iv);

    SAES->CR |= 1;		// enable

    while(len){
        SAES->DINR = *wkey ++;
        SAES->DINR = *wkey ++;
        SAES->DINR = *wkey ++;
        SAES->DINR = *wkey ++;

        _wait_ccf();

        len -= 16;
    }

    return 1;
}


#ifdef KTESTING
static const uint32_t test_0[] = { 0, 0, 0, 0 };
static const uint32_t test_1[] = { 0, 0, 0, 0, 0, 0, 0, 2 };

static const u_char zero128[16]   = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
static const u_char azero128[16]  = { 'a',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
static const u_char azero256[32]  = { 'a',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

DEFUN(testwkey, 0)
{
    int r;
    char buf[32];
    char out[32];
    char mac[16];
    int keylen = 32;

    bzero(buf, sizeof(buf));
    r = saes_wrapkey( SAES_KEY_DHUK, test_1, test_0, buf, keylen );

    printf("wk %x, %32,.4H\n", r, buf);

    r = saes_unwrapkey(SAES_KEY_DHUK, buf, test_0, keylen);

    // ****************

    printf("s/cr %x, sr %x; %x, %x\n", SAES->CR, SAES->SR, AES->CR, AES->SR);

    // now a gcm
    bzero(buf, sizeof(buf));
    crypto_gcm_start(0, keylen, zero128, 16);	// key, iv
    // AAD
    crypto_add(azero128, 16 );

    crypto_gcm_encrypt(buf, sizeof(buf));
    // add plaintext
    crypto_add(azero128, 16 );
    crypto_add(azero128, 16 );

    crypto_gcm_final(mac, 16);

    printf("%32,.4H\n", buf);
    printf("%16,.4H\n", mac);

    // using key=test_1
    //   3ABD.EEB8.EB3F.6A0E.6E58.F257.8360.93D1.1C40.35FB.1191.DC56.8880.A66F.573A.FFCD
    //   65C5.4A9C.77D0.743C.AE51.E77E.86E9.8A76


    // decrypt
    // crypto_gcm_start(test_1, keylen, zero128, 16); // works ok
    crypto_gcm_decrypt_start(0, keylen, zero128, 16);	// key, iv
    // AAD
    crypto_add(azero128, 16 );

    crypto_gcm_decrypt(out, sizeof(out));
    crypto_add(buf, 32);
    crypto_gcm_final(mac, 16);

    printf("%32,.4H\n", out);
    printf("%16,.4H\n", mac);

    // expect:
    //   6100.0000.0000.0000.0000.0000.0000.0000.6100.0000.0000.0000.0000.0000.0000.0000
    //   65C5.4A9C.77D0.743C.AE51.E77E.86E9.8A76

}
#endif

/*
  1. Verify that BUSY = 0 in SAES_SR (no RNG random number fetch in progress).
2. Disable the SAES peripheral by clearing the EN bit of the SAES_CR register.
3. In SAES_CR register, select the Mode 1 (encryption) by setting to 00 the MODE[1:0]
bitfield, and select ECB or CBC chaining mode by setting CHMOD[2:0] bitfield to 000 or 001, respectively. Data type can be defined as 32-bit, with DATATYPE[1:0] bitfield set to 00. Key size must be properly configured using KEYSIZE bit, and KMOD[1:0] bitfield must be set as 01 (wrapped key). The KEYSIZE information is used both for the encryption key and for the key to be encrypted.
4. Write the SAES_IVRx registers with the initialization vector if CBC mode has been selected in previous step.
5. Select the DHUK by setting the KEYSEL[2:0] bitfield of the SAES_CR register to 001 or 100. Upon successful key loading BUSY bit is cleared and KEYVALID bit is set in SAES_SR register. Refer to Section 50.4.12: SAES key registers for detail on KEYSEL = 100 usage.
6. Enable SAES by setting the EN bit of the SAES_CR register.
7. Write the SAES_DINR register four times to input the key to encrypt (MSB first, see
Table 475 on page 1985).
8. Wait until the CCF flag is set in the SAES_SR register.
9. Get the encrypted key (MSB first) by reading the SAES_DOUTR register four times. Then clear the CCF flag by setting the CCF bit in SAES_ICR register.
10. Repeat steps 6 to 8 if KEYSIZE is 256 bits.


Decryption in Wrapped-key mode
Recommended sequence to unwrap (i.e. decrypt) a wrapped key is described below:
1. Verify that BUSY = 0 in SAES_SR (no RNG random number fetch in progress).
2. Disable the SAES peripheral by clearing the EN bit of the SAES_CR register.
3. SAES_CR register, select the Mode 2 by setting to 01 the MODE[1:0] bitfield, and
select ECB or CBC chaining mode by setting CHMOD[2:0] to 000 or 001, respectively. Key size must be properly configured using KEYSIZE bit, and KMOD[1:0] bitfield must be set as 01 (wrapped key). Data type selection with DATATYPE[1:0] bitfield must be the same as the one used during encryption (that is, 0x0). The KEYSIZE information is used both for the decryption key and for the key to be decrypted.
If the decrypted key is not to share with a different security context (different security
attribute), the KEYPROT bit of the SAES_CR register must also be set.
4. Select the DHUK by setting the KEYSEL[2:0] bitfield of the SAES_CR register to 001 or
100. Upon successful key loading, the SAES_SR register BUSY bit is cleared and KEYVALID bit set. Refer to Section 50.4.12: SAES key registers for detail on KEYSEL = 100 usage.
5. Enable SAES by setting the EN bit of the SAES_CR register.
6. Wait until the CCF flag is set in the SAES_SR register.
7. Clear the CCF flag. Decryption key is available in AES core, and SAES is disabled automatically.
8. In SAES_CR register select the Mode 3 by setting to 10 the MODE[1:0] bitfield.
9. Write the SAES_IVRx registers with the initialization vector if CBC mode has been selected in previous step.
10. Enable SAES by setting the EN bit of the SAES_CR register.
11. Write the SAES_DINR register four times to input the encrypted random key (MSB first,
see Table 475 on page 1985).
12. Wait until the CCF flag is set in the SAES_SR register.
13. Clear the CCF flag, then repeat steps 10 and 11 if KEYSIZE is 256 bits.
When the decrypted key is loaded in key registers, KEYSEL[2:0] of the SAES_CR register is automatically cleared. Hence, after this sequence, the decrypted wrapped key is available in SAES_KEYRx registers, immediately usable by the application software for any AES operation (normal key mode).
*/
