ORIGIN = PWB
ORIGIN_VER = 2.0
PROJ = ctrltest
PROJFILE = ctrltest.mak
DEBUG = 0

BSCMAKE  = bscmake
SBRPACK  = sbrpack
NMAKEBSC1  = set
NMAKEBSC2  = nmake
CC  = cl
CFLAGS_G  = /W2 /GA /GEf /Zp /BATCH
CFLAGS_D  = /f /Zi /Od /Gs
CFLAGS_R  = /f- /Oe /Og /Os /Gs
CXX  = cl
CXXFLAGS_G  = /AM /W3 /G2 /GA /Yuctrltest.h /GEs /Zp /BATCH
CXXFLAGS_D  = /f /Od /Zi /Gs /D_DEBUG
CXXFLAGS_R  = /f- /Os /Ol /Og /Oe /Gs
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
PCHSRC_CXX  = bbutton.cpp

FILES  = BBUTTON.CPP CTRLTEST.CPP CUSTLIST.CPP CUSTMENU.CPP DERPEN.CPP\
	DERTEST.CPP DLGPEN.CPP FEATPEN.CPP PAREDIT.CPP PAREDIT2.CPP SPIN.CPP\
	SPINTEST.CPP SUBTEST.CPP WCLSTEST.CPP CTRLTEST.RC CTRLTEST.DEF
DEF_FILE  = CTRLTEST.DEF
OBJS  = BBUTTON.obj CTRLTEST.obj CUSTLIST.obj CUSTMENU.obj DERPEN.obj\
	DERTEST.obj DLGPEN.obj FEATPEN.obj PAREDIT.obj PAREDIT2.obj SPIN.obj\
	SPINTEST.obj SUBTEST.obj WCLSTEST.obj
RESS  = CTRLTEST.res
SBRS  = BBUTTON.sbr CTRLTEST.sbr CUSTLIST.sbr CUSTMENU.sbr DERPEN.sbr\
	DERTEST.sbr DLGPEN.sbr FEATPEN.sbr PAREDIT.sbr PAREDIT2.sbr SPIN.sbr\
	SPINTEST.sbr SUBTEST.sbr WCLSTEST.sbr

all: $(PROJ).exe

.SUFFIXES:
.SUFFIXES:
.SUFFIXES: .sbr .obj .res .cpp .rc

BBUTTON.obj : BBUTTON.CPP ctrltest.h
!IF $(DEBUG)
	@$(CXX) @<<$(PROJ).rsp
/Ycctrltest.h /c $(CXXFLAGS_G)
$(CXXFLAGS_D) /FoBBUTTON.obj BBUTTON.CPP
<<
!ELSE
	@$(CXX) @<<$(PROJ).rsp
/Ycctrltest.h /c $(CXXFLAGS_G)
$(CXXFLAGS_R) /FoBBUTTON.obj BBUTTON.CPP
<<
!ENDIF

BBUTTON.sbr : BBUTTON.CPP ctrltest.h
!IF $(DEBUG)
	@$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_D) /FRBBUTTON.sbr BBUTTON.CPP
<<
!ELSE
	@$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_R) /FRBBUTTON.sbr BBUTTON.CPP
<<
!ENDIF

CTRLTEST.obj : CTRLTEST.CPP ctrltest.h
!IF $(DEBUG)
	@$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_D) /FoCTRLTEST.obj CTRLTEST.CPP
<<
!ELSE
	@$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_R) /FoCTRLTEST.obj CTRLTEST.CPP
<<
!ENDIF

CTRLTEST.sbr : CTRLTEST.CPP ctrltest.h
!IF $(DEBUG)
	@$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_D) /FRCTRLTEST.sbr CTRLTEST.CPP
<<
!ELSE
	@$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_R) /FRCTRLTEST.sbr CTRLTEST.CPP
<<
!ENDIF

CUSTLIST.obj : CUSTLIST.CPP ctrltest.h
!IF $(DEBUG)
	@$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_D) /FoCUSTLIST.obj CUSTLIST.CPP
<<
!ELSE
	@$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_R) /FoCUSTLIST.obj CUSTLIST.CPP
