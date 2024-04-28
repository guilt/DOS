========================================================================
      MICROSOFT FOUNDATION CLASS LIBRARY : EXAMPLE CODE
========================================================================

I. Introduction

This directory contains all of the Microsoft Foundation Class (MFC)
library example programs, which highlight many object-oriented
Windows programming techniques and class library features.  Each 
example is a complete and functional program that explores
different aspects of the library.

These programs are useful as learning tools, when used in conjunction
with the MFC reference documentation.  You can take the code provided
and experiment with it.  One group of sample programs, in the TUTORIAL
subdirectory, supplements the MFC Tutorial and should be studied in
conjunction with that document.

Each subdirectory has both PWB-compatible and NMAKE-compatible makefiles.
The PWB makefiles can be identified by the .MAK file extension.  NMAKE
makefiles are called 'makefile', with the exception of the TUTORIAL
subdirectory (the difference is explained in TUTORIAL\README.TXT).

-----------------------------------------------------------------------
If you do not have a required C runtime library, you will have to
re-run the C7 SETUP program, selecting the 'Build Additional Libraries'
option.

Windows libraries (such as LIBW.LIB and COMMDLG.LIB) are installed
by the Microsoft Windows Software Development Kit (SDK)SETUP program.

Windows DLLs (such as SHELL.DLL and MMSYSTEM.DLL) should already
be installed on Windows 3.1 hosts.  These DLLs are also provided by
the Windows 3.1 SDK.
-------------------------------------------------------------------------

II. Compiling sample programs with Microsoft NMAKE

To compile a sample program with NMAKE:

1. Ensure you have the appropriate C runtime and Foundation
runtime libraries.  The prerequisite libraries for each sample
application are listed in Section IV below.   All MFC library
variants necessary to build the samples are provided in binary
form in MFC\LIB.

NOTE: To save disk space, the DEBUG variants have been compiled
without full CodeView information.  By default, DEBUG variants are
compiled with only a few key source modules (startup, main message
pump, and memory diagnostics) compiled with CodeView information.
If you want to trace into all of the MFC libraries while debugging
a sample application, you will have to rebuild the appropriate debug
library variant with CODEVIEW=1 (full CodeView information).  See
MFC\SRC\README.TXT for more information.

NOTE: The MFC sample makefiles assume you are using the combined
C runtime libraries with emulator math support.

2. Ensure you have set up your LIB, INCLUDE, and PATH environment variables
appropriately.  For example:

   set LIB=C:\C700\MFC\LIB;C:\C700\LIB
   set INCLUDE=C:\C700\MFC\INCLUDE;C:\C700\INCLUDE
   set PATH=C:\C700\BIN;C:\WINDOWS;C:\DOS

Remember you must put the MFC\LIB and MFC\INCLUDE directories in
your LIB and INCLUDE paths, respectively, if you wish to compile
Foundation applications.

3. Change your working directory to the appropriate sample file 
directory and invoke NMAKE.  

In most cases, invoking NMAKE with no arguments will compile and 
link the retail version of that directory's sample application.  
If you wish to build the debug version, specify 'DEBUG=1' on the 
NMAKE command line.  If you want to remove object, compiled resource, 
and executable files, specify the 'clean' target.  For example:

  cd \c700\mfc\samples\about2
  nmake                       ' creates retail version of about2.exe
  nmake clean                 ' removes about2.exe/.obj/.res
  nmake DEBUG=0               ' creates retail version of about2.exe
  nmake clean                 ' removes about2.exe/.obj/.res
  nmake DEBUG=1               ' creates debug version of about2.exe

Object and resource files are created in the current directory.

Compilation procedures for the tutorial subdirectory are slightly
different than is documented here.  See MFC\SAMPLES\TUTORIAL\README.TXT
for more information.

NOTE: See technical note MFC\DOC\TN007.TXT for special information
on setting up your Windows environment to handle Foundation library
debugging output.

-----------------------------------------------------------------------

