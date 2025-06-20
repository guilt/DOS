/*
 *  _pc98.h    PC98 (NEC) support definition.
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
#ifndef _SYS__PC98_H_INCLUDED
#define _SYS__PC98_H_INCLUDED

#ifndef _ENABLE_AUTODEPEND
 #pragma read_only_file
#endif

#if defined(__WATCOM_PC98__)
 #ifdef _M_I86
  #ifdef __MEDIUM__
   #pragma library ( "pc98m" )
  #elif defined(__COMPACT__)
   #pragma library ( "pc98c" )
  #elif defined(__LARGE__)
   #pragma library ( "pc98l" )
  #elif defined(__HUGE__)
   #pragma library ( "pc98h" )
  #else
   #pragma library ( "pc98s" )
  #endif
 #elif defined(__SW_3S)
  #pragma library ( "pc983s" )
 #else
  #pragma library ( "pc983r" )
 #endif
#endif

#endif
