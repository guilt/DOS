ORIGIN = PWB
ORIGIN_VER = 2.0
PROJ = oclient
PROJFILE = oclient.mak
DEBUG = 0

BROWSE  = 0
PACK_SBRS  = 1
CC  = cl
CFLAGS_G  = /W2 /GA /GEf /Zp /BATCH /DWINVER=0x0300
CFLAGS_D  = /f /Zi /Od /Gs
CFLAGS_R  = /f- /Oe /Og /Os /Gs
CXX  = cl
CXXFLAGS_G  = /AM /W3 /G2 /GA /DWINVER=0x0300 /Yuoclient.h /GEs /Zp /BATCH
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
PCHSRC_CXX  = fileio.cpp

FILES  = FILEIO.CPP ITEMWND.CPP MAINWND.CPP OCLIENT.CPP OCLIENT.DEF OCLIENT.RC
DEF_FILE  = OCLIENT.DEF
OBJS  = FILEIO.obj ITEMWND.obj MAINWND.obj OCLIENT.obj
RESS  = OCLIENT.res
SBRS  = FILEIO.sbr ITEMWND.sbr MAINWND.sbr OCLIENT.sbr

all: $(PROJ).exe

.SUFFIXES:
.SUFFIXES:
.SUFFIXES: .sbr .obj .res .cpp .rc

FILEIO.obj : FILEIO.CPP oclient.h mainwnd.h itemwnd.h resource.h
!IF $(DEBUG)
        @$(CXX) @<<$(PROJ).rsp
/Ycoclient.h /c $(CXXFLAGS_G)
$(CXXFLAGS_D) /FoFILEIO.obj FILEIO.CPP
<<
!ELSE
        @$(CXX) @<<$(PROJ).rsp
/Ycoclient.h /c $(CXXFLAGS_G)
$(CXXFLAGS_R) /FoFILEIO.obj FILEIO.CPP
<<
!ENDIF

FILEIO.sbr : FILEIO.CPP oclient.h mainwnd.h itemwnd.h resource.h
!IF $(DEBUG)
        @$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_D) /FRFILEIO.sbr FILEIO.CPP
<<
!ELSE
        @$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_R) /FRFILEIO.sbr FILEIO.CPP
<<
!ENDIF

ITEMWND.obj : ITEMWND.CPP oclient.h mainwnd.h itemwnd.h resource.h
!IF $(DEBUG)
        @$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_D) /FoITEMWND.obj ITEMWND.CPP
<<
!ELSE
        @$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_R) /FoITEMWND.obj ITEMWND.CPP
<<
!ENDIF

ITEMWND.sbr : ITEMWND.CPP oclient.h mainwnd.h itemwnd.h resource.h
!IF $(DEBUG)
        @$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_D) /FRITEMWND.sbr ITEMWND.CPP
<<
!ELSE
        @$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_R) /FRITEMWND.sbr ITEMWND.CPP
<<
!ENDIF

MAINWND.obj : MAINWND.CPP oclient.h mainwnd.h itemwnd.h resource.h
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

MAINWND.sbr : MAINWND.CPP oclient.h mainwnd.h itemwnd.h resource.h
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

OCLIENT.obj : OCLIENT.CPP oclient.h mainwnd.h resource.h
!IF $(DEBUG)
        @$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_D) /FoOCLIENT.obj OCLIENT.CPP
<<
!ELSE
        @$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_R) /FoOCLIENT.obj OCLIENT.CPP
<<
!ENDIF

OCLIENT.sbr : OCLIENT.CPP oclient.h mainwnd.h resource.h
!IF $(DEBUG)
        @$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_D) /FROCLIENT.sbr OCLIENT.CPP
<<
!ELSE
        @$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_R) /FROCLIENT.sbr OCLIENT.CPP
<<
!ENDIF

OCLIENT.res : OCLIENT.RC resource.h oclient.ico
        $(RC) $(RCFLAGS1) /r /fo OCLIENT.res OCLIENT.RC


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
