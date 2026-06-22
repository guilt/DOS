ORIGIN = PWB
ORIGIN_VER = 2.0
PROJ = grdemo
PROJFILE = grdemo.mak
DEBUG = 0

BSCMAKE  = bscmake
SBRPACK  = sbrpack
NMAKEBSC1  = set
NMAKEBSC2  = nmake
CC  = cl
CFLAGS_G  = /W3 /BATCH /FR$*.sbr
CFLAGS_D  = /f /Od /Zi
CFLAGS_R  = /f- /Ot /Ol /Og /Oe /Oi /Gs
CXX  = cl
CXXFLAGS_G  = /W2 /BATCH /FR$*.sbr
CXXFLAGS_D  = /f /Zi /Od
CXXFLAGS_R  = /f- /Ot /Oi /Ol /Oe /Og /Gs
MAPFILE_D  = NUL
MAPFILE_R  = NUL
LFLAGS_G  = /NOI /BATCH /ONERROR:NOEXE
LFLAGS_D  = /CO /FAR /PACKC
LFLAGS_R  = /EXE /FAR /PACKC
LINKER	= link
ILINK  = ilink
LRF  = echo > NUL
ILFLAGS  = /a /e
LLIBS_G  = graphics
BRFLAGS  =  /o $(PROJ).bsc
BROWSE	= 1
PACK_SBRS  = 1

FILES  = GRDEMO.C MENU.C MOUSE.C TURTLE.C
OBJS  = GRDEMO.obj MENU.obj MOUSE.obj TURTLE.obj
SBRS  = GRDEMO.sbr MENU.sbr MOUSE.sbr TURTLE.sbr

all: $(PROJ).exe

.SUFFIXES:
.SUFFIXES:
.SUFFIXES: .sbr .obj .c

GRDEMO.obj : GRDEMO.C turtle.h menu.h
!IF $(DEBUG)
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_D) /FoGRDEMO.obj GRDEMO.C
<<
!ELSE
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_R) /FoGRDEMO.obj GRDEMO.C
<<
!ENDIF

GRDEMO.sbr : GRDEMO.C turtle.h menu.h
!IF $(DEBUG)
	@$(CC) @<<$(PROJ).rsp
/Zs $(CFLAGS_G)
$(CFLAGS_D) /FRGRDEMO.sbr GRDEMO.C
<<
!ELSE
	@$(CC) @<<$(PROJ).rsp
/Zs $(CFLAGS_G)
$(CFLAGS_R) /FRGRDEMO.sbr GRDEMO.C
<<
!ENDIF

MENU.obj : MENU.C menu.h mouse.h
!IF $(DEBUG)
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_D) /FoMENU.obj MENU.C
<<
!ELSE
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_R) /FoMENU.obj MENU.C
<<
!ENDIF

MENU.sbr : MENU.C menu.h mouse.h
!IF $(DEBUG)
	@$(CC) @<<$(PROJ).rsp
/Zs $(CFLAGS_G)
$(CFLAGS_D) /FRMENU.sbr MENU.C
<<
!ELSE
	@$(CC) @<<$(PROJ).rsp
/Zs $(CFLAGS_G)
$(CFLAGS_R) /FRMENU.sbr MENU.C
<<
!ENDIF

MOUSE.obj : MOUSE.C mouse.h
!IF $(DEBUG)
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_D) /FoMOUSE.obj MOUSE.C
<<
!ELSE
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_R) /FoMOUSE.obj MOUSE.C
<<
!ENDIF

MOUSE.sbr : MOUSE.C mouse.h
!IF $(DEBUG)
	@$(CC) @<<$(PROJ).rsp
/Zs $(CFLAGS_G)
$(CFLAGS_D) /FRMOUSE.sbr MOUSE.C
<<
!ELSE
	@$(CC) @<<$(PROJ).rsp
/Zs $(CFLAGS_G)
$(CFLAGS_R) /FRMOUSE.sbr MOUSE.C
<<
!ENDIF

TURTLE.obj : TURTLE.C turtle.h
!IF $(DEBUG)
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_D) /FoTURTLE.obj TURTLE.C
<<
!ELSE
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_R) /FoTURTLE.obj TURTLE.C
<<
!ENDIF

TURTLE.sbr : TURTLE.C turtle.h
!IF $(DEBUG)
	@$(CC) @<<$(PROJ).rsp
/Zs $(CFLAGS_G)
$(CFLAGS_D) /FRTURTLE.sbr TURTLE.C
<<
!ELSE
	@$(CC) @<<$(PROJ).rsp
/Zs $(CFLAGS_G)
$(CFLAGS_R) /FRTURTLE.sbr TURTLE.C
<<
!ENDIF


$(PROJ).bsc : $(SBRS)
	$(BSCMAKE) @<<
$(BRFLAGS) $(SBRS)
<<

$(PROJ).exe : $(OBJS)
	-$(NMAKEBSC1) MAKEFLAGS=
	-$(NMAKEBSC2) $(NMFLAGS) -f $(PROJFILE) $(PROJ).bsc
!IF $(DEBUG)
	$(LRF) @<<$(PROJ).lrf
$(RT_OBJS: = +^
) $(OBJS: = +^
)
$@
$(MAPFILE_D)
$(LIBS: = +^
) +
$(LLIBS_G: = +^
) +
$(LLIBS_D: = +^
)
$(DEF_FILE) $(LFLAGS_G) $(LFLAGS_D);
<<
!ELSE
	$(LRF) @<<$(PROJ).lrf
$(RT_OBJS: = +^
) $(OBJS: = +^
)
$@
$(MAPFILE_R)
$(LIBS: = +^
) +
$(LLIBS_G: = +^
) +
$(LLIBS_R: = +^
)
$(DEF_FILE) $(LFLAGS_G) $(LFLAGS_R);
<<
!ENDIF
	$(LINKER) @$(PROJ).lrf


.c.sbr :
!IF $(DEBUG)
	@$(CC) @<<$(PROJ).rsp
/Zs $(CFLAGS_G)
$(CFLAGS_D) /FR$@ $<
<<
!ELSE
	@$(CC) @<<$(PROJ).rsp
/Zs $(CFLAGS_G)
$(CFLAGS_R) /FR$@ $<
<<
!ENDIF

.c.obj :
!IF $(DEBUG)
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_D) /Fo$@ $<
<<
!ELSE
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_R) /Fo$@ $<
<<
!ENDIF


run: $(PROJ).exe
	$(PROJ).exe $(RUNFLAGS)

debug: $(PROJ).exe
	CV $(CVFLAGS) $(PROJ).exe $(RUNFLAGS)
