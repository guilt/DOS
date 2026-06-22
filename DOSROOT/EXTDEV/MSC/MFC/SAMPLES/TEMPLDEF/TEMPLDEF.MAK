ORIGIN = PWB
ORIGIN_VER = 2.0
PROJ = templdef
PROJFILE = templdef.mak
DEBUG = 0

CC  = cl
CFLAGS_G  = /W2 /BATCH
CFLAGS_D  = /f /Zi /Od
CFLAGS_R  = /f- /Ot /Oi /Ol /Oe /Og /Gs
CXX  = cl
CXXFLAGS_G  = /AM /W3 /D_DOS /BATCH
CXXFLAGS_D  = /f /Od /Zi /D_DEBUG
CXXFLAGS_R  = /f- /Os /Ol /Og /Oe /Gs
MAPFILE_D  = NUL
MAPFILE_R  = NUL
LFLAGS_G  = /NOI /NOD /BATCH /ONERROR:NOEXE
LFLAGS_D  = /CO /FAR /PACKC
LFLAGS_R  = /EXE /FAR /PACKC
LINKER  = link
ILINK  = ilink
LRF  = echo > NUL
ILFLAGS  = /a /e
LLIBS_R  = MAFXCR MLIBCE
LLIBS_D  = MAFXCRD MLIBCE
BROWSE  = 0
PACK_SBRS  = 1

FILES  = TEMPLDEF.CPP
OBJS  = TEMPLDEF.obj

all: $(PROJ).exe

.SUFFIXES:
.SUFFIXES:
.SUFFIXES: .obj .cpp

TEMPLDEF.obj : TEMPLDEF.CPP
!IF $(DEBUG)
        @$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_D) /FoTEMPLDEF.obj TEMPLDEF.CPP
<<
!ELSE
        @$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_R) /FoTEMPLDEF.obj TEMPLDEF.CPP
<<
!ENDIF


$(PROJ).exe : $(OBJS)
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


run: $(PROJ).exe
        $(PROJ).exe $(RUNFLAGS)

debug: $(PROJ).exe
        CV $(CVFLAGS) $(PROJ).exe $(RUNFLAGS)
