
# NMAKE makefile to create hellone.exe, a HX 32bit NE binary. Enter
#     nmake /f hellone.mak
# MS masm and link (OMF linker) are used.
# To create a binary with debug info included enter:
#     nmake /f hellone.mak debug=1
# Open Watcom's WD will then allow debugging on source level 
#
# - Borland's Tlink works as well, but requires to set MIXED3216
#   for CODE and DATA in the .DEF file
# - DigitalMars link complains about code and data being in one group!?
#   and it doesn't understand MIXED1632
#
!ifdef DEBUG
AOPTD=-Zi
LOPTD=/CO
!else
AOPTD=
LOPTD=
!endif

SRCNAME = hello
NAME =HELLONE 
OUTDIR=.
LINK=link16.exe
#LINK=tlink.exe
#LINK=d:\dm\bin\link.exe

AOPT= ml -c -Fo$* -I..\..\Include $(AOPTD)
LIBS=
LOPTS=/MAP:FULL/NOE/NON/A:16/NOPACKC/NOD/ONE:NOE $(LOPTD)
#LOPTS=-3 -Txe -m

$(OUTDIR)\$(NAME).EXE: $*.obj $(NAME).def
    $(LINK) $* ..\..\LIBOMF\neflat.obj,$*,$*,,$(NAME).def $(LOPTS)
    ..\..\bin\patchNE -32 $*.EXE

$(OUTDIR)\$(NAME).OBJ: $(SRCNAME).asm $(NAME).mak
     $(AOPT) $(SRCNAME).asm

