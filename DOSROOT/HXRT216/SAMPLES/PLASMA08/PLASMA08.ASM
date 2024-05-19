
;--- X-Calibre's plasma demo with 8bit palettized colors

;--- this is a dual-mode DDRAW app which should run in Win32 and DOS

;--- it uses Win32Inc includes. These may be downloaded from:
;--- http://www.japheth.de/Download/win32inc.zip

;---------------------------------------;
;    DDRAW Plasma Demo                  ;
;                                       ;
;    Author :         X-Calibre         ;
;    ASM version :    Ewald Snel        ;
;    Copyright (C) 1999, Diamond Crew   ;
;                                       ;
;    http://here.is/diamond/            ;
;---------------------------------------;

; View with TAB size 4

    TITLE WIN32ASM EXAMPLE
    .486
    .MODEL FLAT, STDCALL
    option casemap :none

;-----------------------------------------------------------;
;                WIN32ASM / DDRAW PLASMA DEMO               ;
;-----------------------------------------------------------;

    .nolist
    .nocref
WIN32_LEAN_AND_MEAN equ 1    
    INCLUDE windows.inc
    INCLUDE ddraw.inc
    .list
    .cref

    INCLUDELIB kernel32.lib
;   INCLUDELIB gdi32.lib
    INCLUDELIB user32.lib
    INCLUDELIB ddraw.lib

DDINVOKE    MACRO   func, this, arglist :VARARG
    mov         eax , [this]
    mov         eax , [eax]

    IFB <arglist>
        INVOKE [IDirectDrawVtbl. func][eax], this
    ELSE
        INVOKE [IDirectDrawVtbl. func][eax], this, arglist
    ENDIF
ENDM

DDSINVOKE   MACRO   func, this, arglist :VARARG
    mov         eax , [this]
    mov         eax , [eax]

    IFB <arglist>
        INVOKE [IDirectDrawSurfaceVtbl. func][eax], this
    ELSE
        INVOKE [IDirectDrawSurfaceVtbl. func][eax], this, arglist
    ENDIF
ENDM


;;  WinMain     PROTO :DWORD,:DWORD,:DWORD,:DWORD
    WndProc     PROTO :DWORD,:DWORD,:DWORD,:DWORD
    nextFrame   PROTO
    initPlasma  PROTO
;;  DirectDrawCreate    PROTO :DWORD, :DWORD, :DWORD

RETURN  MACRO   arg
    IFNB <arg>
        mov     eax, arg
    ENDIF
    ret
ENDM

FATAL   MACRO   msg
    LOCAL @@msg
    .DATA
    @@msg   db  msg, 0
    .CODE
    call    freeresources 
    INVOKE  MessageBox, hWnd, ADDR @@msg, ADDR szDisplayName, MB_OK
    INVOKE  ExitProcess, 0
ENDM


.DATA?
hWnd            HWND                ?       ; surface window
lpDD            LPDIRECTDRAW        ?       ; DDraw object
lpDDSPrimary    LPDIRECTDRAWSURFACE ?       ; DDraw primary surface
ddsd            DDSURFACEDESC       <?>     ; DDraw surface descriptor
ddscaps         DDSCAPS             <?>     ; DDraw capabilities

palette         dd                  256 dup (?)
table           dd                  512 dup (?)
lpDDPalette     dd                  ?

.DATA
ddwidth         EQU                 640     ; display mode width
ddheight        EQU                 480     ; display mode height
ddbpp           EQU                 8       ; display mode color depth

phaseA          dd                  0
phaseB          dd                  0

factor1         EQU                 -2
factor2         EQU                 -1
factor3         EQU                 1
factor4         EQU                 -2

red             REAL4               400.0
green           REAL4               320.0
blue            REAL4               372.0

scale1          REAL4               2.0
scale2          REAL4               127.5
scale3          REAL4               256.0

szClassName     db                  "DDRAW Plasma Demo", 0  ; class name
szDisplayName   EQU                 <szClassName>           ; window name

wc              WNDCLASSEX          < sizeof WNDCLASSEX, CS_HREDRAW or CS_VREDRAW, offset WndProc, 0, 0, , 0, 0, , 0, offset szClassName, 0 >

.CODE

