
# NMAKE makefile, creates a HX PE binary (DOS), enter
#    nmake /f vesa2.mak
# MS masm and MS OMF linker are used.

# for a binary with debug infos enter:
#    nmake /f vesa2.mak debug=1
# To make WD understand the debugging info of PE binaries, it is best
# to use Open Watcom's wlink for the link step (MSLINK=0)

name = VESA2

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
ASM = ml -c -coff -nologo -Fo$* -D_VESA32_ -D?FLAT=1 -I..\..\Include $(AOPTD)
!else
ASM = jwasm -q -Fo$* -D_VESA32_ -D?FLAT=1 -I..\..\Include $(AOPTD)
!endif

!if $(MSLINK)
#LIBS= ..\..\lib\vesa32.lib
LIBS= ..\..\lib\vesa32s.lib
LOPT=/OUT:$*.EXE /SUBSYSTEM:CONSOLE $(LOPTDM) /FIXED:NO /MAP /NOLOGO /STUB:..\..\bin\loadpe.bin /FileAlign:0x100
MODS=$*.obj
LINK=link 
!else
LOPT=system hxdos $(LOPTDW) name $*.exe opt map opt start=_mainCRTStartup
MODS=file $*.obj
LIBS=library ..\..\lib\vesa32s.lib
LINK=wlink
!endif

$(name).EXE: $*.obj
    $(LINK) @<<
$(LOPT) $(MODS) $(LIBS) 
<<
    ..\..\bin\patchPE $*.EXE

$(name).obj: $(name).asm $*.mak
     $(ASM) $(name).asm

