ORIGIN = PWB
ORIGIN_VER = 2.0
PROJ = testserv
PROJFILE = testserv.mak
DEBUG = 0

BROWSE  = 0
PACK_SBRS  = 1
CC  = cl
CFLAGS_G  = /W2 /GA /GEf /Zp /BATCH /DWINVER=0x0300
CFLAGS_D  = /f /Zi /Od /Gs
CFLAGS_R  = /f- /Oe /Og /Os /Gs
CXX  = cl
CXXFLAGS_G  = /AM /W3 /G2 /GA /DWINVER=0x0300 /Yutestserv.h /GEs /Zp /BATCH
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
LLIBS_G  = LIBW.LIB COMMDLG.LIB OLESVR.LIB SHELL.LIB
LINKER  = link
ILINK  = ilink
LRF  = echo > NUL
ILFLAGS  = /a /e
RC  = rc
RCFLAGS2  = /k /t /30
LLIBS_R  = MAFXCW /NOD:MLIBCE MLIBCEW
LLIBS_D  = MAFXCWD /NOD:MLIBCE MLIBCEW
PCHSRC_CXX  = clipbd.cpp

FILES  = CLIPBD.CPP ERROR.CPP NEWSERV.CPP SERVDOC.CPP TESTS.CPP TESTSERV.CPP\
        TSFILE.CPP TSOBJECT.CPP TESTSERV.DEF TESTSERV.RC
DEF_FILE  = TESTSERV.DEF
OBJS  = CLIPBD.obj ERROR.obj NEWSERV.obj SERVDOC.obj TESTS.obj TESTSERV.obj\
        TSFILE.obj TSOBJECT.obj
RESS  = TESTSERV.res
SBRS  = CLIPBD.sbr ERROR.sbr NEWSERV.sbr SERVDOC.sbr TESTS.sbr TESTSERV.sbr\
        TSFILE.sbr TSOBJECT.sbr

all: $(PROJ).exe

.SUFFIXES:
.SUFFIXES:
.SUFFIXES: .sbr .obj .res .cpp .rc

CLIPBD.obj : CLIPBD.CPP testserv.h tsobject.h servdoc.h newserv.h
!IF $(DEBUG)
        @$(CXX) @<<$(PROJ).rsp
/Yctestserv.h /c $(CXXFLAGS_G)
$(CXXFLAGS_D) /FoCLIPBD.obj CLIPBD.CPP
<<
!ELSE
        @$(CXX) @<<$(PROJ).rsp
/Yctestserv.h /c $(CXXFLAGS_G)
$(CXXFLAGS_R) /FoCLIPBD.obj CLIPBD.CPP
<<
!ENDIF

CLIPBD.sbr : CLIPBD.CPP testserv.h tsobject.h servdoc.h newserv.h
!IF $(DEBUG)
        @$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_D) /FRCLIPBD.sbr CLIPBD.CPP
<<
!ELSE
        @$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_R) /FRCLIPBD.sbr CLIPBD.CPP
<<
!ENDIF

ERROR.obj : ERROR.CPP testserv.h resource.h defs.h tsobject.h servdoc.h\
        newserv.h
!IF $(DEBUG)
        @$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_D) /FoERROR.obj ERROR.CPP
<<
!ELSE
        @$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_R) /FoERROR.obj ERROR.CPP
<<
!ENDIF

ERROR.sbr : ERROR.CPP testserv.h resource.h defs.h tsobject.h servdoc.h\
        newserv.h
!IF $(DEBUG)
        @$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_D) /FRERROR.sbr ERROR.CPP
<<
!ELSE
        @$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_R) /FRERROR.sbr ERROR.CPP
<<
!ENDIF

NEWSERV.obj : NEWSERV.CPP testserv.h defs.h tsobject.h servdoc.h newserv.h
!IF $(DEBUG)
        @$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_D) /FoNEWSERV.obj NEWSERV.CPP
<<
!ELSE
        @$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_R) /FoNEWSERV.obj NEWSERV.CPP
<<
!ENDIF

