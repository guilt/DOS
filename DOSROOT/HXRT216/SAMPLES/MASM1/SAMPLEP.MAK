
# nmake makefile to build samplep.exe with PoASM + PoLink, enter
#   nmake /f samplep.mak
# for a binary with debug info enter:
#   nmake /f samplep.mak debug=1

!ifdef DEBUG
AOPTD=-Zi
LOPTD=/DEBUG
!else
AOPTD=
LOPTD=
!endif

NAME=Sample

AS=poasm.exe
ASMOPT= $(AOPTD) -Fo$*
LINK=polink.exe
LPARAM=$*.obj /NOLOGO /OUT:$*.exe /SUBSYSTEM:CONSOLE /STUB:..\..\bin\dpmist32.bin /FIXED:NO /HEAP:0 /STACK:0x1000 $(LOPTD)

# patchPE is used here to ensure app is executed as DPMI client

$(NAME)P.exe: $*.obj $*.mak
    $(LINK) @<<
$(LPARAM)
<<
    ..\..\Bin\patchPE $*.exe

$(NAME)P.obj: $(NAME).asm $*.mak
    $(AS) $(ASMOPT) $(NAME).asm

