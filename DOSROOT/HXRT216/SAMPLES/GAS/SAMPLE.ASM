
/* a "hello world" sample for GAS using Intel syntax */

.intel_syntax noprefix
.global _start

.data
.extern	_GetStdHandle@4
.extern	_WriteConsoleA@20
.extern	_ExitProcess@4

.set ExitProcess,_ExitProcess@4
.set GetStdHandle,_GetStdHandle@4
.set WriteConsole,_WriteConsoleA@20

message:
.ascii "Hello world!" 	/* define NULL terminated string */
.byte 13,10,0

.text
_start:
	pushd	-11
    call	GetStdHandle
    mov		ebx, eax
	pushd   0
    mov		ecx, esp
	pushd	0			/* push DOUBLE word */
    pushd	ecx
    pushd	14
	push	OFFSET message
	pushd	ebx
	call	WriteConsole
	pushd	0
	call	ExitProcess