NEWSERV.sbr : NEWSERV.CPP testserv.h defs.h tsobject.h servdoc.h newserv.h
!IF $(DEBUG)
        @$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_D) /FRNEWSERV.sbr NEWSERV.CPP
<<
!ELSE
        @$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_R) /FRNEWSERV.sbr NEWSERV.CPP
<<
!ENDIF

SERVDOC.obj : SERVDOC.CPP testserv.h tsobject.h servdoc.h newserv.h
!IF $(DEBUG)
        @$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_D) /FoSERVDOC.obj SERVDOC.CPP
<<
!ELSE
        @$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_R) /FoSERVDOC.obj SERVDOC.CPP
<<
!ENDIF

SERVDOC.sbr : SERVDOC.CPP testserv.h tsobject.h servdoc.h newserv.h
!IF $(DEBUG)
        @$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_D) /FRSERVDOC.sbr SERVDOC.CPP
<<
!ELSE
        @$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_R) /FRSERVDOC.sbr SERVDOC.CPP
<<
!ENDIF

TESTS.obj : TESTS.CPP testserv.h tsobject.h servdoc.h newserv.h
!IF $(DEBUG)
        @$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_D) /FoTESTS.obj TESTS.CPP
<<
!ELSE
        @$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_R) /FoTESTS.obj TESTS.CPP
<<
!ENDIF

TESTS.sbr : TESTS.CPP testserv.h tsobject.h servdoc.h newserv.h
!IF $(DEBUG)
        @$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_D) /FRTESTS.sbr TESTS.CPP
<<
!ELSE
        @$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_R) /FRTESTS.sbr TESTS.CPP
<<
!ENDIF

TESTSERV.obj : TESTSERV.CPP testserv.h resource.h defs.h tsobject.h servdoc.h\
        newserv.h
!IF $(DEBUG)
        @$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_D) /FoTESTSERV.obj TESTSERV.CPP
<<
!ELSE
        @$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_R) /FoTESTSERV.obj TESTSERV.CPP
<<
!ENDIF

TESTSERV.sbr : TESTSERV.CPP testserv.h resource.h defs.h tsobject.h servdoc.h\
        newserv.h
!IF $(DEBUG)
        @$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_D) /FRTESTSERV.sbr TESTSERV.CPP
<<
!ELSE
        @$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_R) /FRTESTSERV.sbr TESTSERV.CPP
<<
!ENDIF

TSFILE.obj : TSFILE.CPP testserv.h resource.h defs.h tsobject.h servdoc.h\
        newserv.h
!IF $(DEBUG)
        @$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_D) /FoTSFILE.obj TSFILE.CPP
<<
!ELSE
        @$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_R) /FoTSFILE.obj TSFILE.CPP
<<
!ENDIF

TSFILE.sbr : TSFILE.CPP testserv.h resource.h defs.h tsobject.h servdoc.h\
        newserv.h
!IF $(DEBUG)
        @$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_D) /FRTSFILE.sbr TSFILE.CPP
<<
!ELSE
        @$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_R) /FRTSFILE.sbr TSFILE.CPP
<<
!ENDIF

TSOBJECT.obj : TSOBJECT.CPP testserv.h resource.h tsobject.h servdoc.h\
        newserv.h
!IF $(DEBUG)
        @$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_D) /FoTSOBJECT.obj TSOBJECT.CPP
<<
!ELSE
        @$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_R) /FoTSOBJECT.obj TSOBJECT.CPP
<<
!ENDIF

TSOBJECT.sbr : TSOBJECT.CPP testserv.h resource.h tsobject.h servdoc.h\
        newserv.h
!IF $(DEBUG)
        @$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_D) /FRTSOBJECT.sbr TSOBJECT.CPP
<<
!ELSE
        @$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_R) /FRTSOBJECT.sbr TSOBJECT.CPP
<<
!ENDIF

TESTSERV.res : TESTSERV.RC resource.h testserv.ico
        $(RC) $(RCFLAGS1) /r /fo TESTSERV.res TESTSERV.RC


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
