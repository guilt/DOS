
# nmake makefile, enter:
#    nmake 
# with symbolic debugging info:
#    nmake debug=1
# for source level debugging with WD use wlink instead of MS link (MSLINK=0)
# WD must be started with parameter /swap on plain DOS

name = TextOut
name2 = DDClass

MSLINK=1

!ifdef DEBUG
COPTD=-Zi -D_DEBUG
LOPTDM=/DEBUG:FULL
LOPTDW=debug dwarf
OUTDIR=.
!else
COPTD=
LOPTDM=/DEBUG:NONE
LOPTDW=
OUTDIR=.
!endif

CC = cl -c -nologo -Fo$* $(COPTD)

!if $(MSLINK)
LIBS= kernel32.lib user32.lib gdi32.lib ddraw.lib dxguid.lib ..\..\Lib\libc32s.lib
LOPT=/OUT:$*.exe /SUBSYSTEM:CONSOLE $(LOPTDM) /FIXED:NO /NOLOGO /LIBPATH:\ddraw\lib /MAP
LINK=link.exe
MODS=$*.obj $(OUTDIR)\$(name2).obj
!else
LOPT=system nt $(LOPTDW) name $*.exe opt map opt start=_start opt stack=0x8000
MODS=file $*.obj, $(OUTDIR)\$(name2).obj
LIBS=library ddraw.lib, ..\..\Lib\libc32s.lib
LINK=wlink.exe
!endif

$(OUTDIR)\$(name).exe: $*.obj $(OUTDIR)\$(name2).obj
    $(LINK) $(MODS) $(LIBS) $(LOPT)

$(OUTDIR)\$(name).obj: $(name).cpp Makefile
     $(CC) $(name).cpp

$(OUTDIR)\$(name2).obj: $(name2).cpp Makefile
     $(CC) $(name2).cpp

