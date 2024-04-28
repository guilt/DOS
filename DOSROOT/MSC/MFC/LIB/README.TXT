==========================================================================
                 MICROSOFT FOUNDATION CLASSES : LIBRARIES
==========================================================================

This directory contains the following MFC library variants:

SAFXCWD.LIB  -- Small model,  Windows,    debug
SAFXCW.LIB   -- Small model,  Windows,    retail
MAFXCWD.LIB  -- Medium model, Windows,    debug
MAFXCW.LIB   -- Medium model, Windows,    retail
MAFXCRD.LIB  -- Medium model, DOS (real), debug
MAFXCR.LIB   -- Medium model, DOS (real), retail
LAFXDWD.LIB  -- Large model,  Windows,    debug, DLL support

These library variants are the minimum set needed to link all
MFC sample applications.

Please note that the debug library variants were built with default
CodeView information to save diskette space.  This means that only
the WinMain, memory diagnostics, and main message pump source files
may be traced into.  If you need to trace into all MFC library code
you should rebuild the library with CODEVIEW=1.

See the file ..\SRC\README.TXT for specific instructions on how
to build MFC library variants.

When you build an MFC library in the ..\SRC directory, the
resulting static library (.LIB) file is placed in this directory.
Your LIB environment variable should contain this directory so that
subsequent invocations of LINK may access the libraries contained
here.  For example:

    set LIB=C:\C700\MFC\LIB;C:\C700\LIB;C:\MYDEV\LIB
