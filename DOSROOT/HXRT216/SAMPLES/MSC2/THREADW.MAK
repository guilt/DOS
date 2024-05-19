
# creates threadw.exe (Win32 binary)

name = THREAD

DEBUG=0

!if $(DEBUG)
COPTD=-Zi -Od
LOPTD=/DEBUG:CV
!else
COPTD=-Ox
LOPTD=
!endif

OUTDIR=.
CC = cl -Fo$* $(COPTD)
LINK=link
LIBS=kernel32.lib user32.lib

$(OUTDIR)\$(name)W.exe: $*.obj
    $(LINK) /SUBSYSTEM:CONSOLE $*.obj $(LIBS) /OUT:$*.exe /FIXED:NO /OPT:NOWIN98 /MAP

$(OUTDIR)\$(name)W.obj: $(name).c $(name)W.mak
     $(CC) $(name).c

