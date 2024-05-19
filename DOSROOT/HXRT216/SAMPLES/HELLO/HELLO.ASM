
;--- a "hello world" sample for MASM and WASM. 
;--- will be linked as a 32bit DPMI client in MZ/NE executable format
;--- to build enter:
;---   nmake /f hellomz.mak to use MASM and MS link (MZ format)
;---   nmake /f hellone.mak to use MASM and MS link (NE format)
;---   wmake /f hellow.mak  to use WASM and WLINK

        .386
        .MODEL SMALL    ;dont use FLAT for MZ/NE executables

        .CONST

szText  db "Hello, world!", 13, 10, "$"

        .CODE

main    proc c

        mov     edx, offset szText
        mov     ah,09
        int     21h
        ret

main    ENDP

;--- mainCRTStartup is a public label called by the initialization code

_mainCRTStartup PROC public
        call    main
        mov     ah, 4Ch
        int     21h
_mainCRTStartup endp

        END

