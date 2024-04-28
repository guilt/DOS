	page	,132
	title	 file - stream i/o tables
;***
;file.asm - stream i/o tables
;
;	Copyright (c) 1990-1992, Microsoft Corporation.  All rights reserved.
;
;Purpose:
;	Stream I/O data tables.
;
;	The _iob[] and _iob2[] tables are each in their own segments
;	so that additions can appended on easily and predictably (e.g.,
;	windows).  Also, note that _lastiob is also defined in its own
;	segment so it always points to the last _iob[] entry regardless
;	of what is added to the table.
;
;*******************************************************************************

?DF	=	1		; define segments

include version.inc
.xlist
include cmacros.inc
include defsegs.inc
include stdio.inc
.list

;
; Segment declarations

CrtDefSegs  <code,data>
CrtDefSegs  <iobsegs>

dataOFFSET equ	offset DGROUP:

;
; Number of files
;

	_NFILE_ equ 20


ifdef _QWIN
;
; Pull in the windows iob/iob2 entries
; (may be overridden by noqwin.obj).
;
	extrn __wiobused:word

endif

;
; _iob[] table
;

sBegin	iobseg

labelNP <PUBLIC,_iob>

	;	ptr,	cnt,	base,	flag,	file

ifdef	_WINDOWS

ifdef	_QWIN

	_iobuf	<0, 0, 0, _IOREAD, _NFILE_>	; stdin
	_iobuf	<0, 0, 0, _IOWRT,  _NFILE_>	; stdout
	_iobuf	<0, 0, 0, _IOWRT,  _NFILE_>	; stderr

	_iobuf	(_NFILE_-4) dup (<?>)

else

	_iobuf	(_NFILE_-1) dup (<?>)		; No stdin/out/err

endif	;_QWIN

else	;!_WINDOWS

	_iobuf	<0, 0, 0, _IOREAD, 0>		; stdin
	_iobuf	<0, 0, 0, _IOWRT,  1>		; stdout
	_iobuf	<0, 0, 0, _IOWRT,  2>		; stderr


	_iobuf <_aux._charbuf, 0, _aux._charbuf, _IORW OR _IONBF, 3>  ; stdaux
	_iobuf <0, 0, 0, _IOWRT, 4>			  ; stdprn

	_iobuf	(_NFILE_-6) dup (<?>)


endif	;_WINDOWS

sEnd


;
; Last entry in _iob[] table
;

sBegin	iobeseg

__last	_iobuf	<?>

sEnd

;
; _iob2[] table
;

sBegin	iob2seg

labelNP <PUBLIC,_iob2>

	;	flag2, charbuf, bufsiz, tmpnum, padding

ifdef	_WINDOWS

ifdef	_QWIN

	_iobuf2 <0, 0, 0, 0>			; stdin
	_iobuf2 <0, 0, 0, 0>			; stdout
	_iobuf2 <0, 0, 0, 0>			; stderr

	_iobuf2 (_NFILE_-4) dup (<?>)

else

	_iobuf2 (_NFILE_-1) dup (<?>)		; No stdin/out/err

endif	;_QWIN

else	;!_WINDOWS

	_iobuf2 <0, 0, 0, 0>			; stdin
	_iobuf2 <0, 0, 0, 0>			; stdout
	_iobuf2 <0, 0, 0, 0>			; stderr


_aux	_iobuf2 <0, 0, 1, 0>			; stdaux
	_iobuf2 <0, 0, 0, 0>			; stdprn

	_iobuf2 (_NFILE_-6) dup (<?>)


endif	;_WINDOWS

sEnd

;
; Last entry in _iob2[] table
;

sBegin	iob2eseg

	_iobuf2  <?>

sEnd

;
; Make _lastiob entry available
;

sBegin data
assumes ds,data

labelNP <PUBLIC,_lastiob>
	dw	dataOFFSET __last

sEnd

	end
