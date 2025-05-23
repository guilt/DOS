/*
 * Copyright (c) 1983, 1993
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
 */

#ifndef _PROTOCOL_TALKD_H_
#define _PROTOCOL_TALKD_H_

#ifndef _ENABLE_AUTODEPEND
 #pragma read_only_file
#endif

#define TALK_VERSION 1

#define LEAVE_INVITE 0
#define LOOK_UP      1
#define DELETE       2
#define ANNOUNCE     3

#define SUCCESS           0
#define NOT_HERE          1
#define FAILED            2
#define MACHINE_UNKNOWN   3
#define PERMISSION_DENIED 4
#define UNKNOWN_REQUEST   5
#define BADVERSION        6
#define BADADDR           7
#define BADCTLADDR        8

#define MAX_LIFE  60
#define RING_WAIT 30

#define NAME_SIZE 12
#define TTY_SIZE  16

#pragma pack( __push, 1 )

typedef struct {
    u_char vers;
    u_char type;
    u_char answer;
    u_char pad;
    u_long id_num;
    struct osockaddr addr;
    struct osockaddr ctl_addr;
    long   pid;
    char   l_name[NAME_SIZE];
    char   r_name[NAME_SIZE];
    char   r_tty[TTY_SIZE];
} CTL_MSG;

typedef struct {
    u_char vers;
    u_char type;
    u_char answer;
    u_char pad;
    u_long id_num;
    struct osockaddr addr;
} CTL_RESPONSE;

#pragma pack( __pop )

#endif