<<
!ENDIF

CUSTLIST.sbr : CUSTLIST.CPP ctrltest.h
!IF $(DEBUG)
	@$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_D) /FRCUSTLIST.sbr CUSTLIST.CPP
<<
!ELSE
	@$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_R) /FRCUSTLIST.sbr CUSTLIST.CPP
<<
!ENDIF

CUSTMENU.obj : CUSTMENU.CPP ctrltest.h
!IF $(DEBUG)
	@$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_D) /FoCUSTMENU.obj CUSTMENU.CPP
<<
!ELSE
	@$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_R) /FoCUSTMENU.obj CUSTMENU.CPP
<<
!ENDIF

CUSTMENU.sbr : CUSTMENU.CPP ctrltest.h
!IF $(DEBUG)
	@$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_D) /FRCUSTMENU.sbr CUSTMENU.CPP
<<
!ELSE
	@$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_R) /FRCUSTMENU.sbr CUSTMENU.CPP
<<
!ENDIF

DERPEN.obj : DERPEN.CPP ctrltest.h
!IF $(DEBUG)
	@$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_D) /FoDERPEN.obj DERPEN.CPP
<<
!ELSE
	@$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_R) /FoDERPEN.obj DERPEN.CPP
<<
!ENDIF

DERPEN.sbr : DERPEN.CPP ctrltest.h
!IF $(DEBUG)
	@$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_D) /FRDERPEN.sbr DERPEN.CPP
<<
!ELSE
	@$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_R) /FRDERPEN.sbr DERPEN.CPP
<<
!ENDIF

DERTEST.obj : DERTEST.CPP ctrltest.h paredit.h
!IF $(DEBUG)
	@$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_D) /FoDERTEST.obj DERTEST.CPP
<<
!ELSE
	@$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_R) /FoDERTEST.obj DERTEST.CPP
<<
!ENDIF

DERTEST.sbr : DERTEST.CPP ctrltest.h paredit.h
!IF $(DEBUG)
	@$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_D) /FRDERTEST.sbr DERTEST.CPP
<<
!ELSE
	@$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_R) /FRDERTEST.sbr DERTEST.CPP
<<
!ENDIF

DLGPEN.obj : DLGPEN.CPP ctrltest.h
!IF $(DEBUG)
	@$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_D) /FoDLGPEN.obj DLGPEN.CPP
<<
!ELSE
	@$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_R) /FoDLGPEN.obj DLGPEN.CPP
<<
!ENDIF

DLGPEN.sbr : DLGPEN.CPP ctrltest.h
!IF $(DEBUG)
	@$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_D) /FRDLGPEN.sbr DLGPEN.CPP
<<
!ELSE
	@$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_R) /FRDLGPEN.sbr DLGPEN.CPP
<<
!ENDIF

FEATPEN.obj : FEATPEN.CPP ctrltest.h
!IF $(DEBUG)
	@$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_D) /FoFEATPEN.obj FEATPEN.CPP
<<
!ELSE
	@$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_R) /FoFEATPEN.obj FEATPEN.CPP
<<
!ENDIF

FEATPEN.sbr : FEATPEN.CPP ctrltest.h
!IF $(DEBUG)
	@$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_D) /FRFEATPEN.sbr FEATPEN.CPP
<<
!ELSE
	@$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_R) /FRFEATPEN.sbr FEATPEN.CPP
<<
!ENDIF

PAREDIT.obj : PAREDIT.CPP ctrltest.h paredit.h
!IF $(DEBUG)
	@$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_D) /FoPAREDIT.obj PAREDIT.CPP
<<
!ELSE
	@$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_R) /FoPAREDIT.obj PAREDIT.CPP
<<
!ENDIF

PAREDIT.sbr : PAREDIT.CPP ctrltest.h paredit.h
!IF $(DEBUG)
	@$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_D) /FRPAREDIT.sbr PAREDIT.CPP
<<
!ELSE
	@$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_R) /FRPAREDIT.sbr PAREDIT.CPP
<<
!ENDIF

