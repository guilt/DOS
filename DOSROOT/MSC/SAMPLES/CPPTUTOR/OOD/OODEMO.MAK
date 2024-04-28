ORIGIN = PWB
ORIGIN_VER = 2.0
PROJ = oodemo
PROJFILE = oodemo.mak
DEBUG = 0

BSCMAKE  = bscmake
SBRPACK  = sbrpack
NMAKEBSC1  = set
NMAKEBSC2  = nmake
CC  = cl
CFLAGS_G  = /W2 /BATCH /FR$*.sbr
CFLAGS_D  = /f /Zi /Od
CFLAGS_R  = /f- /Ot /Oi /Ol /Oe /Og /Gs
CXX  = cl
CXXFLAGS_G  = /W3 /BATCH /FR$*.sbr
CXXFLAGS_D  = /f /Od /Zi
CXXFLAGS_R  = /f- /Ot /Ol /Og /Oe /Oi /Gs
MAPFILE_D  = NUL
MAPFILE_R  = NUL
LFLAGS_G  = /NOI /BATCH /ONERROR:NOEXE
LFLAGS_D  = /CO /FAR /PACKC
LFLAGS_R  = /EXE /FAR /PACKC
LINKER	= link
ILINK  = ilink
LRF  = echo > NUL
ILFLAGS  = /a /e
BRFLAGS  =  /o $(PROJ).bsc
BROWSE	= 1
PACK_SBRS  = 1

FILES  = PRIM.CPP MISC.CPP EVENT.CPP LIST.CPP INTERACT.CPP TEXTWIN.CPP\
	LIFEWIN.CPP WINMGR.CPP OODEMO.CPP
OBJS  = PRIM.obj MISC.obj EVENT.obj LIST.obj INTERACT.obj TEXTWIN.obj\
	LIFEWIN.obj WINMGR.obj OODEMO.obj
SBRS  = PRIM.sbr MISC.sbr EVENT.sbr LIST.sbr INTERACT.sbr TEXTWIN.sbr\
	LIFEWIN.sbr WINMGR.sbr OODEMO.sbr

all: $(PROJ).exe

.SUFFIXES:
.SUFFIXES:
.SUFFIXES: .sbr .obj .cpp

PRIM.obj : PRIM.CPP prim.h
!IF $(DEBUG)
	@$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_D) /FoPRIM.obj PRIM.CPP
<<
!ELSE
	@$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_R) /FoPRIM.obj PRIM.CPP
<<
!ENDIF

PRIM.sbr : PRIM.CPP prim.h
!IF $(DEBUG)
	@$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_D) /FRPRIM.sbr PRIM.CPP
<<
!ELSE
	@$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_R) /FRPRIM.sbr PRIM.CPP
<<
!ENDIF

MISC.obj : MISC.CPP misc.h prim.h
!IF $(DEBUG)
	@$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_D) /FoMISC.obj MISC.CPP
<<
!ELSE
	@$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_R) /FoMISC.obj MISC.CPP
<<
!ENDIF

MISC.sbr : MISC.CPP misc.h prim.h
!IF $(DEBUG)
	@$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_D) /FRMISC.sbr MISC.CPP
<<
!ELSE
	@$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_R) /FRMISC.sbr MISC.CPP
<<
!ENDIF

EVENT.obj : EVENT.CPP event.h misc.h prim.h
!IF $(DEBUG)
	@$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_D) /FoEVENT.obj EVENT.CPP
<<
!ELSE
	@$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_R) /FoEVENT.obj EVENT.CPP
<<
!ENDIF

EVENT.sbr : EVENT.CPP event.h misc.h prim.h
!IF $(DEBUG)
	@$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_D) /FREVENT.sbr EVENT.CPP
<<
!ELSE
	@$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_R) /FREVENT.sbr EVENT.CPP
<<
!ENDIF

LIST.obj : LIST.CPP list.h
!IF $(DEBUG)
	@$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_D) /FoLIST.obj LIST.CPP
