
# creates a Win32 PE binary (HX) using Open Watcom
# to add debugging info enter "wmake /f SAMPLEW.MAK DEBUG=1"

!ifndef DEBUG
DEBUG=0
!endif

!if $(DEBUG)
COPTD=-d2
LOPTD=debug dwarf
!else
COPTD=-s
LOPTD=
!endif

NAME=SAMPLE

$(NAME)W.EXE: $(NAME)W.OBJ
    wlink system hxnt $(LOPTD) file $(NAME)W.OBJ name $(NAME)W.EXE op map
    
$(NAME)W.OBJ: $(NAME).C    
    wcc386 -mf -bt=nt $(COPTD) -fo=$(NAME)W.OBJ $(NAME).C
