      ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
      ³                                                               ³
      ³                      OptiVec for C / C++                      ³
      ³                                                               ³
      ³                     Shareware Version 2                       ³
      ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ


1. Introduction
---------------
Use vector functions instead of loops - if it matters to you how fast and
how accurate your data are processed!
The largest portion of almost all programs processing numerical data
consists of loops. Replace these loops by the specialized vector
and matrix functions of OptiVec, and exploit all the advantages of
vectorized programming:

- OptiVec was almost entirely written in Assembly language. The result is a
  highly optimized and numerically accurate code, running 2-3 times faster
  than compiled loops.

- fully vectorized forms of all operators and functions of the language
  C/C++ for all integer and floating-point (including complex!) data types

- Additionally many other real and complex math functions, statistics,
  analysis, FFT techniques, graphics - in total more than 3000!

- Simple and logical syntax, for example
  "VF_exp( Y, X, size );"      for Y[i] = exp( X[i] ) with "float" arrays,
  "VD_FFT( Y, X, size, 1 );"   for double-precision forward FFT
  "ME_mulM( MZ, MX, MY, htX, lenX, lenY );"
                               for extended-precision matrix multiplication

2. System requirements
----------------------
This version of OptiVec is designed for IBM AT, PS/2 or compatibles,
equipped at least with a 80386 CPU and a 80387 coprocessor
(Visual C++ version: at least 486DX).

Depending on your choice when ordering or downloading,
- either for Borland C++ (Turbo C++), version 3.0 or higher, memory
  models Win32, Windows-LARGE, or  DOS-LARGE
- or for Microsoft Visual C++, version 5.0 or higher, "single-thread debug"
  or "multi-thread debug"

Registered version for Borland C/C++:
all memory models; separate libraries optimized for all processors from
486DX/Pentium down to 286 with or without coprocessor.

Registered version for Microsoft Visual C++:
all PC models using the "single-thread", "multi-thread", or
"multi-thread DLL" run-time libraries, both for debug and release.

3. Installation
---------------
Please run the installation program INSTALL.EXE.
If you don't like the default directory structure, you may change it
afterwards.

After you completed the installation, you must set the library search path
and the include-file search path according to your OptiVec directory choice:
Add these paths to the standard settings in the menu
"Options/Project/Directories" of Borland C 4.x, 5.x, and BC++ Builder, or
"Options/Directories" in Borland C++ 3.x.
(Remember: a semicolon is used to separate entries in these fields.)

Special Turbo C 3.x version only:
   In order to avoid table-overflow errors of the TC 3.x linker, the libraries
   VCL3.LIB and MCL3.LIB were split up into 16 smaller libraries. Instead
   of including VCL3.LIB, you have to include VECLIB.LIB and those data-type
   specific libraries which you actually need:
   VF.LIB for VF_ functions,
   VD.LIB for VD_ functions,
   VCF.LIB for VCF_ functions, and so on.
   VI.LIB for VBI_, VSI_, VI_, and VLI_ functions
   VU.LIB for VUB_, VUS_, VU_, and VUL_ functions
   VQI.LIB for VQI_ functions
   MF.LIB for MF_ functions, and so on.


4. Running the examples
-----------------------

Check your installation by compiling and running the appropriate demo file.
Follow the instructions in the header of that file.
If you get compiler errors like "Cannot open include file ...", or a
linker error "Unresolved external", you probably did not set the library
and include paths correctly.

