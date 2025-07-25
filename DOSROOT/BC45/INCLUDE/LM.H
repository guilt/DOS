/*++ BUILD Version: 0001    // Increment this if a change has global effects

Module Name:

    lm.h

Abstract:

    This is the top level include file that includes all the files
    necessary for writing Lan Manager Application.

Author:

    Dan Lafferty (danl) 10-Mar-1991

[Environment:]

    User Mode - Win32

Revision History:

    10-Mar-1991 danl
        Created
    30-Jul-1992 JohnRo
        RAID 2553: lmrepl.h not in public include tree.

--*/

/*
 *      C/C++ Run Time Library - Version 6.5
 *
 *      Copyright (c) 1994 by Borland International
 *      All Rights Reserved.
 *
 */

#ifndef _LM_
#define _LM_
#define __LM_H

#include <lmcons.h>     // LAN Manager common definitions
#include <lmerr.h>      // LAN Manager network error definitions

#include <lmaccess.h>   // Access, Domain, Group and User classes
#include <lmalert.h>    // Alerter
#include <lmchdev.h>    // Character Device and Handle classes
#include <lmshare.h>    // Connection, File, Session and Share classes
#include <lmmsg.h>      // Message class
#include <lmremutl.h>   // Remote Utility class
#include <lmrepl.h>     // Replicator class
#include <lmserver.h>   // Server class
#include <lmsvc.h>      // Service class
#include <lmuse.h>      // Use class
#include <lmwksta.h>    // Workstation class
#include <lmapibuf.h>   // NetApiBuffer class
#include <lmerrlog.h>   // NetErrorLog class
#include <lmconfig.h>   // NetConfig class
#include <lmstats.h>    // NetStats class
#include <lmaudit.h>    // NetAudit class

#endif // _LM_
