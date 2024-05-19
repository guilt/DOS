
# this creates a binary in MZ format using OW WASM and WLINK
# with debugging info.

# wlink must be at least v1.6. Previous versions don't understand how to 
# handle 32bit modules for MZ. 

NAME=HELLO

#MODS=..\..\LibOMF\jmppm32.obj ..\..\LibOMF\dmymove.obj
MODS=..\..\LibOMF\jmppm32.obj,..\..\LibOMF\dmymove.obj

$(NAME)W.EXE: $(NAME)W.OBJ $(NAME)W.MAK
#   link16.exe /ONE:NOE/NOE/MAP:FULL /CO $(MODS) HelloW.OBJ,$*.EXE,$*.MAP,..\..\LibOMF\JMPPM32.LIB;
    wlink system dos debug codeview file $(MODS),$(NAME)W.OBJ name $(NAME)W.EXE op map library ..\..\LibOMF\JMPPM32.LIB

$(NAME)W.OBJ: $(NAME).ASM
#    ml -c -Zi -Fo$*.obj $(NAME).ASM
    wasm -d2 -fo$(NAME)W.obj $(NAME).ASM


