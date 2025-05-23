@ECHO OFF
@BREAK OFF
REM ----------
REM Title:    UltraSound Emulation Picker
REM Purpose:  Give the user one common way to load any of the 3 Gravis
REM           emulators. Features include:
REM           1) Check for presense of ULTRASND & ULTRADIR
REM           2) Unload other emulators if necessary
REM           3) Allow user to pass command line arguments to emulators
REM           4) Allow user to specify without a menu what emulation to load
REM           5) Let the user know what emulation is currently active
REM           6) Make sure the necessary files are there to load
REM USAGE:
REM   GUSEMU What you want to Check
REM      1  - Wait for key press and return number
REM          10 - What emulation is currently loaded?
REM               0 = None 1 = SBOS 2 = UltraMid 3 = Mega-Em
REM
REM      11 - Is SBOS loaded?     1 = True  0 = False
REM      12 - Is UltraMID loaded?
REM      13 - Is Mega-Em loaded?
REM
REM      20 - Remove SBOS      1 = Successfull  0 = Failed
REM      21 - Remove UltraMID
REM
REM Modified:
REM ----------
REM ==========
REM   Quick check to see if GUS has been installed and configured
REM ==========
IF %ULTRASND%!==! GOTO NOGUS
IF %ULTRADIR%!==! GOTO NOGUS
IF %1!==!         GOTO START
IF %1==1          GOTO SBOS
IF %1==2          GOTO ULTRAMID
IF %1==3          GOTO MEGAEM
IF %1==4          GOTO REMOVE
:START
CLS
ECHO  浜様様様様様様様様様様様様様様様様様様様様様様様様様様様様様�
ECHO  �        Gravis UltraSound Emulation Manager                �
ECHO  �                    Version 1.2                            �
ECHO  �                                                           �
GUSEMU 11
IF ERRORLEVEL 1 ECHO  � Currently In: Sound Blaster emulation                     �
GUSEMU 12
IF ERRORLEVEL 1 ECHO  � Currently In: UltraMID (AIL)                              �
GUSEMU 13
IF ERRORLEVEL 1 ECHO  � Currently In: GM/SCC1/MT32 and Sound Blaster mode         �
ECHO  �  1 = Sound Blaster emulation for UltraSound (SBOS)        �
ECHO  �  2 = Sound Blaster emulation for UltraSound MAX (MAXSBOS) �
ECHO  �  3 = UltraMID (AIL)                                       �
ECHO  �  4 = Mega-Em - GM/SCC1/MT32 and Sound Blaster             �
ECHO  �  5 = Remove all emulations                                �
ECHO  �  6 = Exit                                                 �
ECHO  �                                                           �
ECHO  �  Which emulation do you wish to activate?                 �
ECHO  藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様�
GUSEMU 1
IF ERRORLEVEL 6 GOTO STOP
IF ERRORLEVEL 5 GOTO REMOVE
IF ERRORLEVEL 4 GOTO MEGAEM
IF ERRORLEVEL 3 GOTO ULTRAMID
IF ERRORLEVEL 2 GOTO MAXSBOS
IF ERRORLEVEL 1 GOTO SBOS
GOTO EXIT

:MEGAEM
IF NOT EXIST %ULTRADIR%\MEGAEM.EXE        GOTO MISSING
IF NOT EXIST %ULTRADIR%\EMUSET.EXE        GOTO MISSING
CLS
IF %2!==! GOTO MEGALOAD
GOTO EMUSET
:MEGALOAD
MEGAEM %2 %3 %4 %5
:EMUSET
EMUSET %2 %3 %4 %5
GOTO EXIT

:ULTRAMID
IF NOT EXIST %ULTRADIR%\ULTRAMID.EXE      GOTO MISSING
IF NOT EXIST %ULTRADIR%\MIDI\ULTRAMID.INI GOTO MISSING
GUSEMU 11
IF ERRORLEVEL 1 GUSEMU 20
GUSEMU 12
IF ERRORLEVEL 1 GOTO LOADED
GUSEMU 13
IF ERRORLEVEL 1 %ULTRADIR%\MEGAEM /U
CLS
%ULTRADIR%\ULTRAMID %1 %2 %3 %4
GOTO EXIT