;-----------------------------------------------------------;
;                Calculate Next Plasma Frame                ;
;-----------------------------------------------------------;

nextFrame   PROC
    push    ebx
    push    esi
    push    edi

    mov     ecx, ddheight           ; # of scanlines
    mov     edi, [ddsd.lpSurface]   ; pixel output

@@scanline:
    push    ecx
    push    edi

    mov     esi, [phaseA]
    mov     edx, [phaseB]
    sub     esi, ecx
    and     edx, 0FFh
    and     esi, 0FFh
    mov     edx, [table][4*edx][256*4]
    mov     esi, [table][4*esi]     ; [x]  +  table0[a + y]
    sub     edx, ecx                ; [y]  +  table1[b]
    mov     ecx, ddwidth            ; [x] --> pixel counter

@@pixel:
    and     esi, 0FFh
    and     edx, 0FFh
    mov     eax, [table][4*esi]
    mov     ebx, [table][4*edx][256*4]
    add     eax, ebx
    add     esi, factor3
    shr     eax, 1
    inc     edi
    add     edx, factor4
    dec     ecx
    mov     [edi][-1], al
    jnz     @@pixel

    pop     edi
    pop     ecx
    add     edi, [ddsd.lPitch]      ; inc. display position
    dec     ecx
    jnz     @@scanline

    add     [phaseA], factor1
    add     [phaseB], factor2

    pop     edi
    pop     esi
    pop     ebx

    ret
nextFrame   ENDP


;-----------------------------------------------------------;
;                Initalize Plasma Tables                    ;
;-----------------------------------------------------------;

initPlasma  PROC

    LOCAL @@i :DWORD
    LOCAL @@r :DWORD
    LOCAL @@g :DWORD
    LOCAL @@b :DWORD
    LOCAL temp :DWORD

    mov     [@@i], 0

    .WHILE @@i < 256

        mov     edx, [@@i]

; Calculate table0 value

        fldpi
        fimul   [@@i]
        fmul    [scale1]
        fdiv    [scale3]
        fsin
        fmul    [scale2]
        fadd    [scale2]
        fistp   [table][4*edx]

; Calculate table1 value

        fldpi
        fimul   [@@i]
        fmul    [scale1]
        fdiv    [scale3]
        fcos
        fmul    [scale2]
        fadd    [scale2]
        fldpi
        fmulp   st(1), st
        fmul    [scale1]
        fdiv    [scale3]
        fsin
        fmul    [scale2]
        fadd    [scale2]
        fistp   [table][4*edx][4*256]

; Calculate palette value

        xor     eax, eax

        FOR comp, <red, green, blue>
            fldpi
            fimul   [@@i]
            fmul    [scale1]
            fdiv    [comp]
            fcos
            fmul    [scale2]
            fadd    [scale2]
            fistp   [temp]
            shl     eax, 8
            or      eax, [temp]
        ENDM

        bswap   eax
        shr     eax, 8
        mov     [palette][4*edx], eax
        inc     [@@i]

    .ENDW

    ; Set palette
    DDINVOKE    CreatePalette_, lpDD, DDPCAPS_8BIT or DDPCAPS_ALLOW256, ADDR palette, ADDR lpDDPalette, NULL
    .IF eax != DD_OK
        FATAL "Couldn't create palette"
    .ENDIF

    DDSINVOKE   SetPalette, lpDDSPrimary, lpDDPalette
    .IF eax != DD_OK
        FATAL "Couldn't set palette"
    .ENDIF

    ret
initPlasma  ENDP


freeresources proc    

    .IF lpDDSPrimary != NULL
        DDSINVOKE   Release, lpDDSPrimary
        mov     [lpDDSPrimary], NULL
    .ENDIF

    .IF lpDD != NULL
        DDINVOKE RestoreDisplayMode, lpDD
        DDINVOKE    Release, lpDD
        mov     [lpDD], NULL
    .ENDIF
    
    ret
freeresources endp

;-----------------------------------------------------------;
;                WinMain  ( entry point )                   ;
;-----------------------------------------------------------;

WinMain     PROC    hInst     :HINSTANCE,
                    hPrevInst :HINSTANCE,
                    CmdLine   :LPSTR,
                    CmdShow   :DWORD

    LOCAL msg  :MSG

