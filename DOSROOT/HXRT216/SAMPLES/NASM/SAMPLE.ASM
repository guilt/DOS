	
    [BITS 32]
	[section .text]

;--- simple hello world in NASM syntax.
;--- _mainCRTStartup is used as entry point here so MS LINK needs no
;--- /ENTRY:xxx option

	GLOBAL _mainCRTStartup

_mainCRTStartup:
	mov	edx, szString
	mov	ah,9			;print string edx
	int	21h
	mov	ax,4C00h		;terminate app
	int	21h

	[section .data]

szString  db 'Hello world!',13,10,'$'

