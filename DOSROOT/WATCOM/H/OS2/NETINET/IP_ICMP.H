/*
 * Copyright (c) 1982, 1986, 1993
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

#ifndef _NETINET_IP_ICMP_H_
#define _NETINET_IP_ICMP_H_

#ifndef _ENABLE_AUTODEPEND
 #pragma read_only_file
#endif

#define ICMP_MINLEN    8
#define ICMP_TSLEN     (8 + 3 * sizeof (n_time))
#define ICMP_MASKLEN   12
#define ICMP_ADVLENMIN (8 + sizeof (struct ip) + 8)
#define ICMP_ADVLEN(p) (8 + ((p)->icmp_ip.ip_hl << 2) + 8)


#define ICMP_ECHOREPLY            0
#define ICMP_UNREACH              3
#define ICMP_UNREACH_NET          0
#define ICMP_UNREACH_HOST         1
#define ICMP_UNREACH_PROTOCOL     2
#define ICMP_UNREACH_PORT         3
#define ICMP_UNREACH_NEEDFRAG     4
#define ICMP_UNREACH_SRCFAIL      5
#define ICMP_UNREACH_NET_UNKNOWN  6
#define ICMP_UNREACH_HOST_UNKNOWN 7
#define ICMP_UNREACH_ISOLATED     8
#define ICMP_UNREACH_NET_PROHIB   9
#define ICMP_UNREACH_HOST_PROHIB 10
#define ICMP_UNREACH_TOSNET      11
#define ICMP_UNREACH_TOSHOST     12
#define ICMP_SOURCEQUENCH         4
#define ICMP_REDIRECT             5
#define ICMP_REDIRECT_NET         0
#define ICMP_REDIRECT_HOST        1
#define ICMP_REDIRECT_TOSNET      2
#define ICMP_REDIRECT_TOSHOST     3
#define ICMP_ECHO                 8
#define ICMP_ROUTERADVERT         9
#define ICMP_ROUTERSOLICIT       10
#define ICMP_TIMXCEED            11
#define ICMP_TIMXCEED_INTRANS     0
#define ICMP_TIMXCEED_REASS       1
#define ICMP_PARAMPROB           12
#define ICMP_PARAMPROB_OPTABSENT  1
#define ICMP_TSTAMP              13
#define ICMP_TSTAMPREPLY         14
#define ICMP_IREQ                15
#define ICMP_IREQREPLY           16
#define ICMP_MASKREQ             17
#define ICMP_MASKREPLY           18
#define ICMP_MAXTYPE             18

#define ICMP_INFOTYPE(type) \
    ((type) == ICMP_ECHOREPLY || (type) == ICMP_ECHO || \
    (type) == ICMP_ROUTERADVERT || (type) == ICMP_ROUTERSOLICIT || \
    (type) == ICMP_TSTAMP || (type) == ICMP_TSTAMPREPLY || \
    (type) == ICMP_IREQ || (type) == ICMP_IREQREPLY || \
    (type) == ICMP_MASKREQ || (type) == ICMP_MASKREPLY)

#define icmp_pptr    icmp_hun.ih_pptr
#define icmp_gwaddr  icmp_hun.ih_gwaddr
#define icmp_id      icmp_hun.ih_idseq.icd_id
#define icmp_seq     icmp_hun.ih_idseq.icd_seq
#define icmp_void    icmp_hun.ih_void
#define icmp_pmvoid  icmp_hun.ih_pmtu.ipm_void
#define icmp_nextmtu icmp_hun.ih_pmtu.ipm_nextmtu

#define icmp_otime icmp_dun.id_ts.its_otime
#define icmp_rtime icmp_dun.id_ts.its_rtime
#define icmp_ttime icmp_dun.id_ts.its_ttime
#define icmp_ip    icmp_dun.id_ip.idi_ip
#define icmp_mask  icmp_dun.id_mask
#define icmp_data  icmp_dun.id_data

#pragma pack( __push, 1 )

struct icmp {
    u_char  icmp_type;
    u_char  icmp_code;
    u_short icmp_cksum;
    union {
        u_char ih_pptr;
        struct in_addr ih_gwaddr;
        struct ih_idseq {
            n_short icd_id;
            n_short icd_seq;
        } ih_idseq;
        int ih_void;
        struct ih_pmtu {
            n_short ipm_void;
            n_short ipm_nextmtu;
        } ih_pmtu;
    } icmp_hun;
    union {
        struct id_ts {
            n_time its_otime;
            n_time its_rtime;
            n_time its_ttime;
        } id_ts;
        struct id_ip  {
            struct ip idi_ip;
        } id_ip;
        u_long  id_mask;
        char    id_data[1];
    } icmp_dun;
};

#pragma pack( __pop )

#endif
