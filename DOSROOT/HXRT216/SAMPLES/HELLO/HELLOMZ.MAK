
# NMAKE makefile to create hellomz.exe, a HX 32bit MZ binary. Enter
# enter: nmake /f hellomz.mak
# MS masm and MS OMF linker are used.
# for a binary with debug infos enter: nmake /f hellomz.mak debug=1
# Open Watcom's WD will then allow debugging on source level 

# to create a stand-alone binary, activate the second SAMOD line below
# which includes the alternate LOADSRVR.OBJ module. This module contains
# HDPMI32 and will increase the binary size by 34 kB.

LIBS=..\..\LIBOMF

!ifdef DEBUG
AOPTD=-Zi
LOPTD=/CO
MODD=$(LIBS)\dmymove.obj
!else
AOPTD=
LOPTD=
MODD=
!endif

# name of MS 16-bit OMF linker (has to be adjusted)
LINK=link16.exe

SAMOD=
#SAMOD=$(LIBS)\loadsrvr.obj

AOPT= -c -nologo -Fo$* $(AOPTD)
LOPT=/MAP:FULL/NOD/NOE/ONE:NOE $(LOPTD) 

HELLOMZ.EXE: hellomz.obj
    $(LINK) $(LOPT) $(LIBS)\jmppm32 $(SAMOD) $*.OBJ $(MODD),$*.EXE,,$(LIBS)\jmppm32.lib;

HELLOMZ.OBJ: hello.asm
    ml $(AOPT) hello.asm

