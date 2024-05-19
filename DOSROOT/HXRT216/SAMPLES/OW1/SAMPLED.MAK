
# creates a DOS PE binary ("system hxraw") using Open Watcom
# to add debugging info enter "wmake /f SAMPLED.MAK DEBUG=1"

!ifndef DEBUG
DEBUG=0
!endif

!if $(DEBUG)
COPTD=-d2
LOPTD=debug dwarf
!else
COPTD=-s
LOPTD=op map
!endif

NAME=SAMPLE

$(NAME)D.EXE: $(NAME)D.OBJ
    wlink system hxdos $(LOPTD) file $(NAME)D.OBJ name $(NAME)D.EXE
    ..\..\Bin\patchPE $(NAME)D.EXE
    
$(NAME)D.OBJ: $(NAME).C    
    wcc386 -mf -bt=nt $(COPTD) -fo=$(NAME)D.OBJ $(NAME).C
