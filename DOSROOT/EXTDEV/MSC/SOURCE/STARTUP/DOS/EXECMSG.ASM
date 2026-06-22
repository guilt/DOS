	page	,132
	title	execmsg.asm - exec messages
;***
;execmsg.asm - exec error messages
;
;	Copyright (c) 1987-1992, Microsoft Corporation.  All rights reserved.
;
;Purpose:
;	error messages used with exec*() library functions
;	(and spawn*() functions with P_OVERLAY).
;
;*******************************************************************************

?DF=	1			; this is special to define segments
include version.inc
.xlist
include cmacros.inc
include defsegs.inc
include rterr.inc
.list

CrtDefSegs  <nmsg>

public	__execmsg
__execmsg= 9876h

;	Messages used by doexec.asm

sBegin	nmsg
assumes ds,data

;
;	WARNING - Doexec.asm expects these three messages to be together
;		  these messages must always have '$' on the end
;		  (the _RTERR macrotakes care of this).


_RTERR	_RT_EXECMEM, _RT_EXECMEM_TXT, _RT_DOLLAR	; 'not enough memory on exec'
_RTERR	_RT_EXECFORM, _RT_EXECFORM_TXT, _RT_DOLLAR	; 'invalid format on exec'
_RTERR	_RT_EXECENV, _RT_EXECENV_TXT, _RT_DOLLAR	; 'invalid environment on exec'

sEnd

sBegin	npad
assumes ds,data
	dw	-1
; no padding for now;
; MAX padding would be
;	db	72 dup(0)
sEnd

	end
