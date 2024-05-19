
;--- sample for LZAsm + ALINK, create binary with LZASMPL.MAK

model flat,stdcall

includelib "win32.lib"
procdesc WriteConsoleA :dword,:dword,:dword,:dword, :dword
procdesc GetStdHandle :dword

dataseg

szText		db "Hello, world!",13,10
szTextSize	= $ - offset szText
dwWritten	dd 0

codeseg

	startupcode
    call GetStdHandle, -11
    mov ebx,eax
    mov eax, offset dwWritten
	call WriteConsoleA, ebx, offset szText, szTextSize, eax, 0
	exitcode
