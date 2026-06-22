ORIGIN = PWB
ORIGIN_VER = 2.0
PROJ = tracer
PROJFILE = tracer.mak
DEBUG = 0

CC  = cl
CFLAGS_G  = /W2 /ASw /GD /Zp /BATCH /DWINVER=0x0300
CFLAGS_D  = /f /Zi /Od /Gs
CFLAGS_R  = /f- /Oe /Og /Os /Gs
CXX  = cl
CXXFLAGS_G  = /Alfw /W3 /G2 /GD /DWINVER=0x0300 /Zp /BATCH
CXXFLAGS_D  = /f /Od /Zi /Gs /D_DEBUG
CXXFLAGS_R  = /f- /Os /Og /Oe /Gs
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
IMPLIB  = implib
RCFLAGS2  = /30
LLIBS_R  = LAFXDW /NOD:LLIBCE LDLLCEW
LLIBS_D  = LAFXDWD /NOD:LLIBCE LDLLCEW

FILES  = TRACER.CPP TRACER.DEF TRACER.RC
DEF_FILE  = TRACER.DEF
OBJS  = TRACER.obj
RESS  = TRACER.res

all: $(PROJ).dll

.SUFFIXES:
.SUFFIXES:
.SUFFIXES: .obj .res .cpp .rc

TRACER.obj : TRACER.CPP traceapi.h
!IF $(DEBUG)
        @$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_D) /FoTRACER.obj TRACER.CPP
<<
!ELSE
        @$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_R) /FoTRACER.obj TRACER.CPP
<<
!ENDIF

TRACER.res : TRACER.RC
        $(RC) $(RCFLAGS1) /r /fo TRACER.res TRACER.RC


$(PROJ).dll : $(DEF_FILE) $(OBJS) $(RESS)
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
        $(IMPLIB) $*.lib $@


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


run: $(PROJ).dll
        

debug: $(PROJ).dll
        
