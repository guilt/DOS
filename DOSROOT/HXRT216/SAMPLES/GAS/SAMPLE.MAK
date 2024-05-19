
# NMAKE makefile to create helloa.exe
#     nmake /f sample.mak
# needs AS and LD (get them from FreeBasic for example)
#

GNUPATH=\FreeBasic\Bin\win32
LIBPATH=\FreeBasic\Lib\win32

SRCNAME = SAMPLE
NAME = SAMPLE
OUTDIR=.
LINK=$(GNUPATH)\LD
AS=$(GNUPATH)\AS

AOPT= -o $(OUTDIR)\$(NAME).O
LOPTS=-e_start -subsystem console -L$(LIBPATH)  -s -pie

$(OUTDIR)\$(NAME).EXE: $(OUTDIR)\$(NAME).O
    $(LINK) $(LOPTS) -o $(OUTDIR)\$(NAME).EXE $(OUTDIR)\$(NAME).O --library=kernel32
    ..\..\Bin\pestub -n -x -q $(OUTDIR)\$(NAME).EXE 

$(OUTDIR)\$(NAME).O: $(SRCNAME).asm $(NAME).mak
     $(AS) $(AOPT) $(SRCNAME).asm

