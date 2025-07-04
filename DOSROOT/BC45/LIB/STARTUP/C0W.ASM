;[]------------------------------------------------------------[]
;|      C0W.ASM -- Start Up Code For Windows                    |
;[]------------------------------------------------------------[]

;
;       C/C++ Run Time Library - Version 6.5
; 
;       Copyright (c) 1991, 1994 by Borland International
;       All Rights Reserved.
; 

		locals

		__C0__ = 1
include         RULES.ASI

		ASSUME CS:_TEXT, DS:DGROUP

		public  __acrtused              ;satisfy MS for now
__acrtused      equ     0
IFNDEF __DPMI16__
		public  __WINMAINCALL           ; used internally
ENDIF
		public  __INITAPPCALLED         ; used internally

IFNDEF __DPMI16__
extrn           WINMAIN:DIST
ENDIF

extrn           INITAPP:far
extrn           INITTASK:far
extrn           FATALEXIT:far
extrn           WAITEVENT:far
extrn           LOCKSEGMENT:far
extrn           UNLOCKSEGMENT:far
extrn           GETWINFLAGS:far
IFDEF __DPMI16__
  extrn         _main:DIST
  extrn         _OkToInitWindowsRTL:DIST
  extrn         __abort:DIST
ENDIF
extrn           _exit:DIST
extrn           __exit:DIST
extrn           __exitbuf:DIST
extrn           __exitfopen:DIST
extrn           __exitopen:DIST
extrn           __setupio:near                  ;required!
extrn           __ExceptInit:DIST

		public __DestructorCount        ;Offset to global destructor count
__DestructorCount EQU  10H
		public __Exception_list         ;Offset to global exception list
__Exception_list  EQU  14H
NULL            segment
		db      16 dup (0)              ;Windows
		db       4 dup (0)              ;destructor count
		db       2 dup (0)              ;exception list
		db       4 dup (0)              ;exception vptr
		db       6 dup (0)              ;reserved
		db       2 dup (0)              ;VBX control jump vector
						;MUST be at SS:20h
		db       2 dup (0)              ;reserved
		ends

_CVTSEG         segment
		public __RealCvtVector
__RealCvtVector label word
		ends

_SCNSEG         segment
		public __ScanTodVector
__ScanTodVector label word
		ends

_FPSEG          segment
		public __FPVector
__FPVector      dd      0
		ends

_DATA           segment
		public _errno
_errno          dw      0
		public __protected
__protected     dw      0
		public __8086
__8086          dw      0
		public __8087
__8087          dw      0
		public __psp
__psp           dw      0
		public __hInstance
__hInstance     dw      0
		public __hPrev
__hPrev         dw      0
		public __pszCmdline
__pszCmdline    dw      0
		public __cmdShow
__cmdShow       dw      0
		public __version
__version       label word
		public __osversion
__osversion     label word
		public __osmajor
__osmajor       db      0
		public __osminor
__osminor       db      0
		public __osmode         ;Used for OS/2 protected mode by MS,
__osmode        db      0               ;  currently set to 0 under Windows
		public __WinAllocFlag   ;Used by malloc to get additional flags
__WinAllocFlag  dw      0               ;  to pass to GlobalAlloc (for DLL use)
		public __LockWIN87EM    ;Used do lock down WIN87EM to avoid
__LockWIN87EM   dw      1               ;  DLL unload ordering problem
		public  __abend
__abend         dw      0               ;Signals abnormal end, don't run destructors etc.

IFDEF __DPMI16__
  extrn         __C0environ:dword
  extrn         __C0argv:dword
  extrn         __C0argc:word
ENDIF

CopyRight       db      'Borland C++ - Copyright 1994 Borland Intl.',0
IFDEF __DPMI16__
DPMI16Error_s   db      'This DPMI16 application was linked incorrectly and'
		db      ' will fail.',10,13,'$'
ENDIF
		ends

_TEXT           segment

Main            proc near

;Windows initialization.  Sets up registers and stack.

IFDEF   __DPMI16__
		mov     ax, seg DGROUP
		mov     ds, ax
ENDIF

		push    bx cx es
		xor     ax,ax
		push    ax
		call    __ExceptInit
		pop     ax
		pop     es cx bx

		;INITTASK returns:
		;  'Failure:
		;    AX = zero if it failed
		;  Success:
		;    AX = 1
		;    CX = stack limit
		;    DX = cmdShow parameter to CreateWindow
		;    ES:BX = -> DOS format command line (ES = PSP address)
		;    SI = hPrevinstance
		;    DI = hinstance
		call    INITTASK
		or      ax,ax
		jnz     @@OK
		jmp     @@Fail
