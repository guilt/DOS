
# nmake makefile, creates SampleD.exe.

NAME=SAMPLE
CC=wcc386.exe 
LINK=wlink.exe
DEBUG=
#DEBUG=debug dwarf

$(NAME)D.EXE: $(NAME)D.obj $(NAME)D.mak
    $(LINK) system hxdos file $(NAME)D.obj name $(NAME)D.EXE op map
    ..\..\Bin\patchPE $(NAME)D.EXE

$(NAME)D.OBJ: $(NAME).c
    $(CC) -bt=dos -fo$(NAME)D.obj $(NAME).c

