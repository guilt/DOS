                               README.TXT File
               README file for Microsoft(R) C/C++, Version 7.0
                  (C) Copyright Microsoft Corporation, 1992

     This document contains release notes for version 7.0 of Microsoft
     C/C++ and its libraries for MS-DOS(R) and Microsoft Windows(TM)
     operating systems.

========================< IMPORTANT REQUIREMENT >==========================

     Microsoft C/C++ version 7.0 requires DPMI services.  If you wish 
     to use Windows as your development environment, Windows provides 
     DPMI services for you.  TO USE MS-DOS AS YOUR DEVELOPMENT 
     ENVIRONMENT YOU MUST INSTALL 386-Max TO PROVIDE THESE SERVICES. 

================================< CONTENTS >===============================


     This file has the following sections:


     Part 1: ESSENTIAL WINDOWS 3.0 COMPATIBILITY INFORMATION

     Part 2: Setup and Configuration Notes 

     Part 3: Support for Windows 3.1 in the Microsoft Foundation Classes

     Part 4: List of Additional Readme Files 

     Part 5: List of Topics in the DETAILS.TXT file


=======< Part 1: ESSENTIAL WINDOWS 3.0 COMPATIBILITY INFORMATION >======


     To make it easy for you to update to the latest Windows APIs
     and the new features of Windows 3.1, MS C/C++ supports
     Windows 3.1 by default. Windows 3.0 applications that are
     rebuilt with C/C++ will target Windows 3.1 by default.
     Therefore, attempting to run them under Windows 3.0
     generates an error.

     If you do not wish to take advantage of new Windows 3.1
     functionality, or if you want your applications to run on either
     Windows 3.0 or Windows 3.1, then follow these instructions for
     building Windows 3.0 applications.


     Building Windows 3.0 Projects with PWB
     --------------------------------------

     New projects:

          Choose one of the four Windows 3.0 project templates when
          prompted for a project template.

     Rebuilding existing projects:

          Reset the current project template by choosing Project
          Templates from the Options menu and then selecting Set
          Project Template. Note: This resets all build options,
          so check the resulting options to ensure they are
          appropriate for your project.

          An alternative method is to add the WINVER=0x300 macro in
          the Additional Global C/C++ Options dialog box and to
          modify the RC Build command in the Customize Project Template 
          dialog box. This dialog box can be accessed from the Project 
          Templates option on the Options menu. To make this modification,
          change:

          command rc_exe "$(RC) $(RESS) $@"
          
          to:

          command rc_exe "$(RC) /30 $(RESS) $@"


     Building Windows 3.0 Projects from the Command Line
     ---------------------------------------------------

     The two methods for building Windows 3.0 projects from the
     command line are described in this section.


          Using the WINVER Macro
          ----------------------

          To compile Windows 3.0 applications, you must either add
          the line:

          #define WINVER 0x0300

          to your source file before the line including the WINDOWS.H
          include file, or add the /DWINVER=0x0300 option when compiling
          all modules in the Windows 3.0 project. This prevents any 
          Windows 3.1-specific types, functions, or definitions from 
          being included.  


          Using the RC /30 Switch
          -----------------------

          In order to ensure that your application is Windows
          3.0-compatible, use the RC /30 option when combining
          your .EXE and .RES files. Use this option whenever RC
          is invoked after your .EXE file is linked, but do
          not use the /30 option with the /r option.


     Using Windows 3.1 Features in Windows 3.0 Applications
     ------------------------------------------------------

     You can also build a Windows 3.0-compatible application that
     conditionally makes use of new Windows 3.1 features if the
     application is running on a Windows 3.1 system. To do this,
     use the RC /30 command-line option, but do not use the
     #define directive to define WINVER equal to 0x0300.  Use the
     GetVersion() API to determine the version of Windows that is
     running before calling any new Windows 3.1 APIs.

     The sample code below demonstrates how the global constant
     fWin31 can be set to TRUE if Windows version 3.1 or greater
     is running on the system.  You can use similar code in your
     application initialization.

     extern BOOL fWin31;

     {
         UINT version;
         fWin31 = FALSE;
         version = LOWORD(GetVersion());
         if (((LOBYTE(version) << 8 ) | HIBYTE(version)) >= 0x030a)
         {
             fWin31 = TRUE;
         }
     }

     You can call new Windows 3.1 functions directly in your
     source as long as you link to the Windows 3.1 LIBW.LIB. In
     this case, no call to GetProcAddress() is needed.  However,
     on a computer running Windows 3.0, you must make sure new
     Windows 3.1 functions are not called. Here's an example of
     how this can be done:

     extern BOOL fWin31;

     if (fWin31)
     {
         ScrollWindowEx(hwnd, ...);
     }
     else
     {
         ScrollWindow(hwnd, ...);
     }


     Using the MFC Library with Windows 3.0 and Windows 3.1
     ------------------------------------------------------

     The MFC library header files can build applications targeted for 
     either Windows 3.0 or Windows 3.1.  Windows 3.1 is the default 
     target. This means that all of the new Windows 3.1 APIs are available
     for use. If you must target an application for Windows 3.0 only, you
     should define WINVER=0x0300 before including AFXWIN.H in your source
     files. This restricts the Windows and MFC interfaces to Windows 
     3.0-compatible versions only.

     The compiled MFC library (object code) must always be built for 
     Windows 3.1. It will fail to compile if WINVER is defined to be 0x0300.
     The library is compatible with both Windows 3.0 and Windows 3.1 
     run-time systems.  If you customize the MFC library, you should not
     redefine WINVER; the default value (WINVER=0x030A) is sufficient.


