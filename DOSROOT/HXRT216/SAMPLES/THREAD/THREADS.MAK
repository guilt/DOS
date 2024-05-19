
# version with win32 emulation code linked statically
#
# to assemble the Win32Inc include files are needed

name = THREAD

DEBUG=0

!if $(DEBUG)
LOPTD=/DEBUG:FULL
AOPTD=-Zd -DDEBUG
!else
LOPTD=
AOPTD=
!endif

ASM = ml -c -coff -Fo$* -I\win32inc\include

LIBCOFF=..\..\Lib

LIBS=dkrnl32s.lib duser32s.lib imphlp.lib

OUTDIR=.

LOPT=/OUT:$*.EXE /MAP:$*.map /SUBSYSTEM:CONSOLE /FIXED:NO /LIBPATH:$(LIBCOFF) /STUB:..\..\bin\loadpe.bin /OPT:NOWIN98 /MERGE:.BASE=.data
LINK=link

$(OUTDIR)\$(name)S.exe: $*.obj
    $(LINK) $(LIBCOFF)\initw32.obj $*.obj $(LOPT) $(LIBS) 
    ..\..\Bin\PatchPE $*.exe

$(OUTDIR)\$(name)S.obj: $(name).asm $(name)S.mak
     $(ASM) $(name).asm

