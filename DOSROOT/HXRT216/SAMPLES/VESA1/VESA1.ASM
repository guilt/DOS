
;*** sample using VESA 16bit color mode with LFB

        .386
if ?FLAT
        .MODEL FLAT, stdcall
else
        .MODEL SMALL, stdcall
endif
        option casemap:none

        include function.inc
        include vesa32.inc
        include keyboard.inc
        include macros.inc

ifndef ?RES
?RES     = 1
endif

if ?RES eq 1
?MODE   = _640x480x64K or _USELFB
?DX     = 640
?DY     = 480
endif
if ?RES eq 2
?MODE   equ _800x600x64K or _USELFB
?DX     equ 800
?DY     equ 600
endif
if ?RES eq 3
?MODE   equ _1024x768x64K or _USELFB
?DX     = 1024
?DY     = 768
endif

CNTINIT  equ 1000h

GRRECT  struct
dwPosX  dd ?
dwPosY  dd ?
dwSizeX dd ?
dwSizeY dd ?
GRRECT  ends

fill64k proto stdcall xpos:dword,ypos:dword,xlen:dword,ylen:dword,color:dword

        .DATA

svgainfo    SVGAINFO <>

dwColor     dd 0
dwCnt       dd CNTINIT
dwDivisor   dd 3
bDivAdd     db 1

        .CODE

allocmemory proc dwSize:dword
        mov     bx, word ptr dwSize+2
        mov     cx, word ptr dwSize+0
        mov     ax,0501h
        int     31h
        jc      error_am
        push    bx
        push    cx
        pop     eax
        push    si
        push    di
        pop     edx
        ret
error_am:
        xor     eax,eax
        ret
allocmemory endp

freememory proc dwHandle:dword
        mov si, word ptr dwHandle+2
        mov di, word ptr dwHandle+0
        mov ax, 0502h
        int 31h
        jc  error_fm
        ret
error_fm:
        xor eax,eax
        ret
freememory endp

main    proc c

local   dwEsp:dword
local   dwPrevMode:dword
local   dwSaveBuff:dword
local   dwSaveBuff2:dword
local   dwSaveBuff2hdl:dword

        mov     dwEsp, esp
        invoke  GetVesaModeInfo, ?MODE, addr svgainfo
        and     eax,eax
        jz      error
;------------------------------- save the current screen        
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

        invoke  SetVesaMode, ?MODE
        and     eax,eax
        jz      error
        call    DoLoop
;------------------------------- restore the screen
        mov     eax, dwPrevMode
        or      ah,80h
        invoke  SetVesaMode, eax    ;dont fully rely on vesa state restore!
        invoke  RestoreVesaVideoState, dwSaveBuff
        .if (dwSaveBuff2)
            invoke  RestoreVesaVideoMemory, dwSaveBuff2
            invoke  freememory, dwSaveBuff2hdl
        .endif
        mov     esp, dwEsp
        ret
error:
        mov     esp, dwEsp
        mov     edx, CStr(<"VESA mode with LFB not supported",13,10,'$'>)
        mov     ah,9
        int     21h
        ret
main    endp

;--- get a key by examining BIOS vars directly 

getkey  proc
        push    ebx
        xor     eax,eax
        movzx   EBX,word ptr @flat:[041Ah]
        cmp     BX,@flat:[041Ch]
        jz      getkey_1
        mov     AX,@flat:[EBX+400h]
        INC     eBX
        INC     eBX
        CMP     BX,@flat:[0482h]
        JNZ     sm1
        MOV     BX,@flat:[0480h]
sm1:
        MOV     @flat:[041Ah],BX
getkey_1:
        pop     ebx
        ret
getkey  endp

;--- main loop, write some rectangles with variant size and color

DoLoop  proc    near

local   color:dword
local   clspar:GRRECT

        in      al,61h          ;use timer 2
        or      al,1
        out     61h,al

        mov     al,95h
        out     43h,al
        mov     al,0FFh
        out     42h,al
setcb2:
        call    getcolor
        mov     color, eax
;----------------------------------- set dwPosY
        in      al,42h
        mov     ah,al
        in      al,40h
        xor     ah,al
        movzx   eax,ax
        cdq
        mov     ecx,?DY
        div     ecx
        mov     clspar.dwPosY, edx
;----------------------------------- set dwPosX
        in      al,40h
        mov     ah,al
        in      al,42h
        xor     ah,al
        movzx   eax,ax
        cdq
        mov     ecx,?DX
        div     ecx
        mov     clspar.dwPosX, edx