===================< Part 2: Setup and Configuration Notes >===============


     Getting Help on Error Messages
     ------------------------------

     To find information on any error message, you can access Help by
     using the stand-alone utility QuickHelp, by using the Help menu in
     the Programmer's WorkBench (PWB), or by checking the "Comprehensive
     Index and Errors Reference" manual.

     To find out about an error message using QuickHelp, at the
     operating-system prompt type:

          QH cxxxx

     where <c> is the error's alphabetic prefix and <xxxx> is the
     four-digit error number.

     To find out more about how to view errors from within PWB, choose
     "Errors" from the Microsoft Advisor Contents screen in PWB.
     (The Microsoft Advisor Contents screen appears when you choose
     "Contents" from the Help menu in PWB.)

     Some errors are documented in Help but are not in the "Comprehensive
     Index and Errors Reference" manual. See ERRATA2.TXT for a listing of
     these errors.


     Copying a Single File from Installation Disks
     ---------------------------------------------

     See the ANSWERS.TXT file for instructions.


     Installation of Graphics Sample Files
     -------------------------------------

     Setup does not create the SORTDEMO and GRAPHICS subdirectories, 
     or copy their associated graphics samples, unless you request that
     Setup install the graphics libraries.


     Loading Windows From Your AUTOEXEC.BAT File
     -------------------------------------------

     If you allow Setup to modify your AUTOEXC.BAT file, and your
     AUTOEXEC.BAT file contains a statement that loads Windows, the 
     resulting behavior may cause unexpected system problems. Therefore,
     if your AUTOEXEC.BAT file loads Windows, do not allow Setup to 
     modify your AUTOEXEC.BAT file. Save the changes during Setup and 
     modify your file once Setup has finished.


     Using Windows 3.0 and HIMEM.SYS with More Than 16 MB RAM
     --------------------------------------------------------

     Installing C/C++, which provides a new version of HIMEM.SYS, may
     cause a system crash if your computer has more than 16 MB of RAM.
     This is not an issue for Windows 3.1 users or 386-Max users.
     If you do not want to upgrade to Windows 3.1 or you want to run
     both versions of Windows, replace the HIMEM.SYS driver installed
     by C/C++ with the HIMEM.SYS driver from Windows 3.0.


     Incorrect Drivers May Prevent Windows From Running
     --------------------------------------------------

     The Setup program adds a DEVICE statement for the CVW1.386 driver to 
     your SYSTEM.INI file. If your SYSTEM.INI file also contains a DEVICE
     statement for CV1.386, a driver no longer necessary for C/C++, 
     Windows 3.x will not run. Remove the DEVICE statement for CV1.386 
     to solve this problem.


     Avoiding Data Loss When Using SMARTDRV.EXE
     ------------------------------------------

     SMARTDRV.EXE does not write data to disk immediately. If your computer
     should crash after the time data is written to the cache and before
     the data is written to the disk, data can be lost. Issuing the
     following command causes SMARTDRV to write all data in the cache to
     the disk:

     SMARTDRV /c


     Setup May Not Detect Foreign Disk Cache
     ---------------------------------------
     Setup may install SMARTDRV.EXE if it does not detect the foreign 
     disk cache installed on your system. Remove the DEVICE statements 
     for SMARTDRV.EXE from your AUTOEXEC.BAT and CONFIG.SYS files to 
     resolve this problem.


     Fragmented Memory May Cause Internal Compiler Error
     ---------------------------------------------------

     The compiler generates an internal error R6900 if memory has been
     fragmented in such a way that chunks of free memory greater than
     4K exist between allocated memory blocks. To determine if memory
     fragmentation is the cause of the problem, check memory usage with
     the techniques described in Chapter 3 of the "Getting Started"
     manual. Changing the way memory is allocated, or modifying the
     behavior of TSRs, may reduce memory fragmentation.


     Programs That May Be Incompatible with SMARTDRV.EXE
     ---------------------------------------------------

     The following applications may be incompatible with SMARTDRV.EXE,
     version 4.0:

     - The Disk Protect feature in Norton Utilities version 6.0

       Do not use the Disk Protect feature in Disk Monitor. If you do,
       you will encounter an error and your system may hang if you try
       to write to the protected drive. If you want to write to and
       cache a protected drive, use the Norton cache program when using
       Disk Monitor.

     - The Calibrate program in Norton Utilities version 6.01

       Calibrate fails on the Disk Mapping test if SMARTDRV is enabled.

     - DoubleDisk from Vertisoft

       Do not enable write-behind caching for DoubleDisk compressed
       partitions.

     - Storage Dimensions SCSI Driver (SSTOR.SYS)

       Using the SSTOR.SYS driver, the SCSI drive appears corrupted when
       SMARTDRV is loaded. The disk's contents are not altered, but they
       are inaccessible when using SMARTDRV.

     The following drivers, installed in a CONFIG.SYS file, are
     incompatible with SMARTDRV.EXE version 4.0:

     - The SuperStor utility from Addstor (SSTORDRV.SYS)

       Do not use the Create Mountable Drive or Mount and Dismount features
       of SuperStor after SMARTDRV is loaded. You must configure your
       SuperStor partitions before loading SMARTDRV. If your AUTOEXEC.BAT
       file includes "mount" configuration commands, make sure that the
       SMARTDRV command line follows the SuperStor configuration command
       lines.

       Also, you will receive read-write errors if you use SMARTDRV to
       cache a SuperStor compressed drive. To prevent SMARTDRV from
       caching the compressed drive, you must include the driver letter-
       option on the SMARTDRV command line.

       For example, if drive C is the uncompressed drive, and drives E
       and F are the compressed SuperStor drives, you would type the
       following command line or include it in your AUTOEXEC.BAT file:

       smartdrv e- f-

     - The network driver from DNA Networks Inc. (STATION.SYS)

       Using both STATION.SYS and SMARTDRV may cause your system to hang.

     - Versions prior to version 7.x of the driver for the
       Bernoulli Box (RCD.SYS)

       The RCD.EXE program requires that driver RCD.SYS be installed to
       use the Bernoulli Box. When SMARTDRV is running, RCD.EXE does
       not recognize that RCD.SYS has been installed.

     - The Norton Antivirus utility (NAV_.SYS and NAV&.SYS)

       The NAV_.SYS and NAV&.SYS drivers for the Norton Antivirus utility
       may generate "Not enough memory" errors or hang your system when
       loading SMARTDRV.EXE. One workaround is to use the /L command-line
       option to load SMARTDRV.EXE into low memory. An alternative is using
       the /B option with NAV&.SYS to avoid the NAV&.SYS bug that causes
       your system to hang.

     The following driver, installed in an AUTOEXEC.BAT file, is
     incompatible with SMARTDRV.EXE version 4.0:

     - DataMonitor version 7.1 by PC Tools (DATAMON.*)

       Loading DataMonitor after SMARTDRV is installed may cause your
       system to hang.


     Setup Generates a "Cannot write to library file" Error
     -------------------------------------------------------

     If your TMP environment variable is pointing to a RAM drive that
     doesn't have enough space for the temporary files that Setup uses
     during the library-building process, this error can result. To solve
     this problem, set the TMP variable to your hard disk, if your hard
     disk has sufficient space, or select fewer libraries from the Custom
     Installation Setup screen. You can run Setup again later to build
     additional libraries.


     Installation Order May Affect 386-Max Performance
     -------------------------------------------------

     Installing MS C/C++ before 386-Max can improve 386-Max's capability
     for managing the upper memory area.


     Using Earlier Versions of 386-Max with C/C++
     --------------------------------------------

     If you already use 386-Max, be sure to upgrade your system with the
     version of 386-Max that is supplied with Microsoft C/C++. This newer
     version includes bug fixes that affect the performance of C/C++.


