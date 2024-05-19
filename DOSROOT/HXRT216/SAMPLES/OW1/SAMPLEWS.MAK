
# creates a DOS PE binary (HX) using Open Watcom with Win32 emulation
# linked statically.
# to add debugging info enter "wmake /f SAMPLEWS.MAK DEBUG=1"

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

$(NAME)WS.EXE: $(NAME)WS.OBJ
    wlink system hxnts libpath ..\..\Lib $(LOPTD) file $(NAME)WS.OBJ name $(NAME)WS.EXE op map
    ..\..\Bin\patchPE $(NAME)WS.EXE
    
$(NAME)WS.OBJ: $(NAME).C    
    wcc386 -mf -bt=nt $(COPTD) -fo=$(NAME)WS.OBJ $(NAME).C
