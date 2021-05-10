;****************************************************************************
;
; int1C -- A medium model template to define an interrupt handler for INT 1C
;          (if flag=1) or to replace the original INT 1C handler (if flag=0).
;
; Prototype:  void int1C(int flag);
;
;****************************************************************************

           EXTRN   _status1:word ; C global variable for button 1 status
           EXTRN   _status2:word ; C global variable for button 2 status
           EXTRN   _fg_button:far ; Fastgraph routine

int1C_TEXT SEGMENT byte public 'CODE'
           ASSUME  cs:int1C_TEXT

int1C_CS   dw      ?             ; holds original INT 1C segment address
int1C_IP   dw      ?             ; holds original INT 1C offset
orig_DS    dw      ?             ; holds original data segment

_int1C     PROC    far
           PUBLIC  _int1C

           push    bp            ; save caller's BP register
           mov     bp,sp         ; make BP point to argument list
           push    si            ; save caller's SI register
           push    di            ; save caller's DI register

           mov     dx,[bp+6]     ; get the flag parameter
           or      dx,dx         ; replace the old interrupt handler?
           jz      replace       ; yes, branch to that processing

; define a new handler for INT 1C

define:    mov     ax,ds         ; put current data segment in AX
           mov     cs:orig_DS,ax ; save it in the control information area

           mov     al,1Ch        ; interrupt vector to save
           mov     ah,53         ; function 53: get interrupt vector
           int     21h           ; get the interrupt vector
           mov     cs:int1C_CS,es; save the segment
           mov     cs:int1C_IP,bx; save the offset

           push    ds            ; save our DS register
           mov     dx,offset handler ; get offset of interrupt handler
           mov     ax,seg handler; get segment of interrupt handler
           mov     ds,ax         ; put it in DS
           mov     al,1Ch        ; interrupt vector to change
           mov     ah,37         ; function 37: set interrupt vector
           int     21h           ; change the INT 1C vector to our handler
           pop     ds            ; restore our DS register

           jmp     short return  ; return to the caller

; replace the original handler for INT 1C

replace:   push    ds            ; save our DS register
           mov     dx,cs:int1C_IP; put original INT 1C offset in DX
           mov     ds,cs:int1C_CS; put original INT 1C segment in DS
           mov     ah,37         ; function 37: set interrupt vector
           mov     al,1Ch        ; interrupt vector 1C
           int     21h           ; restore original INT 1C vector
           pop     ds            ; restore our DS register

return:    xor     ax,ax         ; in case int1C was called as a function
           pop     di            ; restore our DI register
           pop     si            ; restore our SI register
           pop     bp            ; restore our BP register
           ret

_int1C     ENDP


handler    PROC    far           ; interrupt handler that replaces INT 1C

           cli                   ; disable interrupts while handler is active
           push    ax            ; save registers that may be altered
           push    bx
           push    cx
           push    dx
           push    di
           push    si
           push    ds
           push    es

           mov     ds,cs:orig_DS ; retrieve the original data segment

           mov     ax,1          ; use joystick 1
           push    ax            ; pass joystick number to button routine
           call    _fg_button    ; AX = button status for joystick 1
           add     sp,2          ; remove the argument
           or      _status1,ax   ; update the status variable for joystick 1

           mov     ax,2          ; use joystick 2
           push    ax            ; pass joystick number to button routine
           call    _fg_button    ; AX = button status for joystick 2
           add     sp,2          ; remove the argument
           or      _status2,ax   ; update the status variable for joystick 2

           pop     es            ; restore altered registers
           pop     ds
           pop     si
           pop     di
           pop     dx
           pop     cx
           pop     bx
           pop     ax
           iret                  ; return from the interrupt routine

handler    ENDP

int1C_TEXT ENDS
           END
