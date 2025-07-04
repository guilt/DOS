/*------------------------------------------------------------------------*/
/*                                                                        */
/*  STREAMBL.H                                                            */
/*                                                                        */
/*  Copyright (c) 1992, 1994 Borland International                        */
/*  All Rights Reserved                                                   */
/*                                                                        */
/*  Class definitions for object streaming                                */
/*                                                                        */
/*                                                                        */
/*                 +----------------+  +-------------+                    */
/*                 |TStreamableTypes|  |ObjectBuilder|                    */
/*                 +--+----------+--+  +-------------+                    */
/*                    |class name|     |  BUILDER    |                    */
/*                    +----------+     |  delta      |                    */
/*                          |          +-------------+                    */
/*                          |                 |                           */
/*                          |                /\                           */
/*                          |         +--------                           */
/*                          |         |                                   */
/*                          |         |                                   */
/*                        +----------------+                              */
/*                        |TStreamableClass|                              */
/*                        +----------------+                              */
/*                        |  Module ID     |                              */
/*                        +----------------+                              */
/*                                                                        */
/*------------------------------------------------------------------------*/

#if !defined( CLASSLIB_STREAMBL_H )
#define CLASSLIB_STREAMBL_H

#if !defined( __STRING_H )
#include <string.h>
#endif

#if !defined( CLASSLIB_DEFS_H )
#include <classlib/defs.h>
#endif

#if defined(_FASTTHIS)
#  define _BIDSFASTTHIS __fastthis
#else
#  define _BIDSFASTTHIS
#endif

#if !defined( CLASSLIB_VECTIMP_H )
#include "classlib\vectimp.h"
#endif

#if defined( BI_CLASSLIB_NO_po )
#pragma option -po-
#endif

#if defined( BI_PLAT_MSW ) && !defined( __WINDOWS_H )
#include <windows.h>
#endif

#if defined( BI_NO_PER_INSTANCE_DATA ) && defined(_BIDSDLL)

extern HINSTANCE _hInstance;
typedef unsigned ModuleId;
inline ModuleId GetModuleId() { return (unsigned)_hInstance; }

#else

typedef unsigned ModuleId;
inline ModuleId GetModuleId() { return 1; }

#endif

class _BIDSCLASS _BIDSFASTTHIS _RTTI TStreamer;
class _BIDSCLASS _BIDSFASTTHIS _RTTI TStreamableBase;

typedef TStreamer *(* BUILDER)( TStreamableBase * );

struct _BIDSCLASS ObjectBuilder
{

    enum { NoDelta = -1 };

    _BIDSENTRY ObjectBuilder( BUILDER b, int d ) : Builder( b ), Delta( d )
    {
    }

    BUILDER Builder;
    int Delta;

};

#define __DELTA( d ) (FP_OFF((TStreamable *)(d *)1)-1)

class _BIDSCLASS TStreamableClass : public ObjectBuilder
{

public:

    _BIDSENTRY TStreamableClass( const char *n, 
                             BUILDER b, 
                             int d = NoDelta,
                             ModuleId mid = GetModuleId() );

    _BIDSENTRY ~TStreamableClass();

    int _BIDSENTRY operator == ( const TStreamableClass& n ) const
        {
        if( strcmp( ObjectId, n.ObjectId ) != 0 )
            return 0;
        else
            return (ModId == 0 || n.ModId == 0 || ModId == n.ModId);
        }

    int _BIDSENTRY operator < ( const TStreamableClass& n ) const
        {
        int res = strcmp( ObjectId, n.ObjectId );
        if( res < 0 )
            return 1;
        else if( res > 0 )
            return 0;
        else if( ModId == 0 || n.ModId == 0 || ModId == n.ModId )
            return 0;
        else
            return ModId < n.ModId;
        }

private:

    const char *ObjectId;
    ModuleId ModId;

};

class _BIDSCLASS TStreamableTypes
{

public:

    _BIDSENTRY TStreamableTypes() : Types( 5, 5 ) {}

    void _BIDSENTRY RegisterType( ModuleId id, TStreamableClass& );
    void _BIDSENTRY UnRegisterType( ModuleId id, TStreamableClass& );
    const ObjectBuilder * _BIDSENTRY Lookup( ModuleId id,
                                         const char *name ) const;

private:

    TISVectorImp< TStreamableClass > Types;

};

#if defined( BI_CLASSLIB_NO_po )
#pragma option -po.
#endif

#endif  // CLASSLIB_STREAMBLE_H

