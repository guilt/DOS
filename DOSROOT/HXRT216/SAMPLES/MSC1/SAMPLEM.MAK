
# nmake makefile, will compile Sample.C with MS Visual C, enter:
#   nmake /f samplem.mak
# or, for a binary with debug info, enter:
#   nmake /f samplem.mak debug=1

# please note: WD seems to not understand the output of MS COFF linker
# Instead WLINK must be used to add debug info to the binary!

NAME=SAMPLE

!ifdef DEBUG
COPTD=-Zd -Od
LOPTS=system nt debug dwarf opt start=_mainCRTStartup opt map name $*.EXE  
LIBS=kernel32.lib
LINKOPTS=$(LOPTS) file $*.obj library $(LIBS)
LINK=wlink.exe
!else
LIBS=..\..\Lib\dkrnl32.lib
LOPTS= /MAP /SUBSYSTEM:CONSOLE /STUB:..\..\bin\dpmist32.bin /FIXED:NO $(LOPTD) /OUT:$*.EXE /OPT:NOWIN98
LINKOPTS=$(LOPTS) $*.obj $(LIBS)
LINK=link.exe
COPTD=-Ox
!endif

CC=cl -c -Fo$* -D_MD $(COPTD)

$(NAME)M.EXE: $*.obj $*.mak
    $(LINK) @<<
$(LINKOPTS)
<<

$(NAME)M.obj: $(NAME).c $*.mak
    $(CC) $(NAME).c

