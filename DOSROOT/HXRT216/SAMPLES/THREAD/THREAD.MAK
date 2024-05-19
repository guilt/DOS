
# this sample needs the Win32Inc include files

name = THREAD

WIN32INC=\win32inc

DEBUG=0

!if $(DEBUG)
LOPTD=/DEBUG:FULL
AOPTD=-Zd -DDEBUG
!else
LOPTD=
AOPTD=
!endif

!ifndef MASM
MASM=0
!endif

!if $(MASM)
ASM = ml -c -coff -Fo$* -Fl -Sg -I$(WIN32INC)\include
!else
ASM = jwasm -Fo$* -Fl -I$(WIN32INC)\include
!endif

LIBCOFF=..\..\Lib

LIBS=dkrnl32.lib duser32.lib

OUTDIR=.

LOPT=/OUT:$*.EXE /MAP:$*.map /SUBSYSTEM:CONSOLE /FIXED:NO /LIBPATH:$(LIBCOFF) /STUB:..\..\bin\dpmist32.bin /MERGE:.rdata=.text /MERGE:.reloc=.data /OPT:NOWIN98
LINK=link
MODS=$*.obj

$(OUTDIR)\$(name).exe: $*.obj
    $(LINK) $(MODS) $(LOPT) $(LIBS) 

$(OUTDIR)\$(name).obj: $(name).asm $(name).mak
     $(ASM) $(name).asm

clean:
	erase $(OUTDIR)\*.obj
	erase $(OUTDIR)\*.exe
