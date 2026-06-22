                Welcome to Borland Turbo Assembler 4.0
                --------------------------------------

  This README file contains important information about Borland Turbo
  Assembler. For the latest information about Borland Turbo Assembler
  and its accompanying programs and manuals, read this entire file.

-----------------
TABLE OF CONTENTS
-----------------
1.  How to Get Help
2.  Installation
3.  Features
4.  Important Information

------------------
1. HOW TO GET HELP
------------------

  If you have any problems, please read this file, the files
  in your DOC subdirectory, and check the on-line help and the
  manuals first. If you still have a question and need assistance,
  help is available from the following sources:

  1. For instant on-line access to the Borland forums with
     their libraries of technical information and answers
     to common questions, type

        GO BCPPDOS     - for questions pertaining to DOS

         or

        GO BCPPWIN     - for questions pertaining to Windows

     If you are not a member of CompuServe, see the enclosed
     special offer, and write for full details on how to receive
     a free IntroPak containing a $15 credit toward your first
     month's on-line charges.

  2. Borland offers a wide variety of Technical Support plans
     providing a range of assistance from installation and general
     usage to language syntax, programming, and debugging help. For
     information about these support programs, call 1-800-523-7070.

  3. Borland's TECHFAX service. Call (800) 822-4269 for a FAX
      catalog of technical document entries.

  4. Borland DLBBS. Dial (408) 431-5096 (up to 9600 baud, 8-N-1)
      for a host of free technical documents and example programs.

  5. For immediate assistance with everything from configuring Borland C++
      to programming or debugging, call our C++ Programmer's
      Advisor Lines ($2/minute, first minute free):
            * Windows / Win32:	1-900-555-1002  or 1-800-782-5558 (MC/Visa)
            * DOS :		1-900-555-1004  or 1-800-368-3366 (MC/Visa)

---------------
2. INSTALLATION
---------------
Important!
----------
Do not install Borland Turbo Assembler 4.0 files over previously installed
Borland language product directories.

Installing Borland Turbo Assembler on your hard disk:
-----------------------------------------------------
    1. Put the install disk in a 3.5" floppy drive.
    2. Change to that drive and type

       INSTALL <enter>

    3. Fill in directories as appropriate, and INSTALL will create
       appropriate Windows groups, and add the appropriate files to
       the directories you selected.

Note that if you want to install Win32s, you must insert Disk 4 and
run SETUP.EXE from Windows.

After installing, make sure your path is set correctly, then reboot,
before using these tools.

Configuring Earlier Language products and Borland Turbo Assembler
-----------------------------------------------------------------
The install program for Borland Turbo Assembler will configure your system
to allow the use of Borland Turbo Assembler and either Borland Pascal 7.0
or Borland C++ 3.1 on the same machine.  As long as you have installed Borland
Pascal or Borland C++ 3.1 prior to (rather than after) installing Borland
Turbo Assembler, there are very few guidelines you must follow:

- Each must use their respective copies of tools and utilities that
  depend on debug information, most notably Turbo Debugger for Windows
  (TDW).  You may find it useful to rename the older version of TDW.EXE
  to something like BPTDW.EXE  or BCTDW.EXE to avoid confusing filenames
  in your path.

- Both versions of TDW may not be run simultaneously.

- Make sure that old copies of TDW.INI are removed from your system. 
  (Running the utility TDWINI.EXE will make sure that this takes
  place.)

If you wish to use TDWGUI.DLL with TDW version 3.1 you need to
manually add UseTimer=Yes to the VideoOptions section of TDW.INI. 
Note that this option should not be set when using TDW version 4.0. 
This means that you would need to hand change your TDW.INI file each
time you switched between versions of TDW.  For this reason, we
recommend the non-windowed video DLLs (such as SVGA.DLL) for
customers who debug both BP and BC applications.

If you are installing Borland Pascal 7.0 or Borland C++ 3.1 AFTER Borland
Turbo Assembler has been installed, you will have to manually change the
system settings that allow these products to coexist:

In your system.ini file, check your [386Enh] section for multiple
entries for the device TDDEBUG.386.  Remove duplicate entries of
TDDEBUG.386 so that only the version from this product is loaded. On
disk, you may also want to rename or remove the BP7 or BC3.1 versions of
TDDEBUG.386 and TDWIN.DLL to avoid their accidental loading.  You
must restart Windows after making changes to system.ini.

Win32s and minimum swap file size
---------------------------------
Borland recommends that you have a minimum of 12 MB of memory available to
run Win32s applications.  For example, if your machine has 8 MB of memory
available to Windows, you should configure your "Virtual Memory" (swapfile)
to at least 4 MB.  This will reduce the risk of out-of-memory errors 
occuring in Win32s.

NT console applications and Win32s
----------------------------------
There is no Win32s console, so attempting to run a Win32 console
application without NT loaded will result in an error.

Changes to SYSTEM.INI file
--------------------------
The install program makes these changes to the SYSTEM.INI file:

  1) Adds "device=c:\bc4\bin\windpmi.386" to support our 32-bit tools.
  2) Adds "device=c:\bc4\bin\tddebug.386" to support our debugger.


Configuring the Windows NT command prompt
-----------------------------------------
To run 16-bit protected-mode programs (tlink) under an NT command prompt
you need to add the following line to CONFIG.NT:

  ntcmdprompt

