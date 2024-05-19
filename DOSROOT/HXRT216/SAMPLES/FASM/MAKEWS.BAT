rem create a HX DOS binary with Win32 emulation linked statically
fasm SampleW.asm SampleWS.obj
polink /SUBSYSTEM:CONSOLE ..\..\Lib\InitW32.obj SampleWS.obj ..\..\Lib\dkrnl32s.lib ..\..\Lib\imphlp.lib /OUT:SAMPLEWS.EXE /STUB:..\..\bin\LoadPE.bin /FIXED:NO /MAP
..\..\Bin\PatchPE SAMPLEWS.EXE
