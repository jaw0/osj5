/*
  Copyright (c) 2015
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2015-Dec-13 18:00 (EST)
  Function: crypto

*/

#ifndef __osj5_stm32f7_crypto_h__
#define __osj5_stm32f7_crypto_h__

#ifdef USE_CRYPTO
// crypto device
#define CRYPTO_ALG_TDES_ECB	0
#define CRYPTO_ALG_TDES_CBC	1
#define CRYPTO_ALG_DES_ECB	2
#define CRYPTO_ALG_DES_CBC	3
#define CRYPTO_ALG_AES_ECB	4
#define CRYPTO_ALG_AES_CBC	5
#define CRYPTO_ALG_AES_CTR	6

#else
// AES device
#define CRYPTO_ALG_AES_ECB	0
#define CRYPTO_ALG_AES_CBC	1
#define CRYPTO_ALG_AES_CTR	2
#define CRYPTO_ALG_AES_GCM	3
#define CRYPTO_ALG_AES_GMAC	3
#define CRYPTO_ALG_AES_CCM	4
#endif


#endif /* __osj5_stm32f7_crypto_h__ */
