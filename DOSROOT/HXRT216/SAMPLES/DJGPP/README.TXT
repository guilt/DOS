
  1. About

  This sample shows how DJGPP can be used to make a HX true flat PE
  binary.

  The resulting binary will use HDPMI instead of CWSDPMI as DPMI host.
  Also, since the binary is true flat now, there is no longer a problem
  with using dlls.


  2. Creating the binary
  
  While the compile step is similiar to the standard DJGPP method,
  linking has to be done differently. The differences are:
  
   - There are 2 link steps. The first step used DJGPP's LD to create
     a relocatable COFF object. For this step a modified linker script
     (DJGPP.LD) has to be used. Furthermore, the (GO32 specific) startup
     code (crt0.o) is replaced by (HX compatible) crt0hx.o.
   - the output of this step is to be processed by tool LDFIX due
     to some incompatibilities between DJGPP LD and Win32 PE COFF linkers.
   - after LDFIX a normal Win32 COFF linker will transform the COFF object
     to a PE binary.

  Please read file Makefile for additional information!


  3. Known problems
  
  - Label _end is the highest address of the .bss section, but does not
    include the communal variables, since these variables will be allocated
    by the second link step only.
    A - yet to be done - fix for LDFIX :) might resolve this issue.
    
  Japheth
