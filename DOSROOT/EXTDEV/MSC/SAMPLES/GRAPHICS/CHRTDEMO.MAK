ORIGIN = PWB
ORIGIN_VER = 2.0
PROJ = chrtdemo
PROJFILE = chrtdemo.mak
DEBUG = 0

BSCMAKE  = bscmake
SBRPACK  = sbrpack
NMAKEBSC1  = set
NMAKEBSC2  = nmake
CC  = cl
CFLAGS_G  = /W3 /BATCH /FR$*.sbr
CFLAGS_D  = /f /Od /Zi
CFLAGS_R  = /f- /Ot /Ol /Og /Oe /Oi /Gs
CXX  = cl
CXXFLAGS_G  = /W2 /BATCH /FR$*.sbr
CXXFLAGS_D  = /f /Zi /Od
CXXFLAGS_R  = /f- /Ot /Oi /Ol /Oe /Og /Gs
MAPFILE_D  = NUL
MAPFILE_R  = NUL
LFLAGS_G  = /NOI /BATCH /ONERROR:NOEXE
LFLAGS_D  = /CO /FAR /PACKC
LFLAGS_R  = /EXE /FAR /PACKC
LINKER	= link
ILINK  = ilink
LRF  = echo > NUL
ILFLAGS  = /a /e
LLIBS_G  = graphics pgchart
BRFLAGS  =  /o $(PROJ).bsc
BROWSE	= 1
PACK_SBRS  = 1

FILES  = CHRTDEMO.C CHRTOPT.C CHRTSUPT.C
OBJS  = CHRTDEMO.obj CHRTOPT.obj CHRTSUPT.obj
SBRS  = CHRTDEMO.sbr CHRTOPT.sbr CHRTSUPT.sbr

all: $(PROJ).exe

.SUFFIXES:
.SUFFIXES:
.SUFFIXES: .sbr .obj .c

CHRTDEMO.obj : CHRTDEMO.C chrtdemo.h
!IF $(DEBUG)
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_D) /FoCHRTDEMO.obj CHRTDEMO.C
<<
!ELSE
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_R) /FoCHRTDEMO.obj CHRTDEMO.C
<<
!ENDIF

CHRTDEMO.sbr : CHRTDEMO.C chrtdemo.h
!IF $(DEBUG)
	@$(CC) @<<$(PROJ).rsp
/Zs $(CFLAGS_G)
$(CFLAGS_D) /FRCHRTDEMO.sbr CHRTDEMO.C
<<
!ELSE
	@$(CC) @<<$(PROJ).rsp
/Zs $(CFLAGS_G)
$(CFLAGS_R) /FRCHRTDEMO.sbr CHRTDEMO.C
<<
!ENDIF

CHRTOPT.obj : CHRTOPT.C chrtdemo.h
!IF $(DEBUG)
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_D) /FoCHRTOPT.obj CHRTOPT.C
<<
!ELSE
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_R) /FoCHRTOPT.obj CHRTOPT.C
<<
!ENDIF

CHRTOPT.sbr : CHRTOPT.C chrtdemo.h
!IF $(DEBUG)
	@$(CC) @<<$(PROJ).rsp
/Zs $(CFLAGS_G)
$(CFLAGS_D) /FRCHRTOPT.sbr CHRTOPT.C
<<
!ELSE
	@$(CC) @<<$(PROJ).rsp
/Zs $(CFLAGS_G)
$(CFLAGS_R) /FRCHRTOPT.sbr CHRTOPT.C
<<
!ENDIF

CHRTSUPT.obj : CHRTSUPT.C chrtdemo.h
!IF $(DEBUG)
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_D) /FoCHRTSUPT.obj CHRTSUPT.C
<<
!ELSE
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_R) /FoCHRTSUPT.obj CHRTSUPT.C
<<
!ENDIF

CHRTSUPT.sbr : CHRTSUPT.C chrtdemo.h
!IF $(DEBUG)
	@$(CC) @<<$(PROJ).rsp
/Zs $(CFLAGS_G)
$(CFLAGS_D) /FRCHRTSUPT.sbr CHRTSUPT.C
<<
!ELSE
	@$(CC) @<<$(PROJ).rsp
/Zs $(CFLAGS_G)
$(CFLAGS_R) /FRCHRTSUPT.sbr CHRTSUPT.C
<<
!ENDIF


$(PROJ).bsc : $(SBRS)
	$(BSCMAKE) @<<
$(BRFLAGS) $(SBRS)
<<

$(PROJ).exe : $(OBJS)
	-$(NMAKEBSC1) MAKEFLAGS=
	-$(NMAKEBSC2) $(NMFLAGS) -f $(PROJFILE) $(PROJ).bsc
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


.c.sbr :
!IF $(DEBUG)
	@$(CC) @<<$(PROJ).rsp
/Zs $(CFLAGS_G)
$(CFLAGS_D) /FR$@ $<
<<
!ELSE
	@$(CC) @<<$(PROJ).rsp
/Zs $(CFLAGS_G)
$(CFLAGS_R) /FR$@ $<
<<
!ENDIF

.c.obj :
!IF $(DEBUG)
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_D) /Fo$@ $<
<<
!ELSE
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_R) /Fo$@ $<
<<
!ENDIF


run: $(PROJ).exe
	$(PROJ).exe $(RUNFLAGS)

debug: $(PROJ).exe
	CV $(CVFLAGS) $(PROJ).exe $(RUNFLAGS)
