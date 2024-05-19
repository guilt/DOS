
;--- LDFIX: fix COFF objects relocations
;--- input: relocatable COFF file written by (DJGPP's) LD
;--- output: relocatable COFF file compatible with Win32 COFF linkers

;--- inspired by tool MASM2DJG by Lawrence Rust

;--- how LDFIX works:
;---  1. ensure the input file is a valid COFF object
;---  2. scan relocations of all sections
;---  3. for relocations of type DIR32(0006h) and REL32(0014h) do:
;---     - REL32: set target to 00000000
;---     - DIR32: if storage class of symbol is EXTERN or STATIC, subtract
;---       Symbol's value from target.

;---  <target> is the content of the relocations offset in section's raw data

		.386
if ?FLAT
		.MODEL FLAT, stdcall
else
		.MODEL small, stdcall
endif
		option casemap:none
		option proc:private

		include windef.inc
		include winbase.inc
        include wincon.inc
		include macros.inc

LPSTR	typedef ptr BYTE
lf		equ 0Ah

		.DATA

hStdOut         DWORD 0
hFile		 	DWORD 0		;handle for input file
pszFilename		LPSTR 0

pObjtab			LPSTR 0		;dyn allocated memory for object table
dwObjSize		DWORD 0		;size of object table
fVerbose		BYTE 0		;display maximum msgs

wvsprintfA proto stdcall :dword, :dword, :dword
;printf proto C a1:LPSTR, a2:VARARG

		.CODE

if 1

malloc	proc c public dwBytes:DWORD
		invoke GetProcessHeap
		invoke HeapAlloc, eax, 0, dwBytes
		ret
        align 4
malloc	endp

free  	proc c public pv:DWORD
		invoke GetProcessHeap
		invoke HeapFree, eax, 0, pv
		ret
        align 4
free	endp

else

malloc	proto c :dword

endif

printf  proc c pszFormat:LPSTR, args:VARARG

local   dwWritten:DWORD
local   szOut[512]:byte

        invoke wvsprintfA, addr szOut, pszFormat, addr args
        invoke lstrlen, addr szOut
        lea ecx, dwWritten
        invoke WriteFile, hStdOut, addr szOut, eax, ecx, 0
        ret
        align 4
printf  endp


;--- scan command line for options


getoption proc uses esi pszArgument:LPSTR

		mov 	esi, pszArgument
        mov		eax,[esi]
		cmp 	al,'/'
		jz		@F
		cmp 	al,'-'
		jnz 	getoption_1
@@:
		shr		eax,8
        or		al,20h
        cmp		ax,"v"
        jnz		@F
        mov		fVerbose, 1
        jmp		done
@@:
error:
		stc
		ret
getoption_1:
		.if (!pszFilename)
			mov pszFilename, esi
		.else
			jmp	error
		.endif
done:        
		clc
		ret
        align 4
getoption endp


;*** main proc ***


main	proc c public argc:dword,argv:dword,envp:dword

local	dwSizeSymbols:DWORD
local	pSymbols:DWORD
local	dwWritten:DWORD
local	pRelocs:DWORD
local	cntFix:DWORD
local	cntClsModified:DWORD
local	bError:DWORD
local	filehdr:IMAGE_FILE_HEADER
local	szPath[MAX_PATH]:byte
local	szFile[MAX_PATH]:byte
local	pszFile:LPSTR


        invoke  GetStdHandle, STD_OUTPUT_HANDLE
        mov hStdOut, eax

		mov 	hFile,-1
		mov		bError, TRUE
		cmp 	argc,2
		jb		displayusage
		mov 	ecx, 1
		mov 	ebx,argv
		.while (ecx < argc)
			push	ecx
			invoke	getoption, dword ptr [ebx+ecx*4]
			pop 	ecx
			jc		displayusage2
			inc 	ecx
		.endw

;--------------------------- open executable
		mov 	edx,pszFilename
		and 	edx,edx
		jz		displayusage
        invoke  _lopen, edx, OF_READWRITE
		mov 	hFile,eax
		.if (eax == -1)
        	invoke	GetLastError
            push 	eax
			invoke	printf, CStr(<"cannot open file %s [%X]",lf>), pszFilename, eax
            pop		eax
            .if (eax == 5)
				invoke	printf, CStr(<"no write access permitted",lf>)
            .endif
			jmp 	main_ex
		.endif

		invoke	RtlZeroMemory, addr filehdr, sizeof filehdr

;------------------ read COFF header

		invoke	_lread, hFile, addr filehdr, sizeof IMAGE_FILE_HEADER
        
		.if (eax != sizeof IMAGE_FILE_HEADER)
			invoke	printf, CStr(<"%s is not a COFF object",lf>), pszFilename
			jmp 	main_ex
		.endif
		movzx	eax, filehdr.Machine
;----------------------------------------- is it a executable?
        .if (eax != 14Ch)
			invoke	printf, CStr(<"%s is not a COFF object",lf>), pszFilename
			jmp 	main_ex
        .endif

        movzx eax, filehdr.SizeOfOptionalHeader
		.if (eax)
			invoke	_llseek, hFile, eax, 1
        .endif

        .if (fVerbose)
			invoke	printf, CStr(<"loading object table...",lf>)
        .endif

;--- read section table
        
		movzx	eax,filehdr.NumberOfSections
		mov 	ecx,sizeof IMAGE_SECTION_HEADER
		mul 	ecx
		mov 	dwObjSize,eax
		invoke	malloc, eax
        .if (!eax)
			invoke	printf, CStr(<"memory error",lf>)
            jmp main_ex
        .endif
        mov pObjtab, eax
		invoke	_lread, hFile, pObjtab, dwObjSize
        .if (!eax)
			invoke	printf, CStr(<"Couldn't read object table",lf>)
        	jmp main_ex
        .endif

;--- read symbol table

		mov pSymbols, 0
		.if ((filehdr.PointerToSymbolTable) && (filehdr.NumberOfSymbols))
			.if (fVerbose)
				invoke printf, CStr(<"reading symbol table from %X",10>), filehdr.PointerToSymbolTable
			.endif
			mov eax, sizeof IMAGE_SYMBOL
			mul filehdr.NumberOfSymbols
			mov dwSizeSymbols, eax
			invoke malloc, eax
			.if (eax)
				mov pSymbols, eax
				invoke _llseek, hFile, filehdr.PointerToSymbolTable, 0
				invoke _lread, hFile, pSymbols, dwSizeSymbols
				.if (eax != dwSizeSymbols)
					invoke printf, CStr(<"failed to read symbol table",10>)
					invoke free, pSymbols
					mov pSymbols, 0
				.else
					.if (fVerbose)
						invoke printf, CStr(<"symbol table has been read",10>)
					.endif
				.endif
			.else
				invoke printf, CStr(<"out of memory for symbol table",10>)
                jmp main_ex
			.endif
		.endif

;--- scan section table
        
		mov edi, pObjtab
        mov cntClsModified, 0
		movzx ecx,filehdr.NumberOfSections
		.while (ecx)
        	push ecx
            mov cntFix, 0
            .if (fVerbose)
				invoke	printf, CStr(<"checking section %-8.8s",lf>), addr [edi].IMAGE_SECTION_HEADER.Name_
            .endif
            mov edx, [edi].IMAGE_SECTION_HEADER.Characteristics
            .if (edx & (IMAGE_SCN_LNK_INFO or IMAGE_SCN_LNK_REMOVE))
               	;
            .elseif (![edi].IMAGE_SECTION_HEADER.SizeOfRawData)
               	;
            .elseif (![edi].IMAGE_SECTION_HEADER.NumberOfRelocations)
               	;
            .else

;--- read in relocations for current section

               	movzx eax, [edi].IMAGE_SECTION_HEADER.NumberOfRelocations
				mov ecx, sizeof IMAGE_RELOCATION
				mul ecx
				mov esi, eax
				invoke malloc, eax
                .if (eax)
					mov ebx, eax
	                mov pRelocs, eax
		  			mov eax, [edi].IMAGE_SECTION_HEADER.SizeOfRawData
					invoke _llseek, hFile, [edi].IMAGE_SECTION_HEADER.PointerToRelocations, 0
					invoke _lread, hFile, ebx, esi

					invoke malloc, [edi].IMAGE_SECTION_HEADER.SizeOfRawData
        	        .if (eax)
                    	mov esi, eax
		  				invoke _llseek, hFile, [edi].IMAGE_SECTION_HEADER.PointerToRawData, 0
						invoke _lread, hFile, esi, [edi].IMAGE_SECTION_HEADER.SizeOfRawData
                       	movzx ecx, [edi].IMAGE_SECTION_HEADER.NumberOfRelocations
						.while (ecx)
							push ecx
							.if ([ebx].IMAGE_RELOCATION.Type_ == IMAGE_REL_I386_REL32)

;--- handle the "relative" relocations

								mov eax, [ebx].IMAGE_RELOCATION.VirtualAddress
								mov edx, [edi].IMAGE_SECTION_HEADER.VirtualAddress
								add edx, [edi].IMAGE_SECTION_HEADER.SizeOfRawData
								.if ((eax >= [edi].IMAGE_SECTION_HEADER.VirtualAddress) && (eax < edx))
									sub eax, [edi].IMAGE_SECTION_HEADER.VirtualAddress
									xor ecx, ecx
									.if (ecx != [esi+eax])
                                       	inc cntFix
										mov [esi+eax], ecx
                                        .if (fVerbose)
											invoke printf, CStr(<"REL32 fixup at %X, new value=%X",lf>), eax, ecx
       	                                .endif
									.endif
                                .else
                                	mov ecx, ebx
                                    sub ecx, pRelocs
                                    add ecx, [edi].IMAGE_SECTION_HEADER.PointerToRelocations
									invoke printf, CStr(<"warning: invalid relocation found at %X: %X",lf>), ecx, eax
								.endif
							.elseif ([ebx].IMAGE_RELOCATION.Type_ == IMAGE_REL_I386_DIR32)

;--- handle the "direct" relocations
;--- these cannot be set just to 0, the value of 
;--- the symbol has to be subtracted from the target

								mov eax, [ebx].IMAGE_RELOCATION.VirtualAddress
								mov edx, [edi].IMAGE_SECTION_HEADER.VirtualAddress
								add edx, [edi].IMAGE_SECTION_HEADER.SizeOfRawData
								.if ((eax >= [edi].IMAGE_SECTION_HEADER.VirtualAddress) && (eax < edx))
									sub eax, [edi].IMAGE_SECTION_HEADER.VirtualAddress
									.if (pSymbols)
                                    	push eax
                                        mov eax, sizeof IMAGE_SYMBOL
                                        mul [ebx].IMAGE_RELOCATION.SymbolTableIndex
                                        add eax, pSymbols
                                        mov ecx, eax
                                        pop eax
                                        movzx edx, [ecx].IMAGE_SYMBOL.StorageClass
                                        
;--- check symbols some storage classes
;--- 0002 external
;--- 0003 static
;--- 0127 GNU special "weak external" used by GPP
;--- and check ALL sections (in any case section 0000!, what about FF00-FFFF?)

                                        .if ((edx == IMAGE_SYM_CLASS_STATIC) \
                                          || (edx == IMAGE_SYM_CLASS_EXTERNAL) \
                                          || (edx == 127) \
                                          )
                                            .if (edx == 127)
                                            	mov [ecx].IMAGE_SYMBOL.StorageClass, IMAGE_SYM_CLASS_EXTERNAL
                                                inc cntClsModified
                                            .endif
	                                        mov edx, [ecx].IMAGE_SYMBOL.Value
    	                                    sub [esi+eax], edx
        	                               	inc cntFix
            	                            .if (fVerbose)
			                                    movzx ecx, [ecx].IMAGE_SYMBOL.StorageClass
												invoke printf, CStr(<"DIR32 fixup at %X, new value=%X, StorCls=%u, symbol value=%X",lf>), eax, dword ptr [esi+eax], ecx, edx
       	            	                    .endif
                                        .else  
		                                    movzx ecx, [ecx].IMAGE_SYMBOL.StorageClass
											invoke printf, CStr(<"warning: DIR32 fixup at %X: unknown Storage Class %d",lf>), ecx
                                        .endif
									.endif
                                .else
                                	mov ecx, ebx
                                    sub ecx, pRelocs
                                    add ecx, [edi].IMAGE_SECTION_HEADER.PointerToRelocations
									invoke printf, CStr(<"warning: invalid relocation found at %X: %X",lf>), ecx, eax
                                .endif
							.endif
							add ebx, sizeof IMAGE_RELOCATION
							pop ecx
							dec ecx
						.endw
                        .if (cntFix)
			  				invoke _llseek, hFile, [edi].IMAGE_SECTION_HEADER.PointerToRawData, 0
    		            	invoke _lwrite, hFile, esi, [edi].IMAGE_SECTION_HEADER.SizeOfRawData
                            .if (fVerbose)
								invoke	printf, CStr(<"section %-8.8s needed to be fixed",lf>), addr [edi].IMAGE_SECTION_HEADER.Name_
                            .endif
                        .endif
                        invoke free, esi
                    .else
						invoke	printf, CStr(<"out of memory reading section raw data",lf>)
	                    jmp main_ex
                	.endif
                    invoke free, pRelocs
                .else
					invoke	printf, CStr(<"out of memory reading section relocations",lf>)
                    jmp main_ex
                .endif
			.endif

			add edi,sizeof IMAGE_SECTION_HEADER
            pop ecx
			dec ecx
		.endw

;--- are GNU "weak externals" modified to "externals"?
        
        .if (cntClsModified)
			invoke _llseek, hFile, filehdr.PointerToSymbolTable, 0
			invoke _lwrite, hFile, pSymbols, dwSizeSymbols
			.if (eax != dwSizeSymbols)
            	invoke GetLastError
				invoke printf, CStr(<"failed to rewrite symbol table [%X]",10>), eax
            .endif
        .endif
        
        .if (pSymbols)
        	invoke free, pSymbols
            mov pSymbols, 0
        .endif
        
   	    .if (fVerbose)
			invoke	printf, CStr(<lf,"done",lf>)
        .endif
		mov bError, FALSE
		jmp main_ex
displayusage2:
		invoke	printf, CStr(<"ldfix: parameter %s unknown",lf>), dword ptr [ebx+ecx*4]
displayusage:
		invoke	printf, CStr(<"ldfix v1.0, copyright japheth 2007",lf>)
		invoke	printf, CStr(<"ldfix is used to make a relocatable COFF object",lf>)
		invoke	printf, CStr(<"written by LD compatible with Win32 COFF linkers.",lf>)
		invoke	printf, CStr(<"usage: LDFIX [ options ] file",lf>)
		invoke	printf, CStr(<"  options:",lf>)
		invoke	printf, CStr(<"    -v: verbose",lf>)
		jmp done
main_ex:
		.if (hFile != -1)
			invoke	_lclose, hFile
		.endif
done:
        mov eax, bError
		ret
        align 4
main	endp

_setargv proto c

start:
		invoke _setargv
        invoke main, eax, edx, 0
        invoke ExitProcess, eax

        END start

