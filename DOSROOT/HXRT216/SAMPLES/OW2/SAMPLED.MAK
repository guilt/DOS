
# creates a HX DOS PE binary with Open Watcom

NAME=SAMPLE

$(NAME)D.EXE: $(NAME)D.OBJ
    wlink system hxdos file $(NAME)D.OBJ name $(NAME)D.EXE
    ..\..\Bin\patchpe $(NAME)D.EXE

$(NAME)D.OBJ: $(NAME).C
    wcc386 -mf -bt=dos -d2 -fo=$(NAME)D.OBJ $(NAME).C 

