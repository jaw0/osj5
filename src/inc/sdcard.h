/*
  Copyright (c) 2013
  Author: Jeff Weisberg <jaw @ tcp4me.com>
  Created: 2013-Apr-02 10:37 (EDT)
  Function:  sdcard
*/

#ifndef __sdcard_h__
#define __sdcard_h__

struct SDCard_CID {
    u_char	manuf_id;
    char	oem_id[2];
    char	product[5];
    u_char	version;
    u_char	serialno[4];
    u_char	datecode[2];
    u_char	crc;
};


#endif /* __sdcacrd_h__ */

