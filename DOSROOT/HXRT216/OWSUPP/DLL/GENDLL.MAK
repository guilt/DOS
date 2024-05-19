
# creates a Win32 dll with Open Watcom

GENDLL.DLL: GENDLL.OBJ GENDLL.MAK
    wlink system nt_dll option nostdcall, map file gendll.obj
    
GENDLL.OBJ: GENDLL.C    
    wcc386 -bd -s -zq GENDLL.C
