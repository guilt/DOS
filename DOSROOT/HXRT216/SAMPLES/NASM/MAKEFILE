
# enter: nmake
# here MS LINK is used

NAME=SAMPLE

$(NAME).EXE: $(NAME).obj
    link $(NAME).obj /subsystem:console /map /stub:..\..\bin\dpmist32.bin /fixed:no
    ..\..\bin\patchPE $*.EXE

$(NAME).obj: $(NAME).asm
    nasmw -fwin32 $(NAME).asm -l$(NAME).lst