:MAXSBOS

IF NOT EXIST %ULTRADIR%\MAXSBOS.BAT           GOTO MISSING
IF NOT EXIST %ULTRADIR%\MAXSBOS\LOADER.EXE    GOTO MISSING
IF NOT EXIST %ULTRADIR%\MAXSBOS\DRIVER.EXE    GOTO MISSING
IF NOT EXIST %ULTRADIR%\MAXSBOS\SBOS512.SBS   GOTO MISSING
IF NOT EXIST %ULTRADIR%\MAXSBOS\SBOS1024.SBS  GOTO MISSING
GUSEMU 11
IF ERRORLEVEL 1 GOTO LOADED
GUSEMU 12
IF ERRORLEVEL 1 GUSEMU 21
GUSEMU 13
IF ERRORLEVEL 1 %ULTRADIR%\MEGAEM /U
CLS
CALL %ULTRADIR%\MAXSBOS.BAT %1 %2 %3 %4
GOTO EXIT

:SBOS
IF NOT EXIST %ULTRADIR%\SBOS.BAT           GOTO MISSING
IF NOT EXIST %ULTRADIR%\loadsbos.exe       GOTO MISSING
IF NOT EXIST %ULTRADIR%\sbosdrv.com   GOTO MISSING
IF NOT EXIST %ULTRADIR%\SBOS\SBOSlib.SBS   GOTO MISSING
GUSEMU 11
IF ERRORLEVEL 1 GOTO LOADED
GUSEMU 12
IF ERRORLEVEL 1 GUSEMU 21
GUSEMU 13
IF ERRORLEVEL 1 %ULTRADIR%\MEGAEM /U
CLS
CALL %ULTRADIR%\SBOS.BAT %1 %2 %3 %4
GOTO EXIT


:REMOVE
GUSEMU 11
IF ERRORLEVEL 1 call %ULTRADIR%\SBOS /F >NUL
GUSEMU 11
IF ERRORLEVEL 1 call %ULTRADIR%\MAXSBOS /F > NUL
GUSEMU 12
IF ERRORLEVEL 1 GUSEMU 21
GUSEMU 13
IF ERRORLEVEL 1 %ULTRADIR%\MEGAEM /U
ECHO  浜様様様様様様様様様様様様様様様様様様様様様様様様様様�
ECHO  �  Emulations removed.                                �
ECHO  藩様様様様様様様様様様様様様様様様様様様様様様様様様様�
ECHO �
GOTO EXIT

:NOGUS
ECHO 
ECHO  浜様様様様様様様様様様様様様様様様様様様様様様様様様様�
ECHO  �  Unable to locate your UltraSound card. Please      �
ECHO  �  run SETUP from your UltraSound directory.          �
ECHO  藩様様様様様様様様様様様様様様様様様様様様様様様様様様�
ECHO �
GOTO EXIT

:LOADED
ECHO 
ECHO  浜様様様様様様様様様様様様様様様様様様様様様様様様様様�
ECHO  �  Emulation is currently active.                     �
ECHO  藩様様様様様様様様様様様様様様様様様様様様様様様様様様�
ECHO �
GOTO EXIT

:MISSING
ECHO 
ECHO  浜様様様様様様様様様様様様様様様様様様様様様様様様様様�
ECHO  �  One or more of the files required to run the       �
ECHO  �  Emulation selected is can not be found! Please     �
ECHO  �  check your AUTOEXEC.BAT file to make sure the      �
ECHO  �  SET ULTRADIR= line is pointing to the correct      �
ECHO  �  directory.  If it is pointing to your UltraSound   �
ECHO  �  directory and you still get this error then the    �
ECHO  �  required files may be missing.  If so please       �
ECHO  �  re-install your UltraSound software to correct     �
ECHO  �  this problem.                                      �
ECHO  藩様様様様様様様様様様様様様様様様様様様様様様様様様様�
ECHO �
GOTO EXIT

:STOP
ECHO �
GOTO EXIT

:EXIT