III. Compiling sample programs with Programmer's Workbench (PWB)

To compile a sample program with PWB:

1. Ensure you have the appropriate C runtime and Foundation
runtime libraries.  The prerequisite libraries for each sample
application are listed in Section IV below.   All MFC library
variants necessary to build the samples are provided in binary
form in MFC\LIB.

NOTE: To save disk space, the DEBUG variants have been compiled
without full CodeView information.  By default, DEBUG variants are
compiled with only a few key source modules (startup, main message
pump, and memory diagnostics) compiled with CodeView information.
If you want to trace into all of the MFC libraries while debugging
a sample application, you will have to rebuild the appropriate debug
library variant with CODEVIEW=1 (full CodeView information).  See
MFC\SRC\README.TXT for more information.

NOTE: The MFC sample makefiles assume you are using the combined
C runtime libraries with emulator math support.

2. Ensure you have set up your LIB, INCLUDE, and PATH environment variables
appropriately.  For example:

   set LIB=C:\C700\MFC\LIB;C:\C700\LIB
   set INCLUDE=C:\C700\MFC\INCLUDE;C:\C700\INCLUDE
   set PATH=C:\C700\BIN;C:\WINDOWS;C:\DOS

Remember you must put the MFC\LIB and MFC\INCLUDE directories in
your LIB and INCLUDE paths, respectively, if you wish to compile
Foundation applications.

You should normally set these variables before starting Windows or PWB.  If
necessary, you can change environment variables within PWB using the
Options/Environment Variables... dialog.

3. Start PWB.  Use the Project/Open Project... dialog to navigate
through the MFC\SAMPLES directory tree and locate and open the .MAK
file corresponding to the sample you wish to create.

4. Use the Options/Build Options... dialog to select whether you
wish to build a release or debug version of the program.  'Release'
versions use Foundation retail libraries; 'debug' use debug.

5. Select Project/Build: sample.EXE to start the build.

6. If the build completes with no errors, you can run the program.
Use the Run/Execute or Run/Debug menu selections to run Windows
or DOS programs from within PWB.  Note: this feature of PWB requires
that you have the WX Server installed and running.  See the Programmer's
WorkBench documentation for more information on WX Server.

You can always run a Windows app outside of PWB using the following
procedure:

(If running Windows) - switch (using Alt+Esc) from PWB to the Program
Manager.  Once there, use either File/Run or the File Manager to run
your application.  You can also try using CVW (if debugging) or 
set up an icon to run your program.

(If not running Windows) - start Windows in standard or 386-enhanced
mode, then start your application in one of the ways described in 
the preceding paragraph.

-----------------------------------------------------------------------

IV. Samples

Here is a list of the sample directories and an overview of their
content.  See below for more detailed explanations

	ABOUT2      simple dialog box example.
	CHART       a simple bar/line charting application.
	CTRLTEST    a control test driver showing custom controls.
	DLLTRACE    example of building a dynamic link library (DLL).
	FILEVIEW    a simple text file viewer.
	HELLO       basic application described in the MFC Tutorial.
	HELLOAPP    an extremely simple MFC application.
	MDI         demonstrates how to program to the MFC MDI interface.
	MINMDI      a bare-bones MDI application.
	MINSVR      a minimal OLE server application.
	MINSVRMI    a minimal OLE server application with multiple inheritance.
	MULTIPAD    an MDI NOTEPAD application.
	OCLIENT     an example of an Object Linking and Embedding (OLE) client.
	OSERVER     a simple OLE server application (called BIBREF)
	RESTOOL     a simple non-Windows tool for Windows resources.
	SHOWFONT    a font attribute viewer.
	SPEAKN      a spelling game that uses sound and pen input.
	TEMPLDEF    a non-Windows tool for expanding C++ templates.
	TESTCLNT    a simple OLE client used to test OLE server applications.
	TESTSERV    a simple OLE server used to test OLE client applications.
	TRACER      a Windows utility to view and set diagnostic trace options.
	TUTORIAL    source for tutorial examples.

