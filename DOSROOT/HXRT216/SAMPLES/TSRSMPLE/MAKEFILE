
# this make file generates tsrsmple.exe
# source is in MASM format

NAME=TSRSMPLE
LIBS=..\..\lib
OUTDIR=.

!ifndef MASM
MASM=0
!endif

!if $(MASM)
ASM=ml -c -coff -Fo$* -I..\..\Include
!else
ASM=jwasm -Fo$* -I..\..\Include
!endif

LINK=link.exe

$(OUTDIR)\$(NAME).exe: $*.obj Makefile
    $(LINK) @<<
$(LOPTS) $*.OBJ /OUT:$*.EXE /MAP:$*.MAP $(LIBS)\duser32s.lib
/STUB:..\..\Bin\LOADPE.BIN /FileAlign:0x80 /FIXED:NO /STACK:0,0
/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text /MERGE:.reloc=.text
<<
    ..\..\Bin\PatchPE $*.EXE

$(OUTDIR)\$(NAME).obj: $(NAME).asm
    $(ASM) $(NAME).asm

