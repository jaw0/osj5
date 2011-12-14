
/* $Id: get.h,v 1.2 1999/04/14 19:41:19 jaw Exp $ */

#ifndef __get_h__
#define __get_h__

extern long atoi(const char *a);
extern long atoi_base(int base, const char *buf);
extern long getnum(int base);
extern long strtol(const char*, const char**, int);
extern long long strtoq(const char*, const char**, int);

#endif /* __get_h__ */