-------------------------------------------------------------------------

ABOUT2\ABOUT2.EXE

This program is a re-implementation of the ABOUT program found in
Charles Petzold's book, "Programming Windows"; it has been written
using C++ and the Foundation classes.  ABOUT2 allows you to draw
either a rectangle or an ellipse in one of several colors in the
client area of a application main window.  The source code
illustrates the following concepts:

    - Simple Foundation application structuring.
    - Simple dialog box initialization and management.
    - Graphics Device Interface (GDI) wrapper classes.

This application requires: SLIBCEW.LIB (C Windows runtimes), LIBW.LIB
(Windows library), and either SAFXCW.LIB (MFC small model Windows 
retail) or SAFXCWD.LIB (MFC small model Windows debug).

-------------------------------------------------------------------------

CHART\CHART.EXE

This program implements a simple bar/line charting application.
You can enter a data set (list of integers), display the data in
bar or line chart form, print the chart, save the data to disk, 
and read in previously saved data.  The source code illustrates
the following concepts:

    - Dialog box management.
    - Document state management (dirty, clean).
    - Using GDI calls to draw a graph to a device context.
    - Using Foundation CFile and CArchive classes to save and
      restore user data.
    - Printing.

This application requires: MLIBCEW.LIB (C Windows runtimes), LIBW.LIB
(Windows library), either MAFXCW.LIB (MFC medium model Windows 
retail) or MAFXCWD.LIB (MFC medium model Windows debug), and
COMMDLG.DLL.

-------------------------------------------------------------------------

CTRLTEST\CTRLTEST.EXE

The main application (in DCONTROL.H, DCONTROL.CPP and DCONTROL.RC)
provides a simple frame window with a single menu to drive the tests.
This can be easily extended to drive additional tests.

All the examples are based off a the class CParsedEdit which
is derived from the standard Windows CEdit class.  CParsedEdit
provides a simple keyboard input filter to only allow numbers,
letters, control characters, combinations of the above or any
characters.

This sample also includes MUSCROLL.DLL, the "micro scrolling"
custom control provided in the Windows 3.1 SDK, as well as tests
for Pen Windows edit items (requires Windows for Pen).

The source code illustrates the following concepts:

	- example parsed edit control (CParsedEdit) derived from
		the standard Windows CEdit class.
	- bitmap buttons
	- owner draw/self draw controls
	- owner draw/self draw menus
	- using C++ to create controls for a dialog using Create
		member functions for the controls (not recommended,	
		DERTEST.CPP, DERTEST.DLG)
	- exporting custom controls and registering a new WndClass
		so the controls can be used by the dialog manager
		(the "PAREDIT" control class used in WCLSTEST.CPP
		and WCLSTEST.DLG).  These controls can be edited with the
		SDK dialog editor (DLGEDIT.EXE) as custom controls
		by typing in the class name "PAREDIT" and the
		hex representation of the PES_ styles.
	- using SubclassWindow/SubclassDlgItem to dynamically
		subclass a dialog control to add specialized behaviour
		(SUBTEST.CPP, SUBTEST.DLG).
	- example of an external control packed as a DLL (MUSCROLL.DLL)
		being used by C++ code with a special C++ wrapper class.
	- an example of a spin button using the external MUSCROLL.DLL.
	- examples of Windows for Pen special edit controls

	more advanced topics:
	- ON_CONTROL handler (in WCLSTEST.CPP responding to new
			control notification PEN_INVALIDCHAR).
	- example of how style bits (PES_ style bits for the parsed
		edit) can be stripped off before the normal CEdit
		control is created.

The source code to this application should be read along with
Foundation technical note 14 (MFC\DOC\TN014.TXT) describing
custom controls and other topics.

This application requires: MLIBCEW.LIB (C Windows runtimes), LIBW.LIB
(Windows library), either MAFXCW.LIB (MFC medium model Windows 
retail) or MAFXCWD.LIB (MFC medium model Windows debug), and
COMMDLG.DLL.