===< Part 3: Support for Windows 3.1 in the Microsoft Foundation Classes >===


     The Microsoft Foundation classes provide support for the
     enhancements provided in Windows version 3.1. The following
     features are described in technical notes in the
     \C700\MFC\DOC directory and demonstrated in sample programs in
     \C700\MFC\SAMPLES. These API functions are documented only in 
     the Help system. The following list describes the enhancements 
     that can be used to develop applications for both Windows 3.0 
     and Windows 3.1.

     - The development and use of custom controls is supported. In
       addition, owner draw controls and bitmap buttons are provided. 
       See TN014.TXT and the sample application CTRLTEST.

     - To improve robustness, the Microsoft Foundation Class Library 
       fully supports the STRICT data types defined in the Windows 3.1 
       interface file, WINDOWS.H.

     - Common dialog operations are now supported with easily
       customized classes including CFileDialog (for both File Open
       and File Save As), CFindReplaceDialog (to implement modeless
       find and replace), CColorDialog (for color selection),
       CPrintDialog (for both print setup and print), and
       CFontDialog (for font selection). These new dialogs are
       described in TN013.TXT.

     - The Microsoft Foundation Classes were designed and implemented
       using the Windows 3.1 Debug Kernel.  If your application issues
       any Debug Kernel warnings, they are most likely due to the way you
       structured your application code.  If you receive any Fatal Exit
       messages, the cause is most likely a result of an incorrectly
       used feature.  Some Debug Kernel warnings (such as 'Invalidate with
       fErase == FALSE prevents EraseBackground') will be issued even
       when features are used correctly .

     - Dialog boxes now feature a gray background that is easily 
       customized.

     - OLE servers now register themselves at startup so that
       users do not need to use REGEDIT.EXE.

     - Microsoft Foundation Classes now support the Microsoft Pen Windows
       controls (see TN015.TXT). A sample application, SPEAKN.EXE,
       is provided to demonstrate the use of Pen and MultiMedia. 
       A pen palette and/or MultiMedia extensions are NOT required. 
       Applications developed with the Microsoft Foundation classes 
       are automatically "pen-aware."

     - Using multiple inheritance with Microsoft Foundation
       classes is demonstrated in the sample application MINSVRMI,
       a small OLE server that uses multiple inheritance.

     - For applications that target Windows 3.1 only, the Microsoft 
       Foundation Class Library supports the most useful of the new 
       Windows 3.1 API functions and messages.


==================< Part 4: List of Additional Readme Files >==============


FILE                      CONTENTS
----                      --------

ANSWERS.TXT               Answers to commonly asked questions
DETAILS.TXT               Product notes for Microsoft C/C++. See Part 5
                          of this file for a list of topics in DETAILS.TXT
ERRATA1.TXT               Documentation additions and corrections for
                          "Environment and Tools," "C++ Tutorial,"
                          "C Language Reference," "C++ Language
                          Reference," and "Programming Techniques."
ERRATA2.TXT               Documentation additions and corrections for
                          "Run-Time Library Reference," "Class Libraries
                          Reference," "Class Libraries User's Guide,"
                          "Comprehensive Index and Errors Reference,"
                          CLANG.HLP, CL.HLP, LINK Help, header files, and
                          Microsoft Class Libraries Quick-Reference Card
BIN\MSD.TXT               Documentation for diagnostics utility
SOURCE\MOVE\MOVEAPI.TXT   Move - Help document
SOURCE\STARTUP\README.TXT Startup build instructions

From the C700\SAMPLES directory:
    IOSTUTOR\README.TXT     Instructions for building iostream demo
    CPPTUTOR\OOD\OODEMO.TXT Notes on the OODEMO sample
    SAMPLES.TXT             Samples document

MFC README Files:
    MFC\README.TXT        Introduction to the MFC library
    MFC\SRC\README.TXT    How to build the libraries
    MFC\LIB\README.TXT    Information file for MFC Libraries

MFC README Files from the MFC\DOC directory:
    README.TXT            Overview of tech notes
    TN001.TXT             Tech note on class registration
    TN002.TXT             Tech note on persistence
    TN003.TXT             Tech note on handle maps
    TN004.TXT             Tech note on templates
    TN005.TXT             Tech note on MDI
    TN006.TXT             Tech note on message maps
    TN007.TXT             Tech note on Windows debugging aids
    TN008.TXT             Tech note on Foundation OLE support
    TN009.TXT             Tech note on writing an OLE client with MFC
    TN010.TXT             Tech note on writing an OLE server with MFC
    TN011.TXT             Tech note on DLL support
    TN012.TXT             Tech note on robustness issues 
                                       (including WIN 3.1 STRICT)
    TN013.TXT             Tech note on standard dialog classes
    TN014.TXT             Tech note on custom controls
    TN015.TXT             Tech note on Pen Windows
    TN016.TXT             Tech note on multiple inheritance

MFC README Files from the MFC\SAMPLES directory:
    ABOUT2\README.TXT         Information file for About2
    HELLO\README.TXT          Hello/Generic application
    README.TXT                Explanation of the MFC Samples
    TEMPLDEF\README.TXT       Instructions
    TESTCLNT\README.TXT       MFC OLE Test Client Sample
    TESTSERV\README.TXT       MFC OLE Test Server Sample
    TUTORIAL\CHAR\README.TXT  Tutorial samples applications
    TUTORIAL\README.TXT       Tutorial samples applications
    TUTORIAL\WIN\README.TXT   Tutorial samples applications

     IMPORTANT: See README.SDK for release information relating to the
     Windows 3.1 SDK product. Documentation for the Windows 3.1 functions 
     is available in Help only.


=================< Part 5: Topics Covered in DETAILS.TXT >=================


     See the DETAILS.TXT file for information on the following topics:

     - Using PWB
          Running PWB in a Window  
          Using Precompiled Headers from PWB
          New PWB Switches: Friction and Factor 
          Minimum Memory Requirement for Accessing Help in PWB
     - Command-Line Options
          New CL Default is /Od if Optimizations Not Specified
          Mixing P-Code and Fully Optimized Machine Code
     - C++ Topics
          Destructors for Objects in Global and Static Arrays
          Defining const struct Parameters for Member Functions
          Return Types for Based Virtual Functions
          Calling Temporary Objects of Types with Destructors
          Explicit Conversion Recommended for Member Functions
          Function-Style Initializers Starting with Casts
     - Specifying Program Starting Execution Points
          Windows 3.x Executable Files (EXE)
          Windows 3.x Dynamic-Link Libraries (DLL)
          Windows 3.x and the NOCRT Libraries
     - Run-Time Support for Windows Exit Procedure Routines
          Information on the Windows WEP Routine
          Providing Your Own DLL Termination Routine
          General Notes
          Library Initialization Code in Windows DLLs
     - New Function and Pragma Behavior
          Using the Intrinsic Version of strlen
          The check_pointer Pragma
          The data_seg Pragma
     - Identifier Naming Issues
          Finding Local Static Variables in Browser Information
          Missing Symbol Names for enums
          Long Identifier Names Create Problems for LIB.EXE
     - Using the CodeView(R) Debugger with MS C/C++ 
          CodeView Now Runs in a Windows-Like Environment
          CodeView Error When Debugging Programs Built With Class Libraries
          Extended-Line Modes Enabled for CodeView Debugger
          Remote Debugging with CodeView
          Debugging Locally on an 80286
          Running CodeView on an 80286 Computer
          Debugging P-Code
          CodeView's Access to Function Code in Libraries
          Unloading DLLs When CodeView Terminates
          Removing CodeView 3.07 from SDK Program Manager Group
          Unsuccessful Connection to Remote Terminal
          Running Screen Saver Programs While Debugging
          DOS Session Running in a Window Does Not Have Mouse Support
          Application I/O When Debugging Can Cause Screen Corruption
          Recovering From "Internal Debugger Error"
          Debugging Applications That Use a Mouse
          Debugging Basic or FORTRAN in the Windows Environment
          Setting the Scope of the Show Address Option in CodeView
          Disable the Minimize On Use Option When Debugging



=============================================================================


     Microsoft, MS, MS-DOS, and CodeView are registered trademarks, and
     Windows is a trademark of Microsoft Corporation.

     386-Max is a trademark of Qualitas, Inc.

     Bernoulli Box is a trademark of Iomega Corporation.

     Norton Utilities is a registered trademark of Peter Norton Computing.

     SuperStor is a trademark and Addstor is a registered trademark of
     Addstor, Inc.

     NOTE: Microsoft improves its languages documentation at the time of
     reprinting, so some of the information in this file may already be
     included in your manuals.

