ORIGIN = PWB
ORIGIN_VER = 2.0
PROJ = MDI
PROJFILE = MDI.MAK
DEBUG = 0

BROWSE	= 0
PACK_SBRS  = 1
CC  = cl
CFLAGS_G  = /W2 /GA /GEf /Zp /BATCH /DWINVER=0x0300
CFLAGS_D  = /f /Zi /Od /Gs
CFLAGS_R  = /f- /Oe /Og /Os /Gs
CXX  = cl
CXXFLAGS_G  = /AM /W3 /G2 /GA /DWINVER=0x0300 /Yumdi.h /GEs /Zp /BATCH
CXXFLAGS_D  = /f /Od /Zi /D_DEBUG
CXXFLAGS_R  = /f- /Os /Ol /Og /Oe /Gs
BSCMAKE  = bscmake
SBRPACK  = sbrpack
NMAKEBSC1  = set
NMAKEBSC2  = nmake
MAPFILE_D  = NUL
MAPFILE_R  = NUL
LFLAGS_G  = /NOD /BATCH /ONERROR:NOEXE
LFLAGS_D  = /CO /NOF
LFLAGS_R  = /NOF
LLIBS_G  = LIBW.LIB COMMDLG.LIB
LINKER	= link
ILINK  = ilink
LRF  = echo > NUL
ILFLAGS  = /a /e
RC  = rc
RCFLAGS2  = /k /t /30
LLIBS_R  = MAFXCW /NOD:MLIBCE MLIBCEW
LLIBS_D  = MAFXCWD /NOD:MLIBCE MLIBCEW
PCHSRC_CXX  = bounce.cpp

FILES  = BOUNCE.CPP HELLO.CPP MDI.CPP MDI.RC MDI.DEF
DEF_FILE  = MDI.DEF
OBJS  = BOUNCE.obj HELLO.obj MDI.obj
RESS  = MDI.res
SBRS  = BOUNCE.sbr HELLO.sbr MDI.sbr

all: $(PROJ).exe

.SUFFIXES:
.SUFFIXES:
.SUFFIXES: .sbr .obj .res .cpp .rc

BOUNCE.obj : BOUNCE.CPP mdi.h hello.h bounce.h resource.h common.h
!IF $(DEBUG)
	@$(CXX) @<<$(PROJ).rsp
/Ycmdi.h /c $(CXXFLAGS_G)
$(CXXFLAGS_D) /FoBOUNCE.obj BOUNCE.CPP
<<
!ELSE
	@$(CXX) @<<$(PROJ).rsp
/Ycmdi.h /c $(CXXFLAGS_G)
$(CXXFLAGS_R) /FoBOUNCE.obj BOUNCE.CPP
<<
!ENDIF

BOUNCE.sbr : BOUNCE.CPP mdi.h hello.h bounce.h resource.h common.h
!IF $(DEBUG)
	@$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_D) /FRBOUNCE.sbr BOUNCE.CPP
<<
!ELSE
	@$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_R) /FRBOUNCE.sbr BOUNCE.CPP
<<
!ENDIF

HELLO.obj : HELLO.CPP mdi.h hello.h bounce.h resource.h common.h
!IF $(DEBUG)
	@$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_D) /FoHELLO.obj HELLO.CPP
<<
!ELSE
	@$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_R) /FoHELLO.obj HELLO.CPP
<<
!ENDIF

HELLO.sbr : HELLO.CPP mdi.h hello.h bounce.h resource.h common.h
!IF $(DEBUG)
	@$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_D) /FRHELLO.sbr HELLO.CPP
<<
!ELSE
	@$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_R) /FRHELLO.sbr HELLO.CPP
<<
!ENDIF

MDI.obj : MDI.CPP mdi.h hello.h bounce.h resource.h common.h
!IF $(DEBUG)
	@$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_D) /FoMDI.obj MDI.CPP
<<
!ELSE
	@$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_R) /FoMDI.obj MDI.CPP
<<
!ENDIF

MDI.sbr : MDI.CPP mdi.h hello.h bounce.h resource.h common.h
!IF $(DEBUG)
	@$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_D) /FRMDI.sbr MDI.CPP
<<
!ELSE
	@$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_R) /FRMDI.sbr MDI.CPP
<<
!ENDIF

MDI.res : MDI.RC resource.h mdi.ico hello.ico about.dlg
	$(RC) $(RCFLAGS1) /r /fo MDI.res MDI.RC


$(PROJ).bsc : $(SBRS)
	$(BSCMAKE) @<<
$(BRFLAGS) $(SBRS)
<<

$(PROJ).exe : $(DEF_FILE) $(OBJS) $(RESS)
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
	$(RC) $(RCFLAGS2) $(RESS) $@


.cpp.sbr :
!IF $(DEBUG)
	@$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_D) /FR$@ $<
<<
!ELSE
	@$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_R) /FR$@ $<
<<
!ENDIF

.cpp.obj :
!IF $(DEBUG)
	@$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_D) /Fo$@ $<
<<
!ELSE
	@$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_R) /Fo$@ $<
<<
!ENDIF

.rc.res :
	$(RC) $(RCFLAGS1) /r /fo $@ $<


run: $(PROJ).exe
	WX $(WXFLAGS) $(PROJ).exe $(RUNFLAGS)

debug: $(PROJ).exe
	WX /p $(WXFLAGS) CVW $(CVFLAGS) $(PROJ).exe $(RUNFLAGS)
