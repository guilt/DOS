echo off
echo.
echo C Startup Build (C 7.00)
echo.
REM
REM Copyright (c) 1986-1992, Microsoft Corporation.  All rights reserved.
REM

if not %1.==?. goto args


REM
REM --- Help message
REM

:help
echo	Usage:	cstartup [?] [os] [models]
echo.
echo		[?] displays this help message.
echo.
echo		[os] is an optional list of one or more OS designators
echo		seperated by spaces (DOS, WIN); default is all.
echo.
echo		[model] is an optional list of memory model designators
echo		seperated by spaces (S, M, C, L); default is all.
echo.
echo	Examples:
echo.
echo		cstartup dos	/* Build all DOS startup files */
echo.
echo		cstartup s l	/* Build small and large files, all systems */
echo.
echo		cstartup	/* Build all startup files */
echo.
echo	Refer to the startup readme.txt file for more information.
echo.
goto end


REM
REM --- Error messages
REM

:err_arg
echo *** ERROR: Invalid argument.
goto err_end

:err_dos
echo *** ERROR: Makefile for DOS not available.
goto err_end


:err_win
echo *** ERROR: Makefile for WIN not available.
goto err_end

:err_nomem
echo *** ERROR: No memory model designation.
goto err_end

:err_build
ECHO *** ERROR: Startup build failed.
goto err_end

:err_end
echo		   (Enter "cstartup ?" for more help.)
goto end


REM
REM --- Validate args and set up for build
REM
REM Set up environment arguments in the following form:
REM
REM	OSTARGET_DOS = Build DOS
REM	OSTARGET_WIN = Build WIN
REM
REM	MEMTARGET_S  = Build Small model
REM	MEMTARGET_M  = Build Medium model
REM	MEMTARGET_C  = Build Compact model
REM	MEMTARGET_L  = Build Large model
REM
REM If an environment variable is not defined, the corresponding OS or
REM model should not be built.
REM

:args

:os_args
:os_nextarg
if %1.==DOS. goto os_dosarg
if %1.==dos. goto os_dosarg
if %1.==WIN. goto os_winarg
if %1.==win. goto os_winarg
goto os_argchk

:os_dosarg
set OSTARGET_DOS=DOS
goto os_shift


:os_winarg
set OSTARGET_WIN=WIN
REM goto os_shift

:os_shift
shift
if not %1.==. goto os_nextarg

:os_argchk
if %OSTARGET_DOS%.==DOS. goto os_argdone
if %OSTARGET_WIN%.==WIN. goto os_argdone
set OSTARGET_DOS=DOS
set OSTARGET_WIN=WIN

:os_argdone
if %OSTARGET_DOS%.==DOS. if not exist makefile.dos goto err_dos
if %OSTARGET_WIN%.==WIN. if not exist makefile.win goto err_win

:mem_args
if %1.==. goto mem_argchk

:mem_nextarg
if %1.==S. goto mem_sarg
if %1.==s. goto mem_sarg
if %1.==M. goto mem_marg
if %1.==m. goto mem_marg
if %1.==C. goto mem_carg
if %1.==c. goto mem_carg
if %1.==L. goto mem_larg
if %1.==l. goto mem_larg
goto err_arg

:mem_sarg
set MEMTARGET_S=S
goto mem_shift

:mem_marg
set MEMTARGET_M=M
goto mem_shift

:mem_carg
set MEMTARGET_C=C
goto mem_shift

:mem_larg
set MEMTARGET_L=L
REM goto mem_shift

:mem_shift
shift
if not %1.==. goto mem_nextarg

:mem_argchk
if not %MEMTARGET_S%.==. goto argdone
if not %MEMTARGET_M%.==. goto argdone
if not %MEMTARGET_C%.==. goto argdone
if not %MEMTARGET_L%.==. goto argdone
set MEMTARGET_S=S
set MEMTARGET_M=M
set MEMTARGET_C=C
set MEMTARGET_L=L

:argdone


REM
REM -- Build all the appropriate files
REM

set CSTARTUPERR=
echo --- Directory creation errors may occur - Ignore these ---

:dos
if not %OSTARGET_DOS%.==DOS. goto end_dos
for %%i in (%MEMTARGET_S% %MEMTARGET_M% %MEMTARGET_C% %MEMTARGET_L%) do call csub DOS %%i
:end_dos


:win
if not %OSTARGET_WIN%.==WIN. goto end_win
for %%i in (%MEMTARGET_S% %MEMTARGET_M% %MEMTARGET_C% %MEMTARGET_L%) do call csub WIN %%i
:end_win

:build_done
if not %CSTARTUPERR%.==. goto err_build
echo Done.

REM
REM -- Clean up
REM

:end
set OSTARGET_DOS=
set OSTARGET_WIN=
set MEMTARGET_S=
set MEMTARGET_M=
set MEMTARGET_C=
set MEMTARGET_L=
set CSTARTUPERR=