Under the default NT command-line prompt, DOS COMMAND.COM is run after
returning from a TSR (such as RTM.EXE which bcc and tlink load). Adding the 
above line will cause the original NT CMD.EXE to be run.


Outdated versions of Win32s
---------------------------
It is essential to remove any older versions of Win32s from your
system before you use this product. To remove an old version of Win32s
perform the following steps:

  1. Change directory to the WINDOWS directory on your hard drive.  This
     is most likely C:\WINDOWS.

  2. Edit the SYSTEM.INI file and remove the line in the [386Enh]
     section that reads:

       device=C:\WINDOWS\SYSTEM\WIN32S\W32S.386

     (The actual path in the above line may be different to reflect your
      configuration.)

  3. Change directory to the SYSTEM subdirectory.

  4. Remove the following files:

       W32SYS.DLL
       WIN32S.INI
       WIN32S16.DLL

  5. Change directory to the WIN32S subdirectory.

  6. Remove all files here.

  7. Change directory back to SYSTEM and remove the WIN32S subdirectory.

You will now be ready to run the INSTALL program.  Be sure to select
<Install Win32s> in the INSTALL program so that the newer version of Win32s
will be installed on your system.


-----------
3. FEATURES
-----------

  - 32-bit instruction support, including Pentium
  - Linkers now handle binding of resources; no need for a separate RC or
    RLINK step.
  - Linker debug capacity expanded.
  - Turbo Debugger (TD32) for Win32s and Windows NT.
  - Support for OS exception handling.
  - Support for C/C++ exception handling.
  - Windows NT thread support.
  - Video DLL to run TDW in a window.
  - Remote debugging with TDW.
  - Debugger session state saving.
  - Debugger process attach for Windows NT.
  - Turbo Debugger Video Configuration Utility (TDWINI.EXE). 


------------------------
4. IMPORTANT INFORMATION
------------------------
GENERAL
-------
Note that if you have only 8 MB of RAM, you might experience some out-of-memory
problems building and using 32-bit applications. Please see the section below
titled, "Out of memory and MAKESWAP".


Object File Format
------------------
This product is designed to use and generate only object files which adhere
to the Intel OMF (Object Module Format) specification. This means that TLINK32
and TLIB only accept files of this format, and all provided libraries use 
this format. There is no support in the linker or librarian for COFF object
modules produced by Microsoft C tools.

MAKE 
----
MAKE will not put a space between two sets of file list macros as in BC++ 3.1
and before.  The example makefile below illustrates this; simply execute MAKE
in the directory containing the makefile. The output is:

   ALLOBJS1 = one onetwo two
   ALLOBJS2 = one one two two

makefile:

OBJS1 = \
   one \
   one

OBJS2 = \
   two \
   two

ALLOBJS1 = $(OBJS1)$(OBJS2)
ALLOBJS2 = $(OBJS1) $(OBJS2)

..:

   @@echo ALLOBJS1 = $(ALLOBJS1)
   @@echo ALLOBJS2 = $(ALLOBJS2)


Out of Memory and MAKESWAP
--------------------------
If you get "Out of Memory" errors from DOS when running the
command-line tools, create a swap file with the MAKESWAP utility.
(Note that this applies to DOS only, not to DOS boxes opened under
Windows.) MAKESWAP takes the size of the file to create in KBytes,
for example:

  MAKESWAP 12000

will create a 12MB swap file in the current directory called EDPMI.SWP
for use by Borland command line tools.  To enable the swap file, use
the DPMI32 environment variable by issuing the following command at
the DOS prompt:

  set DPMI32=SWAPFILE <location of swap file>\EDPMI.SWP


Creating 16-bit import libraries from .DEF files
------------------------------------------------
Use the /o implib switch when creating 16-bit import libraries from .DEF files
to prevent implib from generating extensions for import entry module names.


----------
New Tools
----------
The 16-bit linker has been modified in this version to allow for more than 64K
symbols in the executable's symbol table. The following tools have changed to
conform to the resulting new debug information format:

  TDW
  TDUMP
  Turbo Debugger 

These tools have versioning information, so that if you attempt to use any of
them with executables created in prior versions, an error message will result.
You will then need to relink your executables.

If you don't see correct dump information when using TDUMP version 4.1 on your
executables, check the header at the top of the output. If it does not indicate
version 4.0 debug information, the associated .EXE file must be recompiled with
version 4.0 tools.

-------------------------------------
Running from a Windows 3.1 DOS Prompt
-------------------------------------
If you run TLINK from a Windows DOS box and you get out of memory errors,
increase the XMS memory (in the 'Maximum' setting) allocated for the DOS
box by editing the appropriate .PIF file (usually DOSPRMPT.PIF).

NOTE: You must set the 'Maximum:' setting to the amount needed, not
      the 'Required:' setting.  Using the 'Required:' setting only
      sets aside memory for XMS, NOT for DPMI services and hence
      any amount set in the 'Required:' setting box is unavailable.



--------------------------
Turbo Debugger for Windows
--------------------------
You can use TD32 to debug under Win32s. However, to do so, you must
ensure you use SVGA.DLL or equivalent support in the VideoDLL entry
in the [TurboDebugger] section of TDW.INI.

TD32 can support dual monitor debugging under Win32s. Ensure that
a monochrome adapter is installed in your machine and set the
Mono=yes flag in the [VideoOptions] section of TDW.INI:

	[VideoOptions]
	MONO=yes

See the online text file called td_help!.txt for more information on
using TD32 and TDW.

