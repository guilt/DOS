/*
 *  nldef.h     Network layer definitions
 *
 * =========================================================================
 *
 *                          Open Watcom Project
 *
 * Copyright (c) 2004-2025 The Open Watcom Contributors. All Rights Reserved.
 *
 *    This file is automatically generated. Do not edit directly.
 *
 * =========================================================================
 */

#ifndef _NLDEF_
#define _NLDEF_

#ifndef _ENABLE_AUTODEPEND
 #pragma read_only_file
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Network layer maximum metric component */
#define NL_MAX_METRIC_COMPONENT 0x7FFFFFFFL

/* Macro to declare route protocols */
#define MAKE_ROUTE_PROTOCOL( p1, p2 ) \
    MIB_IPPROTO_##p1    = p2, \
    PROTO_IP_##p1       = p2

/* Network interface current session */
#define NET_IF_CURRENT_SESSION  0xFFFFFFFFL

/* Network layer prefix origins */
typedef enum {
    IpPrefixOriginOther                 = 0,
    IpPrefixOriginManual                = 1,
    IpPrefixOriginWellKnown             = 2,
    IpPrefixOriginDhcp                  = 3,
    IpPrefixOriginRouterAdvertisement   = 4,
    IpPrefixOriginUnchanged             = 8
} NL_PREFIX_ORIGIN;
#define NlpoOther               IpPrefixOriginOther
#define NlpoManual              IpPrefixOriginManual
#define NlpoWellKnown           IpPrefixOriginWellKnown
#define NlpoDhcp                IpPrefixOriginDhcp
#define NlpoRouterAdvertisement IpPrefixOriginRouterAdvertisement

/* Network layer suffix origins */
typedef enum {
    NlsoOther                       = 0,
    NlsoManual                      = 1,
    NlsoWellKnown                   = 2,
    NlsoDhcp                        = 3,
    NlsoLinkLayerAddress            = 4,
    NlsoRandom                      = 5,
    IpSuffixOriginOther             = 0,
    IpSuffixOriginManual            = 1,
    IpSuffixOriginWellKnown         = 2,
    IpSuffixOriginDhcp              = 3,
    IpSuffixOriginLinkLayerAddress  = 4,
    IpSuffixOriginRandom            = 5,
    IpSuffixOriginUnchanged         = 8
} NL_SUFFIX_ORIGIN;

/* Network layer DAD states */
typedef enum {
    NldsInvalid             = 0,
    NldsTentative           = 1,
    NldsDuplicate           = 2,
    NldsDeprecated          = 3,
    NldsPreferred           = 4,
    IpDadStateInvalid       = 0,
    IpDadStateTentative     = 1,
    IpDadStateDuplicate     = 2,
    IpDadStateDeprecated    = 3,
    IpDadStatePreferred     = 4
} NL_DAD_STATE;

/* Network layer route protocols */
typedef enum {
    RouteProtocolOther      = 1,
    RouteProtocolLocal      = 2,
    RouteProtocolNetMgmt    = 3,
    RouteProtocolIcmp       = 4,
    RouteProtocolEgp        = 5,
    RouteProtocolGgp        = 6,
    RouteProtocolHello      = 7,
    RouteProtocolRip        = 8,
    RouteProtocolIsIs       = 9,
    RouteProtocolEsIs       = 10,
    RouteProtocolCisco      = 11,
    RouteProtocolBbn        = 12,
    RouteProtocolOspf       = 13,
    RouteProtocolBgp        = 14,
    MAKE_ROUTE_PROTOCOL( OTHER, 1 ),
    MAKE_ROUTE_PROTOCOL( LOCAL, 2 ),
    MAKE_ROUTE_PROTOCOL( NETMGMT, 3 ),
    MAKE_ROUTE_PROTOCOL( ICMP, 4 ),
    MAKE_ROUTE_PROTOCOL( EGP, 5 ),
    MAKE_ROUTE_PROTOCOL( GGP, 6 ),
    MAKE_ROUTE_PROTOCOL( HELLO, 7 ),
    MAKE_ROUTE_PROTOCOL( RIP, 8 ),
    MAKE_ROUTE_PROTOCOL( IS_IS, 9 ),
    MAKE_ROUTE_PROTOCOL( ES_IS, 10 ),
    MAKE_ROUTE_PROTOCOL( CISCO, 11 ),
    MAKE_ROUTE_PROTOCOL( BBN, 12 ),
    MAKE_ROUTE_PROTOCOL( OSPF, 13 ),
    MAKE_ROUTE_PROTOCOL( BGP, 14 ),
    MAKE_ROUTE_PROTOCOL( NT_AUTOSTATIC, 10002 ),
    MAKE_ROUTE_PROTOCOL( NT_STATIC, 10006 ),
    MAKE_ROUTE_PROTOCOL( NT_STATIC_NON_DOD, 10007 )
} NL_ROUTE_PROTOCOL;
typedef NL_ROUTE_PROTOCOL   *PNL_ROUTE_PROTOCOL;

