
# makefile for NMAKE to be used with MicroFocus Object Cobol

# CBLDYN  -> 1=link cobol runtime dynamically (use MFRTS32.DLL)
# CDYN    -> 1=link C runtime dynamically (use MSVCRT.DLL)
# DEBUG   -> 1=generate debug code for ANIMATOR2 (usage: ANIM2 xxxx.EXE)

NAME=MFCobol

CBLDYN=1
CDYN=1
DEBUG=0

OUTDIR=.

!if $(DEBUG)
CDEBUG=/eanim
LDEBUG=/DEBUG /DEBUGTYPE:CV
DEPS=$*.obj $*.idy $*.gdy
!else
CDEBUG=/noanim
LDEBUG=/DEBUG:NONE
DEPS=$*.obj
!endif

!if $(CDYN)
CLIB=msvcrt.lib
#CLIB=crtdll.lib
!else
#--- libc doesn't work with mfrts32s.lib, gives linker errors
CLIB=libc.lib
!endif

!if $(CBLDYN)
CBLLIB=mfrts32.lib
CNPARM=
!else
CBLLIB=mfrts32s.lib
CNPARM=-T
!endif

COBC = cobol /list"$*.lst" /obj"$*.obj" /cobidy"$*.idy" $(CDEBUG)
LINK= link
LOPTS=/SUBSYSTEM:CONSOLE $(SYSTEM) $(LDEBUG) /MAP /FIXED:NO
LIBS=kernel32.lib user32.lib $(CBLLIB) $(CLIB)


$(OUTDIR)\$(NAME).exe: $(DEPS) $(NAME).mak $(OUTDIR)\cblnames.obj
     $(LINK) $*.obj $(OUTDIR)\cblnames.obj /OUT:$*.exe $(LOPTS) $(LIBS) /STUB:..\bin\dpmist32.bin

$(OUTDIR)\cblnames.obj: $(OUTDIR)\$(NAME).obj
     cblnames -M$(NAME) -O$*.obj $(CNPARM) $(OUTDIR)\$(NAME).obj

$(OUTDIR)\$(NAME).obj: $(NAME).cbl $(NAME).mak
  $(COBC) $(NAME).cbl;
!if $(DEBUG)
     del $*.int
!endif

!if $(DEBUG)

$(OUTDIR)\$(NAME).idy: $(NAME).cbl $(NAME).mak
  $(COBC) $(NAME).cbl;
  del $*.int
$(OUTDIR)\$(NAME).gdy: $(NAME).cbl $(NAME).mak
  $(COBC) $(NAME).cbl;
  del $*.int

!endif

