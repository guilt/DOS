
# this is a Makefile for DJGPP's make, it won't work with nmake!

# Make a HX PE binary with DJGPP. Before running MAKE check file
# /hx/lib/djgpp.ld. This file contains full paths to the djgpp libraries 
# and most likely has to be adjusted.

MSLINK=1
DEBUG=0

NAME=hello
LIBPATH=../../Lib

ifeq ($(MSLINK),1)
ifeq ($(DEBUG),1)
LOPTD=/DEBUG /DEBUGTYPE:COFF
endif
LINK=link /nologo /subsystem:console /entry:start /out:$(NAME).exe /fixed:no /map:$(NAME).map $(LOPTD) /opt:nowin98
else
ifeq ($(DEBUG),1)
LOPTD=
endif
LINK=/msys/mingw/bin/ld -e start -o $(NAME).exe -pie -Map $(NAME).map $(LOPTD) 
endif

ifeq ($(DEBUG),1)
COPT=-gcoff
else
COPT=-O
endif

# Second link step uses a Win32 COFF linker (MS LINK or MinGW LD).
#
# Note 1: there are 5 stubs available: DPMIST32.BIN, DPMILD32.BIN, 
# LOADPE.BIN, LOADPEX.BIN, HDLD32.BIN. All can be used with Djgpp.
# Read the notes in HXDEV.TXT for details about the pros and cons
# of these stubs.
#
# Note 2: the .text section has to be made writeable since DJGPP places
# some variables into the code segment (irrelevant if LOADPE(X).BIN stub
# is used).
#
# Note 3: some Win32 COFF linkers (ALINK, WLINK) won't accept an optional
# header in an input module. Therefore they cannot be used here.

$(NAME).exe: $(NAME).bin
	$(LINK) $(NAME).bin
	../../Bin/pestub -q -n -w -x -s $(NAME).exe loadpe.bin

# First link step using DJGPP's LD. A modified startup file (crt0hx.o) and
# a special linker script file are used. The -r switch will tell LD to create
# a relocatable COFF object. With the -s switch, one will get rid of the
# .comment section.
#
# After LD tool LDFIX will run to make the COFF object Win32 compatible.
    
$(NAME).bin: $(NAME).o
	ld -T $(LIBPATH)/djgpp.ld -r -s -Map $(NAME)_.map $(NAME).o $(LIBPATH)/crt0hx.o -lc -lgcc -o $(NAME).bin 
	../../Bin/ldfix $(NAME).bin

$(NAME).o: $(NAME).c makefile
	gcc.exe -c $(COPT) -o $(NAME).o $(NAME).c


clean:
#	del $(NAME).exe
	del $(NAME).bin
	del $(NAME).o
	del $(NAME)*.map
