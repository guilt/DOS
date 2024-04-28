	page	,132
	title	crt0dat - DOS and Windows shared startup and termination
;***
;crt0dat.asm - DOS and Windows shared startup and termination
;
;	Copyright (c) 1985-1992, Microsoft Corporation.  All rights reserved.
;
;Purpose:
;	Shared startup and termination.
;
;	NOTE:  This source is included in crt0.asm for assembly purposes
;	when building .COM startup.  This is so the .COM startup resides
;	in a single special object that can be supplied to the user.
;
;*******************************************************************************

_NFILE_ =	20		; Maximum number of file handles

ifdef _QWIN
_WFILE_ =	20		; Maximum number of QWIN file handles
endif

?DF	=	1		;; tell cmacros.inc we want to define our own segments

.xlist
include version.inc
include cmacros.inc
include msdos.inc
include defsegs.inc
include stdlib.inc
.list

ifndef _WINDOWS
	_DEBUGSCREEN equ 1		; debug screen swapping
endif

ifdef FARSTACK
ife sizeD
error <You cannot have a far stack in Small or Medium memory models.>
endif
endif

ifdef	_COM_
    if sizeC or sizeD
	error <Must use Small memory model for .COM files.>
    endif
endif	;_COM_


CrtDefSegs  <code,cdata,data>

ifdef _DEBUGSCREEN
    CrtDefSegs	<dbdata>
endif	; _DEBUGSCREEN

ifndef _WINDOWS
    CrtDefSegs	<xiqcseg>
endif

    CrtDefSegs	<xifseg,xiseg,xoseg,xofseg,xpseg,xcseg,xcfseg>

    CrtDefSegs	<xifcseg>


ifdef  _COM_
    CrtDefSegs <emdata, emcode>
endif	;_COM_

defGrp	DGROUP			; define DGROUP

codeOFFSET equ	offset _TEXT:
dataOFFSET equ	offset DGROUP:

page


sBegin	xifbseg
xifbegin label	byte		; Far initializers begin/end
sEnd	xifbseg

sBegin	xifeseg
xifend	label	byte
sEnd	xifeseg


sBegin	xibseg
xibegin label	byte		; Initializers begin/end
sEnd	xibseg

sBegin	xieseg
xiend	label	byte
sEnd	xieseg


    sBegin  xifcbseg
    xifcbegin label   byte	; far C++ constructors begin/end
    sEnd    xifcbseg

    sBegin  xifceseg
    xifcend   label   byte
    sEnd    xifceseg


sBegin	xobseg
xontab	label	byte		; atexit/onexit begin/end
sEnd	xobseg

sBegin	xoeseg
xonend	label	byte
sEnd	xoeseg


ife sizeC
    ; in large model _fatexit = atexit so table not needed
    sBegin  xofbseg
    xfontab  label   byte	; far atexit/onexit begin/end
    sEnd    xofbseg

    sBegin  xofeseg
    xfonend  label   byte
    sEnd    xofeseg
endif


sBegin	xpbseg
xpbegin label	byte		; Pre-terminators begin/end
sEnd	xpbseg

sBegin	xpeseg
xpend	label	byte
sEnd	xpeseg


sBegin	xcbseg
xcbegin label	byte		; C terminators begin/end
sEnd	xcbseg

sBegin	xceseg
xcend	label	byte
sEnd	xceseg


sBegin	xcfbseg
xcfbegin label	byte		; C far terminators begin/end
sEnd	xifbseg

sBegin	xcfeseg
xcfend	label	byte
sEnd	xcfeseg


sBegin	cdata			; floating point setup segment
assumes ds,data

	dw	0		; force segment to be at least 0's
labelD	<PUBLIC,_fpinit>	; public for signal
fpmath	dd	1 dup (?)	; linking trick for fp
fpdata	dd	1 dup (?)
fpsignal dd	1 dup (?)	; fp signal message

sEnd


