
# NMAKE makefile to create vesa3.exe
#   nmake /f vesa3.mak
# MS VC and LINK are used
# to add debug info enter:
#   nmake /f vesa3.mak debug=1
# for source level debugging with WD use wlink instead of MS link (MSLINK=0)

name = vesa3

MSLINK=1

!ifdef DEBUG
COPTD=-Zd -DDEBUG
LOPTDM=/DEBUG:FULL
LOPTDW=debug dwarf
!else
COPTD=
LOPTDM=
LOPTDW=
!endif

# if vesa32 is linked statically, define _VESA32_ and use vesa32s.lib

CC = cl -c -nologo -D_VESA32_ -Fo$* -I..\..\Include $(COPTD)
!if $(MSLINK)
#LIBS= ..\..\lib\vesa32.lib
LIBS= ..\..\lib\vesa32s.lib
LOPT=/OUT:$*.exe /SUBSYSTEM:CONSOLE $(LOPTDM) /FIXED:NO /NOLOGO /MAP /NODEFAULTLIB /STUB:..\..\bin\loadpe.bin /FileAlign:0x200
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

$(name).obj: $(name).cpp $*.mak
     $(CC) $(name).cpp

