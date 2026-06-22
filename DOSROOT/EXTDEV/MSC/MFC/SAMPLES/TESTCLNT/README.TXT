==========================================================================
       MICROSOFT FOUNDATION CLASS LIBRARY : TESTCLNT SAMPLE PROGRAM
==========================================================================

This file contains basic information on how to set up and use the
Test Client (TESTCLNT) sample program.  

CAUTION: TESTCLNT should only be run by knowledgable OLE
developers familar with the testing tools provided in the Microsoft
OLE 1.0 Software Development Kit.  All others should use the OCLIENT
program before using TESTCLNT.  It is also suggested that you read
the MFC OLE technical notes (TN008.TXT, TN009.TXT, and TN010.TXT) for
more information on OLE, clients, and servers.

TESTCLNT is a testing apparatus that exercises production servers.
Developers writing OLE servers can use TESTCLNT to examine
interactions between OLE clients and servers.  

TESTCLNT dumps debugging and status information to a debugging
terminal or auxiliary port.  The program also provides a logging
facility that will dump certain events to a file, TESTCLNT.LOG.
TESTCLNT will also catch many symptoms of server errors. The two most
common responses from TESTCLNT will be assertions and exceptions. 


Required Equipment for TESTCLNT
----------------------------------
Three DLLs are required to run the TESTCLNT program: 
SHELL.DLL, OLECLI.DLL, and COMMDLG.DLL.

It does not make sense to run TESTCLNT without having an OLE
server installed on your system.  You can build the BIBREF application
(in ..\OSERVER directory) and install that, or try using an
existing OLE server.

Running TESTCLNT
-------------------
TESTCLNT behaves much like any normal OLE client.  You can
Insert Objects, Paste Objects, Copy Objects to the clipboard, 
Paste Links, and create objects from files.  Note that creating an
object from a file means that you saved the object using TESTCLNT. 
TESTCLNT uses a private file format to distinguish its own files
from other OLE files.  

In addition, TESTCLNT allows activation of the objects from a
server by editing or playing them (from the Object menu).  

Finally, TESTCLNT also allows you to call some of the OLE APIs
directly from the menu.  You should be very sure of what you are
doing before calling these APIs directly; calling some of them, out
of order, may hang your machine.