OptiVec for Borland C/C++:
  VDEMOB.BPR  is a BC++ Builder 4+ project,
  VDEMOW.CPP  is for Windows with Borland C++ 5.0 or higher.
  VDEMO.CPP   is a DOS program,
  Separate versions of the Windows demo program are supplied for
  older BC versions:
  VDEMOW1.CPP is for Borland C++ 3.x with OWL 1.0
  VDEMOW2.CPP is for Borland C++ 4.0 with OWL 2.0

  For BC++ Builder 4+, open the project VDEMOB.BPR, compile and run.

  For Windows95, 98 or NT with Borland C++ 4.x, 5.x or higher (without OWL),
      either do a command-line compile:
          a) 32-bit: type
               BCC32 -W -Iinclude vdemow.cpp lib\vcf3w.lib
          b) 16-bit: type
               BCC -ml -W -Iinclude vdemow.cpp lib\vcl3w.lib
      and run the program by typing:  vdemow

      or create a project containing
      VDEMOW.CPP and VCF3W.LIB.
      In the TargetExpert, choose as target
        Application [.EXE]  for Win32, GUI model.
        Tick the boxes for Standard Libraries ClassLibrary, and Runtime.
        Use Static linking and Single-Thread

  For Windows95, 98 or NT with Borland C++ 4.x and OWL 2.0
      create a project containing
      VDEMOW2.CPP and VCF3W.LIB.
      In the TargetExpert, choose as target
        Application [.EXE]  for Win32, GUI model.
        Tick the boxes for Standard Libraries OWL, ClassLibrary, and Runtime.
        Use Static linking and Single-Thread (which means: don't check the
        Multithread box).

  For 16-bit Windows with Borland C++ 4.x, 5.x or higher (without OWL)
      create a project containing
      VDEMOW.CPP and VCL3W.LIB.
      In the TargetExpert, choose as target
        Application [.EXE]  for Windows 3.x, model LARGE.
        Tick the boxes for Standard Libraries ClassLibrary, and Runtime.
        Use, as you prefer, either Dynamic or Static linking.

  For DOS, create a project containing
     VDEMO.CPP,  VCL3.LIB, and  GRAPHICS.LIB.
     Choose the application either as DOS Standard or as DOS Overlay.
     VCL3.LIB may or may not be used as an overlay (option to be set:
     "Project/Local Options/Overlay this module").
     Choose the memory  model LARGE.
     Check the floating-point options. Neither "No floating-point" nor
     "Floating-point emulation" should be selected.

  For 16-bit Windows with Borland C++ 3.x and OWL 1.0
      create a project containing
      VDEMOW1.CPP,  VCL3W.LIB, and OWL.DEF.
      Choose the application as Windows-EXE, model LARGE.
      Choose the memory model LARGE and 287 floating-point operations

  For 16-bit Windows with Borland C++ 4.x and OWL 2.0
      create a project containing
      VDEMOW2.CPP and VCL3W.LIB.
      In the TargetExpert, choose as target
        Application [.EXE]  for Windows 3.x, model LARGE.
        Tick the boxes for Standard Libraries OWL, ClassLibrary, and Runtime.
        Use, as you prefer, either Dynamic or Static linking.


OptiVec for Microsoft Visual C++:
    create a project as a "Win32 application", containing
    VDEMOW.CPP  and  OVVCSD.LIB.
    Choose single-thread debug.

Data-fitting functions demo:
    There is a demo file for the data-fitting functions, FITDEMO.CPP.
    You can use it with Borland C++ (4.x or higher) or Visual C++,
    under Windows 3.1 or Windows 95/98/NT.
    With BC++ Builder, you can alternatively open the project FITDEMOB.BPR.

    Follow the instructions given above for VDEMOW.CPP and VDEMOB.BPR.
    With 16-bit BC++, you must additionally include the library MCL3W.LIB.


5. Documentation
----------------
The full OptiVec documentation is to be found in the files
HANDBOOK.TXT, FUNCREF.TXT, MATRIX.TXT, and CMATH.TXT as ASCII text.
If you want to load the documentation into a word processor under Windows,
you must use the filter "ASCII text" or "DOS text".


6. Copyright
------------
The copyright owner of this product as a whole and of all its constituent
parts is
         Dr. Martin Sander Software Development
         Steinachstr. 9A
         D-69198 Schriesheim
         Germany
         e-mail: MartinSander@optivec.com

This Shareware version of OptiVec is freely distributable in unchanged form.
For the distribution of applications created using OptiVec, you need the
registered version. The detailed licence terms are described in chapter 1.2
of the file HANDBOOK.TXT.


7. Registered Version
---------------------
If you like OptiVec and decide to use it, please be fair and register.
The registered version

-  supports all memory models of Windows95, NT, 3.x, and DOS of Borland C++,
   or all PC debug and release targets of Visual C++, respectively.

-  has individually optimized libraries for each degree of processor
   backward-compatibility (Borland C++ only):
      486DX/Pentium+
      386+ (387 coprocessor required)
      286+ (no coprocessor required).

-  comes with printed documentation.

-  entitles you to two years of free updates
   (by downloading from our web site)

-  costs USD 199 for the commercial edition,
         USD  89 for the educational edition,
   and can be ordered by e-mail from the author or through the
   following secure-server Internet sites:

   Atlantic Coast's SoftShop:
   http://www.soft-shop.com/cgi-bin/order.html?136

   ShareIt:
   OptiVec for Borland C++:
      http://www.shareit.com/programs/101557.htm         (English handbook)
      http://www.shareit.com/deutsch/programs/101556.htm (German handbook)
   OptiVec for MSVC:
      http://www.shareit.com/programs/103421.htm

See chapter 1.3 of the file HANDBOOK.TXT for further details about
ordering.


    * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

Copyright (C) Martin Sander 1996-2000
