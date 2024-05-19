
 1. About

 This directory contains 32-bit samples. 

 To prepare Open Watcom to be used with HX please read OWSUPP\Readme.txt
 and follow the instructions to install HX's OW support for 32bit. 

 Please note that all makefiles supplied are in NMAKE format. Using 
 Borland's MAKE.EXE or Open Watcom's WMAKE.EXE may require some adjustments.

 The samples in MZ and NE format should be regarded as obsolete. The PE file
 format has several advantages, and since the simplified PE loader stub
 LOADPE.BIN is available, even the "size argument" won't count anymore.


 2. Sample Description 

 a). PE File Format Samples

  Name      Language  Comment
  ----------------------------------------------------------------------
  Masm1     MASM      hello world app (DOS).
                      - SampleM.mak, JWasm/Masm
                      - SampleP.mak, PoAsm
                      - SampleW.mak, Wasm

  Masm2     MASM      hello world app (Win32 API).
                      - SampleM.mak, JWasm/Masm (Win32)
                      - SampleMS.mak, JWasm/Masm (DOS, Win32 linked statically)
                      - SampleP.mak, PoAsm (Win32)
                      - SampleW.mak, Wasm (Win32)
                      - SampleWS.mak, Wasm (DOS, Win32 linked statically)

  Masm3     MASM      Memory allocation test (Win32 API).
                      - SampleM.mak (JWasm/Masm, Win32)
                      - SampleMS.mak (JWasm/Masm, DOS, Win32 linked statically)
                      
  Nasm      NASM      Simple hello world for NASM. Uses DOS API. 

  Fasm      FASM      SampleD  (DOS)
                      SampleW  (Win32 console)
                      SampleWS (DOS, Win32 linked statically)
                      
  LZAsm     LZAsm     a "hello, world" for LZAsm. Uses Win32 console API.

  GAS       GAS       hello world app. Uses Win32 console API.
                      - Sample.mak:  uses AS + LD

  MSC1      C         simple hello world sample. Use these makefiles 
                      to create:
                      - SampleM.mak for MSC (Win32)
                      - SampleMS.mak for MSC (DOS, Win32 linked statically)
                      - SampleP.mak for PellesC (Win32)

  MSC2      C         thread sample for MSC.
                      - ThreadW.mak for MSC (Win32)
                      - ThreadWS.mak for MSC (DOS, Win32 linked statically)
  
  OW1       C         simple hello world sample for Open Watcom.
                      - SampleD.mak (DOS, "system hxdos")
                      - SampleW.mak (Win32, "system hxnt")
                      - SampleWS.mak (DOS, "system hxnts")

  OW2       C         memory allocation test for OW.
                      - SampleD.mak (DOS, "system hxdos")
                      - SampleW.mak (Win32, "system nt")

  OW3       C         spawn() test for OW.
                      - SampleD.mak (DOS, "system hxdos")
                      - SampleW.mak (Win32, "system nt")
                      
  OW4       C         thread sample for OW.
                      - SampleW.mak (Win32, "system nt")
                      - SampleWS.mak (DOS, "system hxnts")
                      
  CC386     C         simple hello world sample for LADSoft CC386. Use 
                      these makefiles:
                      - Sample.mak (Win32)
                      - SampleD.mak (DOS)
                      - SampleWS.mak (DOS, Win32 linked statically)
  
  Djgpp     C         A sample showing how to make HX PE binaries with DJGPP.

  Pascal1   Pascal    a "hello, world" in Pascal. Makefiles:
                      - dcc1.mak for Delphi (Win32)
                      - fpc1.mak for FreePascal (Win32)
                      - ppro1.mak for Pascal Pro (DOS)
                      - vpc1.mak for Virtual Pascal (Win32)

  Pascal2   Pascal    a sample using Win32 API in Pascal. Makefiles:
                      - dcc2.mak for Delphi
                      - fpc2.mak for FreePascal

  PBasic    BASIC     Powerbasic sample. Uses Win32 console API. 
                      Thanks to Steve Hutchesson (Hutch)!

  MFCobol   COBOL     a simple hello world in MicroFocus Object Cobol.
                      Uses Win32 console API.  To be built with MFCobol.mak.
                      Will only work with cobol runtime dll MFRTS32.DLL.
                      Binary is not included.

  Vesa1     MASM      a simple app using VESA graphics mode with linear frame
                      buffer (LFB). Uses DOS API. May not work in NT/2K/XP DOS
                      boxes. Makefile for JWasm/Masm is included.

  Vesa2     MASM      another app using VESA graphics mode with linear frame
                      buffer (LFB). It has been converted from a DirectDraw 
                      sample written by X-Calibre. Uses DOS API. ALT-X will
                      terminate. Makefile for JWasm/Masm is included. The
                      sample may not work in NT/2K/XP DOS boxes.

  Vesa3     C++       a sample using VESA32.DLL. Use vesa3.mak to build it.
                      May not work in NT/2K/XP DOS boxes.

  Plasma32  MASM      this is pretty much like sample vesa2.asm, but this 
                      time written as a DirectDraw app. Such apps may run
                      in DOS with the help of DDDRAW.DLL, a DirectDraw
                      emulation dll. This is a benefit compared to native 
                      VESA apps, which may not run on NT platforms, at least
                      if they use LFB. To successfully assemble this sample
                      you will need a full set of Win32 include files. These
                      may be downloaded from 
                      http://www.japheth.de/Download/Win32inc.zip.

  Plasma08  MASM      this is pretty much like sample plasma32.asm, but uses
                      8-bit palette colors only. Should demonstrate that
                      emulation of IDirectDrawPalette works.
                      To successfully assemble this sample you will need a
                      full set of Win32 include files. These may be downloaded
                      from http://www.japheth.de/Download/Win32inc.zip.

  Dynload   MASM      a sample demonstrating how to use the loader API to
                      load a dll, get a function's address and at last free
                      the dll. Uses DOS API.

  ShowBmp   C++       A DirectDraw sample. It will display bitmap files in
                      fullscreen mode.

  TextOut   C++       A DirectDraw sample. It will display a text in
                      fullscreen mode.

  Thread    MASM      A sample showing threads in HX. Makefile for 
                      JWasm/Masm is included.

  TsrSmple  MASM      makes a DPMI TSR program, which will hook keyboard
                      interrupt and display a small rectangle on the upper
                      right corner of the screen on every keypress. Very
                      simple and cannot be removed from memory once it is
                      installed. Makefile for JWasm/Masm is included.


 b). MZ File Format Samples

  Name      Language  Comment
  ----------------------------------------------------------------------
  Hello     MASM      Hello world app. Use 
                      - helloMZ.mak to create binary hellomz.exe (Masm/
                        JWasm) in MZ file format. For creating a stand-alone
                        MZ binary read the comments in helloMZ.mak
                      - helloNE.mak to create the binary hellone.exe (Masm/
                        JWasm) in NE file format.
                      - helloW.mak to create binary hellow.exe (Wasm)

  Fasm      FASM      SampleMZ: DOS sample in MZ format.

