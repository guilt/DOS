ORIGIN = PWB
ORIGIN_VER = 2.0
PROJ = showfont
PROJFILE = showfont.mak
DEBUG = 0

BROWSE	= 0
PACK_SBRS  = 1
CC  = cl
CFLAGS_G  = /W2 /GA /GEf /Zp /BATCH /DWINVER=0x0300
CFLAGS_D  = /f /Zi /Od /Gs
CFLAGS_R  = /f- /Oe /Og /Os /Gs
CXX  = cl
CXXFLAGS_G  = /AM /W3 /G2 /GA /DWINVER=0x0300 /Yushowfont.h /GEs /Zp /BATCH
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
LLIBS_G  = LIBW.LIB
LINKER	= link
ILINK  = ilink
LRF  = echo > NUL
ILFLAGS  = /a /e
RC  = rc
RCFLAGS2  = /k /t /30
LLIBS_R  = MAFXCW /NOD:MLIBCE MLIBCEW
LLIBS_D  = MAFXCWD /NOD:MLIBCE MLIBCEW
PCHSRC_CXX  = cfont.cpp

FILES  = CFONT.CPP DIALOGS.CPP DRAWING.CPP MAINWND.CPP SHOWFONT.CPP\
	SHOWFONT.RC SHOWFONT.DEF
DEF_FILE  = SHOWFONT.DEF
OBJS  = CFONT.obj DIALOGS.obj DRAWING.obj MAINWND.obj SHOWFONT.obj
RESS  = SHOWFONT.res
SBRS  = CFONT.sbr DIALOGS.sbr DRAWING.sbr MAINWND.sbr SHOWFONT.sbr

all: $(PROJ).exe

.SUFFIXES:
.SUFFIXES:
.SUFFIXES: .sbr .obj .res .cpp .rc

CFONT.obj : CFONT.CPP showfont.h resource.h mainwnd.h
!IF $(DEBUG)
	@$(CXX) @<<$(PROJ).rsp
/Ycshowfont.h /c $(CXXFLAGS_G)
$(CXXFLAGS_D) /FoCFONT.obj CFONT.CPP
<<
!ELSE
	@$(CXX) @<<$(PROJ).rsp
/Ycshowfont.h /c $(CXXFLAGS_G)
$(CXXFLAGS_R) /FoCFONT.obj CFONT.CPP
<<
!ENDIF

CFONT.sbr : CFONT.CPP showfont.h resource.h mainwnd.h
!IF $(DEBUG)
	@$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_D) /FRCFONT.sbr CFONT.CPP
<<
!ELSE
	@$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_R) /FRCFONT.sbr CFONT.CPP
<<
!ENDIF

DIALOGS.obj : DIALOGS.CPP showfont.h resource.h mainwnd.h
!IF $(DEBUG)
	@$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_D) /FoDIALOGS.obj DIALOGS.CPP
<<
!ELSE
	@$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_R) /FoDIALOGS.obj DIALOGS.CPP
<<
!ENDIF

DIALOGS.sbr : DIALOGS.CPP showfont.h resource.h mainwnd.h
!IF $(DEBUG)
	@$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_D) /FRDIALOGS.sbr DIALOGS.CPP
<<
!ELSE
	@$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_R) /FRDIALOGS.sbr DIALOGS.CPP
<<
!ENDIF

DRAWING.obj : DRAWING.CPP showfont.h resource.h mainwnd.h
!IF $(DEBUG)
	@$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_D) /FoDRAWING.obj DRAWING.CPP
<<
!ELSE
	@$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_R) /FoDRAWING.obj DRAWING.CPP
<<
!ENDIF

DRAWING.sbr : DRAWING.CPP showfont.h resource.h mainwnd.h
!IF $(DEBUG)
	@$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_D) /FRDRAWING.sbr DRAWING.CPP
<<
!ELSE
	@$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_R) /FRDRAWING.sbr DRAWING.CPP
<<
!ENDIF

MAINWND.obj : MAINWND.CPP showfont.h resource.h mainwnd.h
!IF $(DEBUG)
	@$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_D) /FoMAINWND.obj MAINWND.CPP
<<
!ELSE
	@$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_R) /FoMAINWND.obj MAINWND.CPP
<<
!ENDIF

MAINWND.sbr : MAINWND.CPP showfont.h resource.h mainwnd.h
!IF $(DEBUG)
	@$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_D) /FRMAINWND.sbr MAINWND.CPP
<<
!ELSE
	@$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_R) /FRMAINWND.sbr MAINWND.CPP
<<
!ENDIF

SHOWFONT.obj : SHOWFONT.CPP showfont.h resource.h mainwnd.h
!IF $(DEBUG)
	@$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_D) /FoSHOWFONT.obj SHOWFONT.CPP
<<
!ELSE
	@$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_R) /FoSHOWFONT.obj SHOWFONT.CPP
<<
!ENDIF

SHOWFONT.sbr : SHOWFONT.CPP showfont.h resource.h mainwnd.h
!IF $(DEBUG)
	@$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_D) /FRSHOWFONT.sbr SHOWFONT.CPP
<<
!ELSE
	@$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_R) /FRSHOWFONT.sbr SHOWFONT.CPP
<<
!ENDIF

SHOWFONT.res : SHOWFONT.RC resource.h showfont.ico about.dlg cfont.dlg
	$(RC) $(RCFLAGS1) /r /fo SHOWFONT.res SHOWFONT.RC


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
