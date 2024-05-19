
# nmake makefile, will compile Sample.C with LadSoft CC386, enter:
#   nmake /f sample.mak

# the -STB parameter below may need to be adjusted, because 
# VALX versions below 3.3.1.12 will accept absolute paths only.

# the result will be a Win32 binary. With CC386 it is also
# possible to create a flat DOS binary (see SampleD.mak) or a
# DOS binary with HX's Win32 emulation linked statically (see SampleWS.mak).

NAME=SAMPLE

LIBS=clwin.lib climp.lib
CCDIR=\cc386

#LOPTS= -map -nci -con -pe -32 -fa:512 -STB:(c:\div\dpmist32.bin) /L:(\cc386\lib) $(LOPTD)
LOPTS= -map -nci -con -pe -32 -fa:0x200 -oa:0x1000 -STB:(..\..\bin\dpmist32.bin) /L:($(CCDIR)\lib) $(LOPTD)
LINKOPTS=$(LOPTS) c0xwin.obj $*.obj, $*.exe, $*.map, $(LIBS);
LINK=valx.exe

CC=cc386 /c /D_MD /o$*

$(NAME)C.EXE: $*.obj $*.mak
    $(LINK) @<<
$(LINKOPTS)
<<

$(NAME)C.obj: $(NAME).c $*.mak
    $(CC) $(NAME).c