@@OK:           mov     word ptr ss:[__Exception_list], -1
		mov     __psp,es
		mov     word ptr __pszCmdline,bx
		mov     __hPrev,si
		mov     __hInstance,di
		mov     __cmdShow,dx

IF LDATA EQ false
		mov     ax,-1
		push    ax
		call    LOCKSEGMENT
ENDIF

;Clear _BSS, uninitialized data area

IFNDEF  __HUGE__
		xor     ax, ax
		push    ds
		pop     es
		mov     di,offset DGROUP:BeginBSS
		mov     cx,offset DGROUP:EndBSS
		sub     cx,di
		cld
		rep
		stosb
ENDIF

;Init the Windows App

		xor     ax,ax
		push    ax
		call    WAITEVENT
		push    __hInstance
		call    INITAPP
__INITAPPCALLED:or      ax,ax
		jnz     @@InitOK
		jmp     @@Fail
@@InitOK:

;Determine DOS version

		mov     ah, 30h
		int     21h
		mov     __version, ax   ; save minor and major revision

;Determine whether we are in protected mode

		call    GETWINFLAGS
		test    ax,1            ; WF_PMODE = 1
		jz      @@realmode      ; Note:  GETWINFLAGS returns a long,
					; so if WF_PMODE changed it could be
					; in the high word.
		mov     __protected, 8  ; Eight is for convenience.
@@realmode:

;Test for 8086/8087 presence

		test    ax,0400h        ; WF_8087 = 0x0400
		jz      @@no8087
		mov     __8087, 1
@@no8087:
		and     ax,08h+04h+02h  ; WF_CPU486|WF_CPU386|WF_CPU286
		shr     ax,1            ; Convert to 4 or 2 or 1 or 0
		test    ax,0004h        ; Have 4, 486 done
		jnz     @@NoAdjust
		or      ax,ax           ; Have 0, 8086 done
		jz      @@NoAdjust
		inc     ax              ; Have 2 or 1, need 3 or 2
@@NoAdjust:
		mov     __8086,ax       ; Set CPU Type


IFDEF  __DPMI16__
;
; Here we attempt to prevent an early death caused by linking
; the libs in the wrong order
;
		call    _OkToInitWindowsRTL
		or      ax, ax
		jnz     DPMI16Error
ENDIF

;Call our initialization functions, including C++ static constructors.

		mov     ax,ds
		mov     es,ax
		mov     si,offset DGROUP:InitStart      ;si = start of table
		mov     di,offset DGROUP:InitEnd        ;di = end of table
		call    Initialize

IFDEF __DPMI16__
;Set up and call _main for DPMI16 application

		push    word ptr [__C0environ+2]
		push    word ptr [__C0environ]
		push    word ptr [__C0argv+2]
		push    word ptr [__C0argv]
		push    [__C0argc]
		call    _main
ELSE
;Set up and call WinMain for Windows application
		push    __hInstance
		push    __hPrev
		push    __psp
		push    word ptr __pszCmdline
		push    __cmdShow
__WINMAINCALL:  call    WINMAIN
ENDIF
		push    ax      ; Push return value

		cmp     __abend, 0
		jne     @@abnormalexit
		call    _exit   ; Normal exit
@@abnormalexit: call    __exit  ; Abnormal exit, don't call destructors etc.

IFDEF  __DPMI16__
DPMI16Error:
		mov     ah, 9
		mov     dx, offset DPMI16Error_s
		int     21h
		call    __abort
ENDIF
;---------------------------------------------------------------------------
;       _cleanup()      call all #pragma exit cleanup routines.
;       _checknull()    check for null pointer zapping copyright message
;       _terminate(int) exit program with error code
;       _restorezero()  restore interrupt vectors
;
;       These functions are called by exit(), _exit(), _cexit(),
;       and _c_exit().
;---------------------------------------------------------------------------

;       Call cleanup routines

__cleanup       PROC    DIST
		PUBLIC  __cleanup

		mov     ax,ds
		mov     es,ax
		push    si
		push    di
		mov     si,offset DGROUP:ExitStart
		mov     di,offset DGROUP:ExitEnd
		call    Cleanup
		pop     di
		pop     si
		ret
__cleanup       ENDP

;       Check for null pointers before exit.  NO-OP on Windows.

