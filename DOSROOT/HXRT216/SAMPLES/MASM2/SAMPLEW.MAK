
# makefile to build sample2w.exe, enter:
#    wmake /f sample2w.mak
# to add debug info enter:
#    wmake /f sample2w.mak debug=1

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

ASMOPT= -fo$(NAME) $(AOPTD)

$(NAME).EXE: $(NAME).obj $(NAME).mak
    $(LINK) system hxnt file $(NAME).obj name $(NAME).exe library ..\..\Lib\dkrnl32.lib 

$(NAME).OBJ: $(NAME).asm $(NAME).mak
    $(ASM) $(ASMOPT) $(NAME).asm

