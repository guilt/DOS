;***
;stdio.inc - Definitions and declarations needed by the STDIO functions
;	     written in assembler.
;
;	Copyright (c) 1988-1992, Microsoft Corporation. All rights reserved.
;
;Purpose:
;	Analog of STDIO.H and FILE2.H for assembler routines.
;
;*******************************************************************************

; Miscellaneous constants

BUFSIZ		equ	200h
EOF		equ	0FFFFh


; Element structure for _iob array

_iobuf	struc

if sizeD				; far data
	_ptr		dd	?
	_cnt		dw	?
	_base		dd	?
	_flag		db	?
	_file		db	?

else					; near data
	_ptr		dw	?
	_cnt		dw	?
	_base		dw	?
	_flag		db	?
	_file		db	?
endif

_iobuf	ends


; Size of _iob element (i.e., size of stream structure)

if sizeD				; far data

_STREAMSZ	equ	12

else					; near data

_STREAMSZ	equ	8

endif


; Element structure for _iob2 array

_iobuf2 struc

	_flag2		db     ?
	_charbuf	db     ?
	_bufsiz 	dw     ?
	_tmpnum 	dw     ?

if sizeD
	_padding	db     6 dup (?)
else
	_padding	db     2 dup (?)
endif

_iobuf2 ends

; Standard streams

stdin		equ	dataOFFSET _iob
stdout		equ	dataOFFSET _iob + _STREAMSZ
stderr		equ	dataOFFSET _iob + 2 * _STREAMSZ
stdaux		equ	dataOFFSET _iob + 3 * _STREAMSZ
stdprn		equ	dataOFFSET _iob + 4 * _STREAMSZ

; Flags

_IOREAD 	equ	01h
_IOWRT		equ	02h

_IOFBF		equ	0h
_IOLBF		equ	040h
_IONBF		equ	04h

_IOMYBUF	equ	08h
_IOEOF		equ	010h
_IOERR		equ	020h
_IOSTRG 	equ	040h
_IORW		equ	080h

_IOYOURBUF	equ	01h
_IOFEOF 	equ	08h
_IOFLRTN	equ	10h
_IOCTRLZ	equ	20h
_IOCOMMIT	equ	40h
