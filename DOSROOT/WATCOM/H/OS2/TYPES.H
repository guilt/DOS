/*-
 * Copyright (c) 1982, 1986, 1991, 1993, 1994
 *      The Regents of the University of California.  All rights reserved.
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
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
 */

#ifndef _TYPES_H_
#define _TYPES_H_

#ifndef _ENABLE_AUTODEPEND
 #pragma read_only_file
#endif

#include <machine/ansi.h>
#include <machine/types.h>

#ifndef _POSIX_SOURCE
typedef unsigned char   u_char;
typedef unsigned short  u_short;
typedef unsigned long   u_long;
typedef unsigned short  ushort;
typedef unsigned int    u_int;
typedef unsigned int    uint;
typedef int             long_int;
typedef char *          caddr_t;
typedef int32_t         pid_t;

#include <sys/cdefs.h>
#include <machine/endian.h>

#ifdef  _BSD_SIZE_T_
typedef _BSD_SIZE_T_    size_t;
#undef  _BSD_SIZE_T_
#endif

#ifdef  _BSD_SSIZE_T_
typedef _BSD_SSIZE_T_   ssize_t;
#undef  _BSD_SSIZE_T_
#endif

#ifndef _POSIX_SOURCE

#ifndef FD_SETSIZE
    #define FD_SETSIZE 64
#endif
#define NBBY           8
#define MAXSOCKETS     32768
#define BSDMAXSOCKETS  2048

#define FD_CLR(fd, set) do { \
    u_int __i; \
    for (__i = 0; __i < ((fd_set *)(set))->fd_count ; __i++) { \
        if (((fd_set *)(set))->fd_array[__i] == fd) { \
            while (__i < ((fd_set *)(set))->fd_count-1) { \
                ((fd_set *)(set))->fd_array[__i] = \
                    ((fd_set *)(set))->fd_array[__i+1]; \
                __i++; \
            } \
            ((fd_set *)(set))->fd_count--; \
            break; \
        } \
    } \
} while(0)

#define FD_SET(fd, set) do { \
    if (((fd_set *)(set))->fd_count < FD_SETSIZE) \
        ((fd_set *)(set))->fd_array[((fd_set *)(set))->fd_count++]=fd;\
} while(0)

#define FD_ZERO(set)      (((fd_set *)(set))->fd_count=0)
#define FD_ISSET(fd, set) __TCPFDIsSet((int)fd, (fd_set *)set)
#define FD_COPY(f, t)     memcpy(t, f, sizeof(*(f)))

#pragma pack( __push, 4 )

typedef struct fd_set {
    u_short fd_count;
    int     fd_array[FD_SETSIZE];
} fd_set;

#pragma pack( __pop )

__BEGIN_DECLS
extern int _System __TCPFDIsSet __TCPPROTO((int, fd_set *));
__END_DECLS

#endif
#endif

#endif
