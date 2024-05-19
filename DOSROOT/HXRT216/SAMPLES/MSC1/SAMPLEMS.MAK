
# nmake makefile to create SampleMS.EXE with MS Visual C. Enter
#   nmake /f samplems.mak
# or, for a binary with debug info, enter:
#   nmake /f samplems.mak debug=1

# the binary is in DOS PE format, the Win32 emulation is linked statically.
# This allows to use the original MSC RTL code in DOS.

NAME=SAMPLE

MODS=..\..\Lib\InitW32.obj 
# some versions of MS VC will additionally need the GETMODH.obj module
#MODS=..\..\Lib\InitW32.obj ..\..\Lib\GETMODH.obj 

LIBS=..\..\Lib\dkrnl32s.lib ..\..\Lib\imphlp.lib libc.lib
LOPTS= /MAP /NODEFAULTLIB /SUBSYSTEM:CONSOLE /STUB:..\..\bin\loadpe.bin /FIXED:NO $(LOPTD) /OUT:$*.EXE /OPT:NOWIN98
LINKOPTS=$(LOPTS) $(MODS) $*.obj $(LIBS)
LINK=link.exe
COPTD=-Ox

CC=cl -c -Fo$* -D_MD $(COPTD)

$(NAME)MS.EXE: $*.obj $*.mak
    $(LINK) @<<
$(LINKOPTS)
<<
	..\..\Bin\PatchPE.EXE $*.exe

$(NAME)MS.obj: $(NAME).c $*.mak
    $(CC) $(NAME).c

