	page	,132
	title	nmsghdr - near message handler and finder
;***
;nmsghdr.asm - near message handler and finder
;
;	Copyright (c) 1986-1992, Microsoft Corporation.  All rights reserved.
;
;Purpose:
;	Near message handler and finder.
;
;*******************************************************************************


?DF=	1			; this is special for c startup
include version.inc
?PLM=	1			; pascal calling conventions
.xlist
include cmacros.inc
include msdos.inc
include defsegs.inc
.list

ifndef _WINDOWS
	_DEBUGSCREEN equ 1		; debug screen swapping
endif

;
; segment definitions
;

CrtDefSegs  <code,data>
CrtDefSegs  <nmsg>
CrtDefSegs  <dbdata>

codeOFFSET equ	<offset _TEXT:>
dataOFFSET equ	<offset DGROUP:>

;
; data segments
;

sBegin	nhdr
assumes ds,data

	db	'<<NMSG>>'

stnmsg	label	byte

sEnd

sBegin	npad
assumes ds,data

	dw	-1		; message padding marker

sEnd

sBegin	nepad
assumes ds,data

	db	-1

sEnd

ifdef _QWIN
sBegin	data
assumes ds,data
extrn	__nfile:word		; Maximum number of file handles
extrn	__qwinused:word 	; QWIN used/notused flag
sEnd
endif	; _QWIN

ifdef _DEBUGSCREEN
sBegin	dbdata				;
	assumes ds,data 		; Used to do the running under
externW 	___aDBswpflg		; a debugger screen swapping
externW 	___aDBswpchk		;
sEnd	dbdata				;
	extrn	__aDBdoswp:ABS		;
endif	; _DEBUGSCREEN


;
; external functions
;

ifdef _QWIN
externNP   __wwrite		; Write to QWIN window handle
endif

ifdef	_WINDEBUG
externFP OUTPUTDEBUGSTRING		; debug output call
endif


sBegin	code
assumes cs,code
assumes ds,data

page
;***
;__NMSG_TEXT(messagenumber) - find message for given message number
;
;Purpose:
;	This routine returns a near pointer to the message associated with
;	messagenumber.	If the message does not exist, then a 0 is returned.
;
;	This routine assumes DS = DGROUP
;
;Entry:
;	==PASCAL CALLING CONVENTIONS==
;	messagenumber = WORD message number of desired message
;
;Exit:
;	AX	= pointer to message text or 0 if no message exists.
;
;Uses:
;
;Exceptions:
;
;*******************************************************************************

cProc	__NMSG_TEXT,<PUBLIC>,<si,di>  ; pascal calling

	parmW	msgt

cBegin
	push	ds
	pop	es
	mov	dx,msgt 	; dx = message number
	mov	si,dataOFFSET stnmsg ; start of near messages

tloop:
	lodsw			; ax = current message number
	cmp	ax,dx
	je	found		;   found it - return address
	inc	ax
	xchg	ax,si
	jz	found		;   at end and not found - return 0
	xchg	di,ax
	xor	ax,ax
	mov	cx,-1
	repne	scasb		; skip until 00
	mov	si,di
	jmp	tloop		; try next entry

found:
	xchg	ax,si
cEnd


page
;***
;__NMSGWRITE(messagenumber) - writes message on stderr
;
;Purpose:
;	This routine writes the message associated with messagenumber
;	to stderr.
;
;
ifdef _WINDOWS
;	NOTES:
;
;	(1) _WINDOWS = Only output if under QuickWin (no stderr
;	otherwise).
;
;	(2) _WINDLL = Can't do any output (no stderr).
;
ifdef _WINDEBUG
;	(3) _WINDEBUG = Send output to OUTPUTDEBUGSTRING.  Can't
;	use this for standard libs because that call sends output
;	to AUX port if no debugger present (bogus popup on users
;	screen about attempting to write to AUX).
;
endif	;_WINDEBUG
endif	;_WINDOWS
;
;Entry:
;	==PASCAL CALLING CONVENTIONS==
;	messagenumber = WORD number of desired message
;
;Exit:
;
;Uses:
;
;Exceptions:
;
;*******************************************************************************

cProc	__NMSG_WRITE,<PUBLIC>,<di>  ; pascal calling

	parmW	msgw

cBegin

ifndef _WINDLL

ifdef _QWIN
	cmp	[__qwinused],0	; QWIN enabled ??
	je	nowrite 	; nope, can't write to stderr
endif
	push	msgw
	callcrt __NMSG_TEXT	; find near text pointer
	or	ax,ax
	jz	nowrite 	; don't write anything if not there

	xchg	dx,ax		; ds:dx = string address
	mov	di,dx
	xor	ax,ax
	mov	cx,-1
	repne	scasb		; es = ds from __NMSG_TEXT
	not	cx
	dec	cx		; cx = string length
ifdef _QWIN
	mov	bx,[__nfile]	; bx = __nfile (QWIN std file handle)
	call	__wwrite	; QWIN call
else
	mov	bx,2		; bx = stderr
ifdef _DEBUGSCREEN
	cmp	___aDBswpflg,__aDBdoswp ; Aware debugger as parent?
	jne	@F			; No -- skip
	call	___aDBswpchk		; Yes -- see if we need to swap screens
@@:
endif	; _DEBUGSCREEN

	callos	write		; write to stderr
endif


endif	;!_WINDLL

nowrite:

ifdef _WINDEBUG

	;
	; Put out the message to the system debugger,
	; (message goes to AUX port if no debugger).
	;

	push	msgw
	callcrt __NMSG_TEXT		; find near text pointer
	or	ax,ax
	jz	endwrite		; don't write anything if not there

	push	ds
	push	ax
	call	OUTPUTDEBUGSTRING	; OUTPUTDEBUGSTRING(errormsg)

endwrite:

endif	;_WINDEBUG

cEnd

sEnd

	end