-------------------------------------------------------------------------

DLLTRACE\HELLO1.EXE
DLLTRACE\TRACER.DLL

The DLLTRACE sample directory contains a simple example of building
a dynamic link library (DLL) that uses MFC Windows classes, and
an application that uses the DLL.  This sample builds in DEBUG
mode only.

This application requires: MLIBCEW.LIB (C Windows runtimes for building
an executable), LIBW.LIB (Windows library), LDLLCEW (C Windows runtimes
for building a DLL),  MAFXCWD.LIB (MFC medium model Windows debug)
and LAFXDWD.LIB (MFC large model Windows debug with DLL support).

-------------------------------------------------------------------------

FILEVIEW\FILEVIEW.EXE

This program implements a simple text file viewer.  Unlike 
Windows NotePad, this program places no limit on the size 
of the text file that may be viewed.  This program is for
viewing text files only, and not editing them.  The source code
illustrates the following concepts:

    - Foundation application structuring.
    - Use of the Foundation file classes as base
      classes for derivation and specialization.
    - Use of the GDI classes for graphical output.
    - Use of Message Maps for handling window scrolling.

This application requires: MLIBCEW.LIB (C Windows runtimes), LIBW.LIB
(Windows library), either MAFXCW.LIB (MFC medium model Windows 
retail) or MAFXCWD.LIB (MFC medium model Windows debug), and
COMMDLG.DLL.

-------------------------------------------------------------------------

HELLO\HELLO.EXE

Described in the MFC Tutorial, this application shows the basics of
using the Microsoft Foundation Class Library to write applications
for the Microsoft Windows environment.  This application creates and
displays a fully-functional frame window, which in turn displays a
text string in its center.  The source code illustrates the following
concepts:

    - Simple Foundation application structuring.
    - Integrating Windows resources with your application.

This application requires: SLIBCEW.LIB (C Windows runtimes), LIBW.LIB
(Windows library), and either SAFXCW.LIB (MFC small model Windows 
retail) or SAFXCWD.LIB (MFC small model Windows debug).

-------------------------------------------------------------------------

HELLOAPP\HELLOAPP.EXE

This is an extremely simple MFC application that simply creates a
main frame window with the caption 'Hello World!'.  It is compiled
using retail libraries only.  HELLOAPP requires: SLIBCEW.LIB (C
Windows runtimes), LIBW.LIB (Windows library), and SAFXCW.LIB (MFC
small model Windows retail).

-------------------------------------------------------------------------

MDI\MDI.EXE

The MDI application demonstrates how to program to the MFC wrapper of 
the Windows Multiple Document Interface (MDI) wrapper.  When started,
the MDI application provides an MDI frame window, and two kinds of MDI
child windows that you may open within the frame.  One child window
is similar to the HELLO example program (it displays "Hello World"
in its client area).  The other kind of child window contains a 
bouncing ball.  The source code illustrates the following concepts:

    - Foundation MDI application structuring.
    - Coordinating MDI frame and child classes.
    - Using Windows timers.
    - Using the CBitmap class for constructing and drawing a
      bit pattern into a device context.

This application requires: MLIBCEW.LIB (C Windows runtimes), LIBW.LIB
(Windows library), and either MAFXCW.LIB (MFC medium model Windows
retail) or MAFXCWD.LIB (MFC medium model Windows debug).

-------------------------------------------------------------------------

MINMDI\MINMDI.EXE

This is a bare-bones MDI application that concentrates on showing the
minimum work needed to set up and maintain MDI child windows within
an MDI frame window.  You can use this application as a starting point
for your own experimentation with the MDI interface.  The source code
illustrates the following concepts:

    - Foundation MDI application structuring.
    - Coordinating MDI frame and child classes.

This application requires: SLIBCEW.LIB (C Windows runtimes), LIBW.LIB
(Windows library), and either SAFXCW.LIB (MFC small model Windows 
retail) or SAFXCWD.LIB (MFC small model Windows debug).

