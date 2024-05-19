
# usage: nmake /f sample.mak
# creates a win32 console app using LZAsm + ALink
# please note: modify ALINKDIR to the directory where win32.lib resides

NAME=SAMPLE
AS=lzasm.exe
AOPT=
LINK=alink.exe
OUTDIR=.
ALINKDIR=c:\tools\alink

$(OUTDIR)\$(NAME).EXE: $*.obj $(NAME).mak
    $(LINK) -oPE -subsys con -stub ..\..\bin\dpmist32.bin -L $(ALINKDIR) $*.obj -o $*.EXE

$(OUTDIR)\$(NAME).OBJ: $(NAME).asm $(NAME).mak
    $(AS) $(AOPT) $(NAME).asm

