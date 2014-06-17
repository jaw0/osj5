
/* based on NetBSD/1.6/src/sys/lib/libkern */

/*      $NetBSD: libkern.h,v 1.39 2001/12/28 07:37:06 thorpej Exp $     */
/*-
 * Copyright (c) 1992, 1993
 *      The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *      This product includes software developed by the University of
 *      California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *      @(#)libkern.h   8.2 (Berkeley) 8/5/94
 */

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
