ORIGIN = PWB
ORIGIN_VER = 2.0
PROJ = chart
PROJFILE = chart.mak
DEBUG = 0

BROWSE  = 0
PACK_SBRS  = 1
CC  = cl
CFLAGS_G  = /W2 /GA /GEf /Zp /BATCH /DWINVER=0x0300
CFLAGS_D  = /f /Zi /Od /Gs
CFLAGS_R  = /f- /Oe /Og /Os /Gs
CXX  = cl
CXXFLAGS_G  = /AM /W3 /G2 /GA /DWINVER=0x0300 /Yuchart.h /GEs /Zp /BATCH
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
PCHSRC_CXX  = chart.cpp

FILES  = CHART.CPP CHARTDLG.CPP CHARTWND.CPP CHFILE.CPP DOBJECT.CPP CHART.DEF\
        CHART.RC
DEF_FILE  = CHART.DEF
OBJS  = CHART.obj CHARTDLG.obj CHARTWND.obj CHFILE.obj DOBJECT.obj
RESS  = CHART.res
SBRS  = CHART.sbr CHARTDLG.sbr CHARTWND.sbr CHFILE.sbr DOBJECT.sbr

all: $(PROJ).exe

.SUFFIXES:
.SUFFIXES:
.SUFFIXES: .sbr .obj .res .cpp .rc

CHART.obj : CHART.CPP chart.h resource.h dobject.h chartwnd.h chartdlg.h
!IF $(DEBUG)
        @$(CXX) @<<$(PROJ).rsp
/Ycchart.h /c $(CXXFLAGS_G)
$(CXXFLAGS_D) /FoCHART.obj CHART.CPP
<<
!ELSE
        @$(CXX) @<<$(PROJ).rsp
/Ycchart.h /c $(CXXFLAGS_G)
$(CXXFLAGS_R) /FoCHART.obj CHART.CPP
<<
!ENDIF

CHART.sbr : CHART.CPP chart.h resource.h dobject.h chartwnd.h chartdlg.h
!IF $(DEBUG)
        @$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_D) /FRCHART.sbr CHART.CPP
<<
!ELSE
        @$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_R) /FRCHART.sbr CHART.CPP
<<
!ENDIF

CHARTDLG.obj : CHARTDLG.CPP chart.h resource.h dobject.h chartwnd.h chartdlg.h
!IF $(DEBUG)
        @$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_D) /FoCHARTDLG.obj CHARTDLG.CPP
<<
!ELSE
        @$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_R) /FoCHARTDLG.obj CHARTDLG.CPP
<<
!ENDIF

CHARTDLG.sbr : CHARTDLG.CPP chart.h resource.h dobject.h chartwnd.h chartdlg.h
!IF $(DEBUG)
        @$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_D) /FRCHARTDLG.sbr CHARTDLG.CPP
<<
!ELSE
        @$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_R) /FRCHARTDLG.sbr CHARTDLG.CPP
<<
!ENDIF

CHARTWND.obj : CHARTWND.CPP chart.h resource.h dobject.h chartwnd.h chartdlg.h
!IF $(DEBUG)
        @$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_D) /FoCHARTWND.obj CHARTWND.CPP
<<
!ELSE
        @$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_R) /FoCHARTWND.obj CHARTWND.CPP
<<
!ENDIF

CHARTWND.sbr : CHARTWND.CPP chart.h resource.h dobject.h chartwnd.h chartdlg.h
!IF $(DEBUG)
        @$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_D) /FRCHARTWND.sbr CHARTWND.CPP
<<
!ELSE
        @$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_R) /FRCHARTWND.sbr CHARTWND.CPP
<<
!ENDIF

CHFILE.obj : CHFILE.CPP chart.h resource.h dobject.h chartwnd.h chartdlg.h
!IF $(DEBUG)
        @$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_D) /FoCHFILE.obj CHFILE.CPP
<<
!ELSE
        @$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_R) /FoCHFILE.obj CHFILE.CPP
<<
!ENDIF

CHFILE.sbr : CHFILE.CPP chart.h resource.h dobject.h chartwnd.h chartdlg.h
!IF $(DEBUG)
        @$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_D) /FRCHFILE.sbr CHFILE.CPP
<<
!ELSE
        @$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_R) /FRCHFILE.sbr CHFILE.CPP
<<
!ENDIF

DOBJECT.obj : DOBJECT.CPP chart.h resource.h dobject.h chartwnd.h chartdlg.h
!IF $(DEBUG)
        @$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_D) /FoDOBJECT.obj DOBJECT.CPP
<<
!ELSE
        @$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_R) /FoDOBJECT.obj DOBJECT.CPP
<<
!ENDIF

DOBJECT.sbr : DOBJECT.CPP chart.h resource.h dobject.h chartwnd.h chartdlg.h
!IF $(DEBUG)
        @$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_D) /FRDOBJECT.sbr DOBJECT.CPP
<<
!ELSE
        @$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_R) /FRDOBJECT.sbr DOBJECT.CPP
<<
!ENDIF

CHART.res : CHART.RC resource.h CHART.ICO about.dlg entry.dlg
        $(RC) $(RCFLAGS1) /r /fo CHART.res CHART.RC


$(PROJ).bsc : $(SBRS)
        $(BSCMAKE) @<<
$(BRFLAGS) $(SBRS)
<<

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
        $(RC) $(RCFLAGS2) $(RESS) $@


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

.rc.res :
        $(RC) $(RCFLAGS1) /r /fo $@ $<


run: $(PROJ).exe
        WX $(WXFLAGS) $(PROJ).exe $(RUNFLAGS)

debug: $(PROJ).exe
        WX /p $(WXFLAGS) CVW $(CVFLAGS) $(PROJ).exe $(RUNFLAGS)
