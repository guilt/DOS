
 1. About

 These files are intended to make HX DOS extender work with Open Watcom (OW).
 They have been tested with OW V1.3 - V1.7.


 2. Installation

 a). Installing HX's Support for OW

 - copy file HX.LNK to \WATCOM\BINW. Then open file 
   \WATCOM\BINW\WLSYSTEM.LNK with an editor and add this line:

   @%watcom%\binw\hx.lnk

   After the modification WLINK will know "system hxnt", "system hxdos"
   and "system hxnts". However, you will have to ensure that the HX stubs 
   (files DPMIST32.BIN and LOADPE.BIN) can be found by WLINK, the easiest
   way to achieve this is to copy these files to the WATCOM\BINW directory.

   The modifications may be omitted if you want to create native Win32
   console applications only, then feed WLINK with "system nt" and install
   HXLdr32 in native DOS to run the binaries.

 - copy files DOS\*.* to \WATCOM\LIB386\DOS.
   This step is required only if "system hxdos" is to be used.

 - copy files NT\*.* to \WATCOM\LIB386\NT.
   This step is required only if "system hxnts" is to be used.

 - copy files WDSUPP\*.* to \WATCOM\BINW.
   This step is required only if the OW debugger WD is to be used with
   the HX debugger trap file.


 b). Installing OW's Debugger WD/WDW

 ---------------------------------------------------------------------------
 Please note: since OW 1.5 the zip files described below are no longer
 available for download on the OW site.
 However, one might still get selective files from                                    
 http://www.ibiblio.org/pub/micro/pc-stuff/freedos/files/devel/c/openwatcom
 ---------------------------------------------------------------------------

 If you don't have OW installed and just want to use OW's debugger WD with
 HX, this can be done.

 Download all files beginning with "cm_dbg_". This will be a download
 of about 4-5 MB, but possibly may be further reduced because:

 - "cm_dbg_os2.zip" is only required when running the debugger on OS/2
 - "cm_dbg_win.zip" is only required when running the debugger on win3x
 - "cm_dbg_nt.zip" is only required when the windowed debugger WDW.EXE is
        to be used on Win32 platforms (win9x/ME/NT/2k/XP).
 - "cm_dbg_net.zip" is only required for Novell Netware

 Copy all files in a directory, say C:\WATCOM und unpack them. Then to debug
 with WD (DOS debugger), add C:\WATCOM\BINW to the PATH variable. To Debug
 with WDW/WD (Win32 debugger version), add C:\WATCOM\BINNT;C:\WATCOM\BINW to
 PATH.

 Debugging under Windows 9x/3x requires an additional step, WDEBUG.386 has to
 be added to system.ini to make winserv.exe work. Add a line 
 "device=c:\watcom\binw\wdebug.386" to the [386Enh] section of system.ini.


 3. Compiling and Linking

 These are the options how to create HX binaries with OW:

 a) use wlink option "system nt": this will create a normal Win32 console
    application. To run it in native DOS install HXLdr32. To create a dll
    use "system nt_dll".

 b) use wlink option "system hxnt": this will create a Win32 console
    application as well, with the one difference that wlink will add
    stub DPMIST32.BIN. HXLdr32 is not needed to run such binaries in
    native DOS. 

 c) use wlink option "system hxdos": this will create a 32bit DOS-extended
    binary in PE format. Wlink will add OW's CRT object modules for DOS
    extenders. To run the binary, a DPMI host is required, but no other
    external modules. HX's simplified PE loader (LOADPE.BIN) is added as
    MZ stub. It will load HDPMI32 if no DPMI host is installed.
     After the link step HX's PatchPE tool has to be applied to the binary.
    This is to ensure that is is not loaded as a Win32 process if launched
    in a Windows DOS box. 

 d) use wlink option "system hxnts": this will create a 32bit DOS-extended
    binary in PE format. The difference to "system hxdos" is that OW's CRT
    object modules for Win32 are used in the link step and the HX Win32 
    emulation is linked statically to the binary.
     Binaries linked with "system hxnts" are larger than those linked with
    "system hxdos" (35-45 kB), but they can use Win32 features and support
    for LFNs is included.
     Please note that old WLINK versions had a bug which made them display
    error "dynamic memory exhausted" when using the static HX Win32 COFF 
    libraries. This is true for all WLINK versions <= v1.7.

 As a reference view the following Makefiles in directory Samples:

 Location              Tools           Binary type
 ---------------------------------------------------------
 OW1\SampleD.MAK       WCC386, WLINK   DOS PE
 OW1\SampleW.MAK       WCC386, WLINK   Win32 PE
 OW1\SampleWS.MAK      WCC386, WLINK   DOS PE with static Win32 
 OW2\SampleD.MAK       WCC386, WLINK   DOS PE
 OW2\SampleW.MAK       WCC386, WLINK   Win32 PE
 OW3\SampleD.MAK       WCC386, WLINK   DOS PE
 OW3\SampleW.MAK       WCC386, WLINK   Win32 PE
 OW4\SampleW.MAK       WCC386, WLINK   Win32 PE
 OW4\SampleWS.MAK      WCC386, WLINK   DOS PE with static Win32
 Masm1\Sample1W.MAK    WASM, WLINK     DOS PE
 Hello\HelloW.MAK      WASM, MS LINK   DOS 32-bit MZ

 Please note: in previous versions "system hxnt" was "system hx" and 
 "system hxdos" was "system hxraw".
 

 4. Debugging

 The trap helper file HXHELP.EXE requires the HX runtime binaries
 DPMILD32.EXE and - in DOS - HDPMI32.EXE to run. So to prepare for debugging
 either make sure the HX runtime binaries are located in a directory included
 in the PATH environment variable or copy DPMILD32.EXE and HDPMI32.EXE to
 \WATCOM\BINW.

 Then enter

 in *plain* DOS: WD /TR=HX sample1.exe

 in win9x/ME:    1. DOS box: winserv /TR=HX
                 2. DOS box: WD /TR=WIN sample1.exe

 in winnt/2k/xp: 1. DOS box: vdmserv /TR=HX
                 2. DOS box: WD|WDW /TR=VDM sample1.exe  

 To locally debug graphics applications in DOS option /SWAP must also be set.
 See the Open Watcom debugger help for more details.

 The HX trap files should enable WD to debug any DOS real-mode or 32bit DPMI
 application, they are not restricted to HX binaries. However, if a 32bit
 DPMI application is to be debugged in plain DOS, it must be ensured that it
 will use the currently installed DPMI host and doesn't use its own one.

 Debugging on source code level will only work for binary formats supported
 by HX, that is: PE, NE and MZ. But although WD understands the codeview
 debugging format it will most likely not understand the debugging info
 of MS COFF linkers. Then Open Watcom's WLINK should be used for the link
 step.

 WD isn't designed for mixed-mode debugging, so once an application has
 switched to protected mode, it shouldn't be stopped in real-mode. Doing
 this may confuse WD, although it works in most cases.

 Some additional support has been added for DJGPP binaries, because older
 versions of DJGPP contained a bug which is also a good debugger trap.
 So the HX trap files check if a DJGPP binary is to be debugged and will
 *not* stop at the real-mode entry but continue until the debuggee has 
 switched to a stack with HIWORD(esp) != 0. Regretably WD doesn't understand
 the DJGPP debug info, so such binaries can only be debugged at assembly
 level.

 FreeDOS note: debugging DOS-extended applications with WD on FreeDOS
 doesn't seem to work, at least with current versions of FreeDOS! You will
 need to use MS-DOS or DR-DOS instead.


 5. Creating a new CSTRTDHX.OBJ

 The file CSTRTDHX.OBJ is a slightly modified OW C startup code
 (CSTRT386.ASM), which is not included here to avoid copyright violations.

 If you are experienced and want to create a CSTRTDHX.ASM from the source
 supplied with OW, use the file CSTRTDHX.DIF to patch CSTRT386.ASM (usually
 found in WATCOM\BLD\CLIB\STARTUP\A), assemble it and finally copy it to 
 \WATCOM\LIB386\DOS as CSTRTDHX.OBJ.


 6. Content of HXOW.LIB
 
 HXOW.LIB contains modified modules:
 
 - SPAWN386.ASM: int 21h, ax=4B00h, exec parameter block changed from
   DOS4/G to HX compatible style.


 Japheth

