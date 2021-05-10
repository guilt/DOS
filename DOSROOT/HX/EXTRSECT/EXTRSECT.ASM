
;--- extract section contents from a PE/MZ binary
;--- the MZ binary is extraced full (without MZ header)
;--- copyright japheth.

	.386
	.MODEL FLAT, stdcall
	option casemap:none
	option proc:private

WIN32_LEAN_AND_MEAN equ 1
	.nolist
	.nocref
	include windows.inc
	include stdlib.inc
	include stdio.inc
	.list
	.cref

lf	equ 0Ah
cr	equ 0Dh

CStr macro text:VARARG
local x
	.const
x	db text,0
	.code
	exitm <offset x>
	endm

_setargv proto c

	.DATA

hFileOut	DWORD 0		;handle for file to write
hFileInp	DWORD 0		;handle for input file
pszFileInp 	LPSTR 0
pszFileOut 	LPSTR 0

pObjtab		LPSTR 0		;dyn allocated memory for object table
dwObjSize	DWORD 0		;size of object table
dwSection	DWORD 0		;section number for -x
fVerbose	BYTE 0		;display maximum msgs
fQuiet		BYTE 0
fInclude	BYTE 0
fMZ			BYTE 0
fJustOne	BYTE 0		;one section only
fHeader		BYTE 0
fExpectNumber	BYTE 0

_errno	dd 0

	.CONST

szLF	db lf,0

	.CODE

;--- get a decimal number
;--- esi -> text
;--- out: number in EAX
;--- C on error

getdec proc
	mov cl,0
	xor edx, edx
nextitem:
	lodsb
	cmp al,'0'
	jb done
	cmp al,'9'
	ja done
	push eax
	mov eax,edx
	mov edx,10
	mul edx
	mov edx, eax
	pop eax
	sub al,'0'
	movzx eax,al
	add edx, eax
	inc cl
	jmp nextitem
done:
	mov eax, edx
	cmp cl,1
	ret
getdec endp

;--- scan command line for options

getoption proc uses esi pszArgument:LPSTR

	mov esi, pszArgument
	mov eax,[esi]
	cmp al,'/'
	jz @F
	cmp al,'-'
	jnz getoption_1
@@:
	shr eax,8
	or al,20h
	cmp ax,"v"
	jnz @F
	mov fVerbose, 1
	jmp done
@@:
	cmp ax,"q"
	jnz @F
	mov fQuiet, 1
	jmp done
@@:
	cmp ax,"i"
	jnz @F
	mov fInclude, 1
	jmp done
@@:
	cmp ax,"h"
	jnz @F
	mov fHeader, 1
	jmp done
@@:
	cmp ax,"m"
	jnz @F
	mov fMZ, 1
	jmp done
@@:
	cmp ax,"x"
	jnz @F
	mov fJustOne, 1
	mov fExpectNumber, 1
	jmp done
@@:
	jmp error
getoption_1:
	.if (fExpectNumber)
		mov fExpectNumber, 0
		call getdec
		jc error
		mov dwSection, eax
		jmp done
	.endif
	.if (!pszFileInp)
		mov pszFileInp, esi
	.elseif (!pszFileOut)
		mov pszFileOut, esi
	.else
		jmp error
	.endif
done:
	clc
	ret
error:
	stc
	ret
getoption endp

;--- write content of a section

WriteContent proc pMem:ptr, dwSize:dword

local	szLine[80]:byte

	.if (fInclude)
		pushad
		mov esi,pMem
		mov ecx,dwSize
		mov ebx,0
		.while (ecx >= 16)
			push ecx
			mov ecx, 16
			sub esp, 16*4
			mov edi, esp
			xor eax, eax
@@:
			lodsb
			stosd
			loop @B
			invoke wsprintf, addr szLine, CStr("db %3u,%3u,%3u,%3u,%3u,%3u,%3u,%3u,%3u,%3u,%3u,%3u,%3u,%3u,%3u,%3u",cr,lf )
			add esp, 16*4
			invoke _lwrite, hFileOut, addr szLine, eax
			pop ecx
			sub ecx,16
		.endw
		.if (ecx)
			push ecx
			lea ebx, szLine
			invoke wsprintf, ebx, CStr("db ")
			add ebx, eax
			pop ecx
			.repeat
				xor eax, eax
				lodsb
				push ecx
				.if (ecx > 1)
					invoke wsprintf, ebx, CStr("%3u,"), eax
				.else
					invoke wsprintf, ebx, CStr("%3u",cr,lf), eax
				.endif
				pop ecx
				add ebx, eax
				dec ecx
			.until (ecx == 0)
			invoke strlen, addr szLine
			invoke _lwrite, hFileOut, addr szLine, eax
		.endif
		popad
	.else
		invoke _lwrite, hFileOut, pMem, dwSize
		.if (eax != dwSize)
			invoke printf, CStr("file write error",lf)
			xor eax, eax
		.endif
	.endif
	ret
WriteContent endp

;*** main proc ***

main proc c public argc:dword,argv:dword