; Fill WNDCLASSEX structure with required variables

    mov     eax, [hInst]
    mov     [wc.hInstance], eax
;   INVOKE  GetStockObject, BLACK_BRUSH
;   mov     [wc.hbrBackground], eax
    mov     [wc.hbrBackground], 0

    INVOKE  RegisterClassEx, ADDR wc

; Create window at following size

    INVOKE  CreateWindowEx, 0, ADDR szClassName, ADDR szDisplayName, WS_POPUP, 0, 0, ddwidth, ddheight, NULL, NULL, hInst, NULL
    mov     [hWnd], eax

    INVOKE  SetFocus, hWnd
    INVOKE  ShowCursor, 0

; Initialize display

    INVOKE  DirectDrawCreate, NULL, ADDR lpDD, NULL
    .IF eax != DD_OK
        FATAL "Couldn't init DirectDraw"
    .ENDIF

    DDINVOKE    SetCooperativeLevel, lpDD, hWnd, DDSCL_EXCLUSIVE or DDSCL_FULLSCREEN
    .IF eax != DD_OK
        FATAL "Couldn't set DirectDraw cooperative level"
    .ENDIF

    DDINVOKE    SetDisplayMode, lpDD, ddwidth, ddheight, ddbpp
    .IF eax != DD_OK
        FATAL "Couldn't set display mode"
    .ENDIF

    mov     [ddsd.dwSize], sizeof DDSURFACEDESC
    mov     [ddsd.dwFlags], DDSD_CAPS
    mov     [ddsd.ddsCaps.dwCaps], DDSCAPS_PRIMARYSURFACE
    DDINVOKE    CreateSurface, lpDD, ADDR ddsd, ADDR lpDDSPrimary, NULL
    .IF eax != DD_OK
        FATAL "Couldn't create primary surface"
    .ENDIF

    INVOKE  ShowWindow, hWnd, CmdShow

    call    initPlasma

; Loop until PostQuitMessage is sent

    .WHILE 1

        INVOKE  PeekMessage, ADDR msg, NULL, 0, 0, PM_REMOVE
        .IF eax != 0
            .break .IF (msg.message == WM_QUIT)
            INVOKE  TranslateMessage, ADDR msg
            INVOKE  DispatchMessage, ADDR msg
        .ELSE
            INVOKE  GetFocus

            .IF eax == hWnd

                mov     [ddsd.dwSize], sizeof DDSURFACEDESC
                mov     [ddsd.dwFlags], DDSD_PITCH

                .WHILE 1

                    DDSINVOKE   Lock_, lpDDSPrimary, NULL, ADDR ddsd, DDLOCK_WAIT, NULL

                    .BREAK .IF eax == DD_OK

                    .IF eax == DDERR_SURFACELOST
                        DDSINVOKE   Restore, lpDDSPrimary
                    .ELSE
                        FATAL "Couldn't lock surface"
                    .ENDIF
                .ENDW

                DDINVOKE    WaitForVerticalBlank, lpDD, DDWAITVB_BLOCKBEGIN, NULL

                call    nextFrame

                DDSINVOKE   Unlock, lpDDSPrimary, ddsd.lpSurface

            .ENDIF
        .ENDIF
    .ENDW

    call freeresources

    RETURN  msg.wParam
    
WinMain     ENDP


;-----------------------------------------------------------;
;             Window Proc  ( handle events )                ;
;-----------------------------------------------------------;

WndProc     PROC    hWin   :DWORD,
                    uMsg   :DWORD,
                    wParam :DWORD,
                    lParam :DWORD

    .IF uMsg == WM_KEYDOWN
        .IF wParam == VK_ESCAPE
        	invoke DestroyWindow, hWin
            xor eax, eax
            ret
        .ENDIF
    .ELSEIF uMsg == WM_DESTROY
        INVOKE  PostQuitMessage, NULL
    .ENDIF

    INVOKE  DefWindowProc, hWin, uMsg, wParam, lParam

    ret
WndProc     ENDP

start proc c
    INVOKE  GetModuleHandle, NULL
    INVOKE  WinMain, eax, NULL, NULL, SW_SHOWDEFAULT
    INVOKE  ExitProcess, eax
start endp

	END start
