;***
;defsegs.inc - defines segments.
;
;   Copyright (c) 1989-1992, Microsoft Corporation.  All rights reserved.
;
;Purpose:
;   This file defines segments for the C and C++ libs.
;
;   NOTE:  As needed, special "CRT" segments can be added into the existing
;   init/term tables.  These will be for our use only -- users who put
;   stuff in here do so at their own risk. (See XFCCRT for an example.)
;
;*******************************************************************************

;
; Define all segments used by the C runtime library
;

CrtDefSegs macro   SegList
    irp     seg, <SegList>

	ifidni	<seg>,<code>
	    ifdef  FAR_CODE
		createSeg _RTEXT, code, word, public, code, <>
	    else
		createSeg _TEXT, code, word, public, code, <>
	    endif

	elseifidni <seg>,<wepcode>
	    createSeg WEP_TEXT, wepcode, word, public, code, <>

	elseifidni <seg>,<rcode>
	    createSeg _RTEXT, rcode, word, public, code, <>

	elseifidni <seg>,<etext>
	    createSeg C_ETEXT,etext, word,  public, ENDCODE,<>

	elseifidni <seg>,<cdata>
	    createSeg CDATA, cdata, word, common, DATA, DGROUP

	elseifidni <seg>,<data>
	    createSeg _DATA, data, word, public, DATA, DGROUP

	elseifidni <seg>,<null>
	    createSeg NULL, null, para, public, BEGDATA, DGROUP

	elseifidni <seg>,<stack>
	    ifdef FARSTACK
		; This segment has STACK class so it is at the end of DGROUP;
		; it is the first entry in the near heap.
		createSeg NEARHEAP, stubheap, para, <>, STACK, DGROUP
		; Here is the real stack, not in DGROUP
		createSeg STACK, stack, para,	stack,	STACK, <>
	    else ; not FARSTACK
		createSeg STACK, stack, para,	stack,	STACK,	DGROUP
	    endif ;FARSTACK

	elseifidni <seg>,<const>
	    createSeg CONST, const, word, public, CONST,DGROUP

	elseifidni <seg>,<bss>
	    createSeg _BSS, _bss, word, public, BSS, DGROUP

	elseifidni <seg>,<emcode>
	    createSeg EMULATOR_TEXT, EmCode, para, public, CODE, DGROUP

	elseifidni <seg>,<emdata>
	    createSeg EMULATOR_DATA, EmData, para, public, FAR_DATA, DGROUP

	elseifidni <seg>,<dbdata>
	    ifndef  IBM
		createSeg DBDATA, dbdata, word, common, DATA, DGROUP
	    else
		%out <Error in CrtDefSeg:  DBDATA segment used in IBM version.>
		.err
	    endif   ; !IBM

	elseifidni <seg>,<eseg>
	    createSeg EXEC, eseg, word, common, DATA, DGROUP

	elseifidni <seg>,<xiqcseg>
	    createSeg XIQC, xiqcseg, word, common, DATA, DGROUP  ; QC initializer -Zr  (DOS only)

	elseifidni <seg>,<xifseg>
	    createSeg XIFB, xifbseg, word, public, DATA, DGROUP
	    createSeg XIF,  xifseg,  word, public, DATA, DGROUP ; far init's
	    createSeg XIFE, xifeseg, word, public, DATA, DGROUP

	elseifidni <seg>,<xiseg>
	    createSeg XIB,  xibseg, word, public, DATA, DGROUP
	    createSeg XI,   xiseg,  word, public, DATA, DGROUP ; init's
	    createSeg XIE,  xieseg, word, public, DATA, DGROUP

	elseifidni <seg>,<xifcseg>
	    createSeg XIFCB, xifcbseg, word, public, DATA, DGROUP
	    createSeg XIFU,  xifuseg,  word, public, DATA, DGROUP ; far C++ User constructors.
	    createSeg XIFL,  xiflseg,  word, public, DATA, DGROUP ; far C++ Lib constructors.
	    createSeg XIFM,  xifmseg,  word, public, DATA, DGROUP ; far C++ MS constructors.
	    createSeg XIFCE, xifceseg, word, public, DATA, DGROUP

	elseifidni <seg>,<xoseg>
	    createSeg XOB,  xobseg, word, public, BSS, DGROUP
	    createSeg XO,   xoseg,  word, public, BSS, DGROUP ; atexit/onexit table
	    createSeg XOE,  xoeseg, word, public, BSS, DGROUP ; (in BSS because it is not initialized)

	elseifidni <seg>,<xofseg>
	    createSeg XOFB,  xofbseg, word, public, BSS, DGROUP
	    createSeg XOF,   xofseg,  word, public, BSS, DGROUP ; far atexit/onexit table
	    createSeg XOFE,  xofeseg, word, public, BSS, DGROUP ; (in BSS because it is not initialized)

	elseifidni <seg>,<xpseg>
	    createSeg XPB,  xpbseg, word, public, DATA, DGROUP
	    createSeg XP,   xpseg,  word, public, DATA, DGROUP ; preterm's
	    createSeg XPE,  xpeseg, word, public, DATA, DGROUP

	elseifidni <seg>,<xcseg>
	    createSeg XCB,  xcbseg, word, public, DATA, DGROUP
	    createSeg XC,   xcseg,  word, public, DATA, DGROUP ; term's
	    createSeg XCE,  xceseg, word, public, DATA, DGROUP

	elseifidni <seg>,<xcfseg>
	    createSeg XCFB,   xcfbseg,	 word, public, DATA, DGROUP
	    ; *** XCFCRT is for CRT usage only and should be executed last ***
	    createSeg XCFCRT, xcfcrtseg, word, public, DATA, DGROUP ; far term's (CRT Only)
	    createSeg XCF,    xcfseg,	 word, public, DATA, DGROUP ; far term's
	    createSeg XCFE,   xcfeseg,	 word, public, DATA, DGROUP

	elseifidni <seg>,<iobsegs>
	    createSeg IOB,   iobseg,  word, public, DATA, DGROUP
	    createSeg IOBX,  iobxseg, word, public, DATA, DGROUP ; stdio iobs
	    createSeg IOBE,  iobeseg, word, public, DATA, DGROUP
	    createSeg IOB2,  iob2seg, word, public, DATA, DGROUP
	    createSeg IOB2X, iob2xseg,word, public, DATA, DGROUP
	    createSeg IOB2E, iob2eseg,word, public, DATA, DGROUP

	elseifidni <seg>,<nmsg>
	    createSeg HDR,  nhdr,  byte, public, MSG, DGROUP
	    createSeg MSG,  nmsg,  byte, public, MSG, DGROUP ; near message text
	    createSeg PAD,  npad,  byte, common, MSG, DGROUP
	    createSeg EPAD, nepad, byte, common, MSG, DGROUP

	elseifidni <seg>,<fmsg>
	    createSeg FAR_HDR,	fhdr,  byte, public, FAR_MSG, FMGROUP
	    createSeg FAR_MSG,	fmsg,  byte, public, FAR_MSG, FMGROUP ; far message text
	    createSeg FAR_PAD,	fpad,  byte, common, FAR_MSG, FMGROUP
	    createSeg FAR_EPAD, fepad, byte, common, FAR_MSG, FMGROUP

	else
	    %out <Error in CrtDefSeg:  Unknown segment &seg&.>
	    .err
	endif

    endm    ;; irp loop
endm	;; CrtDefSeg macro


;
; Group text segments into DGROUP for COM libs
;

DefGrpCom macro
    ifdef   _COM_
	; all segments are together in DGROUP
	DGROUP	group  _TEXT, C_ETEXT, _DATA	; define DGROUP
    else
	 %out <Error in DefGrpCom: _COM_ not defined.>
	 .err
    endif
endm	;; DefGrpCom
