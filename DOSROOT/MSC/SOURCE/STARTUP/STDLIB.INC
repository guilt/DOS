;***
;stdlib.inc - General definitions
;
;	Copyright (c) 1990-1992, Microsoft Corporation. All rights reserved.
;
;Purpose:
;	General definitions of values required by the C runtime.
;	This is roughly analogous to STDLIB.H but not identical.
;
;*******************************************************************************

ifdef _QWIN
; maximum std file handle
_MAX_STDFH   equ     2
endif

;
; Sizes for buffers used by the _makepath() and _splitpath() functions.
; Notes: (1) sizes include space for 0-terminator
;	 (2) values should match those in stdlib.h
;

_MAX_PATH	equ	260	; max. length of full pathname
_MAX_DRIVE	equ	3	; max. length of drive component
_MAX_DIR	equ	256	; max. length of path component
_MAX_FNAME	equ	256	; max. length of file name component
_MAX_EXT	equ	256	; max. length of extension component

;
; OS mode
;

_DOS_MODE      equ	0	; DOS
_OS2_MODE      equ	1	; OS/2
_WIN_MODE      equ	2	; Windows

;
; CPU mode
;

_REAL_MODE     equ	0	; real mode
_PROT_MODE     equ	1	; protect mode
