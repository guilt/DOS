@echo off
if "%1"=="" goto dowindir

:OtherDir
rem *) This method will copy all files to the directory  
rem *) specified on the command line.
set dest=%1
cls
echo.
echo.  
echo  Windows 95 Supplemental DOS Tools
echo           MANUAL INSTALL
echo  ====================================
echo.
echo  Ready to copy the Supplemental Tools to: %Dest%
echo.
echo  Press any key to Continue  (to Cancel, press CTRL-C)
pause > nul
echo.
echo  Now Installing...
copy *.* %dest% > nul

cls
echo.
echo.  
echo  Windows 95 Supplemental DOS Tools
echo           MANUAL INSTALL
echo  ====================================
echo.
echo  The Supplemental Tools have been installed to: 
echo.            %Dest%
echo  In order to work correctly, you should copy the following 
echo  files to the directory where you have installed Windows 95:
echo.
echo       MEMMAKER.HLP 
echo       MEMMAKER.INF 
echo       MEMMAKER.EXE
echo       SIZER.EXE
echo       CHKSTATE.SYS
goto SetVer


:dowindir
set dest=%windir%
if "%dest%"=="" goto nowindir
cls
echo.
echo.  
echo  Windows 95 Supplemental DOS Tools
echo  ====================================
echo.
echo  Ready to copy the Supplemental Tools to: %Dest%
echo.
echo  Press any key to Continue  (to Cancel, press CTRL-C)
pause > nul
echo.
echo  Now Installing...
copy *.* %dest%\command > nul
copy msbackup\*.* %dest%\command > nul

rem Copy the MemMaker elements to the Win95 directory
copy SIZER.EXE %dest% > nul
copy MEMMAKER.HLP %dest% > nul
copy MEMMAKER.INF %dest% > nul
copy CHKSTATE.SYS %dest% > nul
copy MEMMAKER.EXE %dest% > nul

rem ...And remove them from the \COMMAND directory (just to clean things up!)
del %dest%\COMMAND\SIZER.EXE > nul
del %dest%\COMMAND\MEMMAKER.HLP > nul
del %dest%\COMMAND\MEMMAKER.INF > nul
del %dest%\COMMAND\CHKSTATE.SYS > nul
del %dest%\COMMAND\MEMMAKER.EXE > nul
del %dest%\command\instsupp.bat > nul
cls
echo.
echo.  
echo  Windows 95 Supplemental DOS Tools
echo  ====================================
echo.
echo  The Supplemental Tools have been installed.

:SetVer
setver graphics.com 6.22 > nul
setver intersvr.exe 6.22 > nul
setver print.exe 6.22 > nul
setver replace.exe 6.22 > nul
setver tree.com 6.22 > nul

echo.
echo *************************************************************************
echo * Please restart your machine before you use the new supplemental utils *
echo *************************************************************************
echo.
goto end

:nowindir
echo Usage :
echo From real mode DOS :
echo      INSTSUPP {SubDirectory}
echo From inside win95 DOS box :
echo      INSTSUPP
echo        (For installing into the Windows 95 command subdirectory)
echo      INSTSUPP {dirname}
echo        (For installing into a subdirectory other than Win95 command directory.)

:end