ifdef _DEBUGSCREEN
sBegin	dbdata				;
	assumes ds,data 		; Used to do the running under
externW 	__aDBswpflg		; a debugger screen swapping
externW 	__aDBexit		;
sEnd	dbdata				;
	extrn	__aDBdoswp:ABS		;
endif	; _DEBUGSCREEN

ifndef _WINDOWS
sBegin	xiqcseg
labelW <PUBLIC,__qczrinit>		;* QC -Zr initializer call address
	dw 1 dup(?)
sEnd	xiqcseg
endif


ifdef  _COM_
    sBegin  EmData
    labelB  _EmDataLabel
    sEnd    EmData

    sBegin  EmCode
    globalW _EmDataSeg,0
    sEnd    EmCode

else	;not _COM
  ifndef  _WINDOWS
    EMULATOR_DATA  segment para public 'FAR_DATA'
    EMULATOR_DATA  ends

    EMULATOR_TEXT  segment para public 'CODE'

    public __EmDataSeg
    __EmDataSeg dw  EMULATOR_DATA

    EMULATOR_TEXT  ends
  endif   ;not _WINDOWS
endif	;not _COM_

sBegin	data
assumes ds,data

ifndef _WINDLL
;	special C environment string
	labelB	<PUBLIC,_acfinfo>
	cfile	db	'_C_FILE_INFO='
	cfilex	db	0
	cfileln =	cfilex-cfile
endif	;!_WINDLL

globalD _aintdiv,0		; divide error interrupt vector save

globalT _fac,0			; floating accumulator
globalW errno,0 		; initial error code
globalW _umaskval,0		; initial umask value

ifndef _WINDLL
;=============== following must be in this order

