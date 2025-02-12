@ECHO OFF

REM LIMITS VARIABLES
FILES=100
FCBS=100,0

REM SWITCH DRIVE
C:

REM GOTO NO3DGFX
SET _3DGFX_HOME=C:\3DGFX
SET INCLUDE=%_3DGFX_HOME%\INCLUDE;%_3DGFX_HOME%\EINCLUDE
SET PATH=%PATH%;%_3DGFX_HOME%\EXAMPLES
:NO3DGFX

REM GOTO NOFG
SET FG_HOME=C:\FG
SET PATH=%PATH%;%FG_HOME%
SET INCLUDE=%INCLUDE%;%FG_HOME%\INCLUDE
SET LIB=%LIB%;%FG_HOME%\LIB
:NOFG

GOTO NOTP
SET TP_HOME=C:\TP
SET PATH=%PATH%;%TP_HOME%\
SET TPP_HOME=C:\TPPATCH
SET PATH=%PATH%;%TPP_HOME%\
:NOTP

GOTO NOPP
SET PPDIR=C:\PP
SET PPPLAT=GO32V2
SET PATH=%PATH%;%PPDIR%\BIN\%PPPLAT%
:NOPP

GOTO NOBC
SET BC_HOME=C:\BORLANDC
SET PATH=%PATH%;%BC_HOME%\BIN
SET INCLUDE=%INCLUDE%;%BC_HOME%\INCLUDE;%BC_HOME%\CLASSLIB\INCLUDE;%BC_HOME%\OWL\INCLUDE;%BC_HOME%\TVISION\INCLUDE
SET LIB=%LIB%;%BC_HOME%\LIB;%BC_HOME%\CLASSLIB\LIB;%BC_HOME%\OWL\LIB;%BC_HOME%\TVISION\LIB
:NOBC

GOTO NODJ
SET DJDIR=C:\DJGPP
SET DJGPP=%DJDIR%\DJGPP.ENV
SET PATH=%PATH%;%DJDIR%\BIN
SET LFN=no
:NODJ

GOTO NOOW
SET WATCOM=C:\WATCOM
SET EDPATH=%WATCOM%\EDDAT
SET WWINHELP=%WATCOM%\BINW
SET WIPFC=%WATCOM%\WIPFC
SET PATH=%PATH%;%WATCOM%\BINW
SET INCLUDE=%WATCOM%\H;%INCLUDE%
SET FINCLUDE=%WATCOM%\SRC\FORTRAN;%WATCOM%\SRC\FORTRAN\DOS
:NOOW

REM GOTO NOMSC
SET MSC_HOME=C:\MSC
SET PATH=%PATH%;%MSC_HOME%\BIN
SET HELPFILES=%HELPFILES%;%MSC_HOME%\HELP
SET PATH=%PATH%;%MSC_HOME%\PROFILER\BIN;%MSC_HOME%\PROFILER\BINP
SET INCLUDE=%INCLUDE%;%MSC_HOME%\INCLUDE;%MSC_HOME%\MFC\INCLUDE
SET LIB=%LIB%;%MSC_HOME%\LIB;%MSC_HOME%\MFC\LIB
:NOMSC

REM GOTO NOMASM
SET MASM_HOME=C:\MASM
SET PATH=%PATH%;%MASM_HOME%\BIN;%MASM_HOME%\BINR
SET HELPFILES=%HELPFILES%;%MASM_HOME%\HELP
SET INCLUDE=%INCLUDE%;%MASM_HOME%\INCLUDE
:NOMASM

REM GOTO NOQB
SET MQB_HOME=C:\MQB
SET PATH=%PATH%;%MQB_HOME%\
SET HELPFILES=%HELPFILES%;%MQB_HOME%\HELP
SET INCLUDE=%INCLUDE%;%MQB_HOME%\INCLUDE
SET LIB=%LIB%;%MQB_HOME%\LIB
:NOQB

REM GOTO NOPK
SET PK_HOME=C:\PKZIP
SET PATH=%PATH%;%PK_HOME%\
:NOPK

SET ZCXDIR=C:\EDB19
SET PATH=%PATH%;%ZCXDIR%\DOS

GOTO NOHWINFO
SET HWINFO=C:\HWINF623
SET PATH=%PATH%;%HWINFO%
:NOHWINFO

REM GOTO NOHX
SET HX_HOME=C:\HXRT216
SET PATH=%PATH%;%HX_HOME%\BIN
SET INCLUDE=%INCLUDE%;%HX_HOME%\INCLUDE
SET LIB=%LIB%;%HX_HOME%\LIB

REM LOAD DPMI DRIVERS
HDPMI16 -r
HDPMI32 -r

:NOHX

REM LOAD MOUSE DRIVER
MOUSE

REM LOAD LAN DRIVER
SET LANTASTIC_HOME=C:\LANTASTI
DEVICE %LANTASTIC_HOME%\PROTMAN.DOS /I:%LANTASTIC_HOME%
CALL C:\LANTASTI\STARTNET.BAT