-------------------------------------------------------------------------

MINSVR\MINSVR.EXE

MINSVR is a minimal OLE server application that implements
a graphical ellipse drawing.  When running MINSVR *directly* (from
the program manager, file manager, or an icon), MINSVR is registered
with the registration data base.  YOU MUST RUN MINSVR DIRECTLY before
you can use it with other OLE programs.  Once you have run MINSVR
directly, you can use it with OLE Clients where it provides basic
embeddable object services.

The source code illustrates the following concepts:

    - Constructing a minimal OLE server
    - Programming with the MFC OLE classes
    - Supporting embedded objects

It is highly recommended that you read Foundation technical notes 8, 9,
and 10 (MFC\DOC\TN008.TXT, etc.) for more information on the MFC OLE
classes and constructing OLE clients and servers using MFC.

MINSVR requires:  MLIBCEW.LIB (C Windows runtimes), LIBW.LIB
(Windows library), either MAFXCW.LIB (MFC medium model Windows
retail) or MAFXCWD.LIB (MFC medium model Windows debug), COMMDLG.DLL,
COMMDLG.LIB (standard Windows dialogs), SHELL.DLL, SHELL.LIB (OLE
registration libraries), OLESVR.DLL, and OLESVR.LIB (OLE server
libraries).


-------------------------------------------------------------------------

MINSVRMI\MINSVRMI.EXE

MINSVRMI is a simple OLE server application that implements a
graphical elliptical drawing.  It is the same program as MINSVR
except it is implemented using multiple inheritance.  When MINSVRMI is
*directly* run, it registers itself with the registration database. 
YOU MUST RUN MINSVRMI directly before using it with other OLE
programs.  When run from an OLE client, MINSVRMI allows you to embed
objects in the client application's document.

The source code illustrates the following concepts:

    - Constructing a minimal OLE server
    - Programming with the MFC OLE classes
    - Using multiple inheritance with MFC and MFC OLE classes
    - Supporting embedded objects

It is highly recommended that you read Foundation technical notes 8, 9,
and 10 (MFC\DOC\TN008.TXT, etc.) for more information on the MFC OLE
classes and constructing OLE clients and servers using MFC.

You should also read Foundation technical note 16 (MFC\DOC\TN016.TXT)
for more information on MFC and multiple inheritance.

MINSVRMI requires:  MLIBCEW.LIB (C Windows runtimes), LIBW.LIB
(Windows library), either MAFXCW.LIB (MFC medium model Windows
retail) or MAFXCWD.LIB (MFC medium model Windows debug), COMMDLG.DLL,
COMMDLG.LIB (standard Windows dialogs), SHELL.DLL, SHELL.LIB (OLE
registration libraries), OLESVR.DLL, and OLESVR.LIB (OLE server
libraries).

-------------------------------------------------------------------------

MULTIPAD\MULTIPAD.EXE

Microsoft Windows provides a simple application called NOTEPAD.  The
MFC library adaptation of this program uses the MDI paradigm to allow
the user to manipulate any number of concurrently open text files. 
MULTIPAD is fully functional and includes printing support as well as
other features usually found only in commercial Windows applications:
a status bar at the bottom of the window, and a cache of
most-recently-used filenames (saved between program invocations) so
that users may quickly access recently used documents.  The source
code illustrates the following concepts:

    - Non-trivial MDI application structuring.
    - Menu command dispatching.
    - Dialog box initialization and management.
    - Printing.
    - Porting existing Windows code for use with MFC.
    - Swap tuning an application for Windows for maximum efficiency.

This application requires: MLIBCEW.LIB (C Windows runtimes), LIBW.LIB
(Windows library), either MAFXCW.LIB (MFC medium model Windows 
retail) or MAFXCWD.LIB (MFC medium model Windows debug), and
COMMDLG.DLL.

-------------------------------------------------------------------------

OCLIENT\OCLIENT.EXE

