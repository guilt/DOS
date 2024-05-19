fasm SampleW.asm
polink SampleW.obj ..\..\Lib\dkrnl32.lib /SUBSYSTEM:CONSOLE /ENTRY:start /STUB:..\..\bin\dpmist32.bin /FIXED:NO
