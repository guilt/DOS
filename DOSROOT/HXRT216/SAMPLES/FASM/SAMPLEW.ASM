
;--- a Win32 console application with FASM
;--- linked with HX's DPMIST32.BIN, so it also runs in DOS with HX

format MS COFF

section '.data' data readable writeable

dwWritten dd 0
szText db 'hello world',13,10
sizeText = $ - szText

extrn '__imp__ExitProcess@4' as ExitProcess:dword
extrn '__imp__WriteConsoleA@20' as WriteConsole:dword
extrn '__imp__GetStdHandle@4' as GetStdHandle:dword

STD_OUTPUT_HANDLE	equ -11

section '.text' code executable readable

public _mainCRTStartup

_mainCRTStartup:

	push	STD_OUTPUT_HANDLE
    call	[GetStdHandle]
    push	0
	push	dwWritten
	push	sizeText
	push	szText
	push	eax
	call	[WriteConsole]
	push	0
	call	[ExitProcess]