OCLIENT is an example of an Object Linking and Embedding (OLE) client
application.  It uses the Foundation OLE classes.  This program is a port
of the OLEDEMOC program which is shipped by the Microsoft OLE Software
Development Kit.  The program allows you to insert both embedded and
linked objects into a document.  OCLIENT also allows you to perform both
file and clipboard operations on the objects as well as activate the
servers to which the objects belong. The source code illustrates the
following concepts:

    - OLE client programming using MFC
    - Inserting embedded objects into a client
    - Pasting linked and embedded objects into a client
    - Copying objects to the clipboard
    - Loading and saving objects to and from disk

It is highly recommended that you read Foundation technical notes 8, 9,
and 10 (MFC\DOC\TN008.TXT, etc.) for more information on the MFC OLE
classes and constructing OLE clients and servers using MFC.

OCLIENT requires:  MLIBCEW.LIB (C Windows runtimes), LIBW.LIB
(Windows library), either MAFXCW.LIB (MFC medium model Windows
retail) or MAFXCWD.LIB (MFC medium model Windows debug), COMMDLG.DLL,
COMMDLG.LIB (Standard Windows Dialogs), SHELL.DLL, SHELL.LIB (OLE
Registration libraries), OLECLI.DLL, and OLECLI.LIB (OLE Client
libraries).

-------------------------------------------------------------------------

OSERVER\BIBREF.EXE

BIBREF is a simple OLE server application that implements
bibliographical references.  When BIBREF is *directly* run, it
registers itself with the registraton database and allows you to add,
modify, and delete bibliographical references from a list maintained
by the application.  YOU MUST RUN BIBREF DIRECTLY before using it
with other OLE programs.  When run from an OLE client, BIBREF allows
you to embed objects containing these references in the client
application's document.

The source code illustrates the following concepts:

    - Constructing an OLE server
    - Programming with the MFC OLE classes
    - Supporting embedded objects

It is highly recommended that you read Foundation technical notes 8, 9,
and 10 (MFC\DOC\TN008.TXT, etc.) for more information on the MFC OLE
classes and constructing OLE clients and servers using MFC.

OSERVER requires:  MLIBCEW.LIB (C Windows runtimes), LIBW.LIB
(Windows library), either MAFXCW.LIB (MFC medium model Windows
retail) or MAFXCWD.LIB (MFC medium model Windows debug), COMMDLG.DLL,
COMMDLG.LIB (standard Windows dialogs), SHELL.DLL, SHELL.LIB (OLE
registration libraries), OLESVR.DLL, and OLESVR.LIB (OLE server
libraries).

-------------------------------------------------------------------------

RESTOOL\RESTOOL.EXE

RESTOOL is a simple non-Windows application that reads a Microsoft
Windows compiled resource (.RES) file and generates C++ class
declarations for any dialog boxes found in the resource file.
This allows you to quickly put together MFC CDialog-derived classes
that manipulate dialog boxes you already use in existing applications.

RESTOOL's output must be reviewed before using (RESTOOL uses some
heuristics that are not universally applicable) and you must put the 
generated code into a proper C++ header file.  The source code
illustrates the following concepts:

    - Using MFC libraries to write a non-Windows application.
    - Microsoft Windows resource file format.

RESTOOL requires: MLIBCE.LIB (DOS C runtimes), and either MAFXCR.LIB
(MFC medium model DOS retail) or MAFXCRD.LIB (MFC medium model DOS
debug).

-------------------------------------------------------------------------

SHOWFONT\SHOWFONT.EXE

This program is a C++/Foundation adaptation of a sample application
provided in the Microsoft Windows 3.0 Software Development Kit (SDK).
SHOWFONT is a font attribute viewer.  It allows you to quickly
determine the visual and logical characteristics of Windows GDI FONT
resources.  The source code illustrates the following concepts:

    - Modal and modeless dialog box management.
    - CFont attribute manipulation.
    - Menu command dispatching.

