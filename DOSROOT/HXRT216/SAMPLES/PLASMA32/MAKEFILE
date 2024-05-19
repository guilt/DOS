
# nmake makefile, enter
#    nmake
# or, with symbolic debugging info:
#    nmake debug=1
# tools used:
# - assembler: JWasm or Masm
# - Win32 include files and libraries: Win32Inc
# - linker: MS link or WLink
#
# for source level debugging with WD use wlink instead of MS link (MSLINK=0)
# WD must be started with parameter /swap on plain DOS

name = plasma32
MSLINK=1
WIN32INC=\Win32Inc

!ifdef DEBUG
AOPTD=-Zi -DDEBUG
LOPTDM=/DEBUG:FULL
LOPTDW=debug dwarf
!else
AOPTD=
LOPTDM=/DEBUG:NONE
LOPTDW=
!endif

!ifndef MASM
MASM=0
!endif

!if $(MASM)
ASM = ml -c -coff -nologo -Fo$* $(AOPTD) -I$(WIN32INC)\Include
!else
ASM = jwasm -q -Fo$* $(AOPTD) -I$(WIN32INC)\Include
!endif

!if $(MSLINK)
LIBS= kernel32.lib user32.lib ddraw.lib
LOPT=/OUT:$*.exe /SUBSYSTEM:CONSOLE $(LOPTDM) /FIXED:NO /NOLOGO /LIBPATH:$(WIN32INC)\Lib /Entry:start
LINK=link.exe
MODS=$*.obj
!else
LOPT=system nt $(LOPTDW) name $*.exe opt map opt start=_start opt stack=0x8000
MODS=file $*.obj
LIBS=libpath $(WIN32INC)\Lib library ddraw.lib
LINK=wlink.exe
!endif

$(name).exe: $*.obj
    $(LINK) $(MODS) $(LIBS) $(LOPT)

$(name).obj: $(name).asm Makefile
     $(ASM) $(name).asm

