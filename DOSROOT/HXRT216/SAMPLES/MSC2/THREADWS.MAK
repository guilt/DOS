
# creates threadws.exe (DOS binary, static Win32)

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
LIBS=..\..\Lib\dkrnl32s.lib ..\..\Lib\duser32s.lib ..\..\Lib\imphlp.lib libc.lib

$(OUTDIR)\$(name)WS.exe: $*.obj
    $(LINK) /NOD /SUBSYSTEM:CONSOLE ..\..\Lib\InitW32.obj $*.obj $(LIBS) /OUT:$*.exe /FIXED:NO /OPT:NOWIN98 /MAP /STUB:..\..\Bin\LOADPE.BIN
    ..\..\Bin\patchPE $*.exe

$(OUTDIR)\$(name)WS.obj: $(name).c $(name)WS.mak
     $(CC) $(name).c

