
#--- better use DJLDFIX!

#--- LDFIX is a tool to fix COFF objects written by (some) LD versions
#--- to make them compatible with MS COFF linker

name = LDFIX

#--- this app may be generated as standard MZ executable as well
#--- but then set the path of the 16-bit OMF linker first
#--- currently used: Digital Mars C++ OMF linker

MZAPP=0
USEDLL=0

!ifndef DEBUG
DEBUG=0
!endif

!if $(MZAPP)
OUTDIR=TEXT
AOPTD=
!elseif $(DEBUG)
OUTDIR=DEBUG
AOPTD=-Zi -D_DEBUG
!else
OUTDIR=RELEASE
AOPTD=
!endif

!include <..\..\dirs>

!ifndef MASM
MASM=0
!endif

!if $(MZAPP)

LOPTD=

ASMOPT=-c -nologo -Sg -Fl$* -Fo$* -D?FLAT=0 -D_ML $(AOPTD) -I..\$(INC32DIR)
!if $(MASM)
ASM = @ml.exe $(ASMOPT)
!else
ASM = @jwasm.exe $(ASMOPT)
!endif

!if 0
LIBS=jmppm32.lib dkrnl32s.lib duser32s.lib libc32.lib
LOPT=/MAP:FULL/NON/NOE/NOD/ONE:NOE/NOLOGO $(LOPTD)
LINK=link16.exe
MODS=jmppm32.obj $*.obj dmythunk.obj
!else
LIBS=jmppm32.lib dkrnl32s.lib libc32.lib
LOPT=/MAP:FULL/NON/NOE
LINK=$(DMCDIR)\link.exe
MODS=$*.obj jmppm32.obj dmythunk.obj
!endif

!else

!if $(DEBUG)
LOPTD=/DEBUG
!else
LOPTD=
!endif

ASMOPT2=-c -nologo -Sg -Fl$* -Fo$* -D?FLAT=1 -coff $(AOPTD) -I..\$(INC32DIR)
!if $(MASM)
ASM = @ml.exe $(ASMOPT2)
!else
ASM = @jwasm.exe $(ASMOPT2)
!endif

!if $(USEDLL)
CRTLIB=crtdll.lib
!else
CRTLIB=libc32s.lib
!endif
LIBS= dkrnl32.lib duser32s.lib $(CRTLIB)
LOPT=/OUT:$*.EXE /NOLOGO /NODEFAULTLIB /MAP:$*.map /SUBSYSTEM:CONSOLE $(LOPTD) /FIXED:NO  /STUB:..\..\..\bin\dpmist32.bin /MERGE:.rdata=.data /MERGE:.reloc=.text
LINK=polink

!endif

!if $(MZAPP)
$(OUTDIR)\$(name).EXE: $*.obj makefile
    $(LINK) @<<
$(MODS),$*,$*,$(LIBS) $(LOPT);
<<
!else
$(OUTDIR)\$(name).EXE: $*.obj makefile
#   set LIB=\lib\coff
    $(LINK) $*.obj /LIBPATH:..\..\..\Lib $(LOPT) $(LIBS) 
#!if $(DEBUG)==0
#	@copy $*.EXE ..\..\bin\*.* >NUL
#!ifdef TOOLSDIR
#	@copy $*.EXE $(TOOLSDIR)\$(name).EXE
#!endif    
#!endif
!endif

$(OUTDIR)\$(name).obj: $(name).asm makefile
     $(ASM) $(name).asm

clean:
	@del $(OUTDIR)\*.obj
	@del $(OUTDIR)\*.exe
	@del $(OUTDIR)\*.lst
	@del $(OUTDIR)\*.map

