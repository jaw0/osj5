
/* $Id: misc.h,v 1.1 1998/11/07 21:32:29 jaw Exp $ */

#ifndef __misc_h__
#define __misc_h__

#ifdef __cplusplus
# define EXTERN extern "C"
#else
# define EXTERN extern
#endif

#define __QUOTIFY(x)	#x
#define QUOTIFY(x)	__QUOTIFY(x)

#define __CONCAT(x,y)	x ## y
#define CONCAT(x,y)	__CONCAT(x,y)

#define ELEMENTSIN(T) (sizeof(T)/sizeof(T[0]))


extern const char ident[];
extern const char archid[];
extern const char version[];

extern unsigned long long fnv64_hash(const unsigned char *, int);


#endif /* __misc_h__ */

