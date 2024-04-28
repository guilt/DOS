PROJ = QSORT
PROJFILE = QSORT.MAK
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
FOR  = fl
FORFLAGS_G  = /W2
FORFLAGS_R  = /Ot /Ol /Gs
FORFLAGS_D  = /Od /Zi /D/4Yb
MAPFILE_D  = NUL
MAPFILE_R  = NUL
LFLAGS_G  =  /NOI  /BATCH
LFLAGS_D  =  /CO /FAR /PACKC /PACKD  /PMTYPE:VIO
LFLAGS_R  = /EXE /FAR /PACKC /PACKD /PMTYPE:VIO
LINKER  = link
ILINK  = ilink
LRF  = echo > NUL
LLIBS_R  =  /NOD:LLIBFOR7 LLIBF7P
LLIBS_D  =  /NOD:LLIBFOR7 LLIBF7P
PROFBY  = 4
PROFTYPE  = 22
PROFSAMPCNT  = 1000
PROFACCUM  = FALSE
PROFREPORT  = 54

OBJS  = QSORT.obj
SBRS  = QSORT.sbr

all: $(PROJ).exe $(PROJ).pbt

.SUFFIXES:
.SUFFIXES: .obj .sbr .for

QSORT.obj : QSORT.FOR

QSORT.sbr : QSORT.FOR


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


.for.obj :
!IF $(DEBUG)
        $(FOR) /c $(FORFLAGS_G) $(FORFLAGS_D) /Fo$@ $<
!ELSE
        $(FOR) /c $(FORFLAGS_G) $(FORFLAGS_R) /Fo$@ $<
!ENDIF

.for.sbr :
!IF $(DEBUG)
        $(FOR) /Zs $(FORFLAGS_G) $(FORFLAGS_D) /FR$@ $<
!ELSE
        $(FOR) /Zs $(FORFLAGS_G) $(FORFLAGS_R) /FR$@ $<
!ENDIF


run: $(PROJ).exe
        $(PROJ).exe $(RUNFLAGS)

debug: $(PROJ).exe
        CVP $(CVFLAGS) $(PROJ).exe $(RUNFLAGS)
