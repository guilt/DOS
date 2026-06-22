PROJ = qsort
PROJFILE = qsort.mak
DEBUG = 1

PBTDEPEND  = $(PROJ).exe
PREP  = prep
PROFILE  = profile
PLIST  = plist
PROFSET  = set
PROFNMAKE  = nmake
PWBRMAKE  = pwbrmake
NMAKEBSC1  = set
NMAKEBSC2  = nmake
CC  = cl
CFLAGS_G  = /W2 /Zp /G2 /BATCH
CFLAGS_D  = /Gi$(PROJ).mdt /Zi /Od
CFLAGS_R  = /Ot /Oi /Ol /Oe /Og /Gs
ASM  = ml
AFLAGS_G  = /Cx /W2 /WX
AFLAGS_D  = /Zi
AFLAGS_R  = /nologo
MAPFILE_D  = NUL
MAPFILE_R  = NUL
LFLAGS_G  =   /BATCH
LFLAGS_D  =  /CO /FAR /PACKC
LFLAGS_R  = /EXE /FAR /PACKC
LINKER  = link
ILINK  = ilink
LRF  = echo > NUL
BC  = bc
BCFLAGS_R  = /Ot
BCFLAGS_D  = /D /Zi
BCFLAGS_G  = /O /FPi /G2 /Lp
PROFBY  = 4
PROFTYPE  = 22
PROFSAMPCNT  = 1000
PROFACCUM  = FALSE
PROFREPORT  = 54

OBJS  = QSORT.obj
SBRS  = QSORT.sbr

all: $(PROJ).exe $(PROJ).pbt

.SUFFIXES:
.SUFFIXES: .obj .sbr .bas

QSORT.obj : QSORT.BAS

QSORT.sbr : QSORT.BAS


$(PROJ).pbt : 
        $(PROFSET) MAKEFLAGS=
        $(PROFNMAKE) $(NMFLAGS) -f $(PROJFILE) $(PBTDEPEND)
        $(PREP) /P $(PBTDEPEND) /OT $(PROJ).pbt

$(PROJ).bsc : $(SBRS)
        $(PWBRMAKE) @<<
$(BRFLAGS) $(SBRS)
<<

$(PROJ).exe : $(OBJS)
!IF $(DEBUG)
        $(LRF) @<<$(PROJ).lrf
$(RT_OBJS: = +^
) $(OBJS: = +^
)
$@
$(MAPFILE_D)
$(LLIBS_G: = +^
) +
$(LLIBS_D: = +^
) +
$(LIBS: = +^
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
$(LLIBS_G: = +^
) +
$(LLIBS_R: = +^
) +
$(LIBS: = +^
)
$(DEF_FILE) $(LFLAGS_G) $(LFLAGS_R);
<<
!ENDIF
        $(LINKER) @$(PROJ).lrf


.bas.obj :
!IF $(DEBUG)
        $(BC) /Z $(BCFLAGS_G) $(BCFLAGS_D) $<, $@;
!ELSE
        $(BC) /Z $(BCFLAGS_G) $(BCFLAGS_R) $<, $@;
!ENDIF

.bas.sbr :
!IF $(DEBUG)
        $(BC) /Z $(BCFLAGS_G) $(BCFLAGS_D) $<, nul;
!ELSE
        $(BC) /Z $(BCFLAGS_G) $(BCFLAGS_R) $<, nul;
!ENDIF


run: $(PROJ).exe
        $(PROJ).exe $(RUNFLAGS)

debug: $(PROJ).exe
        CVP $(CVFLAGS) $(PROJ).exe $(RUNFLAGS)
