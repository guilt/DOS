	page	,132
	title	crt0msg - startup messages
;***
;dos/crt0msg.asm - startup error messages
;
;	Copyright (c) 1985-1992, Microsoft Corporation.  All rights reserved.
;
;Purpose:
;	Core collection of error messages contained in programs
;	which use the C startup code; also contains _FF_MSGBANNER
;	for writing the first portion of run-time error messages.
;
;*******************************************************************************


?DF=		1			; this is special for c startup
include version.inc
.xlist
include cmacros.inc
include cmsgs.inc
include defsegs.inc
include rterr.inc
.list

CrtDefSegs <nmsg>
CrtDefSegs <code,data>


public	__acrtmsg
__acrtmsg=	9876h

;	Messages used by crt0.asm

sBegin	nmsg
assumes ds,data

_RTERR	_RT_STACK, _RT_STACK_TXT, _RT_STANDARD		; 'stack overflow'
_RTERR	_RT_INTDIV, _RT_INTDIV_TXT, _RT_STANDARD	; 'integer divide by 0'

_RTERR	_RT_SPACEENV, _RT_SPACEENV_TXT, _RT_STANDARD	; 'not enough space for environment'

ifdef	_WINDOWS
_RTERR	_RT_HEAP, _RT_HEAP_TXT, _RT_STANDARD		; 'unexpected heap error'
ifdef	_QWIN
_RTERR	_RT_QWIN, _RT_QWIN_TXT, _RT_STANDARD		; 'unexpected QuickWin error'
endif
ifndef	_WINDLL
_RTERR	_RT_SPACEARG, _RT_SPACEARG_TXT, _RT_STANDARD	; 'not enough space for arguments'
_RTERR	_RT_NOMAIN, _RT_NOMAIN_TXT, _RT_STANDARD	; 'no main procedure'
endif
endif	;_WINDOWS

; Special error message entries
_RTERR	_RT_CRNL, _RT_CRNL_TXT, _RT_STRING	; <13,10>
_RTERR	_RT_BANNER, _RT_BANNER_TXT, _RT_STRING	; 'run-time error '

sEnd	nmsg

sBegin	npad
assumes ds,data
	dw	-1
; no padding for now;
; MAX padding would be
;	db	114 dup(0)
sEnd

externP 	_NMSG_WRITE

sBegin	data
	assumes ds,data

globalCP	_adbgmsg,0	; For C, _FF_DBGMSG is inactive, so
				; _adbgmsg is set to null;
				; For FORTRAN, _adbgmsg is set to
				; point to _FF_DBGMSG in dbginit
				; initializer in dbgmsg.asm

sEnd	data


sBegin	code
	assumes cs,code
	assumes ds,data

page
;***
;_FF_MSGBANNER - writes out first part of run-time error messages
;
;Purpose:
;	This routine writes "\r\nrun-time error " to standard error.
;
;	For FORTRAN $DEBUG error messages, it also uses the _FF_DBGMSG
;	routine whose address is stored in the _adbgmsg variable to print out
;	file and line number information associated with the run-time error.
;	If the value of _adbgmsg is found to be null, then the _FF_DBGMSG
;	routine won't be called from here (the case for C-only programs).
;
;Entry:
;	No arguments.
;
;Exit:
;	Nothing returned.
;
;Uses:
;	AX,BX,CX,DX,ES are destroyed.
;
;Exceptions:
;	None handled.
;
;*******************************************************************************

cProc	_FF_MSGBANNER,<PUBLIC>,<>

cBegin

	mov	ax,_RT_CRNL		; "\r\n" to begin error message
	push	ax
	callcrt _NMSG_WRITE

ifndef _WINDOWS
if sizeC
	cmp	word ptr [__adbgmsg+2],0
else					; not needed for C-only version
	cmp	[__adbgmsg],0
endif
	jz	dbgmsg_inactive
	call	[__adbgmsg]		; near or far call as appropriate
dbgmsg_inactive:
endif	;!_WINDOWS

	mov	ax,_RT_BANNER		; run-time error message banner
	push	ax
	callcrt _NMSG_WRITE

cEnd

sEnd	code

	end
