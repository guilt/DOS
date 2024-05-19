
# NMAKE makefile, creates a HX PE binary (DOS), enter
#    nmake /f vesa1.mak
# MS masm and MS OMF linker are used.

# for a binary with debug infos enter:
#    nmake /f vesa1.mak debug=1
# To make WD understand the debugging info of PE binaries, it is best
# to use Open Watcom's wlink for the link step (MSLINK=0)

name = vesa1

MSLINK=1

!ifdef DEBUG
AOPTD=-Zi -DDEBUG
LOPTDM=/DEBUG:FULL
LOPTDW=debug dwarf
!else
AOPTD=
LOPTDM=
LOPTDW=
!endif

!ifndef MASM
MASM=0
!endif

!if $(MASM)
ASM = ml -c -coff -nologo -Fo$* -D?RES=2 -D?FLAT=1 -D_VESA32_ -I..\..\Include $(AOPTD)
!else
ASM = jwasm -q -Fo$* -D?RES=2 -D?FLAT=1 -D_VESA32_ -I..\..\Include $(AOPTD)
!endif

!if $(MSLINK)
#LIBS= ..\..\lib\vesa32.lib
LIBS= ..\..\lib\vesa32s.lib
LOPT=/OUT:$*.exe /SUBSYSTEM:CONSOLE $(LOPTD) /MAP /FIXED:NO /NOLOGO /STUB:..\..\bin\loadpe.bin /FileAlign:0x100
LINK=link
MODS=$*.obj
!else
LOPT=system hx $(LOPTDW) name $*.exe opt map opt start=_mainCRTStartup
MODS=file $*.obj
LIBS=library ..\..\lib\vesa32s.lib
LINK=wlink
!endif

$(name).exe: $*.obj
    $(LINK) @<<
$(LOPT) $(MODS) $(LIBS)
<<
    ..\..\bin\patchPE $*.exe

$(name).obj: $(name).asm $*.mak
     $(ASM) $(name).asm

