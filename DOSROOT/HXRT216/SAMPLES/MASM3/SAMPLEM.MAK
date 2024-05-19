
# create a Win32 binary
# tools:
# - JWasm/Masm v6
# - MS Link

NAME=Sample
LINK=link

!ifndef MASM
MASM=0
!endif

!if $(MASM)
ASM=ml -c -coff -Fo$* /I..\..\Include
!else
ASM=jwasm -Fo$* /I..\..\Include
!endif

LOPT=/fixed:no /map /stub:..\..\Bin\DPMIST32.BIN /OUT:$*.exe /LIBPATH:..\..\Lib /OPT:NOWIN98
LIBS=dkrnl32.lib duser32.lib

$(NAME)M.EXE: $*.obj
    $(LINK) $* $(LOPT) $(LIBS)

$(NAME)M.OBJ: $(NAME).asm $*.mak
    $(ASM) $(NAME).asm
