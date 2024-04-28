ORIGIN = PWB
ORIGIN_VER = 2.0
PROJ = testclnt
PROJFILE = testclnt.mak
DEBUG = 0

BROWSE  = 0
PACK_SBRS  = 1
CC  = cl
CFLAGS_G  = /W2 /GA /GEf /Zp /BATCH /DWINVER=0x0300
CFLAGS_D  = /f /Zi /Od /Gs
CFLAGS_R  = /f- /Oe /Og /Os /Gs
CXX  = cl
CXXFLAGS_G  = /AM /W3 /G2 /GA /DWINVER=0x0300 /Yutestclnt.h /GEs /Zp /BATCH
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
LLIBS_G  = LIBW.LIB COMMDLG.LIB SHELL.LIB OLECLI.LIB
LINKER  = link
ILINK  = ilink
LRF  = echo > NUL
ILFLAGS  = /a /e
RC  = rc
RCFLAGS2  = /k /t /30
LLIBS_R  = MAFXCW /NOD:MLIBCE MLIBCEW
LLIBS_D  = MAFXCWD /NOD:MLIBCE MLIBCEW
PCHSRC_CXX  = clipbd.cpp

FILES  = CLIPBD.CPP ERROR.CPP NEWCLNT.CPP NEWDOC.CPP TCFILE.CPP TCOBJECT.CPP\
        TESTCLNT.CPP TESTS.CPP TESTCLNT.DEF TESTCLNT.RC
DEF_FILE  = TESTCLNT.DEF
OBJS  = CLIPBD.obj ERROR.obj NEWCLNT.obj NEWDOC.obj TCFILE.obj TCOBJECT.obj\
        TESTCLNT.obj TESTS.obj
RESS  = TESTCLNT.res
SBRS  = CLIPBD.sbr ERROR.sbr NEWCLNT.sbr NEWDOC.sbr TCFILE.sbr TCOBJECT.sbr\
        TESTCLNT.sbr TESTS.sbr

all: $(PROJ).exe

.SUFFIXES:
.SUFFIXES:
.SUFFIXES: .sbr .obj .res .cpp .rc

CLIPBD.obj : CLIPBD.CPP testclnt.h resource.h defs.h newdoc.h newclnt.h
!IF $(DEBUG)
        @$(CXX) @<<$(PROJ).rsp
/Yctestclnt.h /c $(CXXFLAGS_G)
$(CXXFLAGS_D) /FoCLIPBD.obj CLIPBD.CPP
<<
!ELSE
        @$(CXX) @<<$(PROJ).rsp
/Yctestclnt.h /c $(CXXFLAGS_G)
$(CXXFLAGS_R) /FoCLIPBD.obj CLIPBD.CPP
<<
!ENDIF

CLIPBD.sbr : CLIPBD.CPP testclnt.h resource.h defs.h newdoc.h newclnt.h
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

ERROR.obj : ERROR.CPP testclnt.h resource.h defs.h newdoc.h newclnt.h
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

ERROR.sbr : ERROR.CPP testclnt.h resource.h defs.h newdoc.h newclnt.h
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

NEWCLNT.obj : NEWCLNT.CPP resource.h testclnt.h defs.h newdoc.h newclnt.h
!IF $(DEBUG)
        @$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_D) /FoNEWCLNT.obj NEWCLNT.CPP
<<
!ELSE
        @$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_R) /FoNEWCLNT.obj NEWCLNT.CPP
<<
!ENDIF

NEWCLNT.sbr : NEWCLNT.CPP resource.h testclnt.h defs.h newdoc.h newclnt.h
!IF $(DEBUG)
        @$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_D) /FRNEWCLNT.sbr NEWCLNT.CPP
<<
!ELSE
        @$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_R) /FRNEWCLNT.sbr NEWCLNT.CPP
<<
!ENDIF

NEWDOC.obj : NEWDOC.CPP testclnt.h newdoc.h newclnt.h
!IF $(DEBUG)
        @$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_D) /FoNEWDOC.obj NEWDOC.CPP
<<
!ELSE
        @$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_R) /FoNEWDOC.obj NEWDOC.CPP
<<
!ENDIF

NEWDOC.sbr : NEWDOC.CPP testclnt.h newdoc.h newclnt.h
!IF $(DEBUG)
        @$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_D) /FRNEWDOC.sbr NEWDOC.CPP
<<
!ELSE
        @$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_R) /FRNEWDOC.sbr NEWDOC.CPP
<<
!ENDIF

TCFILE.obj : TCFILE.CPP testclnt.h defs.h resource.h newdoc.h newclnt.h
!IF $(DEBUG)
        @$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_D) /FoTCFILE.obj TCFILE.CPP
<<
!ELSE
        @$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_R) /FoTCFILE.obj TCFILE.CPP
<<
!ENDIF

TCFILE.sbr : TCFILE.CPP testclnt.h defs.h resource.h newdoc.h newclnt.h
!IF $(DEBUG)
        @$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_D) /FRTCFILE.sbr TCFILE.CPP
<<
!ELSE
        @$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_R) /FRTCFILE.sbr TCFILE.CPP
<<
!ENDIF

TCOBJECT.obj : TCOBJECT.CPP resource.h testclnt.h defs.h newdoc.h newclnt.h
!IF $(DEBUG)
        @$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_D) /FoTCOBJECT.obj TCOBJECT.CPP
<<
!ELSE
        @$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_R) /FoTCOBJECT.obj TCOBJECT.CPP
<<
!ENDIF

TCOBJECT.sbr : TCOBJECT.CPP resource.h testclnt.h defs.h newdoc.h newclnt.h
!IF $(DEBUG)
        @$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_D) /FRTCOBJECT.sbr TCOBJECT.CPP
<<
!ELSE
        @$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_R) /FRTCOBJECT.sbr TCOBJECT.CPP
<<
!ENDIF

TESTCLNT.obj : TESTCLNT.CPP testclnt.h resource.h defs.h newdoc.h newclnt.h
!IF $(DEBUG)
        @$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_D) /FoTESTCLNT.obj TESTCLNT.CPP
<<
!ELSE
        @$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_R) /FoTESTCLNT.obj TESTCLNT.CPP
<<
!ENDIF

TESTCLNT.sbr : TESTCLNT.CPP testclnt.h resource.h defs.h newdoc.h newclnt.h
!IF $(DEBUG)
        @$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_D) /FRTESTCLNT.sbr TESTCLNT.CPP
<<
!ELSE
        @$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_R) /FRTESTCLNT.sbr TESTCLNT.CPP
<<
!ENDIF

TESTS.obj : TESTS.CPP testclnt.h resource.h defs.h newdoc.h newclnt.h
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

TESTS.sbr : TESTS.CPP testclnt.h resource.h defs.h newdoc.h newclnt.h
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

TESTCLNT.res : TESTCLNT.RC resource.h testclnt.ico
        $(RC) $(RCFLAGS1) /r /fo TESTCLNT.res TESTCLNT.RC


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
