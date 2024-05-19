
# create a stand-alone HX binary with Win32 linked statically.
#
# There's a problem with CC386's C RTL for Win32: it calls
# Win32 functions without the stdcall decorations, but HX's static
# Win32 modules HAS these decorations. VALX isn't smart enough
# to handle this situation. As a work-around, the LIBC32 supplied
# with HX is used.

# Since VALX also cannot handle libraries in COFF format, MS link is used
# instead (MS link accepts both COFF and OMF object modules as input).
# OW's WLINK is also an option, but the current release version (1.7)
# still has a bug which prevents it from using the HX Win32 emulation libs.

NAME=SAMPLEWS

$(NAME).exe: $(NAME).obj
    link @<<
/SUBSYSTEM:CONSOLE ..\..\Lib\InitW32.obj $(NAME).obj 
/stub:..\..\BIN\loadpe.bin
/OUT:$(NAME).EXE
/ENTRY:start
/MAP
..\..\Lib\libc32s.lib  ..\..\Lib\dkrnl32s.lib ..\..\Lib\imphlp.lib
/OPT:NOWIN98
/FIXED:NO
<<
    ..\..\Bin\patchpe $(NAME).exe

$(NAME).obj: sample.c
   cc386 /c /o$(NAME).obj sample.c
