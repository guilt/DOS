=================================
C Runtime Library Startup Sources
=================================

The directory \startup and its subdirectories contain the files
necessary for building the startup portion of the C runtime library.
The \startup directory contains the startup source files, the include
files, the batch file, and the make files used to build the startup
object files.  The subdirectories of \startup contain OS specific
sources.

The startup object files can be built by invoking cstartup.bat (DOS/WIN)
from within the \startup directory.  This batch file assumes the following:

      * Nmake.exe, link.exe, the C compiler, and the assembler must
	be in the execution path.  MASM 6.0 and C 7.0 or later are
	required to build the startup sources.

      * Environment variable INCLUDE must be set to the directory that
	contains your C include files.

      * Environment variable LIB must be set to the directory that
	contains your C library files.	The library files for your OS
	target must exist in that directory (e.g., ?libcer.lib for DOS,
	?libcewq.lib for WIN, etc.).

      * For WIN, libw.lib must be in the directory specified by the LIB
	environment variable and windows.h must be in the directory specified
	by the INCLUDE environment variable.

Cstartup will create memory model specific subdirectories and place the
appropriate object files there.  Under each memory model subdirectory,
cstartup creates additional subdirectories where OS specific objects reside.

	OBJ Directories 	Contents
	--------------- 	--------

        S, M, C, L              Small, medium, compact, large model
                                directories which contain OS specifc
                                objects

        S/DOS, M/DOS, etc.      MS-DOS startup objects

        S/WIN, M/WIN, etc.      Windows EXE startup objects

        S/DLL, M/DLL, etc.      Windows DLL startup objects

The message "<cEnd - nogen>" is generated when some of the assembly language 
source files are assembled.  This message is expected and is totally benign.


Running C Startup
-----------------

Use the cstartup batch file to build the various C runtime startup objects.
The cstartup batch file allows you to select various combinations of
OS platforms and models.  The interface is:

	Usage:	cstartup [?] [os] [models]

		[?] displays this help message.

		[os] is an optional list of one or more OS designators
		seperated by spaces (DOS, WIN); default is all.

		[model] is an optional list of memory model designators
		seperated by spaces (S, M, C, L); default is all.

Examples:

	cstartup dos s		/* build small model DOS objects */

	cstartup win s l	/* build small and large model WIN objects */

	cstartup		/* build all startup objects */

	cstartup ?		/*** display a help message ***/


[Note:	You may need to delete old objects from previous startup builds
if you alter build options, startup sources, etc.]


Startup Files
-------------

The following files are contained in the \startup directory:

Startup source files:

	CHKSTK.ASM
	CHKSUM.ASM
	CRT0FP.ASM
	FILE.ASM
	FMSGHDR.ASM
	RCHKSTK.ASM
	SETARGV.ASM
	WILD.C
	_FILE.C

	DOS\CRT0.ASM
	DOS\CRT0DAT.ASM
	DOS\CRT0MSG.ASM
	DOS\EXECMSG.ASM
	DOS\NMSGHDR.ASM
	DOS\STDALLOC.ASM
	DOS\STDARGV.ASM
	DOS\STDENVP.ASM

	WIN\CRT0.ASM
	WIN\FATAL.ASM
	WIN\NOQWIN.ASM
	WIN\QWCINIT.ASM
	WIN\STUBMAIN.ASM
	WIN\STUBWEP.ASM
	WIN\WCHKSTK.ASM
	WIN\WEP.ASM
	WIN\WFILE.ASM
	WIN\WINDGRP.ASM
	WIN\WINDGRPX.C
	WIN\WNULL.ASM

Include files:

	CMACROS.INC
	CMSGS.INC
	DEFSEGS.INC
	FCNTL.INC
	HEAP.INC
	MSDOS.INC
	RTERR.INC
	STDLIB.INC
	STDIO.INC
	VERSION.INC

	FILE2.H
	INTERNAL.H
	MSDOS.H
	REGISTER.H

Build files:

	CSTARTUP.BAT	;builds objs and links null program on DOS and WIN
	CSUB.BAT	;(used by cstartup)

	MAKEFILE.DOS	;makefile used in DOS build
	MAKEFILE.WIN	;makefile used in WIN build
	WINDLL.MKF	;makefile used in WIN DLL build
	WINEXE.MKF	;makefile used in WIN EXE build

	NULBODY.C	;null C program
	DOS\NULBODY.LNK ;DOS link script for null program
	WIN\NULBODY.DEF ;WIN def file for null program
	WIN\NULBODY.LNK ;WIN link script for null program

Documentation:

	README.TXT	;information about \startup directory structure
			;and contents

[Note:	Startup sources written in assembly language have been edited with
tab stops set to 8.  Startup sources written in C have been edited with
tab stops set to 4.]


Placing the Stack outside of DGROUP
-----------------------------------

If your program requires a large amount of stack space, the run time
library can be configured to place the stack in a seperate segment
outside of DGROUP.  By doing this, the stack can be up to 64K in size
without reducing the amount of storage available in DGROUP for near
data.  In order to do this your program must be either compact, large,
or huge model.	You must also direct the compiler to assume that
that SS != DS.	Thus, your memory model specification should be -ACw,
-ALw, or -AHw.	See the compiler documentation for more information
about these options.

To use a far stack, you must assemble the startup sources provided
with C 7.0.  In the startup sources directory is a file called "makefile.dos"
which controls the startup module build process for the run time library.
To enable a far stack, you need to edit the makefile.  Near the top of
the file are two lines which begin "CFLAGS=" and "ASMFLAGS=".  You should
add the text " -DFARSTACK" to the end of these two lines.  Then build
the startup modules according to instructions given previously in this
file.  You should then use the LIB utility to replace the startup modules
in your library with the new modules you have built.  When linking, the
size of the stack can be controlled with the /STACK command line option.

If you are creating DOS programs, the size of your .EXE file will be
increased by the size of your stack.  This is a consequence of the DOS
.EXE format.  To reduce the size of your .EXE file, link with the
/EXEPACK option.

[Note:	The far stack option is not supported in the Windows
startup files.]


				--- End ---
