
# creates threadws.exe (DOS binary, static Win32)

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

$(OUTDIR)\$(name)WS.exe: $*.obj
    $(LINK) libpath ..\..\Lib system hxnts $(LOPTD) file $*.obj name $*.exe
    ..\..\Bin\patchPE $*.exe

$(OUTDIR)\$(name)WS.obj: $(name).c $(name)WS.mak
     $(CC) -mf -bt=nt $(name).c

