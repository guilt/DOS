#
# CNT.MAK - A simple non-PWB makefile for building
# the PWB tutorial example program COUNT.EXE .
#
# NOTE: The LIBS macro assumes the default library name.
#       If you have built the libraries with different
#       names, you must change the LIBS macro.
#

#
# Macros
#
CC      = cl
CFLAGS  = /Oc /f
LFLAGS  = /NOD:SLIBCE.LIB /NOE /NOI /EXE /FAR /PACKC
LINKER  = link
OBJS    = COUNT.OBJ COUNTBUF.OBJ COUNTCH.OBJ
STDOBJS = SETARGV.OBJ
LIBS    = SLIBCE

#
# The "all" target.
# Building 'all' builds COUNT.EXE.
#
all: COUNT.EXE

#
# The file suffixes NMAKE needs to "know" about
# for this project.
#
.SUFFIXES:
.SUFFIXES: .obj .c

#
# An inference rule to make an object file from a
# C source file.
#
.c.obj :
        $(CC) /c $(CFLAGS) /Fo$@ $<

#
# The description block for building COUNT.EXE
# from the object files and libraries.
#
COUNT.exe : $(OBJS)
    $(LINKER) $(LFLAGS) $(OBJS) $(STDOBJS),$@,,$(LIBS);

# The 'clean' target. Delete intermediate files
# that might be clutter after a release build
#
clean :
    -del *.obj
    -del *.mdt
    -del *.ilk
    -del *.sym
