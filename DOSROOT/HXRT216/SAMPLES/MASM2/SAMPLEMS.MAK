
# nmake makefile to build sample2ms.exe, enter:
#    nmake /f sample2ms.mak
# to add debug info enter:
#    nmake /f sample2ms.mak debug=1

# JWasm/Masm + MS link are used, static Win32 libs are used

NAME=Sample

!ifdef DEBUG
AOPTD=-Zi
LOPTD=/DEBUG
!else
AOPTD=
LOPTD=
!endif

!ifndef MASM
MASM=0
!endif

!if $(MASM)
ASM=ml.exe -c -coff -nologo -Fo$* -I..\..\Include $(AOPTD)
!else
ASM=jwasm.exe -q -Fo$* -I..\..\Include $(AOPTD)
!endif

LINK=link.exe

STUB=loadpe.bin

$(NAME)MS.EXE: $*.obj $*.mak
    $(LINK) ..\..\Lib\InitW32.obj $*.obj /OUT:$*.exe ..\..\Lib\dkrnl32s.lib ..\..\Lib\imphlp.lib /NOLOGO /MAP /OUT:$*.EXE /SUBSYSTEM:CONSOLE /STUB:..\..\bin\$(STUB) /FIXED:NO $(LOPTD) /OPT:NOWIN98
    ..\..\Bin\PatchPE.exe $*.exe

$(NAME)MS.OBJ: $(NAME).asm $*.mak
    $(ASM) $(NAME).asm

