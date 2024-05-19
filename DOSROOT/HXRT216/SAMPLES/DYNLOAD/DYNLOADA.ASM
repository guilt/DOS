
;--- test dynamic load functions of dpmild32 (PE loader)
;--- this app doesn't use dkrnl32 at all. it will load a dll (dynloadd.dll),
;--- get an export's value, call this procedure and at last free the dll.
;--- This is done by using the PE loader's API directly

		.386
		.MODEL FLAT,stdcall
        option casemap:none

        include macros.inc

		.CODE

;--- use the wvsprintfA function included in duser32s.lib,
;--- which is small and can be used without initialization

wvsprintfA proto stdcall :ptr byte, :ptr byte, :ptr	

;--- simple printf implementation

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

main	proc c public

local	hModule:DWORD
local	var1:dword

        invoke printf, CStr(<"app: calling int 21h, ax=4B00h (LoadLibrary), edx='dynloadd.dll'",10>)
		mov edx, CStr("dynloadd.dll")
        mov ax,  4B00h
        int 21h
        .if (!CARRY?)
        	mov ebx, eax
			invoke printf, CStr(<"app: int 21h, ax=4B00h returned eax=%X",10>),eax
            mov edx, CStr("DllFunction1")
            mov ax, 4B81h
            int 21h
            .if (!CARRY?)
            	mov esi, eax
				invoke printf, CStr(<"app: int 21h, ax=4B81h (GetProcAddress) returned eax=%X",10>),eax
                lea eax, var1
                call esi
            .else
				invoke printf, CStr(<"app: int 21h, ax=4B81h failed, eax=%X",10>),eax
            .endif
	        invoke printf, CStr(<"app: calling int 21h, ax=4B80h (FreeLibrary), edx=%X",10>), ebx
            mov edx, ebx
            mov ax, 4B80h
            int 21h
		.else
			invoke printf, CStr(<"app: int 21h, ax=4B00h failed, eax=%X",10>),eax
        .endif
        invoke printf, CStr(<"app: calling int 21h, ax=4C00h",10>)
		mov ax,4c00h
        int 21h
        
main	endp

		END main

