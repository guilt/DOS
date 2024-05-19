
# create a DOS-PE with Win32 emulation linked statically
# tools:
# - JWasm/Masm v6
# - MS Link

# initw32.obj: used to initialize the win32 emulation
# loadpe.bin: avoids need of DPMILD32.EXE, thus this
# binary will run stand-alone if a DPMI host is available

NAME=Sample
LINK=link

!ifndef MASM
MASM=0
!endif

!if $(MASM)
ASM= -c -coff -Fo$* /I..\..\Include
!else
ASM=jwasm -Fo$* /I..\..\Include
!endif

LOPT=/fixed:no /map /stub:..\..\Bin\LOADPE.BIN /OUT:$*.exe /LIBPATH:..\..\Lib /OPT:NOWIN98
LIBS=dkrnl32s.lib duser32s.lib imphlp.lib

$(NAME)MS.EXE: $*.obj
    $(LINK) ..\..\Lib\initw32.obj $* $(LOPT) $(LIBS)
    patchpe $*.exe

$(NAME)MS.OBJ: $(NAME).asm $*.mak
    $(ASM) $(NAME).asm
