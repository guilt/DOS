
                        LANtastic 8.0
                       Readme.txt File
                      (c) Artisoft, Inc.
                      Edition 1 [5/13/98]
                     ====================


============================================================
Contents of this Readme File
============================================================

This file is divided into the following main sections:

   I. General

  II. LANtastic for Windows 95/98 and Windows NT

 III. LANtastic for Windows NT only

  IV. LANtastic for Windows 95/98 only

   V. LANtastic for DOS only

Read the information in the General section, then proceed
to the section(s) that apply to the LANtastic interface(s)
that you plan to use.

============================================================
I. General
============================================================

-------------------------------------
1. Error messages and their solutions
-------------------------------------
Commonly received error messages are documented in two files 
(ERRS_95.PDF and ERRS_DW.PDF), as explained in the LANtastic 
Installation and Setup Manual. However, the following 
error messages don't appear in the documentation.

A. "Cannot locate network computer name or resource."

   If you receive this error when expanding the Entire
   Network tree in either the Assign Drives, Assign Printers
   or LANtastic Connections window - OR when expanding the
   Microsoft network tree in the Browse Network window -
   it means one of two things. Either:

   - The Client for Microsoft networks is installed but no 
     Microsoft servers in your workgroups are available on
     the network at this time.
 
     OR

   - The Client for Microsoft networks is installed but your 
     workgroup name doesn't match the workgroup name for the 
     Microsoft servers on the network.

   The solution is to remove the Client for Microsoft
   networks OR correct your workgroup name. To perform
   either task, right-click the Network Neighborhood icon
   on your desktop, then select Properties.

B. "386MAX VxD Error V1014: Disk Cache or other file I*/O
   software using EMS memory. 386MAX VxD not loaded.
   Windows initialization terminated. Press any key to
   return to DOS."

   If you receive this error, you're using EMS
   (non-conventional) memory with Qualitas' 386Max, which
   doesn't allow disk emulator use of EMS under Windows.
   When using 386Max, use either the default of
   /MEM=CONVENTIONAL or use /MEM=XMS. You can change this
   setting in LANtastic server startup parameters. Further
   information about 386MAX's memory configuration can be
   found in Qualitas' documentation.
 
C. "FATAL ERROR: Out of memory in EMemCalloc, caller: 7
   press any key..."

   If you receive this error message, you're installing
   LANtastic for DOS without having the minimum of 499K of
   free conventional memory available. At the DOS prompt,
   type MEM <Enter> to view your computer's current memory
   availability.  

D. "The network is not present or not started."

   If you receive this error when expanding the Entire 
   Network tree in the Assign Drives, Assign Printers or 
   LANtastic Connections windows - OR when expanding the 
   NetWare network tree in the Browse Network window - it 
   means the Client for NetWare networks is installed but 
   no NetWare servers are available on the network at this
   time.

   The solution is to either remove the Client for NetWare
   networks OR install a NetWare server on your network. 
   To perform either task, right-click the Network 
   Neighborhood icon on your desktop, then select
   Properties.

E. "ERROR: Cannot locate network name, LOGIN has failed."

   If you receive this error message when attempting to 
   connect a LANtastic DOS or Windows computer to a Windows 
   95/98 computer through an Artisoft Central Station, the 
   Windows 95/98 computer must be configured to allow 
   unpublished routes. Do this by clicking Start, Settings,
   Control Panel, then double-clicking Network and selecting
   Artisoft NetBIOS. Click Properties and from the Advanced
   tab, select Unpublished Routes Allowed and click Yes. 
   Click OK and close the Network Control Panel, then
   restart your computer.

F. "A network error has occurred. Abort, Retry, Fail."
    or "This device does not exist on the network. Reading
    drive XX. Abort, Retry, Fail."

    You are attempting to view files on a drive that is
    redirected to a LANtastic for DOS or Windows 3.x
    global resource.

    Neither LANtastic for Windows 95/98 nor LANtastic for
    Windows NT supports global resources.     

----------------------------------------
2. Getting updated LANtastic information
----------------------------------------
For the latest information about LANtastic 8.0 or other
Artisoft products, visit the Artisoft WWW site at:
www.artisoft.com.


------------------------------------------------
3. Making installation diskettes from the CD-ROM
------------------------------------------------
Even if you have the LANtastic CD-ROM, you may find that you
need a set of installation diskettes. For example, you would
need diskettes if you had to perform a remote installation
on a computer without a CD-ROM drive.

