
# nmake makefile to build sample2p.exe, enter:
#    nmake /f sample2p.mak
# to add debug info enter:
#    nmake /f sample2p.mak debug=1

# PoASM + Polink are used

NAME=Sample

!ifdef DEBUG
AOPTD=-Zi
LOPTD=/DEBUG
!else
AOPTD=
LOPTD=
!endif

ASM=poasm.exe
LINK=polink.exe

ASMOPT= -Fo$* -I..\..\Include $(AOPTD)

$(NAME)P.EXE: $*.obj $*.mak
    $(LINK) $*.obj ..\..\Lib\dkrnl32.lib /OUT:$*.EXE /SUBSYSTEM:CONSOLE /STUB:..\..\bin\dpmist32.bin /FIXED:NO $(LOPTD)

$(NAME)P.OBJ: $(NAME).asm $*.mak
    $(ASM) $(ASMOPT) $(NAME).asm

