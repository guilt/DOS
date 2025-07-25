/*------------------------------------------------------------------------*/
/*                                                                        */
/*  CHECKS.H                                                              */
/*                                                                        */
/*                                                                        */
/*------------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 6.5
 *
 *      Copyright (c) 1992, 1994 by Borland International
 *      All Rights Reserved.
 *
 */

#ifndef __cplusplus
#error Must use C++ for CHECKS.H
#endif

#if !defined( __CHECKS_H )
#define __CHECKS_H

#if !defined( __DEFS_H )
#include <_defs.h>
#endif  // __DEFS_H

#if !defined( __CSTRING_H )
#include <cstring.h>
#endif   // __CSTRING_H

#if !defined(__EXCEPT_H)
#include <except.h>
#endif   // __EXCEPT_H

#include <systypes.h>
#include <strstrea.h>


#if !defined(RC_INVOKED)

#if defined(__BCOPT__)
#if !defined(_RTL_ALLOW_po) && !defined(__FLAT__)
#pragma option -po-     // disable Object data calling convention
#endif
#endif

#pragma option -Vo-

#if defined(__STDC__)
#pragma warn -nak
#endif

#endif  /* !RC_INVOKED */


//
// TDiagBase - this class forms the base for TDiagGroup classes and
// handles basic message output.
//
class _EXPCLASS TDiagBase
{
public:
    static ostrstream Out;
protected:
    static void _RTLENTRY Trace( const char *group, const char *msg,
                       const char *fname, uint32 line );
    static void _RTLENTRY Warn( const char *group, const char *msg,
                      const char *fname, uint32 line );
    struct Flags
    {
        uint8 Enabled : 1;
        uint8 Level   : 7;
    };

private:
    static void _RTLENTRY Message( const char *type,
                         const char *group, const char *msg,
                         const char *fname, uint32 line );
    static void _RTLENTRY Output( const char *msg );
};


class _EXPCLASS xerror : public xmsg
{
public:
     _RTLENTRY xerror( const char *type,
             const char *txt,
             const char *file,
             uint32 line ) :
             xmsg( MakeString(type,txt,file,line) ) {}
private:
    static string _RTLENTRY MakeString( const char *type,
                         const char *txt,
                       const char *file,
                       uint32 line );
};

class precondition : public xerror
{
public:
     _RTLENTRY precondition( const char *txt,
                  const char *file,
                  uint32 line ) : xerror( "Precondition", txt, file, line )
                  {
                        }
};

class check : public xerror
{
public:
    _RTLENTRY check( const char *txt,
           const char *file,
              uint32 line ) : xerror( "Check", txt, file, line )
           {
              }
};


#if !defined(RC_INVOKED)

#if defined(__STDC__)
#pragma warn .nak
#endif

#pragma option -Vo.

#if defined(__BCOPT__)
#if !defined(_RTL_ALLOW_po) && !defined(__FLAT__)
#pragma option -po.     // restore Object data calling convention
#endif
#endif

#endif  /* !RC_INVOKED */


#endif  // __CHECKS_H


#if !defined( __DEBUG )
#define __DEBUG 0
#endif

#undef PRECONDITION
#undef PRECONDITIONX

#define PRECONDITION(p) PRECONDITIONX(p,#p)

#if __DEBUG < 1
#define PRECONDITIONX(p,s)   ((void)0)
#else
#define PRECONDITIONX(p,s)   \
    if(!(p)) {throw precondition(s,__FILE__,__LINE__);}
#endif

#undef CHECK
#undef CHECKX

#define CHECK(p) CHECKX(p,#p)

#if __DEBUG < 2
#define CHECKX(p,s)    ((void)0)
#else
#define CHECKX(p,s)   \
    if(!(p)) {throw check(s,__FILE__,__LINE__);}
#endif

#if defined(__TRACE) || defined(__WARN)

#if defined( __RTLDLL ) || defined( _BUILDRTLDLL )
#if defined(__OS2__)    
#define DIAG_IMPORT
#else    
#define DIAG_IMPORT __import
#endif    
#define DIAG_EXPORT __export
#else
#define DIAG_IMPORT
#define DIAG_EXPORT
#endif