local	dwWritten:DWORD
local	dwSizeStubOld:DWORD
local	bError:DWORD
local	mzhdr[40h]:BYTE
local	pehdr:IMAGE_NT_HEADERS


	mov hFileInp, -1
	mov hFileOut, -1
	mov bError, TRUE
	cmp argc,2
	jb displayusage
	mov ecx, 1
	mov ebx,argv
	.while (ecx < argc)
		push ecx
		invoke getoption, dword ptr [ebx+ecx*4]
		pop ecx
		jc displayusage
		inc ecx
	.endw
	cmp pszFileOut, 0
	jz displayusage
;--------------------------- open input binary

	invoke _lopen, pszFileInp, OF_READ
	.if (eax == -1)
		movzx eax,ax
		invoke printf, CStr("cannot open file %s [%X]",lf), pszFileInp, eax
		jmp main_ex
	.endif
	movzx eax,ax
	mov hFileInp,eax

	invoke _lread, hFileInp, addr mzhdr, 40h
	.if (eax != 40h)
		invoke printf, CStr("%s is not a valid executable",lf), pszFileInp
		jmp main_ex
	.endif
	movzx eax,word ptr mzhdr
;----------------------------------------- is it a executable?
	.if (eax == "ZM")
		mov eax,dword ptr mzhdr+3Ch
		mov dwSizeStubOld, eax
	.else
		invoke printf, CStr("%s is not an MZ binary object",lf), pszFileInp
		jmp main_ex
	.endif

	.if (fMZ)
		movzx eax,word ptr [mzhdr+8]	;size of header
		shl eax,4
		push eax
		invoke _llseek, hFileInp, eax, FILE_BEGIN 
		movzx eax,word ptr [mzhdr+4]
		dec eax
		shl eax,9
		movzx ecx,[word ptr mzhdr+2]
		add eax, ecx
		pop ecx
		sub eax, ecx
		mov ebx, eax
		invoke malloc, eax
		.if (!eax)
			invoke printf, CStr("out of memory",lf)
			jmp main_ex
		.endif
		mov esi, eax
		invoke _lread, hFileInp, esi, ebx
		invoke _lclose, hFileInp
		mov hFileInp, -1
		invoke _lcreat, pszFileOut, 0
		.if (eax == -1)
			invoke GetLastError
			invoke printf, CStr("cannot create file '%s' [%X]",lf), pszFileOut, eax
			jmp main_ex
		.endif
		mov hFileOut, eax
		invoke WriteContent, esi, ebx
		jmp file_done
	.endif

	invoke _llseek, hFileInp, dwSizeStubOld, FILE_BEGIN 
	.if (eax == -1)
		invoke printf, CStr("%s is not a PE binary - lseek() failed",lf),pszFileInp
		jmp main_ex
	.endif
	invoke memset, addr pehdr, 0, sizeof pehdr
	invoke _lread, hFileInp, addr pehdr.Signature, sizeof IMAGE_NT_HEADERS.Signature
	.if (eax == 0)
		invoke printf, CStr("%s has no valid PE format - read() failed",lf), pszFileInp
		jmp main_ex
	.endif
	movzx eax,word ptr pehdr
	.if (eax != "EP")
		invoke printf, CStr("%s has no valid PE format - magic bytes PE not found",lf), pszFileInp
		jmp main_ex
	.endif
	invoke _lread, hFileInp, addr pehdr.FileHeader, sizeof IMAGE_NT_HEADERS.FileHeader
	.if (eax != sizeof IMAGE_NT_HEADERS.FileHeader)
		invoke printf, CStr("Error reading FileHeader",lf)
		jmp main_ex
	.endif
	invoke memset, addr pehdr.OptionalHeader, 0, sizeof pehdr.OptionalHeader
	movzx eax, pehdr.FileHeader.SizeOfOptionalHeader
	.if (eax > sizeof IMAGE_OPTIONAL_HEADER)
		invoke printf, CStr("Size of optional Header too large",lf)
		jmp main_ex
	.endif
	push eax
	invoke _lread, hFileInp, addr pehdr.OptionalHeader, eax
	pop ecx
	.if (eax != ecx)
		invoke printf, CStr("Error reading optional Header",lf)
		jmp main_ex
	.endif

	.if (fVerbose)
		invoke printf, CStr("loading object table...",lf)
	.endif

	movzx eax,pehdr.FileHeader.NumberOfSections
	mov ecx,sizeof IMAGE_SECTION_HEADER
	mul ecx
	mov dwObjSize,eax
	invoke malloc, eax
	.if (!eax)
		invoke printf, CStr("memory error",lf)
		jmp main_ex
	.endif
	mov pObjtab, eax
	invoke _lread, hFileInp, pObjtab, dwObjSize
	.if (!eax)
		invoke printf, CStr("Couldn't read object table",lf)
		jmp main_ex
	.endif

	invoke malloc, pehdr.OptionalHeader.SizeOfImage
	.if (!eax)
		invoke printf, CStr("out of memory",lf)
		jmp main_ex
	.endif
	mov esi, eax

	movzx ecx, pehdr.FileHeader.NumberOfSections
	mov edi, pObjtab
	.while (ecx)
		push ecx
		.if ([edi].IMAGE_SECTION_HEADER.SizeOfRawData)
			invoke _llseek, hFileInp, [edi].IMAGE_SECTION_HEADER.PointerToRawData,0
			mov ecx, [edi].IMAGE_SECTION_HEADER.VirtualAddress
			add ecx, esi
			invoke _lread, hFileInp, ecx, [edi].IMAGE_SECTION_HEADER.SizeOfRawData
			.if (eax != [edi].IMAGE_SECTION_HEADER.SizeOfRawData)
				invoke printf, CStr("file format error",lf)
				jmp main_ex
			.endif
		.endif
		pop ecx
		add edi, sizeof IMAGE_SECTION_HEADER
		dec ecx
	.endw

	.if (fVerbose)
		invoke printf, CStr("handle relocations",lf)
	.endif

