# $Header:   N:\admin\ocf\source\bocole\make.inv   2.0.1.0   10 Apr 1995 18:05:34   CQUINN  $
#-----------------------------------------------------------------------------
# ObjectComponents - (C) Copyright 1991, 1993 by Borland International
#
# MAKEFILE for ObjectComponents BOcOle Dlls
#
#  BCROOT  = Borland compiler root directory, parent of BIN, LIB, INCLUDE
#  APP     = name of application, used for .DLL
#  DEFNAME = name of .def, .res file
#  OBJS    = list of object files for link, each with .obj extension
#  LIBS    = list of library files to be searched in addition to standard ones
#  OBJDIR  = name of build directory, child of source directory
#  DLL     = defined if making a DLL, not defined for EXE
#------------------------------------------------------------------------

MAKEINC = ..\make.inc

.SUFFIXES: .OBJ .RC .DEF .CPP .C .ASM

!if !$d(TARGET_EXT)
!if $d(DLL)
TARGET_EXT = DLL
WSWITCH    = DE
!else
TARGET_EXT = EXE
WSWITCH    = S
!endif
!endif

!ifdef DIAGS
DEBUG = 1
TRACE = 1
WARN  = 1
!endif

!if !$d(BCROOT)
  BCROOT = $(MAKEDIR)\..   # default bcroot to parent of dir where make lives
!endif

!ifdef WIN32
#OLEINC    = $(SRCDIR)\..\boleui32
#OLELIB    = $(OLEROOT)\LIB;$(SRCDIR)\..\boleui32;
OLEINC    = $(SRCDIR)\boleui32
LIBPATH   = $(RELDIR);$(SRCDIR)\boleui32;$(BCROOT)\LIB
CONFIG    = bcc32.cfg
CPP       = @$(BCROOT)\BIN\BCC32
LINK      = $(BCROOT)\BIN\TLINK32
BRC       = $(BCROOT)\BIN\BRC32 -w32
!else
#OLEINC    = $(SRCDIR)\..\boleui
#OLELIB    = $(OLEROOT)\LIB;$(OLEROOT)\SAMP\LIB
OLEINC    = $(SRCDIR)\boleui
LIBPATH   = $(RELDIR);$(SRCDIR)\boleui;$(BCROOT)\LIB
CONFIG    = turboc.cfg
CPP       = @$(BCROOT)\BIN\BCC
LINK      = $(BCROOT)\BIN\TLINK
BRC       = $(BCROOT)\BIN\BRC
!endif

SRCDIR    = ..
#RELDIR    = $(SRCDIR)\..\..\REL$(VERSION)
RELDIR    = $(SRCDIR)\BIN

LIB       = $(BCROOT)\BIN\TLIB
IMPLIB    = $(BCROOT)\BIN\IMPLIB
ASM       = $(BCROOT)\BIN\TASM
RC        = $(BRC) -i$(BCROOT)\INCLUDE;$(OLEINC)

!ifdef WIN32
RLINK     = $(BCROOT)\BIN\BRC32
!else
RLINK     = $(BCROOT)\BIN\RLINK -fi
!endif
MAPSYM    = $(BCROOT)\BIN\TMAPSYM
CPPFLAGS  = -DINC_OLE2 # -DLOOSE_HRESULT

!if $(DEBUG)
  CPPFLAGS  = $(CPPFLAGS) -v -vi -D_DEBUG
!else
!ifdef WIN32                               # NDEBUG turns assert() off.
  CPPFLAGS  = $(CPPFLAGS) -DNDEBUG -k-     # -k- optimized stack frames.
!else                                      # -OW no inc/dec bp in
  CPPFLAGS  = $(CPPFLAGS) -DNDEBUG -OW -k- #     prolog/epilog (16 bit only).
!endif
!endif

!ifdef TRACE
CPPFLAGS  = $(CPPFLAGS) -D__TRACE
!endif
!ifdef WARN
CPPFLAGS  = $(CPPFLAGS) -D__WARN
!endif

!ifdef WIN32
  CPPFLAGS  = $(CPPFLAGS) -DWIN32 -a4
!ifdef ANSI
  CPPFLAGS =  $(CPPFLAGS) -DANSI
!endif
!endif

!ifdef UNICODE
  CPPFLAGS =  $(CPPFLAGS) -DUNICODE
