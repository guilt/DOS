/*
 * Copyright (c) 1986, 1993
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

#ifndef _NET_IF_ARP_H_
#define _NET_IF_ARP_H_

#ifndef _ENABLE_AUTODEPEND
 #pragma read_only_file
#endif

#define ATF_INUSE       0x01
#define ATF_COM         0x02
#define ATF_PERM        0x04
#define ATF_PUBL        0x08
#define ATF_USETRAILERS 0x10
#define ATF_802_3       0x20

#define ARPHRD_ETHER     1
#define ARPHRD_802       6
#define ARPHRD_FRELAY    15
#define ARPOP_REQUEST    1
#define ARPOP_REPLY      2
#define ARPOP_REVREQUEST 3
#define ARPOP_REVREPLY   4
#define ARPOP_INVREQUEST 8
#define ARPOP_INVREPLY   9

#pragma pack( __push, 1 )

struct  arphdr {
    u_short ar_hrd;
    u_short ar_pro;
    u_char  ar_hln;
    u_char  ar_pln;
    u_short ar_op;
#ifdef COMMENT_ONLY
    u_char  ar_sha[];
    u_char  ar_spa[];
    u_char  ar_tha[];
    u_char  ar_tpa[];
#endif
};

#pragma pack( __pop )


#pragma pack( __push, 4 )

struct arpreq {
    struct   sockaddr arp_pa;
    struct   sockaddr arp_ha;
    long_int arp_flags;
};

struct arpreq_tr {
    struct   sockaddr arp_pa;
    struct   sockaddr arp_ha;
    long_int arp_flags;
    u_short  arp_rcf;
    u_short  arp_rseg[8];
};

#pragma pack( __pop )

#endif