You can copy all of the LANtastic 8.0, i.Share, ModemShare
and XtraMail files from the LANtastic CD-ROM. Or, if you
prefer, you can purchase a set of diskettes (LANtastic for
Windows 3.x and LANtastic for DOS only) by contacting the
Artisoft Direct Team. Instructions for doing so appear on
the Directory of Services you received with this product.

To make diskettes of the LANtastic 8.0 files:

 1. Format the required number of 1.44MB diskettes:

    LANtastic for Windows NT = 3

    LANtastic for Windows 95/98 = 3

    LANtastic for Windows 3.x = 3

    LANtastic for DOS = 2

 2. Go to the ENG\LANTASTI directory of the CD-ROM. There
    you'll see the following subdirectories:

    WINNT, WIN9X, WIN3X and DOS

    Then, within each of these subdirectories, you'll find
    additional subdirectories: DISK1, DISK2, etc. For example:
    ENG\LANTASTI\DOS\DISK1

 3. Label each of your diskettes with the appropriate interface
    name and DISK number, then copy each of the subdirectories'
    contents to the appropriate diskette.

    For example, to make LANtastic for DOS DISK1, put the CD
    into the CD-ROM drive and put the diskette labeled DOS DISK1
    into a floppy drive. At the DOS prompt, type:

    D: <Enter> (where D: is the CD-ROM drive letter you're using)
    CD ENG\LANTASTI\DOS\DISK1 <Enter>
    XCOPY *.* A: /s <Enter> (where A: is the drive with the
    diskette).

 4. Repeat step 3 for each LANtastic interface for which you
    want a set of installation diskettes.


----------------------------------------
4. Setting up a shared HP JetDirect printer
----------------------------------------    
Computers running LANtastic for Windows 95/98 can share an 
HP JetDirect printer, but not through LANtastic. If you do
use LANtastic, the printer won't appear as a resource on 
the Available Printers list in the Share Drives and Printers 
window. 

However, each Windows 95/98 client computer can still use the 
printer by installing HP Services in the Windows 95/98 Network 
Control Panel. Refer to your HP documentation for detailed 
instructions.

LANtastic 8.0 supports HP JetDirect printer sharing under 
the Windows 3.x and DOS platforms. See the LANtastic 
Installation and Setup Manual for instructions on adding 
the printer to your network.


---------------------------------
5. Using the Adobe Acrobat Reader
---------------------------------
The LANtastic documentation that's included on your CD-ROM 
or that you downloaded from the FTP server is in Adobe
Acrobat Portable Document Format (PDF). To use these
files, you must first install the Acrobat Reader. You can
get the Reader from the LANtastic CD-ROM or download it from
Adobe's web site.


Installing the reader on your hard drive
----------------------------------------

In Windows 95/98 or NT:

 1. If you're installing from CD-ROM, put it into the drive. 
    Or if you downloaded the reader to your hard drive change
    to the directory on your computer where you downloaded the 
    reader, for example: C:\DOCS.

 2. Close all applications, then click Start, Run. 

 3. If you're installing from CD-ROM, type D:\DOCS\AR32E30 
    where D: is your CD-ROM drive letter, then click OK. Or, if 
    the reader's on your hard drive, type C:\DOCS\AR32E30 where 
    C:\DOCS\AR32E30 is the location on your hard drive where 
    you downloaded the reader. 

 4. Because Artisoft has met Adobe's licensing requirements 
    you can press Enter to continue past the licensing screen.

 5. Click Install or press Enter to accept the default 
    installation path, then click OK to continue past the 
    registration message. 

 6. Type in your name and press the Tab key, then type your 
    organization name and press Enter. 

 7. When the installation is finished and Windows restarts, 
    open ACROREAD.EXE in your ACROREAD folder. 

    You're now ready to open and use the Online Library PDF 
    files. Go on to the section below called "Viewing and 
    Navigating the PDF files."


In Windows 3.x:

 1. If you're installing from CD-ROM, put it into the drive. 
    Or if you downloaded the reader to your hard drive,
    change to the directory on your computer where you
    downloaded the Reader, for example: C:\DOCS.

 2. Close all applications, then from the File menu, click 
    Run. 

 3. If you're installing from CD-ROM, type D:\DOCS\ACROREAD 
    where D: is your CD-ROM drive letter, then click OK.
    Or If you downloaded the Reader to your hard drive, type 
    C:\DOCS\ACROREAD where C:\DOCS\ACROREAD is the location on 
    your hard drive where you downloaded the reader.

 4. Because Artisoft has met Adobe's licensing requirements, 
    you can click Accept or press Enter to continue past the 
    licensing screen.

 5. Click Install or press Enter to accept the default 
    installation path, then click OK to continue past the 
    registration card message. 

 6. Type in your name and press the Tab key, then type your 
    organization name and press Enter. 

 7. When the installation is finished and Windows restarts, 
    double-click the ACROREAD icon in your Adobe Acrobat
    program group.

    You're now ready to open and use the Online Library PDF 
    files. Go on to the section below called "Viewing and 
    Navigating the PDF files."


In DOS:

 1. If you're installing from CD-ROM, put it into the drive. 
    Or if you downloaded the reader to your hard drive,
    change to the directory on your computer where you
    downloaded the reader, for example: C:\DOCS.

 2. If you're installing from CD-ROM, from the DOS prompt,  
    type D:\DOCS\ACRODOS <Enter> where D: is your CD-ROM drive 
    letter. Or if you downloaded the reader to your hard drive, 
    type C:\DOCS\ACRODOS <Enter> where C:\DOCS\ACRODOS is the 
    location on your hard drive where you downloaded the reader.

 3. Because Artisoft has met Adobe's licensing requirements 
    you can press Enter to continue past the licensing screen.

 4. Press Enter to accept the default installation path, 
    then click OK to continue past the registration card 
    message. 

 5. Type in your name and press the Tab key, then type your 
    organization name and press Enter. 

 6. When the installation is finished, reboot your computer. 
    Then from the DOS prompt, type DOSREAD <Enter>.
    
    You're now ready to open and use the Online Library PDF 
    files. Go on to the next section.


Viewing and navigating the PDF files
------------------------------------

In Windows NT, 95/98 or 3.x:

 1. With the Acrobat Reader running, click the File menu 
    then click Open. 

 2. Select or type in the path to the PDF you want to use. 
    For example, if you want to use a PDF on the LANtastic
    CD-ROM, find your CD-ROM drive in the Drives field by
    selecting or typing in the path D:\DOCS (where D: is
    your CD-ROM drive letter). 

 3. In the File List field, double-click the document you 
    want to view. Then follow the steps below to use the
    manual. 

 4. Click the View menu, then click Bookmarks and Page. A 
    list of the main sections in the file appears on the left 
    side of your screen. 

    You can enlarge the Bookmarks window by dragging the
    double-triangle icon (next to the lower right corner
    of that window) to the right.

 5. Click the triangle to the left of a listing in the 
    bookmarks window to see its subsections. 

 6. You can tell when an item in the file is hypertext-
    linked by the way your cursor looks. Ordinarily,
    the cursor looks like an open hand. Any time the hand
    passes over a hypertext-linked item, it turns into a
    pointing finger. Just click to use that link. One click
    of the mouse takes you from the Chapter Contents list
    to a topic's location. Cross-references are linked, too.
    You can click a cross-reference such as "see page 16" and
    jump directly to the topic on that page.

 7. You can look for a specific topic with the Find feature. 
    Just click the binoculars icon in the toolbar and type in a 
    keyword or two. You can repeat the Find command by pressing 
    the F3 key until you find what you're looking for.

 8. It's a good idea to pull down the Help menu to learn how 
    to use the reader's toolbar, status bar and other features. 
    For instance, it's helpful to know about the Go Back feature 
    under the View menu, which retraces links you've used and 
    takes you back to your starting point.


In DOS:

 1. Go to the directory on your hard drive where you 
    installed Acrobat and type ACROBAT<Enter>.

 2. From the File menu, select Open, then select or type in 
    the path to the PDF you want to use. For example, if you  
    want to use a PDF on the LANtastic CD-ROM, find your CD-ROM 
    drive in the Drives field by selecting or typing in the path 
    D:\DOCS (where D: is your CD-ROM drive letter)

 3. In the DOCS directory, select the PDF file that you want 
    to open. 


Printing the PDF files	
----------------------

You can print all or parts of a PDF file by following these 
steps:

 1. Open the PDF file you want to print, then pull down the 
    File menu and click Print.

 2. Select All, Current or click a page range, then click OK. 
    To print a file from the DOS reader, go to Print Setup and 
    make sure the type of printer you're using is selected: 
    either PostScriptr or Bitmap (select Bitmap for all non-
    PostScript printers). If you select Bitmap, scroll through 
    the list of printer drivers and select the appropriate 
    driver.


============================================================
II. LANtastic for Windows 95/98 and Windows NT
============================================================

----------------------------------------------------------
1. Notes on installing the evaluation version of LANtastic
   for Windows 95/98 or LANtastic for Windows NT
----------------------------------------------------------
LANtastic for Windows 95/98 and LANtastic for Windows NT 
can be installed as evaluation versions or as full versions,
depending on whether you enter a valid Serial Number and
Verification Key during Setup.

If you enter a valid LANtastic Serial Number and Verification
Key, Setup will install the full version of the software.
However, if you do not enter a valid Serial Number and
Verification Key, Setup will install the evaluation version
of the software, which will expire 45 days from the date of
installation.


Limitations of the LANtastic 8.0 evaluation versions
----------------------------------------------------
 - With the evaluation version of LANtastic, you are
   limited to installing on three or fewer computers.

 - The evaluation software will expire 45 days from the
   date of installation.


Upgrading from the evaluation version to the full version
---------------------------------------------------------
If you downloaded the evaluation version of LANtastic for 
Windows 95/98 or Windows NT, and you want to upgrade it to
the full version, you must first contact your Artisoft
dealer or reseller, or the Artisoft Direct Team. The
Artisoft representative will assist you in the purchase
of a full-version Serial Number and Verification Key.

Instructions for contacting Artisoft appear in the Directory
of Support Services, which can be downloaded from Artisoft's
web site at www.artisoft.com.

If you already purchased LANtastic 8.0, but choose to install
the evaluation version, you can upgrade to the full version
by using the LANtastic 8.0 Serial Number and Verification
key that you received with the product.

To perform the upgrade:

 1. Go to a computer that you want to upgrade. 

 2. Click Start, Programs, LANtastic, Upgrade LANtastic.
    The LANtastic Upgrade Utility window appears.

 3. Type in your full-version Serial Number and
    Verification Key.

    NOTE: LANtastic for Windows 95/98 requires that you
    Browse to, or type in, the path to the file ATILA.VPE.
    The path is: \WINDOWS\SYSTEM\ATILA.VPE.
   
 4. Click Finish.

 5. Restart the computer.

 6. Repeat the above steps on each computer that you
    want to upgrade.


-------------------
2. Running LNET.EXE
-------------------
If you run the DOS-based LNET program, the LNET Main
Functions screen will always appear even if your LANtastic
network is not running or is running but not functioning
correctly. 

This is because LNET.EXE does not detect the absence of the 
required file VDM2VDD.DOS. LNET.EXE will load (but will not 
function) even if VDM2VDD.DOS has been commented out of the 
CONFIG.NT file or deleted from the computer.

If you want to use LNET to check that LANtastic is running 
correctly, at the Main Functions screen select the Login or 
Logout option and press Enter. If there are no entries in
the Connect to Computer list and you know there are active
servers broadcasting their names on the network, there
may be a problem with your network.


-------------------------------------------------------
3. Using LNET.EXE to control a LANtastic for DOS server
-------------------------------------------------------
To use LNET to control a LANtastic for DOS server, you
must do ONE of the following:

 - Log in to the computer you want to control using an
   account that has the "A" (Super ACL) privilege.

   Or

 - Make sure that the @SCREEN resource on the computer
   you want to control has at least the following three
   privileges: "R" (Read Access), "W" (Write Access), and
   "L" (Allow File Lookups).


--------------------------------------------------------------
5. Removing remembered connections when uninstalling LANtastic
   for Windows 95/98 or LANtastic for Windows NT
--------------------------------------------------------------
Remembered connections (those that reconnect automatically
each time you start your computer) are not disabled when you
uninstall LANtastic. Therefore, Windows 95/98 or NT will
continue trying to make these connections for you even though
they are no longer valid. To avoid this, break all remembered
connections BEFORE you perform the uninstall, or:

 - At bootup, click No when asked if you want to try
   reconnecting to [servername] the next time you start
   your computer.

 - In Windows Explorer or My Computer, right-click each
   connection that has a red "X", then click disconnect.

-----------------------------------------------------
6. Artisoft Eval software: ModemShare 32, i.Share 3.0
   and XtraMail 1.11
-----------------------------------------------------
The copies of ModemShare 32 and i.Share 3.0 that are on
the LANtastic 8.0 CD-ROM are evaluation versions that will
expire 30 days after installation.

The copy of XtraMail 1.11 on the LANtastic 8.0 CD-ROM is
also an evaluation version, however it will expire 60 days
installation.

If you would like to have the full versions of these products,
contact the Artisoft Direct Team to purchase full-version
Serial Numbers and Verification Keys.

Instructions for contacting the Artisoft Direct Team appear on
the Directory of Support Services that you received with this
product.


============================================================
III. LANtastic for Windows NT only
============================================================

------------------------------------------
1. Specifying a network installation drive
------------------------------------------
The LANtastic 8.0 for Windows NT Setup program will let you
select a network installation drive as your destination drive.
However, if you do so, you will receive an error message
stating that you cannot install to a network drive.

To avoid this problem, select only local drives for
installation.


----------------------------------------------------
2.  Artisoft LANtastic NetBIOS, LANtastic Client and
    LANtastic Server properties
----------------------------------------------------
The Artisoft LANtastic NetBIOS, LANtastic Client and
LANtastic Server entries in the Network Properties
window show the "Properties" and Update" options as
being enabled, although neither option is functional.


-------------------------------------------------------
3.  Using ArcNet adapters with LANtastic for Windows NT
    and the Artisoft LANtastic NetBIOS protocol
-------------------------------------------------------
When an ArcNet adapter is installed and bound to the
Artisoft LANtastic NetBIOS protocol (AILANBIO), any
attempts to connect to other computers with the same
configuration result in the error:

  "Cannot Locate Network Name".

To allow the computers to communicate, the LANtastic for
Windows NT Client and Server must be bound to the NetBEUI
protocol. 

NOTE: All LANtastic computers on the network that are using 
      an ArcNet adapter should use NetBEUI.


---------------------------------------------
4. Installing applications across the network
---------------------------------------------
In order to install some applications, such as Office 95
and Office 97, FROM a network client computer TO a
LANtastic server, you must perform the following steps:

 1. Select the application's Custom Installation option.

 2. Clear the Fast Find checkbox -- DO NOT install Fast
    Find at this time.
    
 3. Finish the installation according to the application's
    instructions.

    NOTE: If you want to use the application's Fast Find
    option, you can perform a second Custom Installation
    and select only the Fast Find option at that time.

Failure to follow the above steps may result in an
incomplete or aborted installation. Note that even if the
installation appears to have completed successfully, the
application still may not run properly.

Alternatively, you can avoid this problem by installing
applications locally on the client computers. Or, in the
case of network versions of applications, install them
on the server according to the network-installation
guidelines that came with each application.

Applications installed on the server can then be accessed
and run from network client computers.


--------------------------------
5.  Installation directory error
--------------------------------
The LANtastic 8.0 for Windows NT Setup will fail if it
finds a file with the same name as the target installation
directory.

If such a file exists, you will receive the following
error message: "Unable to create directory under 
c:\[target directory]\winnt\LDB_Data".

To avoid this error, rename the file or move it to
another location, then retry the installation.


---------------------------
6. Deleting mail using LNET
---------------------------
You cannot delete LANtastic Mail messages using LNET.EXE
from a small DOS window. Any attempts to do so will result
in the error "An error has occurred, press ESC to continue."

To avoid this problem, maximize the DOS window to full-screen
by pressing ESC then ALT+RETURN. You can now delete mail
messages.


------------------------------------------------
7. Increasing the number of allowable open files
------------------------------------------------
Computers with only 16MB of RAM installed will be limited
to 3500 open files, even though LANtastic for Windows NT
permits up to 5000 open files.

To avoid this limitation, make sure that the computer
has at least 32MB of RAM installed.


----------------------------------------------
8. Improper translation of extended characters
----------------------------------------------
When a pop-up message is received from a computer with
extended characters in its name, the computer name will
appear incorrectly in the message. Because of this, a
response will never reach the originator because the
computer name is wrong.

To avoid this, do not use extended characters in computer
names.


--------------------------------------------------
9. Improper display of drives under LNET32.EXE and
   LNET.EXE
--------------------------------------------------
LNET32.EXE displays all removable media (Zip drives,
Bernoulli drives, etc.) as FLOPPY under Assign Drives,
My Computer. These devices should be displayed as
Removable Media Drives.

LNET.EXE does not show that a local CD-ROM drive is using
a drive letter. (Floppy drives and hard drives display
properly.) Note that you can redirect the drive letter
assigned to the CD-ROM, however, by doing so you will
lose access to the CD-ROM as long as the redirection is
in effect.


-----------------------
10. LNET STRING command
-----------------------
The LNET STRING command does not function under LANtastic
for Windows NT.


------------------------------------------------------
11. Choosing LANtastic Sharing from a printer object's
    Properties menu
------------------------------------------------------
When the Properties window appears, the General tab is
displayed. Click the LANtastic Sharing tab to bring it
to the foreground.


-----------------------------------------------------
12. Configuring a NodeRunner Pro adapter for use with
    LANtastic 8.0 for Windows NT
-----------------------------------------------------
In setting up a NodeRunner Pro adapter, make sure to select
the Intel EtherExpress Pro 10+ ISA adapter driver. This
will allow you to configure the adapter through the Windows
NT Driver Configuration Screen.

NOTE: You must have access to the Windows NT CD-ROM in order
      to add this driver.


-------------------------------------------------
13. Configuring a NodeRunner adapter for use with
    LANtastic for Windows NT
-------------------------------------------------
Because Windows NT cannot directly access hardware, you
must configure your network adapter in DOS.

To do so, boot to a prior version of DOS (if your system is
using FAT), or create a DOS boot disk from a DOS computer,
then boot off the DOS diskette.

Once you are in DOS:

 1. Run NRSETUP from the \SUPPORT directory on the LANtastic 8.0
    CD-ROM.

 2. Use NRSETUP to configure the adapter for NE2000 mode
    and set the I/O Base and IRQ. Make sure to select an
    I/O Base and IRQ that do not conflict with the settings
    in use by other devices.

 3. If the adapter is installed in a Pentium computer, use
    NRSETUP to configure the adapter to change IOCS16 timing
    from NORMAL to EARLY.

-------------------------------------------
14. Logging in to a computer using LNET.EXE 
-------------------------------------------
When logging in to a computer with a command such as:

 lnet login/wait \\server ?"Username: " ^"Password: "

the password is echoed on the screen instead of being
encrypted and displayed as a series of diamonds.

Instead, use the pound sign (#) instead of the carat
symbol (^) in this type of command.

In Windows NT, the ^ is a reserved character. Therefore,
LANtastic for Windows NT cannot use the ^ in the LNET
command line.


============================================================
IV. LANtastic for Windows 95/98 only 
============================================================

-------------------------------------------------------
Troubleshooting LANtastic for Windows 95/98 immediately 
after installation
-------------------------------------------------------
If you want to use the Microsoft Client to connect to 
Microsoft servers or use the IPX/SPX-compatible protocol to
connect to NetWare servers at the same time that you're 
running LANtastic for Windows 95/98, you'll need to turn off 
multicast addressing on each LANtastic computer on your 
network.

On computers running LANtastic v5.x or 6.x, you'll need to
do this by editing STARTNET.BAT. Find the AILANBIO command
line and add the /NO_MULTICAST switch to the end of it.
For example:

   AILANBIO /NO_MULTICAST

Save your changes and restart your computer.

NOTE: It is strongly recommended that you upgrade any
      computers running a version of LANtastic older
      than 7.0, to LANtastic 8.0.


To turn off multicast addressing in your computers running 
LANtastic for Windows 95/98:

 1. Right-click the Network Neighborhood icon on your
    desktop, then click Properties. The Network dialog box
    appears.

 2. Double-click Artisoft LANtastic NetBIOS on the
    Configuration page, then click the Advanced tab. A screen
    listing properties and values appears.

 3. Click Multicast, then scroll through the Values drop-down 
    list box and select Off.

 4. Click OK to return to the Network dialog box.

 5. Click OK and click Yes to restart your computer. Repeat 
    these steps on each Windows 95/98 computer.


============================================================
V. LANtastic for DOS only
============================================================

---------------------------
Running the INSTALL program
---------------------------

To run the DOS INSTALL program, you must change directories
to the root of the CD-ROM or installation diskette. For 
example, assuming you are starting at the C: prompt and that
D: is the letter of your CD-ROM drive, the command line would
appear as follows:

C:\> CD D: <Enter>

D:\> INSTALL



---------------
- END OF FILE -
