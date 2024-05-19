
;--- sample demostrating threads with HX
;--- main thread is waiting for user input with
;--- GetNumberOfConsoleInputEvents + ReadConsoleInput

;--- this sample uses win32inc Masm includes

	.386
	.MODEL FLAT, stdcall
	option casemap:none

WIN32_LEAN_AND_MEAN equ 1
	.nolist
	.nocref
	include windows.inc
	.cref
	.list

CStr macro y:req
local sym
	.const
  ifidni <y>,<"">
	sym db 0
  else
	sym db y,0
  endif
	 .code
	exitm <offset sym>
	endm

	.DATA

g_hConOut   dd 0
g_hConInp   dd 0
g_hThread1  dd 0
g_hThread2  dd 0
g_PosX		dd 2
g_PosY		dd 7
g_bCancel	db 0

	.CODE

thread1proc proto stdcall :dword
thread2proc proto stdcall :dword

;--- simple printf emulation (no need for a CRT)

printf proc c pszFormat:ptr BYTE, parms:VARARG

local	dwWritten:DWORD
local	szText[256]:byte

	invoke wvsprintf, addr szText, pszFormat, addr parms
	lea ecx, dwWritten
	invoke WriteConsole, g_hConOut, addr szText, eax, ecx, 0
	ret
	align 4
printf endp

;*** main

main proc c

local	threadid1:dword
local	threadid2:dword
local	dwWritten:DWORD
local	dwNum:dword
local	dwRead:DWORD
local	coord:COORD
local	ir:INPUT_RECORD
local	csbi:CONSOLE_SCREEN_BUFFER_INFO
local	str1[80]:byte

	invoke GetStdHandle, STD_OUTPUT_HANDLE
	mov g_hConOut,eax
	invoke GetStdHandle, STD_INPUT_HANDLE
	mov g_hConInp,eax

	invoke SetConsoleMode, g_hConInp, 0

	invoke GetConsoleScreenBufferInfo, g_hConOut, addr csbi

;--- clear the screen

	mov coord.X, 0
	mov coord.Y, 0
	movzx esi, csbi.dwSize.Y
	.while (esi)
		movzx edi, csbi.dwSize.X
		push 0
		invoke FillConsoleOutputAttribute, g_hConOut, 07h, edi, coord, esp
		invoke FillConsoleOutputCharacter, g_hConOut, '±', edi, coord, esp
		pop eax
		inc coord.Y
		dec esi
	.endw

;--- now write a blue rectangle as "text window"

;--- first calculate its position so it is centered

	movzx eax, csbi.dwSize.X
	sub eax, 60
	jc @F
	shr eax,1
	mov g_PosX, eax
@@:
	movzx eax, csbi.dwSize.Y
	sub eax, 7
	jc @F
	shr eax,1
	mov g_PosY, eax
@@:
	mov eax,g_PosX
	mov ecx,g_PosY
	mov coord.X, ax
	mov coord.Y, cx
	mov esi, 7
	.while (esi)
	   lea ecx, dwWritten
	   invoke FillConsoleOutputAttribute, g_hConOut, 17h, 60, coord, ecx
	   lea ecx, dwWritten
	   invoke FillConsoleOutputCharacter, g_hConOut, ' ', 60, coord, ecx
	   dec esi
	   inc coord.Y
	.endw

;--- set cursor to screen bottom

	movzx eax, csbi.dwSize.Y
	dec eax
	mov coord.X,0
	mov coord.Y,ax
	invoke SetConsoleCursorPosition, g_hConOut, coord

;--- create 2 threads

	lea eax,threadid1
	invoke CreateThread, 0, 4000h, offset thread1proc,0,0,eax
	mov g_hThread1,eax
	and eax,eax
	jz exit
	lea eax,threadid2
	invoke CreateThread, 0, 4000h, offset thread2proc,0,0,eax
	mov g_hThread2,eax
	and eax,eax
	jz exit

;--- wait for ESC to be pressed

	mov dwNum, 0
	mov eax, g_PosX
	mov ecx, g_PosY
	add eax, 1
	add ecx, 5
	mov coord.X, ax
	mov coord.Y, cx
	.while (1)
		invoke GetNumberOfConsoleInputEvents, g_hConInp, addr dwRead
		lea ebx,str1
		invoke wsprintf, ebx, CStr("main thread: %u loops, con events: %u, esp=%X"), dwNum, dwRead, esp
		lea ecx, dwWritten
		invoke WriteConsoleOutputCharacter, g_hConOut, ebx, eax, coord, ecx
		inc dwNum
		.if (dwRead)
			.while (dwRead)
				invoke ReadConsoleInput, g_hConInp, addr ir, 1, addr dwWritten
				.if ((ir.EventType == KEY_EVENT) && (ir.Event.KeyEvent.bKeyDown))
					mov al, ir.Event.KeyEvent.uChar.AsciiChar
					.break .if (al == 1bh)
				.endif
				dec dwRead
				mov al,0
			.endw
			.break .if (al == 1bh)
		.else
			invoke Sleep, 0
		.endif
	.endw

;--- request threads to terminate

	mov g_bCancel, TRUE

;--- wait till they are terminated

	push g_hThread2
	push g_hThread1
	mov edx, esp
	invoke WaitForMultipleObjects, 2, edx, TRUE, 1000
	add esp, 2*4

	xor eax,eax
exit:
	ret
	align 4

main    endp

;*** 1. thread ***

thread1proc proc uses ebx lParam:dword

local	num:dword
local	coord:COORD
local	szText[80]:byte

	mov eax, g_PosX
	mov ecx, g_PosY
	add eax, 1
	add ecx, 1
	mov coord.X, ax
	mov coord.Y, cx
	mov num,0
	.repeat
		lea ebx,szText
		invoke wsprintf, ebx, CStr("thread 1: %u loops, esp=%X"), num, esp
		push 0
		invoke WriteConsoleOutputCharacter, g_hConOut, ebx, eax, coord, esp
		pop eax
		inc num
	.until (g_bCancel)
	ret
	align 4

thread1proc endp

;*** 2. thread ***

thread2proc proc uses ebx lParam:dword

local	num:dword
local	coord:COORD
local	szText[80]:byte

	mov eax, g_PosX
	mov ecx, g_PosY
	add eax, 1
	add ecx, 3
	mov coord.X, ax
	mov coord.Y, cx
	mov num,0
	.repeat
		lea ebx,szText
		invoke wsprintf, ebx, CStr("thread 2: %u loops, esp=%X"), num, esp
		push 0
		invoke WriteConsoleOutputCharacter, g_hConOut, ebx, eax, coord, esp
		pop eax
		inc num
	.until (g_bCancel)
	ret
	align 4

thread2proc endp

mainCRTStartup proc c
	call main
	invoke ExitProcess, eax
mainCRTStartup endp

	END
