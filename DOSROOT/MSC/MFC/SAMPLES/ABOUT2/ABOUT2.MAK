ORIGIN = PWB
ORIGIN_VER = 2.0
PROJ = ABOUT2
PROJFILE = ABOUT2.MAK
DEBUG = 0

BROWSE  = 0
PACK_SBRS  = 1
CC  = cl
CFLAGS_G  = /W2 /GA /GEf /Zp /BATCH /DWINVER=0x0300
CFLAGS_D  = /f /Zi /Od /Gs
CFLAGS_R  = /f- /Oe /Og /Os /Gs
CXX  = cl
CXXFLAGS_G  = /W3 /G2 /GA /DWINVER=0x0300 /GEs /Zp /BATCH
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
LINKER  = link
ILINK  = ilink
LRF  = echo > NUL
ILFLAGS  = /a /e
RC  = rc
RCFLAGS2  = /k /t /30
LLIBS_R  = SAFXCW /NOD:SLIBCE SLIBCEW
LLIBS_D  = SAFXCWD /NOD:SLIBCE SLIBCEW

FILES  = ABOUT2.CPP ABOUT2.RC ABOUT2.DEF
DEF_FILE  = ABOUT2.DEF
OBJS  = ABOUT2.obj
RESS  = ABOUT2.res
SBRS  = ABOUT2.sbr

all: $(PROJ).exe

.SUFFIXES:
.SUFFIXES:
.SUFFIXES: .sbr .obj .res .cpp .rc

ABOUT2.obj : ABOUT2.CPP resource.h about2.h
!IF $(DEBUG)
        @$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_D) /FoABOUT2.obj ABOUT2.CPP
<<
!ELSE
        @$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_R) /FoABOUT2.obj ABOUT2.CPP
<<
!ENDIF

ABOUT2.sbr : ABOUT2.CPP resource.h about2.h
!IF $(DEBUG)
        @$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_D) /FRABOUT2.sbr ABOUT2.CPP
<<
!ELSE
        @$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_R) /FRABOUT2.sbr ABOUT2.CPP
<<
!ENDIF

ABOUT2.res : ABOUT2.RC resource.h about2.ico about2.dlg
        $(RC) $(RCFLAGS1) /r /fo ABOUT2.res ABOUT2.RC


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
