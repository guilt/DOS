
# nmake makefile, will compile Sample.C with PellesC, enter:
#   nmake /f samplep.mak
# or, for a binary with debug info, enter:
#   nmake /f samplep.mak debug=1

# please note: WD seems to not understand the output of polink,
# instead WLINK must be used to add debug info to the binary!

NAME=SAMPLE

LIBS=kernel32.lib

!ifdef DEBUG
COPTD=-Zi
LOPTS=system nt debug dwarf opt start=_mainCRTStartup opt map name $*.EXE  
LINKOPTS=$(LOPTS) file $*.obj library $(LIBS)
LINK=wlink.exe
!else
LOPTS= /MAP /SUBSYSTEM:CONSOLE /STUB:..\..\bin\dpmist32.bin /FIXED:NO $(LOPTD) /OUT:$*.EXE 
#LINKOPTS=$(LOPTS) $*.obj $(LIBS) /NODEFAULTLIB ..\..\Lib\libc32s.lib
LINKOPTS=$(LOPTS) $*.OBJ $(LIBS)
LINK=polink.exe
COPTD=-Ox
!endif

CC=pocc -Fo$*.obj -D_MD $(COPTD)

$(NAME)P.EXE: $*.obj $*.mak
    $(LINK) @<<
$(LINKOPTS)
<<

$(NAME)P.obj: $(NAME).c $*.mak
    $(CC) $(NAME).c

