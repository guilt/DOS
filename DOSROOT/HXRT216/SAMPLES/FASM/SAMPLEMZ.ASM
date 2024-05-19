
;  SAMPLEMZ.ASM FASM Sample for a 32-bit DPMI client.
;  To assemble (+link), use:
;     fasm SampleMZ.asm

;  FASM cannot output an object module in Intel OMF format.
;  That is, if FASM is used to produce a DOS MZ binary, no linker
;  can be used. To include DPMI host HDPMI32, it has to be included
;  as binary object (see STANDALONE below). With the host included,
;  binary size will increase by about 34 kB.

    format MZ

LF      equ     10
CR      equ     13

STANDALONE	equ	1	;1=standalone binary, with DPMI host included

	entry _TEXT:start
    
	segment _TEXT

    use16

if STANDALONE
inithdpmi:
	include "%HXINC%\HDPMI32.INC"
end if

start:
	push cs
    pop ds
    mov ax, ss
    mov cx, es
    sub ax, cx
    mov bx, sp
    shr bx, 4
    inc bx
    add bx, ax          ;release unused DOS memory
    mov ah, 4Ah
    int 21h
    mov ax, 1687h       ;DPMI host installed?
    int 2Fh
    and ax, ax
    jz havehost
if STANDALONE
    push cs				;HDPMI init code returns with a RETF!
    call inithdpmi
else
    mov [execs],ds
    push ds
    pop es
    mov dx, szHDPMI32	;try to load HDPMI32 (must be in current directory)
    mov bx, execp
    mov ax, 4B00h
    int 21h
end if    
    mov ax, 1687h       ;is DPMI host now installed?
    int 2Fh
    and ax, ax
    jnz nohost
     
havehost:    
    push es             ;save DPMI entry address
    push di
    and si, si          ;requires host client-specific DOS memory?
    jz nomemneeded
    mov bx, si
    mov ah, 48h         ;alloc DOS memory
    int 21h
    jc nomem
    mov es, ax
nomemneeded:
    mov bp, sp
    mov ax, 0001        ;start a 32-bit client
    call far [bp]       ;initial switch to protected-mode
    jc initfailed
                        ;now in protected-mode
    mov cx,1            ;get a descriptor for the 32-bit code segment
    mov ax,0
    int 31h
    jc dpmierr
    mov bx,ax
    mov dx,_TEXT32
    mov cx,dx
    shl dx,4
    shr cx,12
    mov ax,7            ;set base
    int 31h
    or dx,-1
    xor cx,cx
    mov ax,8            ;set limit
    int 31h
    mov cx,cs
    lar cx,cx
    shr cx,8
    or  ch,40h          ;make a 32bit CS
    mov ax,9
    int 31h
    push bx
    push start32
    retf                ;jump to 32bit CS
nohost:
    mov dx, dErr1
error:    
    mov ah, 9
    int 21h
    mov ax, 4C00h
    int 21h
nomem:
    mov dx, dErr2
    jmp error
initfailed:
    mov dx, dErr3
    jmp error
dpmierr:
    mov dx, dErr4
    jmp error

;	segment _DATA

    use16

szWelcome db "welcome in protected-mode",CR,LF,'$'
dErr1 db "no DPMI host installed",CR,LF,'$'
dErr2 db "not enough DOS memory for client initialisation",CR,LF,'$'
dErr3 db "DPMI initialisation failed",CR,LF,'$'
dErr4 db "no LDT descriptors available",CR,LF,'$'
if STANDALONE=0
szHDPMI32 db "HDPMI32.EXE",0
execp dw 0
      dw dmycmd
execs dw 0
      dd 0,0
dmycmd db 0,13      
end if

;--- the 32-bit code segment

	segment _TEXT32

    use32

start32:
    mov edx, szWelcome  ;print welcome message
    mov ah,9
    int 21h
    mov ax, 4C00h       ;return to DOS
    int 21h