<<
!ELSE
	@$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_R) /FoLIST.obj LIST.CPP
<<
!ENDIF

LIST.sbr : LIST.CPP list.h
!IF $(DEBUG)
	@$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_D) /FRLIST.sbr LIST.CPP
<<
!ELSE
	@$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_R) /FRLIST.sbr LIST.CPP
<<
!ENDIF

INTERACT.obj : INTERACT.CPP interact.h list.h event.h misc.h prim.h
!IF $(DEBUG)
	@$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_D) /FoINTERACT.obj INTERACT.CPP
<<
!ELSE
	@$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_R) /FoINTERACT.obj INTERACT.CPP
<<
!ENDIF

INTERACT.sbr : INTERACT.CPP interact.h list.h event.h misc.h prim.h
!IF $(DEBUG)
	@$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_D) /FRINTERACT.sbr INTERACT.CPP
<<
!ELSE
	@$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_R) /FRINTERACT.sbr INTERACT.CPP
<<
!ENDIF

TEXTWIN.obj : TEXTWIN.CPP textwin.h interact.h list.h event.h misc.h prim.h
!IF $(DEBUG)
	@$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_D) /FoTEXTWIN.obj TEXTWIN.CPP
<<
!ELSE
	@$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_R) /FoTEXTWIN.obj TEXTWIN.CPP
<<
!ENDIF

TEXTWIN.sbr : TEXTWIN.CPP textwin.h interact.h list.h event.h misc.h prim.h
!IF $(DEBUG)
	@$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_D) /FRTEXTWIN.sbr TEXTWIN.CPP
<<
!ELSE
	@$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_R) /FRTEXTWIN.sbr TEXTWIN.CPP
<<
!ENDIF

LIFEWIN.obj : LIFEWIN.CPP lifewin.h textwin.h interact.h list.h event.h misc.h\
	prim.h
!IF $(DEBUG)
	@$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_D) /FoLIFEWIN.obj LIFEWIN.CPP
<<
!ELSE
	@$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_R) /FoLIFEWIN.obj LIFEWIN.CPP
<<
!ENDIF

LIFEWIN.sbr : LIFEWIN.CPP lifewin.h textwin.h interact.h list.h event.h misc.h\
	prim.h
!IF $(DEBUG)
	@$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_D) /FRLIFEWIN.sbr LIFEWIN.CPP
<<
!ELSE
	@$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_R) /FRLIFEWIN.sbr LIFEWIN.CPP
<<
!ENDIF

WINMGR.obj : WINMGR.CPP winmgr.h interact.h list.h event.h misc.h prim.h
!IF $(DEBUG)
	@$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_D) /FoWINMGR.obj WINMGR.CPP
<<
!ELSE
	@$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_R) /FoWINMGR.obj WINMGR.CPP
<<
!ENDIF

WINMGR.sbr : WINMGR.CPP winmgr.h interact.h list.h event.h misc.h prim.h
!IF $(DEBUG)
	@$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_D) /FRWINMGR.sbr WINMGR.CPP
<<
!ELSE
	@$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_R) /FRWINMGR.sbr WINMGR.CPP
<<
!ENDIF

OODEMO.obj : OODEMO.CPP winmgr.h textwin.h lifewin.h interact.h list.h event.h\
	misc.h prim.h
!IF $(DEBUG)
	@$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_D) /FoOODEMO.obj OODEMO.CPP
<<
!ELSE
	@$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_R) /FoOODEMO.obj OODEMO.CPP
<<
!ENDIF

OODEMO.sbr : OODEMO.CPP winmgr.h textwin.h lifewin.h interact.h list.h event.h\
	misc.h prim.h
!IF $(DEBUG)
	@$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_D) /FROODEMO.sbr OODEMO.CPP
<<
!ELSE
	@$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_R) /FROODEMO.sbr OODEMO.CPP
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


run: $(PROJ).exe
	$(PROJ).exe $(RUNFLAGS)

debug: $(PROJ).exe
	CV $(CVFLAGS) $(PROJ).exe $(RUNFLAGS)
