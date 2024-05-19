
;--- MASM source using Win32 API.
;--- It will be linked with WIN32 emulation libraries DKRNL32(S).LIB
;--- and DUSER32(S).LIB, so a subset of Win32 API can be used here.

	.386
	.MODEL FLAT, stdcall
	option casemap:none

if 1
;--- these includes are supplied with HX. It is only a subset of the
;--- Win32 API, just to be able to assemble the HX source without any
;--- help from external includes. It will work for this sample, though.
	include winbase.inc
	include wincon.inc
	include winuser.inc
else
;--- either use win32inc include files (for MASM/POASM), which may be 
;--- downloaded from http://www.japheth.de/Download/win32inc.zip
;--- or use the include files supplied with MASM32.
  if 1
WIN32_LEAN_AND_MEAN equ 1
	include windows.inc	
  else
	include \masm32\include\windows.inc
	include \masm32\include\kernel32.inc
	include \masm32\include\user32.inc
  endif
endif        
	include macros.inc	;some general purpose macros (CStr()...)

MEMREQ  equ 10000h
INITCNT equ 10h

	.DATA

hConsoleOut DWORD NULL
hConsoleInp DWORD NULL
pattern 	dd 0

	.CODE

;--- emulate printf() crt function

printf  proc c pszFormat:ptr BYTE, args:VARARG

local   dwWritten:DWORD
local   szText[256]:byte

	invoke wvsprintf, addr szText, pszFormat, addr args
	mov ecx, eax
	invoke WriteConsole, hConsoleOut, addr szText, ecx, addr dwWritten, NULL
	ret

printf  endp

;--- emulate _getch() crt function

_getch  proc

local   dwRead:DWORD
local   bChar:BYTE

	invoke SetConsoleMode, hConsoleInp, 0
	invoke ReadConsole, hConsoleInp, addr bChar, 1, addr dwRead, NULL
	.if (dwRead)
		movzx eax, bChar
	.endif
	ret
_getch  endp

;--- main

main PROC c

local   dwMemTotal:dword
local   dwBlocks:dword
local   hHeap:HANDLE
local   dwCnt:dword

	invoke GetStdHandle, STD_OUTPUT_HANDLE
	mov hConsoleOut, eax
	invoke GetStdHandle, STD_INPUT_HANDLE
	mov hConsoleInp, eax

	xor eax,eax
	mov dwMemTotal,eax
	mov dwBlocks, eax
	invoke GetProcessHeap
	mov hHeap, eax

;--------------------------------- now allocate a number of memory blocks

	mov dwCnt,INITCNT
	.while (dwCnt)
		invoke	HeapAlloc, hHeap, 0, MEMREQ
		push eax
		invoke printf, CStr(<'alloc 64 kB - handle=%X',13,10>), eax
		pop eax
		.break .if (!eax)

		add dwMemTotal, MEMREQ
		inc dwBlocks

;--------------------------------- clear the block just to be sure
;--------------------------------- real memory is underlying

		mov edi, eax
		mov ecx,MEMREQ/4
		mov eax,pattern
		cld
		rep stosd
		inc dword ptr pattern

		dec dwCnt
	.endw

	invoke printf, CStr(<13,10>)

	mov eax, dwMemTotal
	mov edx, 0
	mov ecx, 1024
	div ecx
	invoke printf, CStr(<"allocated %u blocks (%u kB)",13,10>), dwBlocks, eax
	invoke printf, CStr("press a key to terminate program ")
	invoke _getch
	invoke printf, CStr(<13,10>)
	ret

main ENDP

;--- mainCRTStartup is the program entry
;--- the initialization code jumps to this location

mainCRTStartup proc c public

	call main
	invoke ExitProcess, eax

mainCRTStartup endp

	END mainCRTStartup

