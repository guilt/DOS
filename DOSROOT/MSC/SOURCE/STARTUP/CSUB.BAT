REM
REM Copyright (c) 1986-1992, Microsoft Corporation.  All rights reserved.
REM

REM
REM Subroutine used in the C startup build procedure.
REM
REM	arg1 = OS target (DOS, WIN)
REM
REM	arg2 = MEM target (S, M, C, L)
REM
REM (1) All arguments are expected to be upper case.
REM (2) Arguments are not validated.
REM

if %1.==WIN. goto winbld

if not exist %2 	mkdir %2
if not exist %2\%1	mkdir %2\%1
cd %2

cd dos
echo on
nmake CINC=%INCLUDE% MODEL=%2 %1 /F ..\..\makefile.%1
echo off
cd ..
if errorlevel 1 goto err_build

if not %1.==DOS. goto end
if not %2.==S. goto end
cd dos
echo on
nmake CINC=%INCLUDE% MODEL=%2 crtcom /F ..\..\makefile.%1
echo off
cd ..
if errorlevel 1 goto err_build
goto end

:winbld
if not exist %2                mkdir %2
if not exist %2\win            mkdir %2\win
if not exist %2\dll            mkdir %2\dll
cd %2

cd win
echo on
nmake CINC=%INCLUDE% MODEL=%2 win /F ..\..\winexe.mkf /F ..\..\makefile.win
echo off
cd ..
if errorlevel 1 goto err_build

cd dll
echo on
nmake CINC=%INCLUDE% MODEL=%2 windll /F ..\..\windll.mkf /F ..\..\makefile.win
echo off
cd ..
if errorlevel 1 goto err_build
goto end


REM
REM -- Error
REM

:err_build
ECHO *** ERROR: Startup build failed, OS=%1, MODEL=%2.
set CSTARTUPERR=YES

:end
cd ..
