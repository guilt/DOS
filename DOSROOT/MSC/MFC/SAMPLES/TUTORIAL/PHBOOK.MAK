ORIGIN = PWB
ORIGIN_VER = 2.0
PROJ = phbook
PROJFILE = phbook.mak
BUILDDIR = WIN
DEBUG = 0

BROWSE  = 0
PACK_SBRS  = 1
CC  = cl
CFLAGS_G  = /W2 /GA /GEf /Zp /BATCH /DWINVER=0x0300
CFLAGS_D  = /f /Zi /Od /Gs
CFLAGS_R  = /f- /Oe /Og /Os /Gs
CXX  = cl
CXXFLAGS_G  = /AM /W3 /G2 /GA /DWINVER=0x0300 /GEs /Zp /BATCH
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
LINKER  = link
ILINK  = ilink
LRF  = echo > NUL
ILFLAGS  = /a /e
RC  = rc
RCFLAGS2  = /k /t /30
LLIBS_R  = MAFXCW /NOD:MLIBCE MLIBCEW
LLIBS_D  = MAFXCWD /NOD:MLIBCE MLIBCEW

FILES  = PHBOOK.DEF PHBOOK.RC DATABASE.CPP VIEW.CPP PERSON.CPP
DEF_FILE  = PHBOOK.DEF
OBJS  = WIN\DATABASE.obj WIN\VIEW.obj WIN\PERSON.obj
RESS  = WIN\PHBOOK.res
SBRS  = WIN\DATABASE.sbr WIN\VIEW.sbr WIN\PERSON.sbr

all: WIN\$(PROJ).exe

.SUFFIXES:
.SUFFIXES:
.SUFFIXES: .sbr .obj .res .cpp .rc

WIN\PHBOOK.res : PHBOOK.RC resource.h phbook.ico phbook.dlg
        $(RC) $(RCFLAGS1) /r /fo WIN\PHBOOK.res PHBOOK.RC

WIN\DATABASE.obj : DATABASE.CPP database.h person.h
!IF $(DEBUG)
        @$(CXX) @<<WIN\$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_D) /FoWIN\DATABASE.obj DATABASE.CPP
<<
!ELSE
        @$(CXX) @<<WIN\$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_R) /FoWIN\DATABASE.obj DATABASE.CPP
<<
!ENDIF

WIN\DATABASE.sbr : DATABASE.CPP database.h person.h
!IF $(DEBUG)
        @$(CXX) @<<WIN\$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_D) /FRWIN\DATABASE.sbr DATABASE.CPP
<<
!ELSE
        @$(CXX) @<<WIN\$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_R) /FRWIN\DATABASE.sbr DATABASE.CPP
<<
!ENDIF

WIN\VIEW.obj : VIEW.CPP resource.h database.h view.h person.h
!IF $(DEBUG)
        @$(CXX) @<<WIN\$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_D) /FoWIN\VIEW.obj VIEW.CPP
<<
!ELSE
        @$(CXX) @<<WIN\$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_R) /FoWIN\VIEW.obj VIEW.CPP
<<
!ENDIF

WIN\VIEW.sbr : VIEW.CPP resource.h database.h view.h person.h
!IF $(DEBUG)
        @$(CXX) @<<WIN\$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_D) /FRWIN\VIEW.sbr VIEW.CPP
<<
!ELSE
        @$(CXX) @<<WIN\$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_R) /FRWIN\VIEW.sbr VIEW.CPP
<<
!ENDIF

WIN\PERSON.obj : PERSON.CPP person.h
!IF $(DEBUG)
        @$(CXX) @<<WIN\$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_D) /FoWIN\PERSON.obj PERSON.CPP
<<
!ELSE
        @$(CXX) @<<WIN\$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_R) /FoWIN\PERSON.obj PERSON.CPP
<<
!ENDIF

WIN\PERSON.sbr : PERSON.CPP person.h
!IF $(DEBUG)
        @$(CXX) @<<WIN\$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_D) /FRWIN\PERSON.sbr PERSON.CPP
<<
!ELSE
        @$(CXX) @<<WIN\$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_R) /FRWIN\PERSON.sbr PERSON.CPP
<<
!ENDIF


WIN\$(PROJ).bsc : $(SBRS)
        $(BSCMAKE) @<<
$(BRFLAGS) $(SBRS)
<<

WIN\$(PROJ).exe : $(DEF_FILE) $(OBJS) $(RESS)
!IF $(DEBUG)
        $(LRF) @<<WIN\$(PROJ).lrf
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
        $(LRF) @<<WIN\$(PROJ).lrf
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
        $(LINKER) @WIN\$(PROJ).lrf
        $(RC) $(RCFLAGS2) $(RESS) $@


.cpp.sbr :
!IF $(DEBUG)
        @$(CXX) @<<WIN\$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_D) /FR$@ $<
<<
!ELSE
        @$(CXX) @<<WIN\$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_R) /FR$@ $<
<<
!ENDIF

.cpp.obj :
!IF $(DEBUG)
        @$(CXX) @<<WIN\$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_D) /Fo$@ $<
<<
!ELSE
        @$(CXX) @<<WIN\$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_R) /Fo$@ $<
<<
!ENDIF

.rc.res :
        $(RC) $(RCFLAGS1) /r /fo $@ $<


run: WIN\$(PROJ).exe
        WX $(WXFLAGS) WIN\$(PROJ).exe $(RUNFLAGS)

debug: WIN\$(PROJ).exe
        WX /p $(WXFLAGS) CVW $(CVFLAGS) WIN\$(PROJ).exe $(RUNFLAGS)
