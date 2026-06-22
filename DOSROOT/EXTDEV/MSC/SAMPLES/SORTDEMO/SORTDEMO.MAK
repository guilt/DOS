ORIGIN = PWB
ORIGIN_VER = 2.0
PROJ = sortdemo
PROJFILE = sortdemo.mak
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
LLIBS_G  = graphics
BRFLAGS  =  /o $(PROJ).bsc
BROWSE	= 1
PACK_SBRS  = 1

FILES  = SORTDEMO.C
OBJS  = SORTDEMO.obj
SBRS  = SORTDEMO.sbr

all: $(PROJ).exe

.SUFFIXES:
.SUFFIXES:
.SUFFIXES: .sbr .obj .c

SORTDEMO.obj : SORTDEMO.C
!IF $(DEBUG)
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_D) /FoSORTDEMO.obj SORTDEMO.C
<<
!ELSE
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_R) /FoSORTDEMO.obj SORTDEMO.C
<<
!ENDIF

SORTDEMO.sbr : SORTDEMO.C
!IF $(DEBUG)
	@$(CC) @<<$(PROJ).rsp
/Zs $(CFLAGS_G)
$(CFLAGS_D) /FRSORTDEMO.sbr SORTDEMO.C
<<
!ELSE
	@$(CC) @<<$(PROJ).rsp
/Zs $(CFLAGS_G)
$(CFLAGS_R) /FRSORTDEMO.sbr SORTDEMO.C
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
