
;*** "hello world" in MASM syntax for MASM/POASM 
;*** uses Win32 API
;*** type "nmake /f sample2m.mak" to create the binary

	.386
	.MODEL FLAT, stdcall
	option casemap:none

STD_OUTPUT_HANDLE equ -11

WriteConsoleA proto :dword, :dword, :dword, :dword, :dword
GetStdHandle  proto :dword
ExitProcess   proto :dword

	.CONST

szString    db 13,10,"hello, world.",13,10
ifdef __POASM__
LSTRING		equ sizeof szString	;POASM has problems with $ operator
else
LSTRING		equ $ - szString
endif

	.CODE

main    proc

local   dwWritten:dword
local   hConsole:dword

	invoke GetStdHandle, STD_OUTPUT_HANDLE
	mov hConsole,eax

	invoke WriteConsoleA, hConsole, addr szString, LSTRING, addr dwWritten, 0

	xor eax,eax
	ret
main    endp

;--- entry

mainCRTStartup  proc c
	invoke main
	invoke ExitProcess, eax
mainCRTStartup endp

	END mainCRTStartup