__checknull     PROC    DIST
		PUBLIC  __checknull
		ret
__checknull     ENDP

;       Restore grabbed interrupt vectors.  NO-OP on Windows.

__restorezero     PROC    DIST
		PUBLIC  __restorezero
		ret
__restorezero     ENDP

;       Exit to DOS

__terminate     PROC    DIST
		PUBLIC  __terminate

IF LDATA EQ false
		mov     ax,-1
		push    ax
		call    UNLOCKSEGMENT
ENDIF
		mov     bp,sp
		mov     al,[bp+cPtrSize]
		mov     ah,4ch                  ;exit
		int     21h
__terminate     ENDP

@@Fail:         mov     al,0ffh
		push    ax
		call    _exit

		mov     ah,4ch                  ;exit
		int     21h
		endp

;       Return default data segment in AX

__GetDGROUP     PROC    FAR
		PUBLIC  __GetDGROUP
		mov     ax, ss
		ret
		endp

;------------------------------------------------------------------
;  Loop through a startup/exit (SE) table,
;  calling functions in order of priority.
;  ES:SI is assumed to point to the beginning of the SE table
;  ES:DI is assumed to point to the end of the SE table
;  First 64 priorities are reserved by Borland
;------------------------------------------------------------------
PNEAR           EQU     0
PFAR            EQU     1
NOTUSED         EQU     0ffh

SE              STRUC
calltype        db      ?                       ; 0=near,1=far,ff=not used
priority        db      ?                       ; 0=highest,ff=lowest
addrlow         dw      ?
addrhigh        dw      ?
SE              ENDS

Initialize      proc near
@@Start:        mov     ax,100h                 ;start with lowest priority
		mov     dx,di                   ;set sentinel to end of table
		mov     bx,si                   ;bx = start of table

@@TopOfTable:   cmp     bx,di                   ;and the end of the table?
		je      @@EndOfTable            ;yes, exit the loop
		cmp     es:[bx.calltype],NOTUSED;check the call type
		je      @@Next
		mov     cl, es:[bx.priority]    ;move priority to CX
		xor     ch, ch
		cmp     cx,ax                   ;check the priority
		jae     @@Next                  ;too high?  skip
		mov     ax,cx                   ;keep priority
		mov     dx,bx                   ;keep index in dx
@@Next:         add     bx,SIZE SE              ;bx = next item in table
		jmp     @@TopOfTable

@@EndOfTable:   cmp     dx,di                   ;did we exhaust the table?
		je      @@Done                  ;yes, quit
		mov     bx,dx                   ;bx = highest priority item
		cmp     es:[bx.calltype],PNEAR  ;is it near or far?
		mov     es:[bx.calltype],NOTUSED;wipe the call type
		push    es                      ;save es
		je      @@NearCall

@@FarCall:      call    DWORD PTR es:[bx.addrlow]
		pop     es                      ;restore es
		jmp     short @@Start

@@NearCall:     call    WORD PTR es:[bx.addrlow]
		pop     es                      ;restore es
		jmp     short @@Start

@@Done:         ret
		endp

Cleanup         proc near
@@Start:        mov     ah,0                    ;start with highest priority
		mov     dx,di                   ;set sentinel to end of table
		mov     bx,si                   ;bx = start of table

@@TopOfTable:   cmp     bx,di                   ;and the end of the table?
		je      @@EndOfTable            ;yes, exit the loop
		cmp     es:[bx.calltype],NOTUSED;check the call type
		je      @@Next
		cmp     es:[bx.priority],ah     ;check the priority
		jb      @@Next                  ;too low?  skip
		mov     ah,es:[bx.priority]     ;keep priority
		mov     dx,bx                   ;keep index in dx
@@Next:         add     bx,SIZE SE              ;bx = next item in table
		jmp     @@TopOfTable

@@EndOfTable:   cmp     dx,di                   ;did we exhaust the table?
		je      @@Done                  ;yes, quit
		mov     bx,dx                   ;bx = highest priority item
		cmp     es:[bx.calltype],PNEAR  ;is it near or far?
		mov     es:[bx.calltype],NOTUSED;wipe the call type
		push    es                      ;save es
		je      @@NearCall

@@FarCall:      call    DWORD PTR es:[bx.addrlow]
		pop     es                      ;restore es
		jmp     short @@Start

@@NearCall:     call    WORD PTR es:[bx.addrlow]
		pop     es                      ;restore es
		jmp     short @@Start

@@Done:         ret
		endp

		ends

		end Main
