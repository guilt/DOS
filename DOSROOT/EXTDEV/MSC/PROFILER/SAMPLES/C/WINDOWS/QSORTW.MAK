ORIGIN = PWB
ORIGIN_VER = 2.0.861
PROJ = QSORTW
PROJFILE = QSORTW.MAK
DEBUG = 1

PBTDEPEND  = $(PROJ).exe
PREP  = prep
PROFILE  = profile
PLIST  = plist
PROFSET  = set
PROFNMAKE  = nmake
CC  = cl
CFLAGS_G  = /W2 /GA /GEf /Zp /BATCH
CFLAGS_D  = /Zi /Od /Gs
CFLAGS_R  = /Oe /Og /Os /Gs
CXX  = cl
CXXFLAGS_G  = /W2 /GA /GEf /Zp /BATCH
CXXFLAGS_D  = /Zi /Od /Gs
CXXFLAGS_R  = /Oe /Og /Os /Gs
FOR  = fl
FORFLAGS_R  = /Ot /Ol /Gs
FORFLAGS_D  = /Zi /Od /4Yb
ASM  = ml
AFLAGS_G  = /Cx /W2 /WX
AFLAGS_D  = /Zi
AFLAGS_R  = /nologo
MAPFILE_D  = NUL
MAPFILE_R  = NUL
LFLAGS_G  = /BATCH /ONERROR:NOEXE
LFLAGS_D  = /CO /NOF
LFLAGS_R  = /NOF
LLIBS_G  = LIBW.LIB
LINKER  = link
ILINK  = ilink
LRF  = echo > NUL
ILFLAGS  = /a /e
RC  = rc
LLIBS_R  = /NOD:SLIBCE SLIBCEW
LLIBS_D  = /NOD:SLIBCE SLIBCEW
PROFBY  = 4
PROFTYPE  = 22
PROFSAMPCNT  = 1000
PROFACCUM  = FALSE
PROFREPORT  = 54

FILES  = QSORTW.DEF QSORTW.C QSORTW.RC
DEF_FILE  = QSORTW.DEF
OBJS  = QSORTW.obj
RESS  = QSORTW.res

all: $(PROJ).exe $(PROJ).pbt

.SUFFIXES:
.SUFFIXES:
.SUFFIXES: .obj .res .c .rc

QSORTW.obj : QSORTW.C
!IF $(DEBUG)
        $(CC) /c $(CFLAGS_G) $(CFLAGS_D) /FoQSORTW.obj QSORTW.C
!ELSE
        $(CC) /c $(CFLAGS_G) $(CFLAGS_R) /FoQSORTW.obj QSORTW.C
!ENDIF

QSORTW.res : QSORTW.RC
        $(RC) $(RCFLAGS) /r /fo QSORTW.res QSORTW.RC


$(PROJ).pbt : 
        $(PROFSET) MAKEFLAGS=
        $(PROFNMAKE) $(NMFLAGS) -f $(PROJFILE) $(PBTDEPEND)
        $(PREP) /P $(PBTDEPEND) /OT $(PROJ).pbt

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
        $(RC) $(RESS) $@


.c.obj :
!IF $(DEBUG)
        $(CC) /c $(CFLAGS_G) $(CFLAGS_D) /Fo$@ $<
!ELSE
        $(CC) /c $(CFLAGS_G) $(CFLAGS_R) /Fo$@ $<
!ENDIF

.rc.res :
        $(RC) $(RCFLAGS) /r /fo $@ $<


run: $(PROJ).exe
        WX $(WXFLAGS) $(PROJ).exe $(RUNFLAGS)

debug: $(PROJ).exe
        WX $(WXFLAGS) CVW $(CVFLAGS) $(PROJ).exe $(RUNFLAGS)
