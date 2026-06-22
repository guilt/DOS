ORIGIN = PWB
ORIGIN_VER = 2.0
PROJ = cmdbook
PROJFILE = cmdbook.mak
BUILDDIR = CHAR
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
LFLAGS_G  = /NOI /NOD /BATCH /ONERROR:NOEXE /STACK:8192
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

FILES  = CMDBOOK.CPP DATABASE.CPP PERSON.CPP
OBJS  = CHAR\CMDBOOK.obj CHAR\DATABASE.obj CHAR\PERSON.obj

all: CHAR\$(PROJ).exe

.SUFFIXES:
.SUFFIXES:
.SUFFIXES: .obj .cpp

CHAR\CMDBOOK.obj : CMDBOOK.CPP database.h person.h
!IF $(DEBUG)
        @$(CXX) @<<CHAR\$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_D) /FoCHAR\CMDBOOK.obj CMDBOOK.CPP
<<
!ELSE
        @$(CXX) @<<CHAR\$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_R) /FoCHAR\CMDBOOK.obj CMDBOOK.CPP
<<
!ENDIF

CHAR\DATABASE.obj : DATABASE.CPP database.h person.h
!IF $(DEBUG)
        @$(CXX) @<<CHAR\$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_D) /FoCHAR\DATABASE.obj DATABASE.CPP
<<
!ELSE
        @$(CXX) @<<CHAR\$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_R) /FoCHAR\DATABASE.obj DATABASE.CPP
<<
!ENDIF

CHAR\PERSON.obj : PERSON.CPP person.h
!IF $(DEBUG)
        @$(CXX) @<<CHAR\$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_D) /FoCHAR\PERSON.obj PERSON.CPP
<<
!ELSE
        @$(CXX) @<<CHAR\$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_R) /FoCHAR\PERSON.obj PERSON.CPP
<<
!ENDIF


CHAR\$(PROJ).exe : $(OBJS)
!IF $(DEBUG)
        $(LRF) @<<CHAR\$(PROJ).lrf
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
        $(LRF) @<<CHAR\$(PROJ).lrf
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
        $(LINKER) @CHAR\$(PROJ).lrf


.cpp.obj :
!IF $(DEBUG)
        @$(CXX) @<<CHAR\$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_D) /Fo$@ $<
<<
!ELSE
        @$(CXX) @<<CHAR\$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_R) /Fo$@ $<
<<
!ENDIF


run: CHAR\$(PROJ).exe
        CHAR\$(PROJ).exe $(RUNFLAGS)

debug: CHAR\$(PROJ).exe
        CV $(CVFLAGS) CHAR\$(PROJ).exe $(RUNFLAGS)
