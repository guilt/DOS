
# makefile to build sample2w.exe, enter:
#    wmake /f sample2ws.mak
# to add debug info enter:
#    wmake /f sample2ws.mak debug=1

# WASM + Wlink are used

NAME=SampleW

!ifdef DEBUG
AOPTD=-d2
LOPTD=debug dwarf
!else
AOPTD=
LOPTD=
!endif

ASM=wasm.exe
LINK=wlink.exe

ASMOPT= -fo$(NAME)S.obj $(AOPTD)

$(NAME)S.EXE: $(NAME)S.obj $(NAME)S.mak
    $(LINK) system hxnts file $(NAME)S.obj name $(NAME)S.exe library ..\..\Lib\dkrnl32s.lib 

$(NAME)S.OBJ: $(NAME).asm $(NAME)S.mak
    $(ASM) $(ASMOPT) $(NAME).asm

