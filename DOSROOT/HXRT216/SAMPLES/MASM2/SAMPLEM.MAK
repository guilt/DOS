
# nmake makefile to build sample2m.exe, enter:
#    nmake /f sample2m.mak
# to add debug info enter:
#    nmake /f sample2m.mak debug=1

# JWasm/Masm + MS link are used

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

STUB=dpmist32.bin

$(NAME)M.EXE: $*.obj $*.mak
    $(LINK) $*.obj ..\..\Lib\dkrnl32.lib /NOLOGO /MAP /OUT:$*.EXE /SUBSYSTEM:CONSOLE /STUB:..\..\bin\$(STUB) /FIXED:NO $(LOPTD) /OPT:NOWIN98

$(NAME)M.OBJ: $(NAME).asm $*.mak
    $(ASM) $(NAME).asm