!endif
!if $d(WIN32)
LINKFLAGS   = -c -C -Tw -n -s c0w$(MODEL)+
LINKFLAGSD  =       -Tpd -n -v -s c0d32+
!else
LINKFLAGS   = -c -C -Tw  -A=16 -n -s c0w$(MODEL)+
LINKFLAGSD  = -c -C -Twd -A=16 -n -v -s c0dl+
!endif

!ifdef WIN32
LIBS      = $(LIBS) cw$(MODEL) import32
!else
LIBS      = $(LIBS) cw$(MODEL) mathw$(MODEL) import
!endif

ALL: cdobj mdbin $(CONFIG) $(APP).$(TARGET_EXT) $(OTHER_TARGETS) cdsrc

cdobj:
  @if not exist $(OBJDIR)\NUL md $(OBJDIR)
  @cd $(OBJDIR)

mdbin:
  @if not exist $(RELDIR)\NUL md $(RELDIR)

cdsrc:
  @cd $(SRCDIR)

turboc.cfg: $(MAKEINC)
  @echo  Building turboc.cfg
  @copy &&|
  $(CPPFLAGS)
  -I$(SRCDIR);$(OLEINC);$(BCROOT)\INCLUDE
#  -I..\..\public;..\..\boleauto;..\..\bole;
  -w-par -w-aus -w-ef
  -c -2 -m$(MODEL) -i42 -d -W$(WSWITCH) -O -Obels -Z -RT- -x-
|       turboc.cfg
  @echo  Building tasm.cfg
  @copy &&|
  /mx/Zi
|       tasm.cfg

bcc32.cfg: $(MAKEINC)
  @echo  Building bcc32.cfg
  @copy &&|
  $(CPPFLAGS)
  -I$(SRCDIR);$(SRCDIR)\..\ole2ui;$(OLEINC);$(BCROOT)\INCLUDE;
#  -I..\..\public;..\..\bole
  -w-par -w-aus -w-ef
  -c -3 -i60 -d -W$(WSWITCH) -O -Obels -Z -RT- -x-
|       bcc32.cfg

$(APP).dll: $(OBJS) $(SRCDIR)\$(DEFNAME).def $(SRCDIR)\$(DEFNAME).res $(RESOURCES)
  $(LINK) $(LINKFLAGSD) @&&|
  -L$(LIBPATH) +
  $(OBJS)
  $@
  $(APP).map
  $(LIBS)
  $(SRCDIR)\$(DEFNAME).def
!ifdef WIN32
  $(SRCDIR)\$(DEFNAME).res $(RESOURCES)
!endif
|
!ifndef WIN32
  $(RLINK) $(SRCDIR)\$(DEFNAME).res $(RESOURCES) $@
!endif
#  copy $(APP).dll $(RELDIR)
  $(IMPLIB) $(RELDIR)\$(FILENAME).lib $(APP).dll

$(APP).exe : $(OBJS) $(DEFNAME).def $(DEFNAME).res
  $(LINK) $(LINKFLAGS) @<<$(APP).lnk
  -L$(LIBPATH) +
  $(OBJS:.obj =+)
  $@
  $(APP).map
  $(LIBS)
  $(DEFNAME).def
<<KEEP
  $(RLINK) $(DEFNAME).res $@
  copy $(APP).exe $(RELDIR)

## .DEF File Generation ##

$(DEFNAME).def : $(MAKEINC)
  copy &&|
  NAME       $(APP)
  DESCRIPTION 'OLE 2.0 $(APP) Sample'
  EXETYPE     WINDOWS
  CODE        PRELOAD MOVEABLE
  DATA        PRELOAD MOVEABLE MULTIPLE
  HEAPSIZE    4096
  STACKSIZE   8192
|       $(DEFNAME).def

## IMPLICIT RULES ##

{$(SRCDIR)}.c{}.obj:
  $(CPP) -c $<

{$(SRCDIR)}.cpp{}.obj:
  $(CPP) -c $<

{$(SRCDIR)}.asm{}.obj:
  $(ASM) /l/ml/n/q/t $<,$@

{$(SRCDIR)}.def{}.lib:
  $(IMPLIB) $@ $<

{$(SRCDIR)}.rc{}.res:
       $(RC) -r -i$(SRCDIR) -fo$@ $<

