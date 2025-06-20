/*
 *  sys/ptrace.h      ptrace system call functions
 *
 * =========================================================================
 *
 *                          Open Watcom Project
 *
 * Copyright (c) 2004-2025 The Open Watcom Contributors. All Rights Reserved.
 * Portions Copyright (c) 1983-2002 Sybase, Inc. All Rights Reserved.
 *
 *    This file is automatically generated. Do not edit directly.
 *
 * =========================================================================
 */
#ifndef _SYS_PTRACE_H_INCLUDED
#define _SYS_PTRACE_H_INCLUDED

#ifndef _ENABLE_AUTODEPEND
 #pragma read_only_file
#endif

#ifndef __COMDEF_H_INCLUDED
 #include <_comdef.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack( __push, 4 )

/* Type of the REQUEST argument to `ptrace.'  */

#define PTRACE_TRACEME      0   /* Enable tracing for process */
#define PTRACE_PEEKTEXT     1   /* Read text memory in traced process */
#define PTRACE_PEEKDATA     2   /* Read data memory in traced process */
#define PTRACE_PEEKUSER     3   /* Read user area structure (CPU regs etc) */
#define PTRACE_POKETEXT     4   /* Write text memory in traced process */
#define PTRACE_POKEDATA     5   /* Write data memory in traced process */
#define PTRACE_POKEUSER     6   /* Write user area structure (CPU regs etc) */
#define PTRACE_CONT         7   /* Continue the process */
#define PTRACE_KILL         8   /* Kill the process */
#define PTRACE_SINGLESTEP   9   /* Single step the process */
#define PTRACE_GETREGS      12  /* Get all general purpose registers */
#define PTRACE_SETREGS      13  /* Set all general purpose registers */
#define PTRACE_GETFPREGS    14  /* Get all floating point registers */
#define PTRACE_SETFPREGS    15  /* Set all floating point registers */
#define PTRACE_ATTACH       16  /* Attached to running process */
#define PTRACE_DETACH       17  /* Detach from running process */
#define PTRACE_GETFPXREGS   18  /* Get all extended FPU registers */
#define PTRACE_SETFPXREGS   19  /* Set all extended FPU registers */
#define PTRACE_SETOPTIONS   21  /* Set special ptrace options */
#define PTRACE_SYSCALL      24  /* Continue and stop at next syscall */

/* From <asm/ptrace.h> */

/* This struct defines the way the registers are stored on the
 * stack during a system call. Strangely this appear to be missing FS and GS
 * compared to the kernel user structure?
 */
struct pt_regs {
    long    ebx;
    long    ecx;
    long    edx;
    long    esi;
    long    edi;
    long    ebp;
    long    eax;
    int     xds;
    int     xes;
    long    orig_eax;
    long    eip;
    int     xcs;
    long    eflags;
    long    esp;
    int     xss;
};

_WCRTLINK extern long ptrace (int __request, int __pid, void *__addr, void *__data);

#pragma pack( __pop )

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* !_SYS_PTRACE_H_INCLUDED */

