@echo off

rem  if using Make is not appropriate (or does not work at all),
rem  this .BAT can be used instead
rem  please note: LOADPE.BIN is used as stub

if "%1"=="" goto usage
\djgpp\bin\gcc.exe -c -O %1.c -o %1.o 
if errorlevel 1 goto end

\djgpp\bin\ld.exe -r -s -T ../../Lib/djgpp.ld -Map %1_.map %1.o ../../Lib/crt0hx.o -lc -lgcc -o %1.bin
if errorlevel 1 goto end

..\..\Bin\ldfix %1.bin
if errorlevel 1 goto end

link %1.bin /nologo /subsystem:console /entry:start /out:%1.exe /fixed:no /map:%1.map /opt:nowin98
if errorlevel 1 goto end

rem Add the stub to the binary.
rem One can choose among 4 stubs: dpmist32.bin, loadpe.bin, dpmild32.bin and hdld32.bin.
rem Each has its pros and cons. loadpe.bin is the most "compatible" one.
..\..\Bin\pestub -q -n -w -x -s %1.exe loadpe.bin
goto end

:usage
echo usage: gcc source_file (without .C extension)

:end