#define DECLARE_DIAG_GROUP(g,qual)                                         \
class qual TDiagGroup##g : private TDiagBase                               \
{                                                                          \
public:                                                                    \
    static void _RTLENTRY Trace( uint8 level, const char *msg,             \
                       const char *fname, uint32 line );                   \
                                                                           \
    static void _RTLENTRY Warn( uint8 level, const char *msg,              \
                      const char *fname, uint32 line );                    \
                                                                           \
    static void _RTLENTRY Enable(uint8 enabled)                            \
                    { Flags.Enabled = uint8(enabled ? 1 : 0); }            \
    static int  _RTLENTRY IsEnabled() { return Flags.Enabled; }            \
                                                                           \
    static void  _RTLENTRY SetLevel( uint8 level ) { Flags.Level = level; }\
    static uint8 _RTLENTRY GetLevel() { return Flags.Level; }              \
                                                                           \
private:                                                                   \
     static Flags Flags;                                                   \
     static char *Name;                                                    \
}

#define DIAG_DECLARE_GROUP(g)                                              \
DECLARE_DIAG_GROUP(g,DIAG_IMPORT);

#define DIAG_DEFINE_GROUP(g,e,l)                                           \
DECLARE_DIAG_GROUP(g,DIAG_EXPORT);                                         \
void _RTLENTRY TDiagGroup##g::Trace( uint8 level, const char *msg,         \
                                    const char *fname, uint32 line )       \
{                                                                          \
     if( IsEnabled() && level <= GetLevel() )                              \
          TDiagBase::Trace( Name, msg, fname, line );                      \
}                                                                          \
                                                                           \
void _RTLENTRY TDiagGroup##g::Warn( uint8 level, const char *msg,          \
                                  const char *fname, uint32 line )         \
{                                                                          \
     if( IsEnabled() && level <= GetLevel() )                              \
          TDiagBase::Warn( Name, msg, fname, line );                       \
}                                                                          \
                                                                           \
char *TDiagGroup##g::Name = #g;                                            \
TDiagBase::Flags TDiagGroup##g::Flags = { (e), (l) }

#define DIAG_ENABLE(g,s)            TDiagGroup##g::Enable(s)
#define DIAG_ISENABLED(g)           TDiagGroup##g::IsEnabled()
#define DIAG_SETLEVEL(g,l)          TDiagGroup##g::SetLevel(l)
#define DIAG_GETLEVEL(g)            TDiagGroup##g::GetLevel()

#if !defined(_BUILD_CHECKS) && !defined( _DEF_DECLARED )
#define _DEF_DECLARED
DECLARE_DIAG_GROUP(Def, _EXPCLASS);
#endif

#else   // !defined(__TRACE) && !defined(__WARN)

#define DIAG_DECLARE_GROUP(g)
#define DIAG_DEFINE_GROUP(g,e,l)

#define DIAG_ENABLE(g,s)            ((void)0)
#define DIAG_ISENABLED(g)           ((void)0)
#define DIAG_SETLEVEL(g,l)          ((void)0)
#define DIAG_GETLEVEL(g)            ((void)0)

#endif

#if defined(__TRACE)
    #define TRACE(m)                    TRACEX(Def,0,m)
    #define TRACEX(g,l,m)\
            {\
                TDiagBase::Out.seekp(0,ostream::beg);\
                TDiagBase::Out << m << ends;\
                TDiagGroup##g::Trace(l,TDiagBase::Out.str(),__FILE__,__LINE__);\
            }
#else
    #define TRACE(m)                    ((void)0)
    #define TRACEX(g,l,m)               ((void)0)
#endif

#if defined(__WARN)
    #define WARN(c,m)                   WARNX(Def,c,0,m)
    #define WARNX(g,c,l,m)\
            if(c)\
            {\
                TDiagBase::Out.seekp(0,ostream::beg);\
                TDiagBase::Out << m << ends;\
                TDiagGroup##g::Warn(l,TDiagBase::Out.str(),__FILE__,__LINE__);\
            }
#else
    #define WARN(c,m)                   ((void)0)
    #define WARNX(g,c,l,m)              ((void)0)
#endif

