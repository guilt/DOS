
# this creates a HX executable (samplew.exe) in PE format using wasm 
# and wlink. Optionally with line number debugging info.

NAME=Sample

!ifdef DEBUG
LOPTD=debug dwarf
AOPTD=-d1
!else
LOPTD=
AOPTD=
!endif

$(NAME)W.EXE: $(NAME)W.OBJ
    wlink system hxnt $(LOPTD) file $(NAME)W.OBJ name $(NAME)W.EXE option quiet
#   make sure this binary isn't loaded in win32 subsystem
    ..\..\Bin\patchpe $(NAME)W.EXE

$(NAME)W.OBJ: $(NAME).ASM
     wasm -zq $(AOPTD) -Fo=$(NAME)W.obj $(NAME).ASM


