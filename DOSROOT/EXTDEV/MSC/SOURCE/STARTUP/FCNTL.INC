;***
;fcntl.inc - defines access mode flags used for open()
;
;	Copyright (c) 1987-1992, Microsoft Corporation.  All rights reserved.
;
;Purpose:
;	This file defines the access mode flags used in calls to the
;	open() routine.
;
;*******************************************************************************

; values for access mode flas used in open() calls.

O_RDONLY equ	0
O_WRONLY equ	1
O_RDWR	equ	2

O_NDELAY equ	0004H
O_APPEND equ	0008H
O_CREAT equ	0100H
O_TRUNC equ	0200H
O_EXCL	equ	0400H

O_TEXT	equ	4000H
O_BINARY equ	8000H

; value for 'whence' parameter used in lseek() calls.  ANSI compatable.

SEEK_SET equ	0
SEEK_CUR equ	1
SEEK_END equ	2

ifdef _WINDOWS
ifndef _WINDLL

; version of win interface
_WINVER 	equ	0

; parameter values for windows screen buffer size
_WINBUFINF	equ	 0
_WINBUFDEF	equ	-1

; size/move settings
_WINSIZEMIN	equ	1
_WINSIZEMAX	equ	2
_WINSIZERESTORE equ	3
_WINSIZECHAR	equ	4

; size/move query types
_WINMAXREQ	equ	100
_WINCURRREQ	equ	101

; pseudo file handle for frame window
_WINFRAMEHAND	equ	-1

; menu items
_WINSTATBAR	equ	1
_WINTILE	equ	2
_WINCASCADE	equ	3
_WINARRANGE	equ	4

; quickwin exit options
_WINEXITPROMPT		equ	1
_WINEXITNOPERSIST	equ	2
_WINEXITPERSIST 	equ	3

; window open structure

_wopeninfo struc

	_version	dw  ?
	_title		dd  ?
	_wbufsize	dd  ?

_wopeninfo ends

; size/move structure

_wsizeinfo struc

	_version	dw  ?
	_type		dw  ?
	_x		dw  ?
	_y		dw  ?
	_h		dw  ?
	_w		dw  ?

_wsizeinfo ends

endif
endif