globalW _pspadr,0		; psp:0 (far * to PSP segment)
globalW _psp,0			; psp:0 (paragraph #)

;=============== above must be in this order
endif

;=============== following must be in this order
ifdef _WINDOWS

labelW	<PUBLIC,_osversion>		; WIN version
globalB _osmajor,0
globalB _osminor,0

labelW	<PUBLIC,_dosversion>		; DOS version
globalB _dosmajor,0
globalB _dosminor,0

else	;!_WINDOWS

labelW	<PUBLIC,_osversion>		; OS version
labelB	<PUBLIC,_dosvermajor>
globalB _osmajor,0
labelB	<PUBLIC,_dosverminor>
globalB _osminor,0

endif	;_WINDOWS
;=============== above must be in this order


ifdef _WINDOWS
globalB _osmode,_WIN_MODE	; Windows
globalB _cpumode,_PROT_MODE	; protect mode (default)
else
globalB _osmode,_DOS_MODE	; DOS
globalB _cpumode,_REAL_MODE	; real mode
endif

labelW	<PUBLIC,_oserr>
globalW _doserrno,0		; initial DOS error code

;
; --- I/O Data ---
;

globalW _nfile,_NFILE_			; maximum number of file handles

ifdef _QWIN
globalW _wfile,_WFILE_			; maximum number of QWIN file handles
globalW _wnfile,(_NFILE_+_WFILE_)	; maximum number of total file handles
endif

ifdef _WINDOWS
labelB	<PUBLIC,_osfile>
	db	_NFILE_ dup (0) 	; (no std files in windows)
else
labelB	<PUBLIC,_osfile>
	db	3 dup (FOPEN+FTEXT)	; stdin, stdout, stderr
	db	2 dup (FOPEN)		; stdaux, stdprn
	db	_NFILE_-5 dup (0)	; the other 15 handles
endif	;_WINDOWS

ifdef	_QWIN
labelB	<PUBLIC,_wsfile>
	db	(FOPEN+FTEXT+FDEV)	; stdin/out/err
	db	_WFILE_-1 dup (0)	; the other QWIN handles

; Make sure _osfile and _wsfile are contiguous
.ERRE	offset _osfile+_NFILE_ EQ offset _wsfile
endif	;_QWIN

ifdef _QWIN
;Force in QWIN system
extrn	__qwinused:word 		; QWIN used/notused flag
endif

; --- End I/O Data ---

globalW __argc,0
globalDP __argv,0
globalDP _environ,0		; environment pointer

labelD	<PUBLIC,_pgmptr>	; pointer to program name
	dw	dataOFFSET dos2nam
ifdef _COM_
	dw	0		; No relocations in tiny model
elseifdef _QC2
	dw	0		; No DGROUP references allowed
elseifdef _WINDOWS
	dw	0		; No DGROUP references allowed
else	;DEFAULT
	dw	DGROUP
endif

dos2nam db	0		; dummy argv[0] for DOS 2.X


; signal related common data

globalW _child,0		; flag used to handle signals from child process

ifndef _WINDOWS
;Overlay related data
globalB _ovlflag,0	;Overlay flag (0 = no overlays)
globalB _intno,0	;Overlay interrupt value (e.g., 3F)
globalD _ovlvec,0	;Address of original overlay handler
endif	;!_WINDOWS


globalB _exitflag,0	; callable exit

sEnd	data

page

externNP _fptrap

ifndef	_WINDLL
	externP _cintDIV
endif

ifndef	_WINDOWS
	externP _nullcheck
endif

ifdef  FARSTACK
    ifdef  _WINDOWS
	externP _GetDGROUP
    endif
endif

ifdef _QWIN
	externNP  _wcexit			; exit the QWIN system
endif

ifdef _WINDLL
	extern	__nearstub:near 		; weak extern substitute
	extern	__freefarheap(__nearstub):near	; free up all far heap mem
	extern	__freebasedheap(__nearstub):near; free up all based heap mem
endif

if (_NFILE_ NE 20)
    ifdef _WINDOWS
	extern	SETHANDLECOUNT:far		; set file count
    endif
endif

sBegin	code
assumes cs,code

if	sizeC
global	proc	far
endif

page
;***
;_cinit - C initialization
;
;Purpose:
;	This routine performs the shared DOS and Windows initialization.
;	The following order of initialization must be preserved -
;
;	1.	Integer divide interrupt vector setup
;	2.	Floating point initialization
;	3.	Copy ;C_FILE_INFO into _osfile
;	4.	Check for devices for file handles 0 - 4
;	5.	General C initializer routines
;
;Entry:
;
;Exit:
;
;Uses:
;
;Exceptions:
;
;*******************************************************************************

cProc	_cinit,<PUBLIC>,<>

ifdef	_WINDOWS		; add windows prolog/epilog code to far frames
if	sizeC
cBegin
else
cBegin	<nogen>
endif	;sizeC
else
cBegin	<nogen> 		; no local frame to set up in standard libs
endif	; _WINDOWS

assumes ds,data
ifndef FARSTACK
assumes ss,data
endif

ifdef _COM_
;
;	Initialize the DGROUP portion of _pgmptr.  We must do this at
;	runtime since there are no load-time fixups in .COM files.
;
	mov	word ptr [_pgmptr+2],ds ; init seg portion of _pgmptr
endif	;_COM_


if (_NFILE_ NE 20)
;
;	*** Increase File Handle Count ***
;
ifdef _WINDOWS
	mov	bx,_NFILE_	; number of file handle to allow
	push	bx
	call	SETHANDLECOUNT	; issue the system call
	;check for error here, if desired (AX equals number of files supported)
else
;	This code only works on DOS Version 3.3 and later.
	mov	ah,67h		; system call number
	mov	bx,_NFILE_	; number of file handles to allow
	callos			; issue the system call
	;check for error here, if desired (if carry set, AX equals error code)
endif
;
;	*** End Increase File Handle Count ***
;
endif	; (_NFILE_ NE 20)


ifndef	_WINDLL

;	1.	Integer divide interrupt vector setup

	mov	ax,DOS_getvector shl 8 + 0
	callos			; save divide error interrupt
	mov	word ptr [_aintdiv],bx
	mov	word ptr [_aintdiv+2],es

	push	cs
	pop	ds
	assumes ds,nothing
	mov	ax,DOS_setvector shl 8 + 0
	mov	dx,codeOFFSET _cintDIV
	callos			; set divide error interrupt

ifdef FARSTACK
    ifdef  _WINDOWS
	callcrt _GetDGROUP
	mov	ds, ax
    else
	mov	ax, DGROUP
	mov	ds, ax
    endif
else
	push	ss
	pop	ds		; restore DS=DGROUP
endif
	assumes ds,data

endif	;!_WINDLL


;	2.	Floating point initialization


if  memS

  ifdef  _WINDOWS
	mov	cx,word ptr [fpmath+2]
	jcxz	nofloat_i

  else	  ;not _WINDOWS
	cmp	word ptr [fpmath], 0	    ; Note: make sure offset __fpmath != 0
	je	nofloat_i

	mov	word ptr [fpmath+2], cs     ; fix up these far addresses
	mov	word ptr [fpsignal+2], cs   ; in the small model math libs

    ifdef  _COM_
	mov	[_EmDataSeg], cs
	mov	ax, offset DGROUP:_EmDataLabel
	sub	ax, offset EMULATOR_DATA:_EmDataLabel
	mov	cl, 4
	shr	ax, cl
	add	[_EmDataSeg], ax
    endif   ;_COM_

  endif   ;not _WINDOWS

else	;not memS

	mov	cx,word ptr [fpmath+2]
	jcxz	nofloat_i

endif	;not memS

ifdef	_WINDLL
	xor	si,si		; no environment in Win DLL
else	;!_WINDLL
	mov	es,[_psp]	; psp segment
	mov	si,es:[DOS_ENVP] ; environment segment
endif	;_WINDLL

	mov	ax, word ptr [fpdata]
	mov	dx, word ptr [fpdata+2]
	xor	bx,bx		; (si) = environment segment
	call	[fpmath]	; fpmath(0) - init
	jnc	fpok
	jmp	_fptrap 	; issue "Floating point not loaded"
				; error and abort
fpok:

ifndef _WINDLL

	mov	ax, word ptr [fpsignal]
	mov	dx, word ptr [fpsignal+2]
	mov	bx,3
	call	[fpmath]	; fpmath(3) - set signal address

endif	;!_WINDLL

nofloat_i:



ifndef _WINDLL

;	3.	Copy _C_FILE_INFO= into _osfile

;	fix up files inherited from parent using _C_FILE_INFO=

	mov	es,[_psp]	; es = PSP
	mov	cx,word ptr es:[DOS_envp] ; es = user's environment
	jcxz	nocfi		;   no environment !!!
	mov	es,cx
	xor	di,di		; start at 0

cfilp:
	cmp	byte ptr es:[di],0 ; check for end of environment
	je	nocfi		;   yes - not found
	mov	cx,cfileln
	mov	si,dataOFFSET cfile
	repe	cmpsb		; compare for '_C_FILE_INFO='
	je	gotcfi		;   yes - now do something with it
	mov	cx,07FFFh	; environment max = 32K
	xor	ax,ax
	repne	scasb		; search for end of current string
	jne	nocfi		;   no 00 !!! - assume end of env.
	jmp	cfilp		; keep searching

;	found _C_FILE_INFO= and transfer info into _osfile

gotcfi:
	push	es
	push	ds
	pop	es		; es = DGROUP
	pop	ds		; ds = env. segment
	assumes ds,nothing
	assumes es,data
	mov	si,di		; si = startup of _osfile info
	mov	di,dataOFFSET _osfile ; di = _osfile block

	mov	cl, 4

osfile_lp:
	lodsb
	sub	al, 'A'
	jb	donecfi
	shl	al, cl
	xchg	dx, ax

	lodsb
	sub	al, 'A'
	jb	donecfi
	or	al, dl
	stosb
	jmp	short osfile_lp

donecfi:
ifdef FARSTACK
	push	es
else
	push	ss
endif
	pop	ds		; ds = DGROUP
	assumes ds,data

nocfi:

endif	;!_WINDLL


ifndef _WINDOWS

;	4.	Check for devices for file handles 0 - 4
;
;		Clear the FDEV bit (which might be inherited from C_FILE_INFO)
;		and then call DOS to see if it really is a device or not
;
	mov	bx,4

devloop:
	and	_osfile[bx],not FDEV ; clear FDEV bit on principal

	mov	ax,DOS_ioctl shl 8 + 0 ; issue ioctl(0) to get dev info
	callos
	jc	notdev

	test	dl,80h		; is it a device ?
	jz	notdev		;   no
	or	_osfile[bx],FDEV ;   yes - set FDEV bit

notdev:
	dec	bx
	jns	devloop

endif	;!_WINDOWS


;	5.	General C initializer routines

	mov	si,dataOFFSET xifbegin
	mov	di,dataOFFSET xifend
	call	farinitterm	; call the far initializers

	mov	si,dataOFFSET xibegin
	mov	di,dataOFFSET xiend
	call	initterm	; call the initializers

	mov	si,dataOFFSET xifcbegin
	mov	di,dataOFFSET xifcend
	call	farinitterm	; call far C++ constructors.

ifdef	_WINDOWS	; add epilog code to windows far frame
if	sizeC
cEnd
else
	ret
cEnd	<nogen>
endif	;sizeC
else
	ret
cEnd	<nogen> 	; standard C libs
endif	; _WINDOWS


page
;***
;exit(status), _exit(status), _cexit(void), _c_exit(void) - C termination
;
;Purpose:
;
;	Entry points:
;
;		exit(code):  Performs all the C termination functions
;			and terminates the process with the return code
;			supplied by the user.
;
;		_exit(code):  Performs a quick exit routine that does not
;			do certain 'high-level' exit processing.  The _exit
;			routine terminates the process with the return code
;			supplied by the user.
;
;		_cexit():  Performs the same C lib termination processing
;			as exit(code) but returns control to the caller
;			when done (i.e., does NOT terminate the process).
;
;		_c_exit():  Performs the same C lib termination processing
;			as _exit(code) but returns control to the caller
;			when done (i.e., does NOT terminate the process).
;
;	Termination actions:
;
;		exit(), _cexit ():
;
;		1.	call user's terminator routines
;		2.	call C runtime preterminators
;
;		_exit(), _c_exit():
;
;		3.	call C runtime terminators
;		4.	perform _nullcheck() for null pointer assignment
;		5.	terminate floating point
;		6.	reset divide by zero interrupt vector
;		7.	return to DOS or caller
;
;	Notes:
;
;	The termination sequence is complicated due to the multiple entry
;	points sharing the common code body while having different entry/exit
;	sequences.
;
;Entry:
;	exit(), _exit()
;		int status - exit status (0-255)
;
;	_cexit(), _c_exit()
;		<no input>
;
;Exit:
;	exit(), _exit()
;		<EXIT to DOS>
;
;	_cexit(), _c_exit()
;		Return to caller
;
;Uses:
;
;Exceptions:
;
;*******************************************************************************

ifndef _WINDLL

;
;--- exit(): Full exit and term process ---
;


public	_exit
_exit:
cProc	dummy1,<>,<>

	parmw	status		; termination code

cBegin

	xor	cx,cx		; exit(): cl = 0, ch = 0
	jmp	short common1	; join common code

cEnd	<nogen>

;
;--- _exit(): Quickie exit and term process ---
;


public	__exit
__exit:
cProc	dummy2,<>,<>

	parmw	status		; termination code

cBegin

	mov	cx,1		; _exit(): cl = 1, ch = 0
	jmp	short common1	; join common code

cEnd	<nogen>

endif	;!_WINDLL

if	sizeC
global	endp
endif

;
;--- _cexit(): Full exit and return to caller ---
;

cProc	_cexit,<PUBLIC>,<SI,DI>

cBegin

	mov	cx,(1 SHL 8)	; _cexit(): ch = 1, cl = 0
	jmp	short common1	; join common code

cEnd	<nogen>

;
;--- _c_exit(): Quickie exit and return to caller ---
;

cProc	_c_exit,<PUBLIC>,<SI,DI>

cBegin

	mov	cx,(1 SHL 8)+1	; _c_exit(): ch = 1, cl = 1
	;fall through

;
;--- Common entry point ---
; cx = entry value:
;	cl = full vs quick exit path
;	     0 = exit() code
;	     1 = _exit() code
;	ch = term process vs return to caller
;	     0 = term process
;	     1 = return to caller
;

common1:			; all code paths join here

assumes ds,data
ifndef FARSTACK
assumes ss,data
endif

;
; save exit flag (used by terminators)
;
	mov	[_exitflag],ch

;
; If _exit()/_c_exit(), jump over the initial termination processing
; cx = entry code
;

	push	cx		; save entry code on top of stack
	or	cl,cl		; cl != 0 means _exit()/_c_exit()
	jnz	short common2	; if _exit()/_c_exit(), jump down
	;fall thru		; continue (exit, _cexit)


;	1.	call user terminators
;		(atexit/onexit processing)

	mov	si,dataOFFSET xontab
	mov	di,dataOFFSET xonend
	call	initterm	; atexit/onexit table

ife sizeC
	; in large code, _fatexit = atexit so no need to walk far table
	mov	si,dataOFFSET xfontab
	mov	di,dataOFFSET xfonend
	call	farinitterm	; far atexit/onexit table
endif

;	2.	call C runtime preterminators
;		- flushall
;		- rmtmp

	mov	si,dataOFFSET xpbegin ; beginning of pre-terminators
	mov	di,dataOFFSET xpend ; end of pre-terminators
	call	initterm

ifdef _QWIN
;
; Exit the QWIN system.  We can't do this in the pre-terminators because
; we want to make sure flushall() gets called before _QWINExit.
;
	mov	si,[status]
	push	si
	call	_wcexit
	add	sp,2

endif	;_QWIN

ifdef _DEBUGSCREEN
;
; Tell the debugger we are going to exit
;
	cmp	__aDBswpflg,__aDBdoswp	; Are we under a debugger?
	jne	@F			; No -- skip forward
	cCall	__aDBexit		; Yes -- tell it we are exiting
@@:
endif	; _DEBUGSCREEN

;
;--- Common entry point ---
;

common2:			; __exit() enters here


;	3.	perform C terminators

	mov	si,dataOFFSET xcbegin
	mov	di,dataOFFSET xcend
	call	initterm	; call the terminators

	mov	si,dataOFFSET xcfbegin
	mov	di,dataOFFSET xcfend
	call	farinitterm	; call the far terminators

;	4.	perform _nullcheck() for null pointer assignment

ifndef	_COM_		; DS:0 is the PSP in .COM files!
ifndef	_WINDOWS	; Don't validate the copyright message in windows

	call	_nullcheck	; check data in NULL data segment at DS:0
				; this must be far call in large code models
				; since user can stub it out
	or	ax,ax		; zero if no null ptr assignment detected
	jz	afternullchk

	pop	ax		; get entry code
	or	ah,ah		; ah != 0 means _cexit()/_c_exit()
	push	ax		; put it back for later
	jnz	 short afternullchk ; jump if no status value (_cexit/_c_exit)

	cmp	status,0	; zero if no other error has occurred
	jnz	short afternullchk
	mov	status,255	; nonzero status to indicate an
				; null-pointer-assignment error
afternullchk:

endif	;_WINDOWS
endif	;_COM_

;	5.	terminate floating point
;	6.	reset divide by zero interrupt vector

	call	_ctermsub	; fast cleanup

ifdef _WINDLL
;	6a.	free up all global memory to the OS
;		[NOTE 1: This is necessary because WINDLL memory is
;		shared and windows won't reclaim it.]
;		[NOTE 2: This routine must be called last because a
;		terminator may reference the heap.]

	call	__freefarheap	 ; free up far memory
	call	__freebasedheap  ; free up based memory
endif

;	7.	return to the DOS or caller

ifdef  _WINDLL
	; Always return to caller (exit/_exit is illegal)
	pop	ax		; clean off stack
else
	pop	ax		; get entry code off top of stack
	or	ah,ah		; ah = 0 means term process
	jnz	 returning	; skip down if not term'ing

;	7a.	 return to the DOS

exiting:
	mov	ax,status	; get return value

	callos	terminate	; exit with al = return code


	;*** PROCESS IS TERMINATED ***

endif	;_WINDLL

;	7b.	Return to caller.

returning:

cEnd	<nolocals>


page
;***
;_ctermsub - more C termination code
;
;Purpose:
;	This routine
;		(1) performs floating-point termination
;		(2) resets the divide by zero interrupt vector
;		(3) restore int 3F handler
;
;Entry:
;
;Exit:
;
;Uses:
;	AX,BX,CX,DX.
;
;Exceptions:
;
;*******************************************************************************

labelNP <PUBLIC,_ctermsub>

;	4.	terminate floating point


	mov	cx,word ptr [fpmath+2] ; test for floating point
	jcxz	nofloat_t	;   no

	mov	bx,2		;   yes - cleanup
	call	[fpmath]

nofloat_t:



ifndef	_WINDLL

;	5.	reset divide by zero interrupt vector

	push	ds
	lds	dx,[_aintdiv]	; ds:dx = restore vector
	mov	ax,DOS_setvector shl 8 + 0
	callos			; set divide error interrupt
	pop	ds

endif	;!_WINDLL


	ret


page
;***
;initterm - do a set of initializers or terminators
;
;Purpose:
;	The initializors and terminators may be written in C
;	so we are assuming C conventions (DS=SS, CLD, SI and DI preserved)
;	We go through them in reverse order for onexit.
;
;Entry:
;	SI	= start of procedure list
;	DI	= end of procedure list
;
;Exit:
;
;Uses:
;
;Exceptions:
;
;*******************************************************************************

if sizeC
farinitterm:			; large code farinitterm = initterm
endif

initterm:
	cmp	si,di		; are we done?
	jae	itdone		;   yes - no more

if	sizeC
	sub	di,4
	mov	ax,[di]
	or	ax,[di+2]
	jz	initterm	; skip null procedures
	call	dword ptr [di]
else
	dec	di
	dec	di
	mov	cx,[di]
	jcxz	initterm	; skip null procedures
	call	cx
endif
	jmp	initterm	; keep looping

itdone:
	ret

page

ife	sizeC			; S/C models only
;***
;farinitterm - do a set of far initializers or terminators
;
;Purpose:
;	The initializors and terminators may be written in C
;	so we are assuming C conventions (DS=SS, CLD, SI and DI preserved)
;	We go through them in reverse order for onexit.
;
;Entry:
;	SI	= start of procedure list
;	DI	= end of procedure list
;
;Exit:
;
;Uses:
;
;Exceptions:
;
;*******************************************************************************

farinitterm:
	cmp	si,di		; are we done?
	jae	faritdone	;   yes - no more

	sub	di,4
	mov	ax,[di]
	or	ax,[di+2]
	jz	farinitterm	; skip null procedures
	call	dword ptr [di]
	jmp	farinitterm	; keep looping

faritdone:
	ret
endif	;sizeC

sEnd

	end