This application requires: MLIBCEW.LIB (C Windows runtimes), LIBW.LIB
(Windows library), and either MAFXCW.LIB (MFC medium model Windows 
retail) or MAFXCWD.LIB (MFC medium model Windows debug).

-------------------------------------------------------------------------

SPEAKN\SPEAKN.EXE

SPEAKN is a simple Windows application that brings together graphics
output, sound output and handwriting recognition.  This highlights
the MultiMedia and Pen extensions made to Windows 3.1.

This application will only run under Windows 3.1.  A sound card
is required (for sound prompts).  Windows for Pen is also required
(the pen simulator provided in the Windows 3.1 SDK is sufficient).

You should read Foundation technical note 15 (MFC\DOC\TN015.TXT)
for more information on the MFC support for Windows for Pen.

The source code illustrates the following concepts:
	- single dialog application
	- Using bitmap buttons
	- Sound output
	- Pen input (BEdit)
	- resizing a BEdit
	- storing MultiMedia data (sounds, bitmaps) in resources

This application requires: MLIBCEW.LIB (C Windows runtimes), LIBW.LIB
(Windows library), MMSYSTEM.LIB (MultiMedia extensions to Windows),
and either MAFXCW.LIB (MFC medium model Windows retail) or MAFXCWD.LIB
(MFC medium model Windows debug).

-------------------------------------------------------------------------

TEMPLDEF\TEMPLDEF.EXE

TEMPLDEF is a non-Windows tool that helps you write and use 
template-like classes.  Templates are a proposed (but not established)
C++ language feature that are very useful for industrial-strength
programming.  The MFC library's collection classes use template
classes (and the tool provided in this directory) to create specific
collection types from general collection types.

The C++ language will someday support such features, but this tool
makes some of these proposed advantages available now.  TEMPLDEF
reads a "template" file, and writes a new C++ class which is
type-safe.

After you have built the templdef tool, you can use the MKCOLL.BAT
batch file and the array, list, and map template files (all in the
TEMPLDEF subdirectory) to generate your own versions of arrays,
lists, and maps.

For more information on the templdef tool, see MFC Technical Note #4,
"Template Classes and AFX" (located in MFC\DOC\TN004.TXT).  For more
information on proposed C++ templates, see Chapter 14 of "The Annotated
C++ Reference Manual," by Ellis and Stroustrup.

This application requires: MLIBCE.LIB (DOS C runtimes), and either
MAFXCR.LIB (MFC medium model DOS retail) or MAFXCRD.LIB (MFC medium
model DOS debug).

-------------------------------------------------------------------------

TESTCLNT\TESTCLNT.EXE

TESTCLNT is a simple testing program for OLE servers.  It should only
be used by knowledgeable OLE developers.  All others should refer to
the OCLIENT sample program for information.  TESTCLNT acts as a
simple OLE client and provides a full feature list that most servers
will wish to support.  It also provides a robust, error-checking,
environment to help track down bugs.  TESTCLNT allows you to call
some of the OLE APIs directly from the menu (only do this if you have
a good understanding of OLE as you can hang your machine). TESTCLNT's
source code illustrates the following concepts:

    - Implementing a robust OLE environment
    - Programming using the MFC OLE classes
    - Testing OLE Servers

It is highly recommended that you read Foundation technical notes 8, 9,
and 10 (MFC\DOC\TN008.TXT, etc.) for more information on the MFC OLE
classes and constructing OLE clients and servers using MFC.

TESTCLNT requires:  MLIBCEW.LIB (C Windows runtimes), LIBW.LIB
(Windows library), either MAFXCW.LIB (MFC medium model Windows
retail) or MAFXCWD.LIB (MFC medium model Windows debug), COMMDLG.DLL,
COMMDLG.LIB (Standard Windows Dialogs), SHELL.DLL, SHELL.LIB (OLE
Registration libraries), OLECLI.DLL, and OLECLI.LIB (OLE Client
libraries).

-------------------------------------------------------------------------

