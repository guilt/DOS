
; this is an example of a DPMI TSR
; it hooks irq 1 (keyboard int)
; and displays a small rectangle in the upper right corner
; of the screen which flashes when the user presses or releases a key.

	.386
	.model flat,stdcall
	option casemap:none

wsprintfA proto near c :dword, :dword, :VARARG
wsprintf textequ <wsprintfA>

	include dpmi.inc
	include macros.inc

	.DATA

flatsel  dd 0			   ;flat data selector
oldint09 df 0			   ;chain to the next keyboard handler proc

	.CODE

; this is the interrupt service routine
; the old handler is a far32 routine

int09   proc far

	push ds
	mov ds,cs:[flatsel]
	mov byte ptr ds:[0b8000h+79*2],'°'
	xor byte ptr ds:[0b8000h+79*2+1],0Fh
	pop ds
	jmp cs:[oldint09]

int09   endp

;--- _cputs() emulation. this prevents the linker from 
;--- including Win32 stuff

_cputs proc c uses esi pszText:ptr byte
	mov esi, pszText
	.while (1)
		lodsb
		.break .if (!al)
		mov dl,al
		mov ah,2
		int 21h
	.endw
	ret
_cputs endp

;--- main: do all initialization and go resident

main proc c

local	psp:dword
local	rmcs:RMCS
local	szText[80]:byte

	mov [flatsel],ds
	mov [psp],ebx

; wsprintf will increase the size of this tsr by a remarkable amount
; but since it is in extended memory, it will not cost any dos memory

	invoke wsprintf, addr szText, CStr(<"current base is %X",13,10>), esi
	invoke _cputs, addr szText

; now change the keyboard interrupt vector

	mov bl,9
	mov ax,0204h
	int 31h
	mov dword ptr [oldint09+0],edx
	mov word ptr [oldint09+4],cx
	mov ecx,cs
	mov edx,offset int09
	mov ax,0205h
	int 31h

; now let's release the environment.
; note that it is a dpmi convention to place a selector
; for the environment at offset 2Ch in the psp.
; some DPMI hosts will not allow the environment to be freed

	mov ebx,[psp]
	xor eax,eax
	xchg ax,[ebx+002Ch]
	push es
	mov es,eax
	mov ah,49h
	int 21h
	pop es

; now the tsr can go resident, but int 21h, AH=31h is not supported
; by most DPMI servers. So it has to be done by using int 31h, ax=0300h.
; the DOS size of the TSR can be restricted to the first 128 bytes of psp

	xor ecx,ecx
	mov rmcs.rSSSP,ecx	   ;clear SS:SP
	mov rmcs.rFlags,cx	   ;clear flags
	mov rmcs.rDX,8		   ;set DX=8 (no of paragraphs)
	mov rmcs.rAX,3100h	   ;set AX=3100h
	lea edi,rmcs		   ;es:edi points to real mode call struct
	mov bx,0021h
	mov ax,0300h
	int 31h

; the above call shouldn't return. If it does, it's a severe error

	invoke _cputs,CStr(<"error: returned from sim real mode int 21h,ax=3100h?",13,10>)

; restore the hooked vector in this case

	mov cx,word ptr [oldint09+4]
	mov edx,dword ptr [oldint09+0]
	mov bl,9
	mov ax,0205h
	int 31h
	ret

main endp

; startup code. 
; segment registers are:
;   cs=ss=ds=es: flat
;   esi=PE base
;   ebx=linear address PSP

mainCRTStartup proc c public
	call main
	mov ah,4ch
	int 21h
mainCRTStartup endp

	END
