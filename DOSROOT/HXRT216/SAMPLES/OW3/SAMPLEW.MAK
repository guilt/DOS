
# nmake makefile, creates SampleW.exe.

NAME=SAMPLE
CC=wcc386.exe 
LINK=wlink.exe
DEBUG=
#DEBUG=debug dwarf

$(NAME)W.EXE: $(NAME)W.obj $(NAME)W.mak
    $(LINK) system nt file $(NAME)W.obj name $(NAME)W.EXE op map

$(NAME)W.OBJ: $(NAME).c
    $(CC) -bt=nt -fo$(NAME)W.obj $(NAME).c

