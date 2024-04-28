ORIGIN = PWB
ORIGIN_VER = 2.0
PROJ = multipad
PROJFILE = multipad.mak
DEBUG = 0

BROWSE  = 0
PACK_SBRS  = 1
CC  = cl
CFLAGS_G  = /W2 /GA /GEf /Zp /BATCH /DWINVER=0x0300
CFLAGS_D  = /f /Zi /Od /Gs
CFLAGS_R  = /f- /Oe /Og /Os /Gs
CXX  = cl
CXXFLAGS_G  = /AM /W3 /G2 /GA /DWINVER=0x0300 /Yumultipad.h /GEs /Zp /BATCH
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
PCHSRC_CXX  = bar.cpp

FILES  = BAR.CPP MPFILE.CPP MPFIND.CPP MPINIT.CPP MPMAIN.CPP MPPRINT.CPP\
        MULTIPAD.DEF MULTIPAD.RC
DEF_FILE  = MULTIPAD.DEF
OBJS  = BAR.obj MPFILE.obj MPFIND.obj MPINIT.obj MPMAIN.obj MPPRINT.obj
RESS  = MULTIPAD.res
SBRS  = BAR.sbr MPFILE.sbr MPFIND.sbr MPINIT.sbr MPMAIN.sbr MPPRINT.sbr

all: $(PROJ).exe

.SUFFIXES:
.SUFFIXES:
.SUFFIXES: .sbr .obj .res .cpp .rc

BAR.obj : BAR.CPP multipad.h bar.h resource.h menu.h
!IF $(DEBUG)
        @$(CXX) @<<$(PROJ).rsp
/Ycmultipad.h /c $(CXXFLAGS_G)
$(CXXFLAGS_D) /FoBAR.obj BAR.CPP
<<
!ELSE
        @$(CXX) @<<$(PROJ).rsp
/Ycmultipad.h /c $(CXXFLAGS_G)
$(CXXFLAGS_R) /FoBAR.obj BAR.CPP
<<
!ENDIF

BAR.sbr : BAR.CPP multipad.h bar.h resource.h menu.h
!IF $(DEBUG)
        @$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_D) /FRBAR.sbr BAR.CPP
<<
!ELSE
        @$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_R) /FRBAR.sbr BAR.CPP
<<
!ENDIF

MPFILE.obj : MPFILE.CPP multipad.h bar.h resource.h menu.h
!IF $(DEBUG)
        @$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_D) /FoMPFILE.obj MPFILE.CPP
<<
!ELSE
        @$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_R) /FoMPFILE.obj MPFILE.CPP
<<
!ENDIF

MPFILE.sbr : MPFILE.CPP multipad.h bar.h resource.h menu.h
!IF $(DEBUG)
        @$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_D) /FRMPFILE.sbr MPFILE.CPP
<<
!ELSE
        @$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_R) /FRMPFILE.sbr MPFILE.CPP
<<
!ENDIF

MPFIND.obj : MPFIND.CPP multipad.h bar.h resource.h menu.h
!IF $(DEBUG)
        @$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_D) /FoMPFIND.obj MPFIND.CPP
<<
!ELSE
        @$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_R) /FoMPFIND.obj MPFIND.CPP
<<
!ENDIF

MPFIND.sbr : MPFIND.CPP multipad.h bar.h resource.h menu.h
!IF $(DEBUG)
        @$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_D) /FRMPFIND.sbr MPFIND.CPP
<<
!ELSE
        @$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_R) /FRMPFIND.sbr MPFIND.CPP
<<
!ENDIF

MPINIT.obj : MPINIT.CPP multipad.h bar.h resource.h menu.h
!IF $(DEBUG)
        @$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_D) /FoMPINIT.obj MPINIT.CPP
<<
!ELSE
        @$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_R) /FoMPINIT.obj MPINIT.CPP
<<
!ENDIF

MPINIT.sbr : MPINIT.CPP multipad.h bar.h resource.h menu.h
!IF $(DEBUG)
        @$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_D) /FRMPINIT.sbr MPINIT.CPP
<<
!ELSE
        @$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_R) /FRMPINIT.sbr MPINIT.CPP
<<
!ENDIF

MPMAIN.obj : MPMAIN.CPP multipad.h bar.h resource.h menu.h
!IF $(DEBUG)
        @$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_D) /FoMPMAIN.obj MPMAIN.CPP
<<
!ELSE
        @$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_R) /FoMPMAIN.obj MPMAIN.CPP
<<
!ENDIF

MPMAIN.sbr : MPMAIN.CPP multipad.h bar.h resource.h menu.h
!IF $(DEBUG)
        @$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_D) /FRMPMAIN.sbr MPMAIN.CPP
<<
!ELSE
        @$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_R) /FRMPMAIN.sbr MPMAIN.CPP
<<
!ENDIF

MPPRINT.obj : MPPRINT.CPP multipad.h bar.h resource.h menu.h
!IF $(DEBUG)
        @$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_D) /FoMPPRINT.obj MPPRINT.CPP
<<
!ELSE
        @$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_R) /FoMPPRINT.obj MPPRINT.CPP
<<
!ENDIF

MPPRINT.sbr : MPPRINT.CPP multipad.h bar.h resource.h menu.h
!IF $(DEBUG)
        @$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_D) /FRMPPRINT.sbr MPPRINT.CPP
<<
!ELSE
        @$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_R) /FRMPPRINT.sbr MPPRINT.CPP
<<
!ENDIF

MULTIPAD.res : MULTIPAD.RC resource.h multipad.ico notepad.ico multipad.dlg\
        menu.h
        $(RC) $(RCFLAGS1) /r /fo MULTIPAD.res MULTIPAD.RC


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
