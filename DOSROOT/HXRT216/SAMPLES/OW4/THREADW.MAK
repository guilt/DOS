
# creates threadw.exe (Win32 binary)

name = THREAD

DEBUG=0

!if $(DEBUG)
COPTD=-d2
LOPTD=debug dwarf
!else
COPTD=-s
LOPTD=
!endif

OUTDIR=.
CC = wcc386 -fo$* $(COPTD)
LINK=wlink

$(OUTDIR)\$(name)W.exe: $*.obj
    $(LINK) system nt $(LOPTD) file $*.obj name $*.exe

$(OUTDIR)\$(name)W.obj: $(name).c $(name)W.mak
     $(CC) $(name).c

