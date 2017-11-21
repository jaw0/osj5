/*
  Copyright (c) 2015
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2015-Dec-12 17:30 (EST)
  Function: base64 encoding, ...

*/


// url + filename safe encoding
static const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

void
base64_encode(const unsigned char *src, int slen, char *dst, int dlen){
    unsigned int l;

    // make sure dst is terminated on empty input
    if( dlen ) *dst = 0;

    while(slen){
        unsigned int e=0;
        int il=slen>3 ? 3 : slen;
        slen -= il;

        if( dlen < 5 ) return;

        switch(il){
        case 3:
            e |= (*src++) << 16;
            // fall thru
        case 2:
            e |= (*src++) << ((4 - il)<<3);
            // fall thru
        case 1:
            e |= (*src++) << ((3 - il)<<3);
            break;
        }

        // output chars
        *dst++ = charset[ (e>>18) & 0x3f ];
        *dst++ = charset[ (e>>12) & 0x3f ];

        if(il > 1 ){
            *dst++ = charset[ (e>> 6) & 0x3f ];
            if( il > 2 )
                *dst++ = charset[ (e    ) & 0x3f ];
        }

        // output padding
        switch(il){
        case 1:
            *dst++ = '=';
            // fall thru
        case 2:
            *dst++ = '=';
            break;
        }

        *dst = 0;
        dlen -= 4;
    }
}


#define HEX(x)		(((x)>9) ? (x) + 'A' - 10 : (x) + '0')

void
hex_encode(const unsigned char *in, int inlen, char *out, int outlen){
    short i;

    if( inlen > outlen/2 ) inlen = outlen/2;

    for(i=0; i<inlen; i++){
        short c = in[i];
        *out++ = HEX(c>>4);
        *out++ = HEX(c&0xF);
    }

    if( outlen > inlen * 2 ) *out = 0;

}

#define HEXD(x)		(((x)>'9') ? (x) - 'A' + 10 : (x) - '0')

void
hex_decode(const char *in, int inlen, unsigned char *out, int outlen){
    short i;

    if( inlen > outlen * 2 ) inlen = outlen * 2;

    for(i=0; i<inlen; i+=2){
        if( !in[i] || !in[i+1] ) break;	// end-of-string
        *out++ = (HEXD(in[i]) << 4) | HEXD(in[i+1]);
    }
}

