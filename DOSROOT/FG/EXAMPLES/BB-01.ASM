          EXTRN   _fg_getmode:far  ; Fastgraph's GETMODE routine
          EXTRN   _fg_reset:far    ; Fastgraph's RESET routine
          EXTRN   _fg_setmode:far  ; Fastgraph's SETMODE routine
          EXTRN   _fg_version:far  ; Fastgraph's VERSION routine

stackseg  SEGMENT stack         ; suppress the linker's
stackseg  ENDS                  ; "no stack segment" error message

_DATA     SEGMENT word public 'DATA'

major     dw      ?             ; major version number
minor     dw      ?             ; minor version number
old_mode  dw      ?             ; original video mode

_DATA     ENDS

dgroup    GROUP   _DATA
          ASSUME  cs:main_TEXT,ds:dgroup

main_TEXT SEGMENT byte public 'CODE'

start:    mov     ax,_DATA      ; load segment location
          mov     ds,ax         ; into DS register

          call    _fg_getmode   ; AX = current video mode
          mov     old_mode,ax   ; save it

          mov     ax,4          ; use video mode 4
          push    ax            ; pass argument to SETMODE
          call    _fg_setmode   ; establish CGA four-color mode
          add     sp,2          ; remove SETMODE argument

          push    old_mode      ; pass argument to SETMODE
          call    _fg_setmode   ; restore original video mode
          add     sp,2          ; remove SETMODE argument

          call    _fg_reset     ; restore screen attributes

          lea     ax,minor      ; get address of minor variable
          push    ax            ; pass argument #2 to VERSION
          lea     ax,major      ; get address of major variable
          push    ax            ; pass argument #1 to VERSION
          call    _fg_version   ; get the Fastgraph version number
          add     sp,4          ; remove VERSION arguments

          mov     ah,76         ; function 76: terminate process
          xor     al,al         ; errorlevel 0
          int     21h           ; exit to DOS

main_TEXT ENDS
          END     start
