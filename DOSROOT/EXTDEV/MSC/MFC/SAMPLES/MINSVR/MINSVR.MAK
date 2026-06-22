ORIGIN = PWB
ORIGIN_VER = 2.0
PROJ = minsvr
PROJFILE = minsvr.mak
DEBUG = 0

CC  = cl
CFLAGS_G  = /W2 /GA /GEf /Zp /BATCH /DWINVER=0x0300
CFLAGS_D  = /f /Zi /Od /Gs
CFLAGS_R  = /f- /Oe /Og /Os /Gs
CXX  = cl
CXXFLAGS_G  = /AM /W3 /G2 /GA /DWINVER=0x0300 /Yuminsvr.h /GEs /Zp /BATCH
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
LLIBS_G  = LIBW.LIB OLESVR.LIB SHELL.LIB
LINKER  = link
ILINK  = ilink
LRF  = echo > NUL
ILFLAGS  = /a /e
RC  = rc
RCFLAGS2  = /k /t /30
LLIBS_R  = MAFXCW /NOD:MLIBCE MLIBCEW
LLIBS_D  = MAFXCWD /NOD:MLIBCE MLIBCEW
PCHSRC_CXX  = mainwnd.cpp

FILES  = MAINWND.CPP MINDOC.CPP MINITEM.CPP MINSVR.CPP MINSVR.RC MINSVR.DEF
DEF_FILE  = MINSVR.DEF
OBJS  = MAINWND.obj MINDOC.obj MINITEM.obj MINSVR.obj
RESS  = MINSVR.res
SBRS  = MAINWND.sbr MINDOC.sbr MINITEM.sbr MINSVR.sbr

all: $(PROJ).exe

.SUFFIXES:
.SUFFIXES:
.SUFFIXES: .obj .sbr .res .cpp .rc

MAINWND.obj : MAINWND.CPP minsvr.h resource.h
!IF $(DEBUG)
        @$(CXX) @<<$(PROJ).rsp
/Ycminsvr.h /c $(CXXFLAGS_G)
$(CXXFLAGS_D) /FoMAINWND.obj MAINWND.CPP
<<
!ELSE
        @$(CXX) @<<$(PROJ).rsp
/Ycminsvr.h /c $(CXXFLAGS_G)
$(CXXFLAGS_R) /FoMAINWND.obj MAINWND.CPP
<<
!ENDIF

MAINWND.sbr : MAINWND.CPP minsvr.h resource.h
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

MINDOC.obj : MINDOC.CPP minsvr.h resource.h
!IF $(DEBUG)
        @$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_D) /FoMINDOC.obj MINDOC.CPP
<<
!ELSE
        @$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_R) /FoMINDOC.obj MINDOC.CPP
<<
!ENDIF

MINDOC.sbr : MINDOC.CPP minsvr.h resource.h
!IF $(DEBUG)
        @$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_D) /FRMINDOC.sbr MINDOC.CPP
<<
!ELSE
        @$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_R) /FRMINDOC.sbr MINDOC.CPP
<<
!ENDIF

MINITEM.obj : MINITEM.CPP minsvr.h resource.h
!IF $(DEBUG)
        @$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_D) /FoMINITEM.obj MINITEM.CPP
<<
!ELSE
        @$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_R) /FoMINITEM.obj MINITEM.CPP
<<
!ENDIF

MINITEM.sbr : MINITEM.CPP minsvr.h resource.h
!IF $(DEBUG)
        @$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_D) /FRMINITEM.sbr MINITEM.CPP
<<
!ELSE
        @$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_R) /FRMINITEM.sbr MINITEM.CPP
<<
!ENDIF

MINSVR.obj : MINSVR.CPP minsvr.h resource.h
!IF $(DEBUG)
        @$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_D) /FoMINSVR.obj MINSVR.CPP
<<
!ELSE
        @$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_R) /FoMINSVR.obj MINSVR.CPP
<<
!ENDIF

MINSVR.sbr : MINSVR.CPP minsvr.h resource.h
!IF $(DEBUG)
        @$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_D) /FRMINSVR.sbr MINSVR.CPP
<<
!ELSE
        @$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_R) /FRMINSVR.sbr MINSVR.CPP
<<
!ENDIF

MINSVR.res : MINSVR.RC resource.h MinSvr.ico about.dlg change.dlg
        $(RC) $(RCFLAGS1) /r /fo MINSVR.res MINSVR.RC


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

.rc.res :
        $(RC) $(RCFLAGS1) /r /fo $@ $<


run: $(PROJ).exe
        WX $(WXFLAGS) $(PROJ).exe $(RUNFLAGS)

debug: $(PROJ).exe
        WX /p $(WXFLAGS) CVW $(CVFLAGS) $(PROJ).exe $(RUNFLAGS)
