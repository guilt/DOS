;---------------------------------------;
;    DDRAW Plasma Demo                  ;
;                                       ;
;    Author :         X-Calibre         ;
;    ASM version :    Ewald Snel        ;
;    Copyright (C) 1999, Diamond Crew   ;
;                                       ;
;    http://here.is/diamond/            ;
;                                       ;
;    translated to DOS by japheth       ;
;    http://www.japheth.de              ;
;---------------------------------------;

?BACKBUFFER equ 1   ;1=use a backbuffer

; View with TAB size 4

    .486
if ?FLAT    
    .MODEL FLAT, STDCALL
else
    .MODEL SMALL, STDCALL
endif
    option casemap :none

    .nolist
    .nocref
    INCLUDE function.inc
    INCLUDE vesa32.inc
    include keyboard.inc
    include macros.inc
    .list
    .cref

    nextFrame   PROTO
    initPlasma  PROTO

RETURN  MACRO   arg
    IFNB <arg>
        mov     eax, arg
    ENDIF
    ret
ENDM

LRETURN MACRO   arg 
    IFNB <arg>
        mov     eax, arg
    ENDIF
    leave
    ret
ENDM

FATAL   MACRO   msg
    LOCAL @@msg
    .DATA
    @@msg   db  msg, 13,10,'$'
    .CODE
    mov ah,9
    mov edx, offset @@msg
    int 21h
    mov ax,4c00h
    int 21h
ENDM


    .DATA?

palette         dd      256 dup (?)
table           dd      512 dup (?)

    .DATA

ddwidth         EQU     640     ; display mode width
ddheight        EQU     480     ; display mode height
dwBytesPixel	dd      4

dwMode          dd      -1
if ?BACKBUFFER
dwScreenSize    dd      0
dwScreenOffs    dd      0
bFlip           db      1
endif
phaseA          dd      0
phaseB          dd      0

factor1         EQU     -1
factor2         EQU     1
factor3         EQU     1
factor4         EQU     -1

red             REAL4   300.0
green           REAL4   320.0
blue            REAL4   340.0

scale1          REAL4   2.0
scale2          REAL4   127.5
scale3          REAL4   256.0

svgainfo    SVGAINFO <>

    .CODE

;-----------------------------------------------------------;
;                Calculate Next Plasma Frame                ;
;-----------------------------------------------------------;

nextFrame   PROC uses ebx esi edi ebp

    mov     ecx, ddheight           ; # of scanlines
    mov     edi, svgainfo.PhysBasePtr
if ?BACKBUFFER
    add     edi, dwScreenOffs
endif
    mov     ebp, dwBytesPixel 
@@scanline:
    push    ecx
    push    edi

    mov     esi, [phaseA]
    mov     edx, [phaseB]
    sub     esi, ecx
    and     edx, 0FFh
    and     esi, 0FFh
    mov     edx, [table][4*edx][256*4]
    mov     esi, [table][4*esi]     ; [x]  +  table0[a + y]
    sub     edx, ecx                ; [y]  +  table1[b]
    mov     ecx, ddwidth            ; [x] --> pixel counter

@@pixel:
    and     esi, 0FFh
    and     edx, 0FFh
    mov     eax, [table][4*esi]
    mov     ebx, [table][4*edx][256*4]
    add     eax, ebx
    add     esi, factor3
    shr     eax, 1
    add     edx, factor4
    and     eax, 0FFh
    add     edi, ebp
    mov     eax, [palette][4*eax]
    cmp     ebp, 4
    jnz     @F
    mov     @flat:[edi-4], eax
    dec     ecx
    jnz     @@pixel
    jmp     done
@@:    
    mov     @flat:[edi-3], ax
    shr     eax,8
    mov     @flat:[edi-1], ah
    dec     ecx
    jnz     @@pixel
done:
    pop     edi
    pop     ecx
    movzx   eax, svgainfo.BytesPerScanLine
    add     edi, eax                        ; inc. display position
    dec     ecx
    jnz     @@scanline

    add     [phaseA], factor1
    add     [phaseB], factor2

    ret
nextFrame   ENDP


;-----------------------------------------------------------;
;                Initalize Plasma Tables                    ;
;-----------------------------------------------------------;

initPlasma  PROC

    LOCAL @@i :DWORD
    LOCAL @@r :DWORD
    LOCAL @@g :DWORD
    LOCAL @@b :DWORD
    LOCAL temp :DWORD

    mov     [@@i], 0

    .WHILE @@i < 256

        mov     edx, [@@i]

; Calculate table0 value

        fldpi
        fimul   [@@i]
        fmul    [scale1]
        fdiv    [scale3]
        fsin
        fmul    [scale2]
        fadd    [scale2]
        fistp   [table][4*edx]

; Calculate table1 value

        fldpi
        fimul   [@@i]
        fmul    [scale1]
        fdiv    [scale3]
        fcos
        fmul    [scale2]
        fadd    [scale2]
        fldpi
        fmulp   st(1), st
        fmul    [scale1]
        fdiv    [scale3]
        fsin
        fmul    [scale2]
        fadd    [scale2]
        fistp   [table][4*edx][4*256]

; Calculate palette value

        xor     eax, eax

        FOR comp, <red, green, blue>
            fldpi
            fimul   [@@i]
            fmul    [scale1]
            fdiv    [comp]
            fcos
            fmul    [scale2]
            fadd    [scale2]
            fistp   [temp]
            shl     eax, 8
            or      eax, [temp]
        ENDM

        mov     [palette][4*edx] , eax
        inc     [@@i]

    .ENDW

    ret
