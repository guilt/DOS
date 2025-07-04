/*
 *  rpc.h       Main RPC header file
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

#ifndef RPC_NO_WINDOWS_H
    #include <windows.h>
#endif

#ifndef __RPC_H__
#define __RPC_H__

#ifndef _ENABLE_AUTODEPEND
 #pragma read_only_file
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* RPC primitive data types */
typedef void    *I_RPC_HANDLE;
typedef long    RPC_STATUS;

/* RPC calling conventions */
#define __RPC_API   __stdcall
#define __RPC_USER  __stdcall
#define __RPC_STUB  __stdcall
#define RPC_ENTRY   __stdcall

/* RPC variable attributes */
#define __RPC_FAR

/* Macros to specify RPC functions */
#define RPCRTAPI    DECLSPEC_IMPORT
#define RPCNSAPI    DECLSPEC_IMPORT

/* RPC exception handling macros */
#define RpcEndExcept    }
#define RpcEndFinally   }
#define RpcExcept( x )  } __except( x ) {
#define RpcFinally      } __finally {
#define RpcTryExcept    __try {
#define RpcTryFinally   __try {

/* Functions implemented as macros */
#define RpcAbnormalTermination()    AbnormalTermination()
#define RpcExceptionCode()          GetExceptionCode()

#ifdef __cplusplus
} /* extern "C" */
#endif

#include <rpcdce.h>
#include <rpcnsi.h>
#include <rpcnterr.h>
#include <rpcasync.h>

#endif /* __RPC_H__ */
