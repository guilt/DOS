/*
 *  rexxsaa.h   OS/2 REXX programming interface include file.
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

#ifndef __REXXSAA_H__
#define __REXXSAA_H__

#ifndef _ENABLE_AUTODEPEND
 #pragma read_only_file
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifndef OS2_INCLUDED
#include <os2.h>
#endif

#if (defined(__IBMC__) || defined(__WATCOMC__)) && !defined(REXX_NODEFLIB)
#pragma library("rexx.lib")
#endif

#define RXCOMMAND    0
#define RXSUBROUTINE 1
#define RXFUNCTION   2

#define RXAUTOBUFLEN 256

#define RXFUNC_DYNALINK  1
#define RXFUNC_CALLENTRY 2

#define RXFUNC_OK         0
#define RXFUNC_DEFINED   10
#define RXFUNC_NOMEM     20
#define RXFUNC_NOTREG    30
#define RXFUNC_MODNOTFND 40
#define RXFUNC_ENTNOTFND 50
#define RXFUNC_NOTINIT   60
#define RXFUNC_BADTYPE   70

#define RXSUBCOM_DROPPABLE 0
#define RXSUBCOM_NONDROP   1

#define RXSUBCOM_OK          0
#define RXSUBCOM_ISREG       1
#define RXSUBCOM_ERROR       1
#define RXSUBCOM_FAILURE     2
#define RXSUBCOM_DUP        10
#define RXSUBCOM_MAXREG     20
#define RXSUBCOM_NOTREG     30
#define RXSUBCOM_NOCANDROP  40
#define RXSUBCOM_LOADERR    50
#define RXSUBCOM_NOPROC    127
#define RXSUBCOM_BADENTRY 1001
#define RXSUBCOM_NOEMEM   1002
#define RXSUBCOM_BADTYPE  1003
#define RXSUBCOM_NOTINIT  1004

#define RXARI_OK                   0
#define RXARI_NOT_FOUND            1
#define RXARI_PROCESSING_ERROR     2

#define RXMACRO_SEARCH_BEFORE      1
#define RXMACRO_SEARCH_AFTER       2
#define RXMACRO_OK                 0
#define RXMACRO_NO_STORAGE         1
#define RXMACRO_NOT_FOUND          2
#define RXMACRO_EXTENSION_REQUIRED 3
#define RXMACRO_ALREADY_EXISTS     4
#define RXMACRO_FILE_ERROR         5
#define RXMACRO_SIGNATURE_ERROR    6
#define RXMACRO_SOURCE_NOT_FOUND   7
#define RXMACRO_INVALID_POSITION   8
#define RXMACRO_NOT_INIT           9

#define RXENDLST 0
#define RXFNC    2
#define RXFNCCAL 1
#define RXCMD    3
#define RXCMDHST 1
#define RXMSQ    4
#define RXMSQPLL 1
#define RXMSQPSH 2
#define RXMSQSIZ 3
#define RXMSQNAM 20
#define RXSIO    5
#define RXSIOSAY 1
#define RXSIOTRC 2
#define RXSIOTRD 3
#define RXSIODTR 4
#define RXSIOTLL 5
#define RXHLT    7
#define RXHLTCLR 1
#define RXHLTTST 2
#define RXTRC    8
#define RXTRCTST 1
#define RXINI    9
#define RXINIEXT 1
#define RXTER    10
#define RXTEREXT 1
#define RXNOOFEXITS 11

#define RXSHV_SET   0
#define RXSHV_FETCH 1
#define RXSHV_DROPV 2
#define RXSHV_SYSET 3
#define RXSHV_SYFET 4
#define RXSHV_SYDRO 5
#define RXSHV_NEXTV 6
#define RXSHV_PRIV  7
#define RXSHV_EXIT  8
#define RXSHV_NOAVL 144

#define RXSHV_OK    0x00
#define RXSHV_NEWV  0x01
#define RXSHV_LVAR  0x02
#define RXSHV_TRUNC 0x04
#define RXSHV_BADN  0x08
#define RXSHV_MEMFL 0x10
#define RXSHV_BADF  0x80

#define MAKERXSTRING(r,p,l) {(r).strptr=(PCH)p;(r).strlength=(ULONG)l;}
#define RXNULLSTRING(r)     (!(r).strptr)
#define RXSTRLEN(r)         (RXNULLSTRING(r)?0L:(r).strlength)
#define RXSTRPTR(r)         (r).strptr
#define RXVALIDSTRING(r)    ((r).strptr && (r).strlength)
#define RXZEROLENSTRING(r)  ((r).strptr && !(r).strlength)

#define RXEXIT_HANDLED       0
#define RXEXIT_NOT_HANDLED   1
#define RXEXIT_RAISE_ERROR (-1)

#define RXEXIT_DROPPABLE     0x00
#define RXEXIT_NONDROP       0x01

#define RXEXIT_ISREG         1
#define RXEXIT_ERROR         1
#define RXEXIT_FAILURE       2
#define RXEXIT_BADENTRY   1001
#define RXEXIT_NOEMEM     1002
#define RXEXIT_BADTYPE    1003
#define RXEXIT_NOTINIT    1004

#define RXEXIT_OK            0
#define RXEXIT_DUP          10
#define RXEXIT_MAXREG       20
#define RXEXIT_NOTREG       30
#define RXEXIT_NOCANDROP    40
#define RXEXIT_LOADERR      50
#define RXEXIT_NOPROC      127

#define REXXSTART               RexxStart
#define REXXREGISTERSUBCOMDLL   RexxRegisterSubcomDll
#define REXXREGISTERSUBCOMEXE   RexxRegisterSubcomExe
#define REXXQUERYSUBCOM         RexxQuerySubcom
#define REXXDEREGISTERSUBCOM    RexxDeregisterSubcom
#define REXXVARIABLEPOOL        RexxVariablePool
#define REXXREGISTERFUNCTIONDLL RexxRegisterFunctionDll
#define REXXREGISTERFUNCTIONEXE RexxRegisterFunctionExe
#define REXXDEREGISTERFUNCTION  RexxDeregisterFunction
#define REXXQUERYFUNCTION       RexxQueryFunction
#define REXXREGISTEREXITDLL     RexxRegisterExitDll
#define REXXREGISTEREXITEXE     RexxRegisterExitExe
#define REXXDEREGISTEREXIT      RexxDeregisterExit
#define REXXSETHALT             RexxSetHalt
#define REXXQUERYEXIT           RexxQueryExit
#define REXXSETTRACE            RexxSetTrace
#define REXXRESETTRACE          RexxResetTrace
#define REXXADDMACRO            RexxAddMacro
#define REXXDROPMACRO           RexxDropMacro
#define REXXSAVEMACROSPACE      RexxSaveMacroSpace
#define REXXLOADMACROSPACE      RexxLoadMacroSpace
#define REXXQUERYMACRO          RexxQueryMacro
#define REXXREORDERMACRO        RexxReorderMacro
#define REXXCLEARMACROSPACE     RexxClearMacroSpace

typedef PUCHAR PEXIT;

typedef struct {
    ULONG strlength;
    PCH   strptr;
} RXSTRING, *PRXSTRING;

typedef struct _SHVBLOCK {
    struct _SHVBLOCK *shvnext;
    RXSTRING         shvname;
    RXSTRING         shvvalue;
    ULONG            shvnamelen;
    ULONG            shvvaluelen;
    UCHAR            shvcode;
    UCHAR            shvret;
} SHVBLOCK, *PSHVBLOCK;

typedef struct _RXSYSEXIT {
    PSZ  sysexit_name;
    LONG sysexit_code;
} RXSYSEXIT, *PRXSYSEXIT;

typedef struct _RXSIOSAY_PARM {
    RXSTRING rxsio_string;
} RXSIOSAY_PARM;

typedef struct _RXSIOTRC_PARM {
    RXSTRING rxsio_string;
} RXSIOTRC_PARM;

typedef struct _RXSIOTRD_PARM {
    RXSTRING rxsiotrd_retc;
} RXSIOTRD_PARM;

typedef struct _RXSIODTR_PARM {
    RXSTRING rxsiodtr_retc;
} RXSIODTR_PARM;

typedef struct _RXMSQSIZ_PARM {
    ULONG rxmsq_size;
} RXMSQSIZ_PARM;

typedef struct _RXMSQNAM_PARM {
    RXSTRING rxmsq_name;
} RXMSQNAM_PARM;

typedef struct _RXHLT_FLAGS {
    unsigned rxfhhalt:1;
} RXHLT_FLAGS;

typedef struct _RXHLTTST_PARM {
    RXHLT_FLAGS rxhlt_flags;
} RXHLTTST_PARM;

typedef struct _RXTRC_FLAGS {
    unsigned rxftrace:1;
} RXTRC_FLAGS;

typedef struct _RXTRCTST_PARM {
    RXTRC_FLAGS rxtrc_flags;
} RXTRCTST_PARM;

typedef struct _RXMSQPLL_PARM {
    RXSTRING     rxmsq_retc;
} RXMSQPLL_PARM;

#pragma pack( __push, 1 )

typedef struct _RXFNC_FLAGS {
    unsigned rxfferr :1;
    unsigned rxffnfnd:1;
    unsigned rxffsub :1;
} RXFNC_FLAGS;

typedef struct _RXFNCCAL_PARM {
    RXFNC_FLAGS rxfnc_flags;
    PUCHAR      rxfnc_name;
    USHORT      rxfnc_namel;
    PUCHAR      rxfnc_que;
    USHORT      rxfnc_quel;
    USHORT      rxfnc_argc;
    PRXSTRING   rxfnc_argv;
    RXSTRING    rxfnc_retc;
} RXFNCCAL_PARM;

typedef struct _RXCMD_FLAGS {
    unsigned rxfcfail:1;
    unsigned rxfcerr :1;
} RXCMD_FLAGS;

typedef struct _RXCMDHST_PARM {
    RXCMD_FLAGS rxcmd_flags;
    PUCHAR      rxcmd_address;
    USHORT      rxcmd_addressl;
    PUCHAR      rxcmd_dll;
    USHORT      rxcmd_dll_len;
    RXSTRING    rxcmd_command;
    RXSTRING    rxcmd_retc;
} RXCMDHST_PARM;

typedef struct _RXMSQ_FLAGS {
    unsigned rxfmlifo:1;
} RXMSQ_FLAGS;

typedef struct _RXMSQPSH_PARM {
    RXMSQ_FLAGS rxmsq_flags;
    RXSTRING    rxmsq_value;
} RXMSQPSH_PARM;

#pragma pack( __pop )

typedef LONG APIENTRY  RexxExitHandler(LONG,LONG,PEXIT);
typedef ULONG APIENTRY RexxSubcomHandler(PRXSTRING,PUSHORT,PRXSTRING);
typedef ULONG APIENTRY RexxFunctionHandler(PUCHAR,ULONG,PRXSTRING,PSZ,PRXSTRING);

APIRET APIENTRY RexxDeregisterExit(PCSZ,PCSZ);
APIRET APIENTRY RexxDeregisterFunction(PCSZ);
APIRET APIENTRY RexxDeregisterSubcom(PCSZ,PCSZ);
APIRET APIENTRY RexxQueryFunction(PCSZ);
APIRET APIENTRY RexxQuerySubcom(PCSZ,PCSZ,PUSHORT,PUCHAR);
APIRET APIENTRY RexxQueryExit(PCSZ,PCSZ,PUSHORT,PUCHAR);
APIRET APIENTRY RexxRegisterExitExe(PCSZ,PFN,PUCHAR);
APIRET APIENTRY RexxRegisterExitDll(PCSZ,PCSZ,PCSZ,PUCHAR,ULONG);
APIRET APIENTRY RexxRegisterFunctionDll(PCSZ,PCSZ,PCSZ);
APIRET APIENTRY RexxRegisterFunctionExe(PCSZ,PFN);
APIRET APIENTRY RexxClearMacroSpace(VOID);
APIRET APIENTRY RexxReorderMacro(PCSZ,ULONG);
APIRET APIENTRY RexxQueryMacro(PCSZ,PUSHORT);
APIRET APIENTRY RexxLoadMacroSpace(ULONG,PCSZ *,PCSZ);
APIRET APIENTRY RexxSaveMacroSpace(ULONG,PCSZ *,PCSZ);
APIRET APIENTRY RexxDropMacro(PCSZ);
APIRET APIENTRY RexxAddMacro(PCSZ,PCSZ,ULONG);

APIRET APIENTRY RexxRegisterSubcomDll(PCSZ,PCSZ,PCSZ,PUCHAR,ULONG);
APIRET APIENTRY RexxRegisterSubcomExe(PCSZ,PFN,PUCHAR);
APIRET APIENTRY RexxResetTrace(PID,TID);
APIRET APIENTRY RexxSetHalt(PID,TID);
APIRET APIENTRY RexxSetTrace(PID,TID);

LONG   APIENTRY RexxStart(LONG,PRXSTRING,PCSZ,PRXSTRING,PCSZ,LONG,PRXSYSEXIT,PSHORT,PRXSTRING);
APIRET APIENTRY RexxVariablePool(PSHVBLOCK);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
