========================================================================
      MICROSOFT FOUNDATION CLASS LIBRARY : TESTSERV SAMPLE PROGRAM
========================================================================

CAUTION: Test Server (TESTSERV) should only be run by knowledgeable
OLE developers familiar with the Microsoft OLE 1.0 Software
Development Kit.  All others should use the OSERVER, MINSVR, and
MINSVRMI sample programs before using TESTSERV.  It is also suggested
that you read the MFC OLE tech notes (TN008.TXT, TN009.TXT, and
TN010.TXT) for more information on MFC OLE support for clients and
servers.

TESTSERV is a testing apparatus that works on production clients. 
Developers writing OLE client applications can use TESTSERV as 
a testbed for examining general OLE client/server interactions.

TESTSERV dumps debugging information to a debugging terminal or
auxiliary port.  It also has a logging facility that will dump out
selected messages to a file named TESTSERV.LOG.  TESTSERV detects
many OLE protocol errors caused by client programs.


Required Equipment
------------------
TESTSERV requires the following dynamic link libraries:
SHELL.DLL, OLESVR.DLL, and COMMDLG.DLL.

Before running TESTSERV as an OLE server (that is, via an OLE client)
you must register it with the system registration database.  This is
done by running TESTSERV DIRECTLY (i.e., from the program manager,
file manager, or by double clicking on an icon ).

If you move TESTSERV.EXE to a different location you must re-run
TESTSERV directly (as discussed above).  This will modify the
information in the system registration database.


Running TESTSERV
-------------------
TESTSERV behaves like a normal OLE server.  You can run the program
directly, or run it as embedded by using a client Insert Object
command.  You can also copy objects to the clipboard in both the
embedded and linking formats.  Finally, you can reactivate the server
by using the edit verb.

TESTSERV allows you to call APIs directly from the menu.  This is not
recommended unless you are very familiar with the workings of OLE. 
Improper use of these APIs can hang your machine.