TESTSERV\TESTSERV.EXE

TESTSERV is a simple data-oriented OLE Server.  Its purpose is to
test OLE clients.  Only knowledgeable OLE developers should use
TESTSERV.  All others should refer to the OSERVER, MINSVR, or
MINSVRMI programs for information on OLE servers.  TESTSERV allows
you to enter a simple line of text which can then be embedded or
linked by a client. TESTSERV also allows you to call some of the OLE
APIs directly from the menu (this is not recommended unless you have
a good understanding of OLE as you can hang your machine). YOU MUST
RUN TESTSERV DIRECTLY before using it to embed objects into OLE
clients.  Running TESTSERV directly causes it to register itself
with the registration database.  TESTSERV's source code illustrates
the following concepts:

    - Providing a more robust environment for OLE servers
    - Programming in OLE with the MFC OLE classes
    - Providing linking services.
    - Providing embedding services.
    - Providing file services for OLE servers



It is highly recommended that you read Foundation technical notes 8, 9,
and 10 (MFC\DOC\TN008.TXT, etc.) for more information on the MFC OLE
classes and constructing OLE clients and servers using MFC.

TESTSERV requires:  MLIBCEW.LIB (C Windows runtimes), LIBW.LIB
(Windows library), either MAFXCW.LIB (MFC medium model Windows
retail) or MAFXCWD.LIB (MFC medium model Windows debug), COMMDLG.DLL,
COMMDLG.LIB (Standard Windows Dialogs), SHELL.DLL, SHELL.LIB (OLE
Registration libraries), OLESVR.DLL, and OLESVR.LIB (OLE Server
libraries).

-------------------------------------------------------------------------

TRACER\TRACER.EXE

TRACER is a tiny Windows utility that allows you to view and set the 
Foundation Windows diagnostic trace option flags described in 
MFC\DOC\TN007.TXT.  The source code illustrates the following concepts:

    - Reading and writing Windows profile strings
    - Writing a Foundation application that uses a modal dialog
      box but does not use the regular Windows/MFC message pump.

TRACER requires: SLIBCEW.LIB (Windows C runtimes), and either SAFXCW.LIB
(MFC small model Windows retail) or SAFXCWD.LIB (MFC small model Windows
debug).

-------------------------------------------------------------------------

TUTORIAL\PHBOOK.EXE

PHBOOK is a phone list maintenance application, and is the subject
of the MFC tutorial.  PHBOOK allows you to create, edit, print and
save lists of people's names and their telephone numbers.  In addition
to MFC application programming techniques, this application demonstrates 
the development of an abstract data model and the coupling of that
data model to a graphical user interface implemented with MFC.  See
TUTORIAL\README.TXT for more information on building this application.
The source code illustrates the following concepts:

    - MFC Application organization.
    - Printing.
    - Dialog box management.
    - Coupling an abstract data model to a user interface.
    - Using MFC object serialization (CArchive class) to save
      and load user data.

PHBOOK requires: MLIBCEW.LIB (C Windows runtimes), LIBW.LIB
(Windows library), either MAFXCW.LIB (MFC medium model Windows 
retail) or MAFXCWD.LIB (MFC medium model Windows debug), and
COMMDLG.LIB.


TUTORIAL\CMDBOOK.EXE

CMDBOOK is a DOS application that implements a simple character mode
interface to the phone book database.

This application requires: MLIBCE.LIB (DOS C medium model runtimes),
either MAFXCR.LIB (MFC medium model DOS retail) or MAFXCRD.LIB (MFC medium
model DOS debug).


TUTORIAL\DMTEST.EXE

DMTEST is a DOS application that tests the tutorial's data model
classes. It does not have any real function other than as a quick
acceptance test.

This application requires: MLIBCE.LIB (DOS C medium model runtimes)
and either MAFXCR.LIB (MFC medium model DOS retail) or MAFXCRD.LIB (MFC
medium model DOS debug).

-------------------------------------------------------------------------
