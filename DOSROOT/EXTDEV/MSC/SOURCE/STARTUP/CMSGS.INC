;***
;cmsgs.inc - defines all C run-time library system messages 
;
;	Copyright (c) 1990-1992, Microsoft Corporation.  All rights reserved.
;
;Purpose:
;	The file defines in one place all literal text strings used within
;	the C run-time library.  Same as cmsgs.h.
;
;*******************************************************************************

;
; fatal run-time error messages
;

_RT_STACK_TXT		EQU <'stack overflow'>
_RT_NULLPTR_TXT		EQU <'null pointer assignment'>
_RT_FLOAT_TXT		EQU <'floating-point support not loaded'>
_RT_INTDIV_TXT		EQU <'integer divide by 0'>

_RT_EXECMEM_TXT		EQU <'not enough memory on exec'>
_RT_EXECFORM_TXT	EQU <'invalid format on exec'>
_RT_EXECENV_TXT		EQU <'invalid environment on exec'>

_RT_SPACEARG_TXT	EQU <'not enough space for arguments'>
_RT_SPACEENV_TXT	EQU <'not enough space for environment'>

ifdef	_WINDOWS
_RT_ABORT_TXT		EQU <'ABNORMAL PROGRAM TERMINATION'>
else
_RT_ABORT_TXT		EQU <"abnormal program termination">
endif	;_WINDOWS

_RT_NPTR_TXT		EQU <'illegal near-pointer use'>
_RT_FPTR_TXT		EQU <'illegal far-pointer use'>

; _RT_BREAK_TXT		EQU <'control-BREAK encountered'>	; QC 1.0 only
; _RT_INT_TXT		EQU <'unexpected interrupt'>		; QC 1.0 only

_RT_THREAD_TXT		EQU <'not enough space for thread data'>
_RT_LOCK_TXT		EQU <'unexpected multithread lock error'>
_RT_HEAP_TXT		EQU <'unexpected heap error'>
_RT_QWIN_TXT		EQU <'unexpected QuickWin error'>
_RT_NOMAIN_TXT		EQU <'no main procedure'>

; special error message entries
_RT_CRNL_TXT		EQU <13,10>
_RT_BANNER_TXT		EQU <'run-time error '>

; max length of any _RT_???_TXT message (includes terminating null char)
_RT_MAXTXTLEN		EQU 34

;
; Definitions that allow caller to strip message out of _RT_STANDARD
; string:
;
; _RT_STANDARD_STARTCHAR = Character that starts an _RT_STANDARD
; error message.
;
; _RT_MATH_STARTCHAR = Character that starts a MATH error message.
;
; _RT_STANDARD_ENDCHAR = Character stored at the end of the string
; portion of an _RT_STANDARD message.
;

_RT_STANDARD_STARTCHAR	equ	<'R'>
_RT_MATH_STARTCHAR	equ	<'M'>
_RT_STANDARD_ENDCHAR	equ	<13>


;
; misc. character constants used throughout C runtime
;

C_LF			EQU 10		; ASCII linefeed character
C_CR			EQU 13		; ASCII carriage return
C_SUB			EQU 26		; ASCII SUB character (^Z)
C_BLANK			EQU ' '		; ASCII space character
C_TAB			EQU 09h		; ASCII horizontal tab character
C_QUOTE			EQU '"'		; ASCII (double) quote charater
C_BACKSLASH		EQU '\'		; ASCII backward slash character
C_EQUALSIGN		EQU <'='>
C_SEMICOLON		EQU <';'>
C_PERIOD		EQU <'.'>

;
; overlay manager message constants:
;

_OVL_MSG0_TXT		EQU <"Incorrect DOS version">
_OVL_MSG1_TXT		EQU <"Please insert diskette containing ">
_OVL_MSG2_TXT		EQU <"in drive ">
_OVL_MSG2A_TXT		EQU <": and strike any key when ready.">
_OVL_MSG3_TXT		EQU <"Please restore original diskette.">
_OVL_MSG3A_TXT		EQU <"Strike any key when ready.">
_OVL_MSG4_TXT		EQU <"Overlay not found">
_OVL_MSG5_TXT		EQU <"Cannot find ">
_OVL_MSG6_TXT		EQU <"Overlay Manager stack overflow">
_OVL_MSG7_TXT		EQU <"Please enter new program spec: ">
_OVL_MSG8_TXT		EQU <"Cannot load overlay:  too many open files">

ifdef _WINDOWS
;
; misc windows strings
;

ifdef _FORTRAN
_WIN_FTITLE_TXT 	EQU <"Unit *",0>
else
_WIN_CTITLE_TXT 	EQU <"Stdin/Stdout/Stderr",0>
endif

endif

;
; Note: the following should not be modified:
;

_OVL_PATH_TXT		EQU <"PATH=">
_OVL_SEGDBG_TXT		EQU <'CVDEBUG'>

_C_FILE_INFO_TXT	EQU <'_C_FILE_INFO'> ; length must be even!
_C_FILE_INFO_LEN	EQU 12		; strlen(_C_FILE_INFO_TXT) 
.errnz _C_FILE_INFO_LEN AND 1		; give error if length not even
