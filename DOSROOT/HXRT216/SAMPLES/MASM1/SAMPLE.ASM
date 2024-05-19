
	.386
	.model flat

;--- this is a very simple hello world app. Only DOS functions are used

	.code

str1 db 13,10,"Hello, world!",13,10,'$'

main proc c

	mov ah, 09h
	mov edx, offset str1
	int 21h
	mov ax, 4c00h
	int 21h

	ret
main endp

	end main
