ORIGIN = PWB
ORIGIN_VER = 2.0
PROJ = bibref
PROJFILE = bibref.mak
DEBUG = 0

BROWSE  = 0
PACK_SBRS  = 1
CC  = cl
CFLAGS_G  = /W2 /GA /GEf /Zp /BATCH /DWINVER=0x0300
CFLAGS_D  = /f /Zi /Od /Gs
CFLAGS_R  = /f- /Oe /Og /Os /Gs
CXX  = cl
CXXFLAGS_G  = /AM /W3 /G2 /GA /DWINVER=0x0300 /Yubibref.h /GEs /Zp /BATCH
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
PCHSRC_CXX  = bibdoc.cpp

FILES  = BIBDOC.CPP BIBITEM.CPP BIBREF.CPP BIBSVR.CPP MAINWND.CPP BIBREF.RC\
        BIBREF.DEF
DEF_FILE  = BIBREF.DEF
OBJS  = BIBDOC.obj BIBITEM.obj BIBREF.obj BIBSVR.obj MAINWND.obj
RESS  = BIBREF.res
SBRS  = BIBDOC.sbr BIBITEM.sbr BIBREF.sbr BIBSVR.sbr MAINWND.sbr

all: $(PROJ).exe

.SUFFIXES:
.SUFFIXES:
.SUFFIXES: .sbr .obj .res .cpp .rc

BIBDOC.obj : BIBDOC.CPP bibref.h bibdoc.h bibitem.h resource.h
!IF $(DEBUG)
        @$(CXX) @<<$(PROJ).rsp
/Ycbibref.h /c $(CXXFLAGS_G)
$(CXXFLAGS_D) /FoBIBDOC.obj BIBDOC.CPP
<<
!ELSE
        @$(CXX) @<<$(PROJ).rsp
/Ycbibref.h /c $(CXXFLAGS_G)
$(CXXFLAGS_R) /FoBIBDOC.obj BIBDOC.CPP
<<
!ENDIF

BIBDOC.sbr : BIBDOC.CPP bibref.h bibdoc.h bibitem.h resource.h
!IF $(DEBUG)
        @$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_D) /FRBIBDOC.sbr BIBDOC.CPP
<<
!ELSE
        @$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_R) /FRBIBDOC.sbr BIBDOC.CPP
<<
!ENDIF

BIBITEM.obj : BIBITEM.CPP bibref.h bibitem.h bibdoc.h resource.h
!IF $(DEBUG)
        @$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_D) /FoBIBITEM.obj BIBITEM.CPP
<<
!ELSE
        @$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_R) /FoBIBITEM.obj BIBITEM.CPP
<<
!ENDIF

BIBITEM.sbr : BIBITEM.CPP bibref.h bibitem.h bibdoc.h resource.h
!IF $(DEBUG)
        @$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_D) /FRBIBITEM.sbr BIBITEM.CPP
<<
!ELSE
        @$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_R) /FRBIBITEM.sbr BIBITEM.CPP
<<
!ENDIF

BIBREF.obj : BIBREF.CPP bibref.h mainwnd.h bibsvr.h resource.h
!IF $(DEBUG)
        @$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_D) /FoBIBREF.obj BIBREF.CPP
<<
!ELSE
        @$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_R) /FoBIBREF.obj BIBREF.CPP
<<
!ENDIF

BIBREF.sbr : BIBREF.CPP bibref.h mainwnd.h bibsvr.h resource.h
!IF $(DEBUG)
        @$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_D) /FRBIBREF.sbr BIBREF.CPP
<<
!ELSE
        @$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_R) /FRBIBREF.sbr BIBREF.CPP
<<
!ENDIF

BIBSVR.obj : BIBSVR.CPP bibref.h bibsvr.h bibdoc.h mainwnd.h resource.h
!IF $(DEBUG)
        @$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_D) /FoBIBSVR.obj BIBSVR.CPP
<<
!ELSE
        @$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_R) /FoBIBSVR.obj BIBSVR.CPP
<<
!ENDIF

BIBSVR.sbr : BIBSVR.CPP bibref.h bibsvr.h bibdoc.h mainwnd.h resource.h
!IF $(DEBUG)
        @$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_D) /FRBIBSVR.sbr BIBSVR.CPP
<<
!ELSE
        @$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_R) /FRBIBSVR.sbr BIBSVR.CPP
<<
!ENDIF

MAINWND.obj : MAINWND.CPP bibref.h mainwnd.h bibdoc.h resource.h
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

MAINWND.sbr : MAINWND.CPP bibref.h mainwnd.h bibdoc.h resource.h
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

BIBREF.res : BIBREF.RC resource.h bibref.ico about.dlg item.dlg
        $(RC) $(RCFLAGS1) /r /fo BIBREF.res BIBREF.RC


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