;----------------------------------- set dwSizeY
        in      al,42h
        mov     ah,al
        in      al,40h
        xor     ah,al
        movzx   eax,ax
        push    eax
        cdq
        mov     eax,?DY
        mov     ecx,dwDivisor
        div     ecx
        mov     ecx,eax
        pop     eax
        cdq
        div     ecx
        inc     edx
        mov     eax,edx
        add     eax,clspar.dwPosY
        cmp     eax,?DY
        jbe     dl_1
        sub     eax,?DY
        sub     edx,eax
dl_1:
        mov     clspar.dwSizeY, edx
;----------------------------------- set dwSizeX
        in      al,40h
        mov     ah,al
        in      al,42h
        xor     al,ah
        movzx   eax,ax
        push    eax
        cdq
        mov     eax,?DX
        mov     ecx,dwDivisor
        div     ecx
        mov     ecx,eax
        pop     eax
        cdq
        div     ecx
        inc     edx
        mov     eax,edx
        add     eax,clspar.dwPosX
        cmp     eax,?DX
        jbe     dl_2
        sub     eax,?DX
        sub     edx,eax
dl_2:
        mov     clspar.dwSizeX, edx

        invoke  fill64k, clspar.dwPosX, clspar.dwPosY, clspar.dwSizeX, clspar.dwSizeY, color

        call    getkey

        cmp     ax,__ALT_X
        jz      @exit
        
        cmp     ah,__ESC_MAKE
        jnz     setcb2
setcb7: call    getkey
        cmp     ax,__ALT_X
        jz      @exit
        cmp     ah,__ESC_MAKE
        jz      setcb2
        jmp     setcb7
@exit:
        ret
DoLoop  endp

;--- get a color in AX

getcolor proc    near

        dec     dwCnt
        jnz     getcolor_1
        mov     dwCnt, CNTINIT
        mov     al, bDivAdd
        mov     ecx, dwDivisor
again:        
        add     cl,al
        and     cl,7Fh
        cmp     cl,3
        jnb     gc_1
        neg     al
        mov     bDivAdd, al
        jmp     again
gc_1:        
        mov     dwDivisor, ecx
getcolor_1:        
        mov     eax, dwColor
        add     eax,1
        mov     dwColor, eax

        mov     cl,0           ;red
        mov     ch,0           ;green
        mov     dl,0           ;blue

        shr     eax,1
        rcl     dl,1
        shr     eax,1
        rcl     ch,1
        shr     eax,1
        rcl     cl,1

        shr     eax,1
        rcl     dl,1
        shr     eax,1
        rcl     ch,1
        shr     eax,1
        rcl     cl,1

        shr     eax,1
        rcl     dl,1
        shr     eax,1
        rcl     ch,1
        shr     eax,1
        rcl     cl,1

        shr     eax,1
        rcl     dl,1
        shr     eax,1
        rcl     ch,1
        shr     eax,1
        rcl     cl,1

        shr     eax,1
        rcl     dl,1
        shr     eax,1
        rcl     ch,1
        shr     eax,1
        rcl     cl,1

        shr     eax,1
        rcl     ch,1


        xor     eax,eax
        mov     al,cl
        shl     eax,6
        or      al,ch
        shl     eax,5
        or      al,dl

        ret
getcolor endp

;--- fill a screen rectangle with a color

fill64k proc stdcall uses edi esi xpos:dword,ypos:dword,xlen:dword,ylen:dword,color:dword

ife ?FLAT
        push    es
        push    gs
        pop     es
endif
        movzx   eax,svgainfo.BytesPerScanLine
        mov     esi,eax

        sub     esi,xlen
        sub     esi,xlen            ;16 bit has 2 bytes
                                    ;esi = offset to next line
        mul     ypos

        add     eax,xpos            ;get position (x,y)
        add     eax,xpos            ;16 bit has 2 bytes!

        mov     edi,svgainfo.PhysBasePtr
        add     edi,eax
        mov     eax,color
        push    ax
        push    ax
        pop     eax
clear2:
        mov     ecx,xlen
        shr     ecx,1
        rep     stosd
        adc     ecx,ecx
        rep     stosw
        add     edi,esi
        dec     ylen
        jnz     clear2
ife ?FLAT
        pop     es
endif
        ret

fill64k endp

mainCRTStartup proc c
ifdef _VESA32_
		call VesaInit
endif        
        call main
ifdef _VESA32_
		call VesaExit
endif
        mov  ah,4Ch
        int  21h
mainCRTStartup endp

        END mainCRTStartup