/* Network layer address types */
typedef enum {
    NlatUnspecified = 0,
    NlatUnicast     = 1,
    NlatAnycast     = 2,
    NlatMulticast   = 3,
    NlatBroadcast   = 4,
    NlatInvalid     = 5
} NL_ADDRESS_TYPE;
typedef NL_ADDRESS_TYPE *PNL_ADDRESS_TYPE;

/* Network layer route origins */
typedef enum _NL_ROUTE_ORIGIN {
    NlroManual              = 0,
    NlroWellKnown           = 1,
    NlroDHCP                = 2,
    NlroRouterAdvertisement = 3,
    Nlro6to4                = 4
} NL_ROUTE_ORIGIN;
typedef NL_ROUTE_ORIGIN *PNL_ROUTE_ORIGIN;

/* Network layer neighbor states */
typedef enum _NL_NEIGHBOR_STATE {
    NlnsUnreachable = 0,
    NlnsIncomplete  = 1,
    NlnsProbe       = 2,
    NlnsDelay       = 3,
    NlnsStale       = 4,
    NlnsReachable   = 5,
    NlnsPermanent   = 6,
    NlnsMaximum     = 7
} NL_NEIGHBOR_STATE;
typedef NL_NEIGHBOR_STATE   *PNL_NEIGHBOR_STATE;

/* Network layer link local address behaviors */
typedef enum _NL_LINK_LOCAL_ADDRESS_BEHAVIOR {
    LinkLocalAlwaysOff  = 0,
    LinkLocalDelayed    = 1,
    LinkLocalAlwaysOn   = 2,
    LinkLocalUnchanged  = -1
} NL_LINK_LOCAL_ADDRESS_BEHAVIOR;

/* Network layer interface offload rod */
typedef struct _NL_INTERFACE_OFFLOAD_ROD {
    BOOLEAN NlChecksumSupported         : 1;
    BOOLEAN NlOptionsSupported          : 1;
    BOOLEAN TlDatagramChecksumSupported : 1;
    BOOLEAN TlStreamChecksumSupported   : 1;
    BOOLEAN TlStreamOptionsSupported    : 1;
    BOOLEAN FastPathCompatible          : 1;
    BOOLEAN TlLargeSendOffloadSupported : 1;
    BOOLEAN TlGiantSendOffloadSupported : 1;
} NL_INTERFACE_OFFLOAD_ROD;
typedef NL_INTERFACE_OFFLOAD_ROD    *PNL_INTERFACE_OFFLOAD_ROD;

/* Network layer router discovery behaviors */
typedef enum _NL_ROUTER_DISCOVERY_BEHAVIOR {
    RouterDiscoveryDisabled     = 0,
    RouterDiscoveryEnabled      = 1,
    RouterDiscoveryDhcp         = 2,
    RouterDiscoveryUnchanged    = -1
} NL_ROUTER_DISCOVERY_BEHAVIOR;

/* Network layer bandwidth flags */
typedef enum _NL_BANDWIDTH_FLAG {
    NlbwDisabled    = 0,
    NlbwEnabled     = 1,
    NlbwUnchanged   = -1
} NL_BANDWIDTH_FLAG;
typedef NL_BANDWIDTH_FLAG   *PNL_BANDWIDTH_FLAG;

/* Network layer path bandwidth rod */
typedef struct _NL_PATH_BANDWIDTH_ROD {
    ULONG64 Bandwidth;
    ULONG64 Instability;
    BOOLEAN BandwidthPeaked;
} NL_PATH_BANDWIDTH_ROD;
typedef NL_PATH_BANDWIDTH_ROD   *PNL_PATH_BANDWIDTH_ROD;

/* Network layer network categories */
typedef enum _NL_NETWORK_CATEGORY {
    NetworkCategoryPublic               = 0,
    NetworkCategoryPrivate              = 1,
    NetworkCategoryDomainAuthenticated  = 2,
    NetworkCategoryUnchanged            = -1,
    NetworkCategoryUnknown              = -1
} NL_NETWORK_CATEGORY;
typedef NL_NETWORK_CATEGORY *PNL_NETWORK_CATEGORY;

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _NLDEF_ */
