@echo off
rem
rem this creates a hx raw PE binary, with HX's DPMI host
rem HDPMI and LOADPE.BIN stub.
rem Thus the binary is stand-alone, but size is increased by about 35 kB.
rem The patchPE tool is used to mark the binary as "PX" instead of "PE"
rem to avoid it being loaded in a Win32 process under Windows
rem
fasm SampleD.asm
link SampleD.obj /SUBSYSTEM:CONSOLE /ENTRY:start /STUB:..\..\bin\loadpex.bin /FIXED:NO /OPT:NOWIN98
patchPE SampleD.exe
