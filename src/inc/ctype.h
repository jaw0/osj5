/*      $NetBSD: libkern.h,v 1.39 2001/12/28 07:37:06 thorpej Exp $     */

#define LIBKERN_INLINE		static inline

LIBKERN_INLINE int
isspace(ch)
        int ch;
{

        return (ch == ' ' || (ch >= '\t' && ch <= '\r'));
}

LIBKERN_INLINE int
isascii(ch)
        int ch;
{

        return ((ch & ~0x7f) == 0);
}

LIBKERN_INLINE int
isupper(ch)
        int ch;
{

        return (ch >= 'A' && ch <= 'Z');
}

LIBKERN_INLINE int
islower(ch)
        int ch;
{

        return (ch >= 'a' && ch <= 'z');
}

LIBKERN_INLINE int
isalpha(ch)
        int ch;
{

        return (isupper(ch) || islower(ch));
}

LIBKERN_INLINE int
isdigit(ch)
        int ch;
{

        return (ch >= '0' && ch <= '9');
}

LIBKERN_INLINE int
isxdigit(ch)
        int ch;
{

        return (isdigit(ch) ||
            (ch >= 'A' && ch <= 'F') ||
            (ch >= 'a' && ch <= 'f'));
}

LIBKERN_INLINE int
toupper(ch)
        int ch;
{

        if (islower(ch))
                return (ch - 0x20);
        return (ch);
}

LIBKERN_INLINE int
tolower(ch)
        int ch;
{

        if (isupper(ch))
                return (ch + 0x20);
        return (ch);
}
