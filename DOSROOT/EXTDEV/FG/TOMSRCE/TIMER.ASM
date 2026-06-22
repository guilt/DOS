;*****************************************************************************
;
; TIMER.ASM
;
; Copyright (c) 1993-1994 Ted Gruber Software.  All rights reserved.
;
; This is a C-callable function illustrating a simple way to change the BIOS
; clock tick interrupt rate under DOS while maintaining an accurate time of
; day clock value.
;
; To accelerate the clock tick interrupt rate, use
;
;         set_rate(factor);
;
; where "factor" represents the acceleration factor for the clock tick rate.
; For example, to quadruple the clock tick rate, specify a factor of 4.  If
; the clock tick rate is already accelerated, nothing further happens.
;
; To revert to the normal clock tick rate, use
;
;         set_rate(0);
;
; If the clock is already running at its normal rate, nothing happens.  You
; must restore the normal clock tick rate before your program exits to DOS.
;
; This function is written for the medium or large memory models.  It can be
; modified to support the small memory model if you do the following:
;
;   - Change the segment name from "time_TEXT" to "_TEXT".
;   - Change the "far" reference in the PROC declaration to "near".
;   - Change the arg1 definition from "[bp+6]" to "[bp+4]".
;
;*****************************************************************************

rate_TEXT SEGMENT byte public 'CODE'
          ASSUME  cs:rate_TEXT

_set_rate PROC    far
          PUBLIC  _set_rate

arg1      equ     [bp+6]        ; address of the function's argument
chan_0    equ     40h           ; port address for channel 0
cmd_reg   equ     43h           ; port address for command register
fp        equ     <far ptr>     ; shorthand notation for far pointer override

          push    bp            ; save caller's BP register
          mov     bp,sp         ; make BP point to argument list

          mov     dx,arg1       ; DX = clock acceleration factor
          cmp     dx,1          ; restore clock to normal rate?
          jle     regular       ; yes, go do it

accel:    cmp     cs:speed,1    ; clock already accelerated?
          jg      return        ; yes, nothing more to do
          mov     cs:speed,dx   ; set speed indicator to accelerated
          mov     cs:countdown,dx ; initialize the timer countdown value
          call    fast          ; accelerate the clock tick interrupt rate
          jmp     short return  ; and return to the caller

regular:  cmp     cs:speed,1    ; clock already at normal speed?
          jle     return        ; yes, nothing to do
          mov     cs:speed,dx   ; set speed indicator to normal
          call    normal        ; restore clock tick rate to 18.2 ticks/second

return:   xor     ax,ax         ; set function return value to zero
          pop     bp            ; restore caller's BP register
          ret                   ; return to the caller

countdown dw      ?             ; clock tick interrupt countdown value
old_int08 dd      ?             ; address of original BIOS INT 08h handler
speed     dw      0             ; clock acceleration factor

_set_rate ENDP

;-----------------------------------------------------------------------------

fastclock PROC    far           ; interrupt handler to replace BIOS INT 08h

          push    ax            ; save altered registers

          dec     cs:countdown  ; decrement the countdown value
          jz      blastoff      ; update time of day when countdown expires
          int     1Ch           ; otherwise just call interrupt 1Ch
          mov     al,20h
          out     20h,al        ; re-enable lower level interrupts
          pop     ax            ; restore altered registers
          iret                  ; go back where we came from

blastoff: pushf                   ; simulate following call as an interrupt
          call    cs:[old_int08]  ; call original BIOS clock tick interrupt
          mov     ax,cs:speed     ; AX = clock acceleration factor
          mov     cs:countdown,ax ; reset countdown value
          mov     al,20h
          out     20h,al        ; re-enable lower level interrupts
          pop     ax            ; restore altered registers
          iret                  ; go back where we came from

fastclock ENDP

;-----------------------------------------------------------------------------

fast      PROC    near          ; accelerate the clock by a factor of DX

          cli                   ; disable interrupts
          xor     ax,ax         ; zero AX
          mov     es,ax         ; point ES to start of memory

          mov     bx,08h*4      ; interrupt vector 08h
          mov     ax,es:[bx]    ; put the interrupt vector offset in AX
          mov     cx,es:[bx+2]  ; put the interrupt vector segment in CX
          lea     bx,old_int08  ; address for saving original INT 08h handler
          mov     cs:[bx],ax    ; save original INT 08h offset
          mov     cs:[bx+2],cx  ; save original INT 08h segment

          mov     bx,08h*4      ; interrupt vector 08h
          lea     ax,fastclock  ; CS:AX = address of accelerated clock handler
          mov     es:[bx],ax
          mov     es:[bx+2],cs  ; point INT 08h vector to the new handler

          mov     al,36h        ; initialize channel 0 for mode 3
          out     cmd_reg,al    ; send above byte to the command register

          mov     bx,dx         ; put the clock acceleration factor in BX
          mov     dx,1
          xor     ax,ax         ; DX:AX = 65,536
          div     bx            ; AX = counter for desired clock acceleration
          out     chan_0,al     ; send low byte of counter to channel 0
          mov     al,ah         ; put high byte of counter in AL
          out     chan_0,al     ; send high byte

          sti                   ; re-enable interrupts
          ret

fast      ENDP

;-----------------------------------------------------------------------------

normal    PROC    near          ; reset the clock rate to 18.2 ticks/second

          cli                   ; disable interrupts
          mov     al,36h        ; initialize channel 0 for mode 3
          out     cmd_reg,al    ; send above byte to the command register

          xor     ax,ax         ; counter for 18.2 ticks per second
          mov     es,ax         ; point ES to start of memory

          out     chan_0,al     ; send low byte of counter to channel 0
          out     chan_0,al     ; send high byte (same as low byte)

          lea     bx,old_int08  ; address of original INT 08h handler
          mov     ax,cs:[bx]    ; AX = original INT 08h offset
          mov     cx,cs:[bx+2]  ; CX = original INT 08h segment
          mov     bx,08h*4      ; interrupt vector 08h
          mov     es:[bx],ax
          mov     es:[bx+2],cx  ; restore original INT 08h vector

          sti                   ; re-enable interrupts
          ret

normal    ENDP

;-----------------------------------------------------------------------------

rate_TEXT ENDS
          END