PAREDIT2.obj : PAREDIT2.CPP ctrltest.h paredit.h
!IF $(DEBUG)
	@$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_D) /FoPAREDIT2.obj PAREDIT2.CPP
<<
!ELSE
	@$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_R) /FoPAREDIT2.obj PAREDIT2.CPP
<<
!ENDIF

PAREDIT2.sbr : PAREDIT2.CPP ctrltest.h paredit.h
!IF $(DEBUG)
	@$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_D) /FRPAREDIT2.sbr PAREDIT2.CPP
<<
!ELSE
	@$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_R) /FRPAREDIT2.sbr PAREDIT2.CPP
<<
!ENDIF

SPIN.obj : SPIN.CPP ctrltest.h spin.h muscroll.h
!IF $(DEBUG)
	@$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_D) /FoSPIN.obj SPIN.CPP
<<
!ELSE
	@$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_R) /FoSPIN.obj SPIN.CPP
<<
!ENDIF

SPIN.sbr : SPIN.CPP ctrltest.h spin.h muscroll.h
!IF $(DEBUG)
	@$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_D) /FRSPIN.sbr SPIN.CPP
<<
!ELSE
	@$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_R) /FRSPIN.sbr SPIN.CPP
<<
!ENDIF

SPINTEST.obj : SPINTEST.CPP ctrltest.h paredit.h spin.h muscroll.h
!IF $(DEBUG)
	@$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_D) /FoSPINTEST.obj SPINTEST.CPP
<<
!ELSE
	@$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_R) /FoSPINTEST.obj SPINTEST.CPP
<<
!ENDIF

SPINTEST.sbr : SPINTEST.CPP ctrltest.h paredit.h spin.h muscroll.h
!IF $(DEBUG)
	@$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_D) /FRSPINTEST.sbr SPINTEST.CPP
<<
!ELSE
	@$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_R) /FRSPINTEST.sbr SPINTEST.CPP
<<
!ENDIF

SUBTEST.obj : SUBTEST.CPP ctrltest.h paredit.h
!IF $(DEBUG)
	@$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_D) /FoSUBTEST.obj SUBTEST.CPP
<<
!ELSE
	@$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_R) /FoSUBTEST.obj SUBTEST.CPP
<<
!ENDIF

SUBTEST.sbr : SUBTEST.CPP ctrltest.h paredit.h
!IF $(DEBUG)
	@$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_D) /FRSUBTEST.sbr SUBTEST.CPP
<<
!ELSE
	@$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_R) /FRSUBTEST.sbr SUBTEST.CPP
<<
!ENDIF

WCLSTEST.obj : WCLSTEST.CPP ctrltest.h paredit.h
!IF $(DEBUG)
	@$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_D) /FoWCLSTEST.obj WCLSTEST.CPP
<<
!ELSE
	@$(CXX) @<<$(PROJ).rsp
/c $(CXXFLAGS_G)
$(CXXFLAGS_R) /FoWCLSTEST.obj WCLSTEST.CPP
<<
!ENDIF

WCLSTEST.sbr : WCLSTEST.CPP ctrltest.h paredit.h
!IF $(DEBUG)
	@$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_D) /FRWCLSTEST.sbr WCLSTEST.CPP
<<
!ELSE
	@$(CXX) @<<$(PROJ).rsp
/Zs $(CXXFLAGS_G)
$(CXXFLAGS_R) /FRWCLSTEST.sbr WCLSTEST.CPP
<<
!ENDIF

CTRLTEST.res : CTRLTEST.RC ctrltest.h ctrltest.ico dertest.dlg wclstest.dlg\
	subtest.dlg dlgpen.dlg featpen.dlg bmtest1.dlg Image1U.bmp Image1D.bmp\
	Image1F.bmp Image2U.bmp Image2D.bmp Image2F.bmp bmtest2.dlg okU.bmp\
	okD.bmp okF.bmp cancelU.bmp cancelD.bmp cancelF.bmp custlist.dlg\
	spintest.dlg
	$(RC) $(RCFLAGS1) /r /fo CTRLTEST.res CTRLTEST.RC


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