;--- ?what?
	cmp [fHeader],1
	jz norelocadjust

	mov ecx, pehdr.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC*sizeof IMAGE_DATA_DIRECTORY].Size_
	mov edi, pehdr.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC*sizeof IMAGE_DATA_DIRECTORY].VirtualAddress
	.if (ecx)
		add edi, esi
		mov edx, pehdr.OptionalHeader.SizeOfHeaders
		push edi
nextpage:
		mov ebx, [edi+0]
		mov ecx, [edi+4]
		jecxz reldone
		add ecx, edi
		add edi, 2*4
		.while (ecx > edi)
			mov ax,[edi]
			.if (ah & 0F0h)
				and eax,0FFFh
				add eax, ebx
				sub [esi+eax],edx
			.endif
			add edi,2
		.endw
		jmp nextpage
reldone:
		pop edi
		mov [edi],dx		;save size of header in first page ofs
	.endif

norelocadjust:

	invoke _lclose, hFileInp
	mov hFileInp, -1

	invoke _lcreat, pszFileOut, 0
	.if (eax == -1)
		invoke GetLastError
		invoke printf, CStr("cannot create file '%s' [%X]",lf), pszFileOut, eax
		jmp main_ex
	.endif
	mov hFileOut, eax

	.if (fHeader)
		invoke WriteContent, addr pehdr, sizeof pehdr
		.if (fVerbose)
			invoke printf, CStr("PE header written",lf)
		.endif
		movzx ecx, pehdr.FileHeader.NumberOfSections
		mov eax, sizeof IMAGE_SECTION_HEADER
		mul ecx
		invoke WriteContent, pObjtab, eax
		.if (fVerbose)
			invoke printf, CStr("section table written",lf)
		.endif
	.endif

	movzx ecx, pehdr.FileHeader.NumberOfSections

	mov edi, pObjtab
	.if (fJustOne)
		mov eax, [dwSection]
		cmp eax, ecx
		jnc file_done
		mov edx, sizeof IMAGE_SECTION_HEADER
		mul edx
		add edi, eax
		mov ecx, 1
	.endif

;--- write the sections, the physical size!

	.while (ecx)
		push ecx
		.if ([edi].IMAGE_SECTION_HEADER.SizeOfRawData)
;			 invoke _lwrite, hFileOut, addr [edi].IMAGE_SECTION_HEADER.SizeOfRawData, 4
			mov ecx, [edi].IMAGE_SECTION_HEADER.VirtualAddress
			add ecx, esi
;			invoke _lwrite, hFileOut, ecx, [edi].IMAGE_SECTION_HEADER.SizeOfRawData
;			.if (eax != [edi].IMAGE_SECTION_HEADER.SizeOfRawData)
			.if (fHeader)
				invoke WriteContent, ecx, [edi].IMAGE_SECTION_HEADER.SizeOfRawData
			.else
				invoke WriteContent, ecx, [edi].IMAGE_SECTION_HEADER.Misc.VirtualSize
			.endif
			.if (fVerbose)
				invoke printf, CStr("section %.8s written",lf), addr [edi].IMAGE_SECTION_HEADER.Name_
			.endif
		.endif
		pop ecx
		add edi, sizeof IMAGE_SECTION_HEADER
		dec ecx
	.endw
file_done:
	invoke free, esi

	.if (!fQuiet)
		invoke printf, CStr("extrsect: file '%s' processed",lf), pszFileInp
	.endif

	mov bError, FALSE
main_ex:
	.if (hFileOut != -1)
		invoke _lclose, hFileOut
	.endif
	.if (hFileInp != -1)
		invoke _lclose, hFileInp
	.endif
	mov eax, bError
	ret
displayusage:
	invoke printf, CStr("extrsect v1.3: extract contents from a PE or MZ binary",lf)
	invoke printf, CStr("usage: extrsect [options] src_file dst_file",lf)
	invoke printf, CStr("  options:",lf)
	invoke printf, CStr("    -v: verbose",lf)
	invoke printf, CStr("    -h: extract PE header as well",lf)
	invoke printf, CStr("    -q: quiet",lf)
	invoke printf, CStr("    -m: assume src_file is a simple MZ binary",lf)
	invoke printf, CStr("    -i: create ASM include as output",lf)
	invoke printf, CStr("    -x n: extract section n only (PE)",lf)
	jmp main_ex
main endp

	END

