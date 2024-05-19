
# creates a Win32 PE binary with Open Watcom

NAME=SAMPLE

$(NAME)W.EXE: $(NAME)W.OBJ
    wlink system nt file $(NAME)W.OBJ name $(NAME)W.EXE

$(NAME)W.OBJ: $(NAME).C
    wcc386 -mf -bt=nt -d2 -fo=$(NAME)W.OBJ $(NAME).C 

