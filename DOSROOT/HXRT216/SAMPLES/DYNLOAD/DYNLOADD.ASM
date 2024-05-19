
;*** dll to be loaded by dynloada.exe
;*** uses DOS API

		.386
		.MODEL FLAT, stdcall
        option casemap:none

        include macros.inc
        include ascii.inc

DLL_PROCESS_ATTACH	equ 1
DLL_PROCESS_DETACH	equ 0

		.CODE

wvsprintfA proto stdcall :ptr byte, :ptr byte, :ptr	

;--- simple printf impelementation

printf	proc c uses esi psz:ptr byte, parms:VARARG 

local	szText[256]:byte

		invoke wvsprintfA, addr szText, psz, addr parms
		lea esi, szText
        .while (1)
        	lodsb
            .break .if (!al)
            .if (al == 10)
            	mov dl,13
                mov ah,2
                int 21h
                mov al,10
            .endif
            mov dl,al
            mov ah,2
            int 21h
        .endw
		ret
printf	endp

DllFunction1 proc stdcall public rc:dword

		invoke printf, CStr(<"dynloadd: in DllFunction1",10>)
		mov eax,rc
		mov dword ptr [eax],12345678h
		mov eax,1
		ret
DllFunction1 endp

DllFunction2 proc stdcall public rc:dword

		invoke printf, CStr(<"dynloadd: in DllFunction2",10>)
		mov eax,rc
		mov dword ptr [eax],87654321h
		mov eax,1
		ret
DllFunction2 endp

;*** DllMain ***

DllMain proc stdcall public handle:dword,reason:dword,dwReserved:dword

		mov    eax,reason
        .if (eax == DLL_PROCESS_ATTACH)
			invoke printf, CStr(<"dynloadd: DllMain, process attach",10>)
        .elseif (eax == DLL_PROCESS_DETACH)
			invoke printf, CStr(<"dynloadd: DllMain, process detach",10>)
        .endif
		mov 	eax,1
		ret
DllMain endp

		END DllMain

