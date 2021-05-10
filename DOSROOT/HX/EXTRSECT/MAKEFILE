
# nmake makefile to create extrsect.exe
# tools needed:
# - jwasm
# - win32inc
# - MS link
# - HX dev

name = EXTRSECT

WIN32INC=\Win32Inc
HX=\hx

# set DOS=1 if a DOS binary is to be created
DOS=0

!ifndef DEBUG
DEBUG=0
!endif

!if $(DEBUG)
OUTDIR=Debug
AOPTD=-Zi
LOPTD=/DEBUG
!else
OUTDIR=Release
AOPTD=
LOPTD=
!endif

ASM =@jwasm.exe -c -nologo -coff -Sg -Fl$* -Fo$* -D_ML $(AOPTD) -I$(WIN32INC)\Include
!if $(DOS)
LIBS=/Libpath:$(HX)\Lib dkrnl32s.lib duser32s.lib libc32s.lib imphlp.lib
LOPT=/NOLOGO /SUBSYSTEM:CONSOLE /OPT:NOWIN98 /FIXED:NO /STUB:$(HX)\Bin\loadpe.bin
MODS=$(HX)\Lib\InitW32.obj
!else
LIBS=/Libpath:$(WIN32INC)\Lib\ kernel32.lib user32.lib $(HX)\Lib\libc32s.lib
LOPT=/NOLOGO /SUBSYSTEM:CONSOLE /OPT:NOWIN98
MODS=
!endif
LINK=@link.exe


ALL: $(OUTDIR) $(OUTDIR)\$(name).EXE

$(OUTDIR):
	@mkdir $(OUTDIR)

$(OUTDIR)\$(name).EXE: $*.obj makefile
	$(LINK) @<<
$*.obj $(MODS) /OUT:$*.exe /MAP:$*.map $(LIBS) $(LOPT) $(LOPTD)
<<
!if $(DOS)
	patchPE $*.exe
!endif

$(OUTDIR)\$(name).obj: $(name).asm makefile
	$(ASM) $(name).asm
