
;*** same as SAMPLE.ASM, but without "proto" and "invoke"
;*** to make it WASM compatible

	.386
	.MODEL FLAT

STD_OUTPUT_HANDLE equ -11

externdef _WriteConsoleA@20:near
externdef _GetStdHandle@4:near
externdef _ExitProcess@4:near

	.CONST

szString	db 13,10,"hello, world.",13,10
LSTRING		equ $ - szString

	.CODE

main proc

local   dwWritten:dword
local   hConsole:dword

	push STD_OUTPUT_HANDLE
	call _GetStdHandle@4
	mov  ebx,eax

	push 0
	lea  eax, dwWritten
	push eax
	push LSTRING
	push offset szString
	push ebx
	call _WriteConsoleA@20

	xor eax,eax
	ret
main endp

;--- entry

_mainCRTStartup  proc
	call main
	push eax
	call _ExitProcess@4
_mainCRTStartup endp

	END _mainCRTStartup
