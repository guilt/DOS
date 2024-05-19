
# nmake makefile
# tools used:
# assembler: JWasm or Masm
# linker: MS link

APPNAME=DYNLOADA
DLLNAME=DYNLOADD

!ifndef MASM
MASM=0
!endif

!if $(MASM)
ASMA=ml.exe -c -coff -nologo -Fo$* -I..\..\Include
ASMD=ml.exe -c -coff -nologo -Fo$* -I..\..\Include
!else
ASMA=jwasm.exe -q -Fo$* -I..\..\Include
ASMD=jwasm.exe -q -Fo$* -I..\..\Include
!endif

LINK=link.exe
LOPTA= /NOLOGO /MAP /SUBSYSTEM:CONSOLE /FIXED:NO /STUB:..\..\bin\dpmist32.bin /Entry:main /OPT:NOWIN98
LOPTD= /NOLOGO /MAP /DLL /DEF:$(DLLNAME).def /Entry:DllMain /OPT:NOWIN98

# use (w)vsprintf included in the static coff lib duser32s.lib
# this avoids having to load duser32.dll (and dkrnl32.dll)
LIBSA=..\..\Lib\duser32s.lib
LIBSD=..\..\Lib\duser32s.lib

ALL: $(APPNAME).EXE $(DLLNAME).DLL

# use the /MERGE linker option to put constant data in .text section

$(APPNAME).EXE: $*.obj Makefile
    $(LINK) $*.obj $(LOPTA) $(LIBSA) /MERGE:.rdata=.text
    ..\..\bin\patchPE $*.exe

$(APPNAME).OBJ: $(APPNAME).asm
    $(ASMA) $(APPNAME).asm

$(DLLNAME).DLL: $*.obj $(DLLNAME).def Makefile
    $(LINK) $*.obj $(LOPTD) $(LIBSD) /MERGE:.rdata=.text

$(DLLNAME).OBJ: $(DLLNAME).asm
    $(ASMD) $(DLLNAME).asm

