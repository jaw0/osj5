

#ifdef __ELF__
# define _C_LABEL(x)    x
#else
# ifdef __STDC__
#  define _C_LABEL(x)   _ ## x
# else
#  define _C_LABEL(x)   _/**/x
# endif
#endif

#define _ASM_LABEL(x)   x

#ifdef __STDC__
# define __CONCAT(x,y)  x ## y
# define __STRING(x)    #x
#else
# define __CONCAT(x,y)  x/**/y
# define __STRING(x)    "x"
#endif
#define _STRING(x)	__STRING(x)

#define _ENTRY(x)               \
        .globl x;               \
        .type x,@function;      \
        .align 2;               \
        x:

#define ENTRY(x)	_ENTRY(_C_LABEL(x))
#define ASMENTRY(x)	_ENTRY(_ASM_LABEL(x))

#define QC_LABEL(x)	_STRING(_C_LABEL(x))