initPlasma  ENDP

;--- get a key by examining BIOS vars directly 

getkey  proc uses ebx
        xor     eax,eax
        movzx   EBX,word ptr @flat:[041Ah]
        cmp     BX,@flat:[041Ch]
        jz      getkey_1
        mov     AX,@flat:[EBX+400h]
        INC     eBX
        INC     eBX
        CMP     BX,@flat:[0482h]
        JNZ     @F
        MOV     BX,@flat:[0480h]
@@:
        MOV     @flat:[041Ah],BX
getkey_1:
        ret
getkey  endp

;--- wait for vertical sync

vsyncwait proc
        mov dx, 3dah
@@:        
        in  al, dx
        test al,8
        jz  @B
        ret
vsyncwait endp

;--- flip screens

if ?BACKBUFFER
FlipScreen proc uses ebx

        .if (dwScreenOffs)
            mov dx,ddheight
            xor eax, eax
        .else
            mov dx,0
            mov eax, dwScreenSize
        .endif
        mov dwScreenOffs, eax
        mov cx,0
        mov bl,00h
        mov bh,00
        mov ax,4F07h
        int 10h
        ret
FlipScreen endp
endif

;--- alloc some memory

allocmemory proc dwSize:dword
        mov     bx, word ptr dwSize+2
        mov     cx, word ptr dwSize+0
        mov     ax,0501h
        int     31h
        jc      error
        push    bx
        push    cx
        pop     eax
ife ?FLAT
externdef __baseadd:dword
        sub     eax,__baseadd   ;adjust linear address (MZ is not zero-based)
endif
        push    si
        push    di
        pop     edx
        ret
error:
        xor     eax,eax
        ret
allocmemory endp

;--- free alloced memory

freememory proc dwHandle:dword
        mov si, word ptr dwHandle+2
        mov di, word ptr dwHandle+0
        mov ax, 0502h
        int 31h
        jc  error
        ret
error:
        xor eax,eax
        ret
freememory endp

;--- main

main    PROC c

local   dwEsp:dword
local   dwPrevMode:dword
local   dwSaveBuff:dword
local   dwSaveBuff2:dword
local   dwSaveBuff2hdl:dword

    invoke  SearchVesaMode, ddwidth, ddheight, 32
    .if (!eax)
		dec dwBytesPixel
	    invoke  SearchVesaMode, ddwidth, ddheight, 24
	   .if (!eax)
    	   FATAL "no matching VESA Mode found"
       .endif
    .endif
    or ah,40h     ;use LFB!!!
    mov dwMode, eax
    
    invoke  GetVesaModeInfo, dwMode, addr svgainfo
    .if (!eax)
        FATAL "required VESA Mode not supported"
    .endif
if ?BACKBUFFER

    invoke  GetVesaVideoMemorySize
    mov ecx, ddwidth * ddheight	;SCREENSIZE = ddwidth * ddheight * bytespixel
    mov edx, ecx
    shl ecx, 1		;*2	
    add ecx, edx	;*3
    .if (dwBytesPixel == 4)
        add ecx, edx
    .endif
    .if (eax < ecx) ;no space for a backbuffer?
        mov bFlip, 0
    .endif
endif    

;------------------------------- save the current screen (state + mem)       
    mov     dwEsp, esp
    invoke  GetVesaStateBufferSize
    mov     ecx, eax
    add     eax,4
    and     al,0FCh
    sub     esp, eax
    mov     dwSaveBuff, esp
    invoke  SaveVesaVideoState, dwSaveBuff, ecx
    invoke  GetVesaMode
    mov     dwPrevMode, eax
    invoke  GetVesaMemoryBufferSize, eax
    invoke  allocmemory, eax
    mov     dwSaveBuff2, eax
    mov     dwSaveBuff2hdl, edx
    .if (eax)
        invoke  SaveVesaVideoMemory, eax, ecx
    .endif

;------------------------------- now set the new mode
    
    invoke  SetVesaMode, dwMode
    .if (!eax)
        FATAL "unable to set VESA Mode"
    .endif
if ?BACKBUFFER
    movzx eax, svgainfo.BytesPerScanLine
    mov   ecx, ddheight
    mul   ecx
    mov   dwScreenSize, eax
endif
    call    initPlasma

;--- main Loop

    .WHILE 1

        INVOKE  getkey
        .break .if (ax == __ALT_X)
        
        .if (ah == __ESC_MAKE)
            .while (1)
                INVOKE  getkey
                .break .if (ah == __ESC_MAKE)
            .endw
        .endif

        call nextFrame

        call vsyncwait
if ?BACKBUFFER
        .if (bFlip)
            call FlipScreen
        .endif
endif

    .ENDW

;------------------------------- restore the screen
    mov eax, dwPrevMode
    or ah,80h
    invoke  SetVesaMode, eax
    invoke  RestoreVesaVideoState, dwSaveBuff
    .if (dwSaveBuff2)
        invoke  RestoreVesaVideoMemory, dwSaveBuff2
        invoke  freememory, dwSaveBuff2hdl
    .endif
    mov esp, dwEsp

    ret
main    ENDP

mainCRTStartup proc c
ifdef _VESA32_
	call	VesaInit
endif
    invoke  main
ifdef _VESA32_
	call	VesaExit
endif
    mov     ax,4c00h
    int     21h
mainCRTStartup endp

    END mainCRTStartup
