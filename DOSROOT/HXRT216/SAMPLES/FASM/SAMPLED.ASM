
;  SAMPLED.ASM FASM Sample for a 32-bit DPMI client.
;  this program is to be linked as DOS PE binary. It is stand-alone.
;  To assemble and link, use:
;     fasm SampleD.asm
;     link SampleD.obj /out:SampleD.exe /stub:hdld32.bin

	format MS COFF

    use32

    public _start

_start:
    mov edx, szWelcome  ;print welcome message
    mov ah,9
    int 21h
    mov ax, 4C00h       ;return to DOS
    int 21h

szWelcome db "welcome in protected-mode",13,10,'$'

