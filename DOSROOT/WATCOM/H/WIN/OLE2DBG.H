/*
 *  ole2dbg.h   Object Linking and Embedding (OLE) 2.0 debugging functions
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

#ifndef __OLE2DBG_H
#define __OLE2DBG_H

#ifndef _ENABLE_AUTODEPEND
 #pragma read_only_file
#endif

/* Functions in OLE2.DLL */
STDAPI_( void ) DbgDumpClassName( IUnknown FAR * );
STDAPI_( void ) DbgDumpExternalObject( IUnknown FAR *, DWORD );
STDAPI_( void ) DbgDumpObject( IUnknown FAR *, DWORD );
STDAPI_( BOOL ) DbgIsObjectValid( IUnknown FAR * );

#endif /* __OLE2DBG_H */
