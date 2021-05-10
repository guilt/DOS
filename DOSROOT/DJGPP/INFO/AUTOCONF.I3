This is Info file autoconf.info, produced by Makeinfo version 1.68 from
the input file autoconf.tex.

START-INFO-DIR-ENTRY
* Autoconf: (autoconf).         Create source code configuration scripts.
END-INFO-DIR-ENTRY

   Autoconf: Creating Automatic Configuration Scripts, by David
MacKenzie.

   This file documents the GNU Autoconf package for creating scripts to
configure source code packages using templates and an `m4' macro
package.

   Copyright (C) 1992, 1993, 1994, 1995, 1996, 1998 Free Software
Foundation, Inc.

   Permission is granted to make and distribute verbatim copies of this
manual provided the copyright notice and this permission notice are
preserved on all copies.

   Permission is granted to copy and distribute modified versions of
this manual under the conditions for verbatim copying, provided that
the entire resulting derived work is distributed under the terms of a
permission notice identical to this one.

   Permission is granted to copy and distribute translations of this
manual into another language, under the above conditions for modified
versions, except that this permission notice may be stated in a
translation approved by the Foundation.


File: autoconf.info,  Node: C Compiler Characteristics,  Next: Fortran 77 Compiler Characteristics,  Prev: Typedefs,  Up: Existing Tests

C Compiler Characteristics
==========================

   The following macros check for C compiler or machine architecture
features.  To check for characteristics not listed here, use
`AC_TRY_COMPILE' (*note Examining Syntax::.) or `AC_TRY_RUN' (*note Run
Time::.)

 - Macro: AC_C_BIGENDIAN
     If words are stored with the most significant byte first (like
     Motorola and SPARC, but not Intel and VAX, CPUs), define
     `WORDS_BIGENDIAN'.

 - Macro: AC_C_CONST
     If the C compiler does not fully support the keyword `const',
     define `const' to be empty.  Some C compilers that do not define
     `__STDC__' do support `const'; some compilers that define
     `__STDC__' do not completely support `const'.  Programs can simply
     use `const' as if every C compiler supported it; for those that
     don't, the `Makefile' or configuration header file will define it
     as empty.

 - Macro: AC_C_INLINE
     If the C compiler supports the keyword `inline', do nothing.
     Otherwise define `inline' to `__inline__' or `__inline' if it
     accepts one of those, otherwise define `inline' to be empty.

 - Macro: AC_C_CHAR_UNSIGNED
     If the C type `char' is unsigned, define `__CHAR_UNSIGNED__',
     unless the C compiler predefines it.

 - Macro: AC_C_LONG_DOUBLE
     If the C compiler supports the `long double' type, define
     `HAVE_LONG_DOUBLE'.  Some C compilers that do not define
     `__STDC__' do support the `long double' type; some compilers that
     define `__STDC__' do not support `long double'.

 - Macro: AC_C_STRINGIZE
     If the C preprocessor supports the stringizing operator, define
     `HAVE_STRINGIZE'.  The stringizing operator is `#' and is found in
     macros such as this:

          #define x(y) #y

 - Macro: AC_CHECK_SIZEOF (TYPE [, CROSS-SIZE])
     Define `SIZEOF_UCTYPE' to be the size in bytes of the C (or C++)
     builtin type TYPE, e.g. `int' or `char *'.  If `type' is unknown
     to the compiler, it gets a size of 0.  UCTYPE is TYPE, with
     lowercase converted to uppercase, spaces changed to underscores,
     and asterisks changed to `P'.  If cross-compiling, the value
     CROSS-SIZE is used if given, otherwise `configure' exits with an
     error message.

     For example, the call
          AC_CHECK_SIZEOF(int *)

     defines `SIZEOF_INT_P' to be 8 on DEC Alpha AXP systems.

 - Macro: AC_INT_16_BITS
     If the C type `int' is 16 bits wide, define `INT_16_BITS'.  This
     macro is obsolete; it is more general to use
     `AC_CHECK_SIZEOF(int)' instead.

 - Macro: AC_LONG_64_BITS
     If the C type `long int' is 64 bits wide, define `LONG_64_BITS'.
     This macro is obsolete; it is more general to use
     `AC_CHECK_SIZEOF(long)' instead.


File: autoconf.info,  Node: Fortran 77 Compiler Characteristics,  Next: System Services,  Prev: C Compiler Characteristics,  Up: Existing Tests

Fortran 77 Compiler Characteristics
===================================

   The following macros check for Fortran 77 compiler characteristics.
To check for characteristics not listed here, use `AC_TRY_COMPILE'
(*note Examining Syntax::.) or `AC_TRY_RUN' (*note Run Time::.), making
sure to first set the current lanuage to Fortran 77 `AC_LANG_FORTRAN77'
(*note Language Choice::.).

 - Macro: AC_F77_LIBRARY_LDFLAGS
     Determine the linker flags (e.g. `-L' and `-l') for the "Fortran
     77 intrinsic and run-time libraries" that are required to
     successfully link a Fortran 77 program or shared library.  The
     output variable `FLIBS' is set to these flags.

     This macro is intended to be used in those situations when it is
     necessary to mix, e.g. C++ and Fortran 77 source code into a single
     program or shared library (*note Mixing Fortran 77 With C and C++:
     (automake)Mixing Fortran 77 With C and C++.).

     For example, if object files from a C++ and Fortran 77 compiler
     must be linked together, then the C++ compiler/linker must be used
     for linking (since special C++-ish things need to happen at link
     time like calling global constructors, instantiating templates,
     enabling exception support, etc.).

     However, the Fortran 77 intrinsic and run-time libraries must be
     linked in as well, but the C++ compiler/linker doesn't know by
     default how to add these Fortran 77 libraries.  Hence, the macro
     `AC_F77_LIBRARY_LDFLAGS' was created to determine these Fortran 77
     libraries.


File: autoconf.info,  Node: System Services,  Next: UNIX Variants,  Prev: Fortran 77 Compiler Characteristics,  Up: Existing Tests

System Services
===============

   The following macros check for operating system services or
capabilities.

 - Macro: AC_CYGWIN
     Checks for the Cygwin environment.  If present, sets shell variable
     `CYGWIN' to `yes'.  If not present, sets `CYGWIN' to the empty
     string.

 - Macro: AC_EXEEXT
     Defines substitute variable `EXEEXT' based on the output of the
     compiler, after .c, .o, and .obj files have been excluded.
     Typically set to empty string if Unix, `.exe' or `.EXE' if Win32.

 - Macro: AC_OBJEXT
     Defines substitute variable `OBJEXT' based on the output of the
     compiler, after .c files have been excluded.  Typically set to
     `.o' if Unix, `.obj' if Win32.

 - Macro: AC_MINGW32
     Checks for the MingW32 compiler environment.  If present, sets
     shell variable `MINGW32' to `yes'.  If not present, sets `MINGW32'
     to the empty string.

 - Macro: AC_PATH_X
     Try to locate the X Window System include files and libraries.  If
     the user gave the command line options `--x-includes=DIR' and
     `--x-libraries=DIR', use those directories.  If either or both
     were not given, get the missing values by running `xmkmf' on a
     trivial `Imakefile' and examining the `Makefile' that it produces.
     If that fails (such as if `xmkmf' is not present), look for them
     in several directories where they often reside.  If either method
     is successful, set the shell variables `x_includes' and
     `x_libraries' to their locations, unless they are in directories
     the compiler searches by default.

     If both methods fail, or the user gave the command line option
     `--without-x', set the shell variable `no_x' to `yes'; otherwise
     set it to the empty string.

 - Macro: AC_PATH_XTRA
     An enhanced version of `AC_PATH_X'.  It adds the C compiler flags
     that X needs to output variable `X_CFLAGS', and the X linker flags
     to `X_LIBS'.  If X is not available, adds `-DX_DISPLAY_MISSING' to
     `X_CFLAGS'.

     This macro also checks for special libraries that some systems
     need in order to compile X programs.  It adds any that the system
     needs to output variable `X_EXTRA_LIBS'.  And it checks for
     special X11R6 libraries that need to be linked with before
     `-lX11', and adds any found to the output variable `X_PRE_LIBS'.


 - Macro: AC_SYS_INTERPRETER
     Check whether the system supports starting scripts with a line of
     the form `#! /bin/csh' to select the interpreter to use for the
     script.  After running this macro, shell code in `configure.in'
     can check the shell variable `interpval'; it will be set to `yes'
     if the system supports `#!', `no' if not.

 - Macro: AC_SYS_LONG_FILE_NAMES
     If the system supports file names longer than 14 characters, define
     `HAVE_LONG_FILE_NAMES'.

 - Macro: AC_SYS_RESTARTABLE_SYSCALLS
     If the system automatically restarts a system call that is
     interrupted by a signal, define `HAVE_RESTARTABLE_SYSCALLS'.


File: autoconf.info,  Node: UNIX Variants,  Prev: System Services,  Up: Existing Tests

UNIX Variants
=============

   The following macros check for certain operating systems that need
special treatment for some programs, due to exceptional oddities in
their header files or libraries.  These macros are warts; they will be
replaced by a more systematic approach, based on the functions they make
available or the environments they provide.

 - Macro: AC_AIX
     If on AIX, define `_ALL_SOURCE'.  Allows the use of some BSD
     functions.  Should be called before any macros that run the C
     compiler.

 - Macro: AC_DYNIX_SEQ
     If on Dynix/PTX (Sequent UNIX), add `-lseq' to output variable
     `LIBS'.  This macro is obsolete; instead, use `AC_FUNC_GETMNTENT'.

 - Macro: AC_IRIX_SUN
     If on IRIX (Silicon Graphics UNIX), add `-lsun' to output variable
     `LIBS'.  This macro is obsolete.  If you were using it to get
     `getmntent', use `AC_FUNC_GETMNTENT' instead.  If you used it for
     the NIS versions of the password and group functions, use
     `AC_CHECK_LIB(sun, getpwnam)'.

 - Macro: AC_ISC_POSIX
     If on a POSIXized ISC UNIX, define `_POSIX_SOURCE' and add
     `-posix' (for the GNU C compiler) or `-Xp' (for other C compilers)
     to output variable `CC'.  This allows the use of POSIX facilities.
     Must be called after `AC_PROG_CC' and before any other macros
     that run the C compiler.

 - Macro: AC_MINIX
     If on Minix, define `_MINIX' and `_POSIX_SOURCE' and define
     `_POSIX_1_SOURCE' to be 2.  This allows the use of POSIX
     facilities.  Should be called before any macros that run the C
     compiler.

 - Macro: AC_SCO_INTL
     If on SCO UNIX, add `-lintl' to output variable `LIBS'.  This
     macro is obsolete; instead, use `AC_FUNC_STRFTIME'.

 - Macro: AC_XENIX_DIR
     If on Xenix, add `-lx' to output variable `LIBS'.  Also, if
     `dirent.h' is being used, add `-ldir' to `LIBS'.  This macro is
     obsolete; use `AC_HEADER_DIRENT' instead.


File: autoconf.info,  Node: Writing Tests,  Next: Results,  Prev: Existing Tests,  Up: Top

Writing Tests
*************

   If the existing feature tests don't do something you need, you have
to write new ones.  These macros are the building blocks.  They provide
ways for other macros to check whether various kinds of features are
available and report the results.

   This chapter contains some suggestions and some of the reasons why
the existing tests are written the way they are.  You can also learn a
lot about how to write Autoconf tests by looking at the existing ones.
If something goes wrong in one or more of the Autoconf tests, this
information can help you understand the assumptions behind them, which
might help you figure out how to best solve the problem.

   These macros check the output of the C compiler system.  They do not
cache the results of their tests for future use (*note Caching
Results::.), because they don't know enough about the information they
are checking for to generate a cache variable name.  They also do not
print any messages, for the same reason.  The checks for particular
kinds of C features call these macros and do cache their results and
print messages about what they're checking for.

   When you write a feature test that could be applicable to more than
one software package, the best thing to do is encapsulate it in a new
macro.  *Note Writing Macros::, for how to do that.

* Menu:

* Examining Declarations::      Detecting header files and declarations.
* Examining Syntax::            Detecting language syntax features.
* Examining Libraries::         Detecting functions and global variables.
* Run Time::                    Testing for run-time features.
* Portable Shell::              Shell script portability pitfalls.
* Testing Values and Files::    Checking strings and files.
* Multiple Cases::              Tests for several possible values.
* Language Choice::             Selecting which language to use for testing.


File: autoconf.info,  Node: Examining Declarations,  Next: Examining Syntax,  Prev: Writing Tests,  Up: Writing Tests

Examining Declarations
======================

   The macro `AC_TRY_CPP' is used to check whether particular header
files exist.  You can check for one at a time, or more than one if you
need several header files to all exist for some purpose.

 - Macro: AC_TRY_CPP (INCLUDES, [ACTION-IF-TRUE [, ACTION-IF-FALSE]])
     INCLUDES is C or C++ `#include' statements and declarations, on
     which shell variable, backquote, and backslash substitutions are
     performed.  (Actually, it can be any C program, but other
     statements are probably not useful.)  If the preprocessor produces
     no error messages while processing it, run shell commands
     ACTION-IF-TRUE.  Otherwise run shell commands ACTION-IF-FALSE.

     This macro uses `CPPFLAGS', but not `CFLAGS', because `-g', `-O',
     etc. are not valid options to many C preprocessors.

   Here is how to find out whether a header file contains a particular
declaration, such as a typedef, a structure, a structure member, or a
function.  Use `AC_EGREP_HEADER' instead of running `grep' directly on
the header file; on some systems the symbol might be defined in another
header file that the file you are checking `#include's.

 - Macro: AC_EGREP_HEADER (PATTERN, HEADER-FILE, ACTION-IF-FOUND [,
          ACTION-IF-NOT-FOUND])
     If the output of running the preprocessor on the system header file
     HEADER-FILE matches the `egrep' regular expression PATTERN,
     execute shell commands ACTION-IF-FOUND, otherwise execute
     ACTION-IF-NOT-FOUND.

   To check for C preprocessor symbols, either defined by header files
or predefined by the C preprocessor, use `AC_EGREP_CPP'.  Here is an
example of the latter:

     AC_EGREP_CPP(yes,
     [#ifdef _AIX
       yes
     #endif
     ], is_aix=yes, is_aix=no)

 - Macro: AC_EGREP_CPP (PATTERN, PROGRAM, [ACTION-IF-FOUND [,
          ACTION-IF-NOT-FOUND]])
     PROGRAM is the text of a C or C++ program, on which shell
     variable, backquote, and backslash substitutions are performed.
     If the output of running the preprocessor on PROGRAM matches the
     `egrep' regular expression PATTERN, execute shell commands
     ACTION-IF-FOUND, otherwise execute ACTION-IF-NOT-FOUND.

     This macro calls `AC_PROG_CPP' or `AC_PROG_CXXCPP' (depending on
     which language is current, *note Language Choice::.), if it hasn't
     been called already.


File: autoconf.info,  Node: Examining Syntax,  Next: Examining Libraries,  Prev: Examining Declarations,  Up: Writing Tests

Examining Syntax
================

   To check for a syntax feature of the C, C++ or Fortran 77 compiler,
such as whether it recognizes a certain keyword, use `AC_TRY_COMPILE' to
try to compile a small program that uses that feature.  You can also use
it to check for structures and structure members that are not present on
all systems.

 - Macro: AC_TRY_COMPILE (INCLUDES, FUNCTION-BODY, [ACTION-IF-FOUND [,
          ACTION-IF-NOT-FOUND]])
     Create a C, C++ or Fortran 77 test program (depending on which
     language is current, *note Language Choice::.), to see whether a
     function whose body consists of FUNCTION-BODY can be compiled.

     For C and C++, INCLUDES is any `#include' statements needed by the
     code in FUNCTION-BODY (INCLUDES will be ignored if the currently
     selected language is Fortran 77).  This macro also uses `CFLAGS'
     or `CXXFLAGS' if either C or C++ is the currently selected
     language, as well as `CPPFLAGS', when compiling.  If Fortran 77 is
     the currently selected language then `FFLAGS' will be used when
     compiling.

     If the file compiles successfully, run shell commands
     ACTION-IF-FOUND, otherwise run ACTION-IF-NOT-FOUND.

     This macro does not try to link; use `AC_TRY_LINK' if you need to
     do that (*note Examining Libraries::.).


File: autoconf.info,  Node: Examining Libraries,  Next: Run Time,  Prev: Examining Syntax,  Up: Writing Tests

Examining Libraries
===================

   To check for a library, a function, or a global variable, Autoconf
`configure' scripts try to compile and link a small program that uses
it.  This is unlike Metaconfig, which by default uses `nm' or `ar' on
the C library to try to figure out which functions are available.
Trying to link with the function is usually a more reliable approach
because it avoids dealing with the variations in the options and output
formats of `nm' and `ar' and in the location of the standard libraries.
It also allows configuring for cross-compilation or checking a
function's runtime behavior if needed.  On the other hand, it can be
slower than scanning the libraries once.

   A few systems have linkers that do not return a failure exit status
when there are unresolved functions in the link.  This bug makes the
configuration scripts produced by Autoconf unusable on those systems.
However, some of them can be given options that make the exit status
correct.  This is a problem that Autoconf does not currently handle
automatically.  If users encounter this problem, they might be able to
solve it by setting `LDFLAGS' in the environment to pass whatever
options the linker needs (for example, `-Wl,-dn' on MIPS RISC/OS).

   `AC_TRY_LINK' is used to compile test programs to test for functions
and global variables.  It is also used by `AC_CHECK_LIB' to check for
libraries (*note Libraries::.), by adding the library being checked for
to `LIBS' temporarily and trying to link a small program.

 - Macro: AC_TRY_LINK (INCLUDES, FUNCTION-BODY, [ACTION-IF-FOUND [,
          ACTION-IF-NOT-FOUND]])
     Depending on the current language (*note Language Choice::.),
     create a test program to see whether a function whose body
     consists of FUNCTION-BODY can be compiled and linked.

     For C and C++, INCLUDES is any `#include' statements needed by the
     code in FUNCTION-BODY (INCLUDES will be ignored if the currently
     selected language is Fortran 77).  This macro also uses `CFLAGS'
     or `CXXFLAGS' if either C or C++ is the currently selected
     language, as well as `CPPFLAGS', when compiling.  If Fortran 77 is
     the currently selected language then `FFLAGS' will be used when
     compiling.  However, both `LDFLAGS' and `LIBS' will be used during
     linking in all cases.

     If the file compiles and links successfully, run shell commands
     ACTION-IF-FOUND, otherwise run ACTION-IF-NOT-FOUND.

 - Macro: AC_TRY_LINK_FUNC (FUNCTION, [ACTION-IF-FOUND [,
          ACTION-IF-NOT-FOUND]])
     Depending on the current language (*note Language Choice::.),
     create a test program to see whether a program whose body consists
     of a prototype of and a call to FUNCTION can be compiled and
     linked.

     If the file compiles and links successfully, run shell commands
     ACTION-IF-FOUND, otherwise run ACTION-IF-NOT-FOUND.

 - Macro: AC_TRY_LINK_FUNC (FUNCTION, [ACTION-IF-FOUND [,
          ACTION-IF-NOT-FOUND]])
     Attempt to compile and link a small program that links with
     FUNCTION.  If the file compiles and links successfully, run shell
     commands ACTION-IF-FOUND, otherwise run ACTION-IF-NOT-FOUND.

 - Macro: AC_COMPILE_CHECK (ECHO-TEXT, INCLUDES, FUNCTION-BODY,
          ACTION-IF-FOUND [, ACTION-IF-NOT-FOUND])
     This is an obsolete version of `AC_TRY_LINK', with the addition
     that it prints `checking for ECHO-TEXT' to the standard output
     first, if ECHO-TEXT is non-empty.  Use `AC_MSG_CHECKING' and
     `AC_MSG_RESULT' instead to print messages (*note Printing
     Messages::.).


File: autoconf.info,  Node: Run Time,  Next: Portable Shell,  Prev: Examining Libraries,  Up: Writing Tests

Checking Run Time Behavior
==========================

   Sometimes you need to find out how a system performs at run time,
such as whether a given function has a certain capability or bug.  If
you can, make such checks when your program runs instead of when it is
configured.  You can check for things like the machine's endianness when
your program initializes itself.

   If you really need to test for a run-time behavior while configuring,
you can write a test program to determine the result, and compile and
run it using `AC_TRY_RUN'.  Avoid running test programs if possible,
because using them prevents people from configuring your package for
cross-compiling.

* Menu:

* Test Programs::               Running test programs.
* Guidelines::                  General rules for writing test programs.
* Test Functions::              Avoiding pitfalls in test programs.


File: autoconf.info,  Node: Test Programs,  Next: Guidelines,  Prev: Run Time,  Up: Run Time

Running Test Programs
---------------------

   Use the following macro if you need to test run-time behavior of the
system while configuring.

 - Macro: AC_TRY_RUN (PROGRAM, [ACTION-IF-TRUE [, ACTION-IF-FALSE [,
          ACTION-IF-CROSS-COMPILING]]])
     PROGRAM is the text of a C program, on which shell variable and
     backquote substitutions are performed.  If it compiles and links
     successfully and returns an exit status of 0 when executed, run
     shell commands ACTION-IF-TRUE.  Otherwise run shell commands
     ACTION-IF-FALSE; the exit status of the program is available in
     the shell variable `$?'.  This macro uses `CFLAGS' or `CXXFLAGS',
     `CPPFLAGS', `LDFLAGS', and `LIBS' when compiling.

     If the C compiler being used does not produce executables that run
     on the system where `configure' is being run, then the test
     program is not run.  If the optional shell commands
     ACTION-IF-CROSS-COMPILING are given, they are run instead.
     Otherwise, `configure' prints an error message and exits.

   Try to provide a pessimistic default value to use when
cross-compiling makes run-time tests impossible.  You do this by
passing the optional last argument to `AC_TRY_RUN'.  `autoconf' prints
a warning message when creating `configure' each time it encounters a
call to `AC_TRY_RUN' with no ACTION-IF-CROSS-COMPILING argument given.
You may ignore the warning, though users will not be able to configure
your package for cross-compiling.  A few of the macros distributed with
Autoconf produce this warning message.

   To configure for cross-compiling you can also choose a value for
those parameters based on the canonical system name (*note Manual
Configuration::.).  Alternatively, set up a test results cache file with
the correct values for the target system (*note Caching Results::.).

   To provide a default for calls of `AC_TRY_RUN' that are embedded in
other macros, including a few of the ones that come with Autoconf, you
can call `AC_PROG_CC' before running them.  Then, if the shell variable
`cross_compiling' is set to `yes', use an alternate method to get the
results instead of calling the macros.

 - Macro: AC_C_CROSS
     This macro is obsolete; it does nothing.


File: autoconf.info,  Node: Guidelines,  Next: Test Functions,  Prev: Test Programs,  Up: Run Time

Guidelines for Test Programs
----------------------------

   Test programs should not write anything to the standard output.  They
should return 0 if the test succeeds, nonzero otherwise, so that success
can be distinguished easily from a core dump or other failure;
segmentation violations and other failures produce a nonzero exit
status.  Test programs should `exit', not `return', from `main',
because on some systems (old Suns, at least) the argument to `return'
in `main' is ignored.

   Test programs can use `#if' or `#ifdef' to check the values of
preprocessor macros defined by tests that have already run.  For
example, if you call `AC_HEADER_STDC', then later on in `configure.in'
you can have a test program that includes an ANSI C header file
conditionally:

     #if STDC_HEADERS
     # include <stdlib.h>
     #endif

   If a test program needs to use or create a data file, give it a name
that starts with `conftest', such as `conftestdata'.  The `configure'
script cleans up by running `rm -rf conftest*' after running test
programs and if the script is interrupted.


File: autoconf.info,  Node: Test Functions,  Prev: Guidelines,  Up: Run Time

Test Functions
--------------

   Function declarations in test programs should have a prototype
conditionalized for C++.  In practice, though, test programs rarely need
functions that take arguments.

     #ifdef __cplusplus
     foo(int i)
     #else
     foo(i) int i;
     #endif

   Functions that test programs declare should also be conditionalized
for C++, which requires `extern "C"' prototypes.  Make sure to not
include any header files containing clashing prototypes.

     #ifdef __cplusplus
     extern "C" void *malloc(size_t);
     #else
     char *malloc();
     #endif

   If a test program calls a function with invalid parameters (just to
see whether it exists), organize the program to ensure that it never
invokes that function.  You can do this by calling it in another
function that is never invoked.  You can't do it by putting it after a
call to `exit', because GCC version 2 knows that `exit' never returns
and optimizes out any code that follows it in the same block.

   If you include any header files, make sure to call the functions
relevant to them with the correct number of arguments, even if they are
just 0, to avoid compilation errors due to prototypes.  GCC version 2
has internal prototypes for several functions that it automatically
inlines; for example, `memcpy'.  To avoid errors when checking for
them, either pass them the correct number of arguments or redeclare them
with a different return type (such as `char').


File: autoconf.info,  Node: Portable Shell,  Next: Testing Values and Files,  Prev: Run Time,  Up: Writing Tests

Portable Shell Programming
==========================

   When writing your own checks, there are some shell script programming
techniques you should avoid in order to make your code portable.  The
Bourne shell and upward-compatible shells like Bash and the Korn shell
have evolved over the years, but to prevent trouble, do not take
advantage of features that were added after UNIX version 7, circa 1977.
You should not use shell functions, aliases, negated character classes,
or other features that are not found in all Bourne-compatible shells;
restrict yourself to the lowest common denominator.  Even `unset' is
not supported by all shells!  Also, include a space after the
exclamation point in interpreter specifications, like this:
     #! /usr/bin/perl
   If you omit the space before the path, then 4.2BSD based systems
(such as Sequent DYNIX) will ignore the line, because they interpret
`#! /' as a 4-byte magic number.

   The set of external programs you should run in a `configure' script
is fairly small.  *Note Utilities in Makefiles: (standards)Utilities in
Makefiles, for the list.  This restriction allows users to start out
with a fairly small set of programs and build the rest, avoiding too
many interdependencies between packages.

   Some of these external utilities have a portable subset of features,
as well; for example, don't rely on `ln' having a `-f' option or `cat'
having any options.  `sed' scripts should not contain comments or use
branch labels longer than 8 characters.  Don't use `grep -s' to
suppress output, because `grep -s' on System V does not suppress
output, only error messages.  Instead, redirect the standard output and
standard error (in case the file doesn't exist) of `grep' to
`/dev/null'.  Check the exit status of `grep' to determine whether it
found a match.


File: autoconf.info,  Node: Testing Values and Files,  Next: Multiple Cases,  Prev: Portable Shell,  Up: Writing Tests

Testing Values and Files
========================

   `configure' scripts need to test properties of many files and
strings.  Here are some portability problems to watch out for when doing
those tests.

   The `test' program is the way to perform many file and string tests.
It is often invoked by the alternate name `[', but using that name in
Autoconf code is asking for trouble since it is an `m4' quote character.

   If you need to make multiple checks using `test', combine them with
the shell operators `&&' and `||' instead of using the `test' operators
`-a' and `-o'.  On System V, the precedence of `-a' and `-o' is wrong
relative to the unary operators; consequently, POSIX does not specify
them, so using them is nonportable.  If you combine `&&' and `||' in
the same statement, keep in mind that they have equal precedence.

   To enable `configure' scripts to support cross-compilation, they
shouldn't do anything that tests features of the host system instead of
the target system.  But occasionally you may find it necessary to check
whether some arbitrary file exists.  To do so, use `test -f' or `test
-r'.  Do not use `test -x', because 4.3BSD does not have it.

   Another nonportable shell programming construction is
     VAR=${VAR:-VALUE}

The intent is to set VAR to VALUE only if it is not already set, but if
VAR has any value, even the empty string, to leave it alone.  Old BSD
shells, including the Ultrix `sh', don't accept the colon, and complain
and die.  A portable equivalent is
     : ${VAR=VALUE}


File: autoconf.info,  Node: Multiple Cases,  Next: Language Choice,  Prev: Testing Values and Files,  Up: Writing Tests

Multiple Cases
==============

   Some operations are accomplished in several possible ways, depending
on the UNIX variant.  Checking for them essentially requires a "case
statement".  Autoconf does not directly provide one; however, it is
easy to simulate by using a shell variable to keep track of whether a
way to perform the operation has been found yet.

   Here is an example that uses the shell variable `fstype' to keep
track of whether the remaining cases need to be checked.

     AC_MSG_CHECKING(how to get filesystem type)
     fstype=no
     # The order of these tests is important.
     AC_TRY_CPP([#include <sys/statvfs.h>
     #include <sys/fstyp.h>], AC_DEFINE(FSTYPE_STATVFS) fstype=SVR4)
     if test $fstype = no; then
     AC_TRY_CPP([#include <sys/statfs.h>
     #include <sys/fstyp.h>], AC_DEFINE(FSTYPE_USG_STATFS) fstype=SVR3)
     fi
     if test $fstype = no; then
     AC_TRY_CPP([#include <sys/statfs.h>
     #include <sys/vmount.h>], AC_DEFINE(FSTYPE_AIX_STATFS) fstype=AIX)
     fi
     # (more cases omitted here)
     AC_MSG_RESULT($fstype)


File: autoconf.info,  Node: Language Choice,  Prev: Multiple Cases,  Up: Writing Tests

Language Choice
===============

   Packages that use both C and C++ need to test features of both
compilers.  Autoconf-generated `configure' scripts check for C features
by default.  The following macros determine which language's compiler
is used in tests that follow in `configure.in'.

 - Macro: AC_LANG_C
     Do compilation tests using `CC' and `CPP' and use extension `.c'
     for test programs.  Set the shell variable `cross_compiling' to
     the value computed by `AC_PROG_CC' if it has been run, empty
     otherwise.

 - Macro: AC_LANG_CPLUSPLUS
     Do compilation tests using `CXX' and `CXXCPP' and use extension
     `.C' for test programs.  Set the shell variable `cross_compiling'
     to the value computed by `AC_PROG_CXX' if it has been run, empty
     otherwise.

 - Macro: AC_LANG_FORTRAN77
     Do compilation tests using `F77' and use extension `.f' for test
     programs.  Set the shell variable `cross_compiling' to the value
     computed by `AC_PROG_F77' if it has been run, empty otherwise.

 - Macro: AC_LANG_SAVE
     Remember the current language (as set by `AC_LANG_C',
     `AC_LANG_CPLUSPLUS' or `AC_LANG_FORTRAN77') on a stack.  Does not
     change which language is current.  Use this macro and
     `AC_LANG_RESTORE' in macros that need to temporarily switch to a
     particular language.

 - Macro: AC_LANG_RESTORE
     Select the language that is saved on the top of the stack, as set
     by `AC_LANG_SAVE', and remove it from the stack.  This macro is
     equivalent to either `AC_LANG_C', `AC_LANG_CPLUSPLUS' or
     `AC_LANG_FORTRAN77', whichever had been run most recently when
     `AC_LANG_SAVE' was last called.

     Do not call this macro more times than `AC_LANG_SAVE'.

 - Macro: AC_REQUIRE_CPP
     Ensure that whichever preprocessor would currently be used for
     tests has been found.  Calls `AC_REQUIRE' (*note Prerequisite
     Macros::.) with an argument of either `AC_PROG_CPP' or
     `AC_PROG_CXXCPP', depending on which language is current.


File: autoconf.info,  Node: Results,  Next: Writing Macros,  Prev: Writing Tests,  Up: Top

Results of Tests
****************

   Once `configure' has determined whether a feature exists, what can
it do to record that information?  There are four sorts of things it can
do: define a C preprocessor symbol, set a variable in the output files,
save the result in a cache file for future `configure' runs, and print
a message letting the user know the result of the test.

* Menu:

* Defining Symbols::            Defining C preprocessor symbols.
* Setting Output Variables::    Replacing variables in output files.
* Caching Results::             Speeding up subsequent `configure' runs.
* Printing Messages::           Notifying users of progress or problems.


File: autoconf.info,  Node: Defining Symbols,  Next: Setting Output Variables,  Prev: Results,  Up: Results

Defining C Preprocessor Symbols
===============================

   A common action to take in response to a feature test is to define a
C preprocessor symbol indicating the results of the test.  That is done
by calling `AC_DEFINE' or `AC_DEFINE_UNQUOTED'.

   By default, `AC_OUTPUT' places the symbols defined by these macros
into the output variable `DEFS', which contains an option
`-DSYMBOL=VALUE' for each symbol defined.  Unlike in Autoconf version
1, there is no variable `DEFS' defined while `configure' is running.
To check whether Autoconf macros have already defined a certain C
preprocessor symbol, test the value of the appropriate cache variable,
as in this example:

     AC_CHECK_FUNC(vprintf, AC_DEFINE(HAVE_VPRINTF))
     if test "$ac_cv_func_vprintf" != yes; then
     AC_CHECK_FUNC(_doprnt, AC_DEFINE(HAVE_DOPRNT))
     fi

   If `AC_CONFIG_HEADER' has been called, then instead of creating
`DEFS', `AC_OUTPUT' creates a header file by substituting the correct
values into `#define' statements in a template file.  *Note
Configuration Headers::, for more information about this kind of output.

 - Macro: AC_DEFINE (VARIABLE [, VALUE [, DESCRIPTION]])
     Define C preprocessor variable VARIABLE.  If VALUE is given, set
     VARIABLE to that value (verbatim), otherwise set it to 1.  VALUE
     should not contain literal newlines, and if you are not using
     `AC_CONFIG_HEADER' it should not contain any `#' characters, as
     `make' tends to eat them.  To use a shell variable (which you need
     to do in order to define a value containing the `m4' quote
     characters `[' or `]'), use `AC_DEFINE_UNQUOTED' instead.
     DESCRIPTION is only useful if you are using `AC_CONFIG_HEADER'.
     In this case, DESCRIPTION is put into the generated `config.h.in'
     as the comment before the macro define; the macro need not be
     mentioned in `acconfig.h'.  The following example defines the C
     preprocessor variable `EQUATION' to be the string constant `"$a >
     $b"':

          AC_DEFINE(EQUATION, "$a > $b")

 - Macro: AC_DEFINE_UNQUOTED (VARIABLE [, VALUE [, DESCRIPTION]])
     Like `AC_DEFINE', but three shell expansions are
     performed--once--on VARIABLE and VALUE: variable expansion (`$'),
     command substitution (``'), and backslash escaping (`\').  Single
     and double quote characters in the value have no special meaning.
     Use this macro instead of `AC_DEFINE' when VARIABLE or VALUE is a
     shell variable.  Examples:

          AC_DEFINE_UNQUOTED(config_machfile, "${machfile}")
          AC_DEFINE_UNQUOTED(GETGROUPS_T, $ac_cv_type_getgroups)
          AC_DEFINE_UNQUOTED(${ac_tr_hdr})

   Due to the syntactical bizarreness of the Bourne shell, do not use
semicolons to separate `AC_DEFINE' or `AC_DEFINE_UNQUOTED' calls from
other macro calls or shell code; that can cause syntax errors in the
resulting `configure' script.  Use either spaces or newlines.  That is,
do this:

     AC_CHECK_HEADER(elf.h, AC_DEFINE(SVR4) LIBS="$LIBS -lelf")

or this:

     AC_CHECK_HEADER(elf.h,
       AC_DEFINE(SVR4)
       LIBS="$LIBS -lelf")

instead of this:

     AC_CHECK_HEADER(elf.h, AC_DEFINE(SVR4); LIBS="$LIBS -lelf")


File: autoconf.info,  Node: Setting Output Variables,  Next: Caching Results,  Prev: Defining Symbols,  Up: Results

Setting Output Variables
========================

   One way to record the results of tests is to set "output variables",
which are shell variables whose values are substituted into files that
`configure' outputs.  The two macros below create new output variables.
*Note Preset Output Variables::, for a list of output variables that
are always available.

 - Macro: AC_SUBST (VARIABLE)
     Create an output variable from a shell variable.  Make `AC_OUTPUT'
     substitute the variable VARIABLE into output files (typically one
     or more `Makefile's).  This means that `AC_OUTPUT' will replace
     instances of `@VARIABLE@' in input files with the value that the
     shell variable VARIABLE has when `AC_OUTPUT' is called.  The value
     of VARIABLE should not contain literal newlines.

 - Macro: AC_SUBST_FILE (VARIABLE)
     Another way to create an output variable from a shell variable.
     Make `AC_OUTPUT' insert (without substitutions) the contents of
     the file named by shell variable VARIABLE into output files.  This
     means that `AC_OUTPUT' will replace instances of `@VARIABLE@' in
     output files (such as `Makefile.in') with the contents of the file
     that the shell variable VARIABLE names when `AC_OUTPUT' is called.
     Set the variable to `/dev/null' for cases that do not have a file
     to insert.

     This macro is useful for inserting `Makefile' fragments containing
     special dependencies or other `make' directives for particular host
     or target types into `Makefile's.  For example, `configure.in'
     could contain:

          AC_SUBST_FILE(host_frag)dnl
          host_frag=$srcdir/conf/sun4.mh

     and then a `Makefile.in' could contain:

          @host_frag@


File: autoconf.info,  Node: Caching Results,  Next: Printing Messages,  Prev: Setting Output Variables,  Up: Results

Caching Results
===============

   To avoid checking for the same features repeatedly in various
`configure' scripts (or repeated runs of one script), `configure' saves
the results of many of its checks in a "cache file".  If, when a
`configure' script runs, it finds a cache file, it reads from it the
results from previous runs and avoids rerunning those checks.  As a
result, `configure' can run much faster than if it had to perform all
of the checks every time.

 - Macro: AC_CACHE_VAL (CACHE-ID, COMMANDS-TO-SET-IT)
     Ensure that the results of the check identified by CACHE-ID are
     available.  If the results of the check were in the cache file
     that was read, and `configure' was not given the `--quiet' or
     `--silent' option, print a message saying that the result was
     cached; otherwise, run the shell commands COMMANDS-TO-SET-IT.
     Those commands should have no side effects except for setting the
     variable CACHE-ID.  In particular, they should not call
     `AC_DEFINE'; the code that follows the call to `AC_CACHE_VAL'
     should do that, based on the cached value.  Also, they should not
     print any messages, for example with `AC_MSG_CHECKING'; do that
     before calling `AC_CACHE_VAL', so the messages are printed
     regardless of whether the results of the check are retrieved from
     the cache or determined by running the shell commands.  If the
     shell commands are run to determine the value, the value will be
     saved in the cache file just before `configure' creates its output
     files.  *Note Cache Variable Names::, for how to choose the name
     of the CACHE-ID variable.

 - Macro: AC_CACHE_CHECK (MESSAGE, CACHE-ID, COMMANDS)
     A wrapper for `AC_CACHE_VAL' that takes care of printing the
     messages.  This macro provides a convenient shorthand for the most
     common way to use these macros.  It calls `AC_MSG_CHECKING' for
     MESSAGE, then `AC_CACHE_VAL' with the CACHE-ID and COMMANDS
     arguments, and `AC_MSG_RESULT' with CACHE-ID.

 - Macro: AC_CACHE_LOAD
     Loads values from existing cache file, or creates a new cache file
     if a cache file is not found.  Called automatically from `AC_INIT'.

 - Macro: AC_CACHE_SAVE
     Flushes all cached values to the cache file.  Called automatically
     from `AC_OUTPUT', but it can be quite useful to call
     `AC_CACHE_SAVE' at key points in configure.in.  Doing so
     checkpoints the cache in case of an early configure script abort.

* Menu:

* Cache Variable Names::        Shell variables used in caches.
* Cache Files::                 Files `configure' uses for caching.


File: autoconf.info,  Node: Cache Variable Names,  Next: Cache Files,  Prev: Caching Results,  Up: Caching Results

Cache Variable Names
--------------------

   The names of cache variables should have the following format:

     PACKAGE-PREFIX_cv_VALUE-TYPE_SPECIFIC-VALUE[_ADDITIONAL-OPTIONS]

for example, `ac_cv_header_stat_broken' or
`ac_cv_prog_gcc_traditional'.  The parts of the variable name are:

PACKAGE-PREFIX
     An abbreviation for your package or organization; the same prefix
     you begin local Autoconf macros with, except lowercase by
     convention.  For cache values used by the distributed Autoconf
     macros, this value is `ac'.

`_cv_'
     Indicates that this shell variable is a cache value.

VALUE-TYPE
     A convention for classifying cache values, to produce a rational
     naming system.  The values used in Autoconf are listed in *Note
     Macro Names::.

SPECIFIC-VALUE
     Which member of the class of cache values this test applies to.
     For example, which function (`alloca'), program (`gcc'), or output
     variable (`INSTALL').

ADDITIONAL-OPTIONS
     Any particular behavior of the specific member that this test
     applies to.  For example, `broken' or `set'.  This part of the
     name may be omitted if it does not apply.

   The values assigned to cache variables may not contain newlines.
Usually, their values will be boolean (`yes' or `no') or the names of
files or functions; so this is not an important restriction.


File: autoconf.info,  Node: Cache Files,  Prev: Cache Variable Names,  Up: Caching Results

Cache Files
-----------

   A cache file is a shell script that caches the results of configure
tests run on one system so they can be shared between configure scripts
and configure runs.  It is not useful on other systems.  If its contents
are invalid for some reason, the user may delete or edit it.

   By default, configure uses `./config.cache' as the cache file,
creating it if it does not exist already.  `configure' accepts the
`--cache-file=FILE' option to use a different cache file; that is what
`configure' does when it calls `configure' scripts in subdirectories,
so they share the cache.  *Note Subdirectories::, for information on
configuring subdirectories with the `AC_CONFIG_SUBDIRS' macro.

   Giving `--cache-file=/dev/null' disables caching, for debugging
`configure'.  `config.status' only pays attention to the cache file if
it is given the `--recheck' option, which makes it rerun `configure'.
If you are anticipating a long debugging period, you can also disable
cache loading and saving for a `configure' script by redefining the
cache macros at the start of `configure.in':

     define([AC_CACHE_LOAD], )dnl
     define([AC_CACHE_SAVE], )dnl
     AC_INIT(whatever)
      ... rest of configure.in ...

   It is wrong to try to distribute cache files for particular system
types.  There is too much room for error in doing that, and too much
administrative overhead in maintaining them.  For any features that
can't be guessed automatically, use the standard method of the canonical
system type and linking files (*note Manual Configuration::.).

   The cache file on a particular system will gradually accumulate
whenever someone runs a `configure' script; it will be initially
nonexistent.  Running `configure' merges the new cache results with the
existing cache file.  The site initialization script can specify a
site-wide cache file to use instead of the default, to make it work
transparently, as long as the same C compiler is used every time (*note
Site Defaults::.).

   If your configure script, or a macro called from configure.in,
happens to abort the configure process, it may be useful to checkpoint
the cache a few times at key points.  Doing so will reduce the amount
of time it takes to re-run the configure script with (hopefully) the
error that caused the previous abort corrected.

      ... AC_INIT, etc. ...
     dnl checks for programs
     AC_PROG_CC
     AC_PROG_GCC_TRADITIONAL
      ... more program checks ...
     AC_CACHE_SAVE
     
     dnl checks for libraries
     AC_CHECK_LIB(nsl, gethostbyname)
     AC_CHECK_LIB(socket, connect)
      ... more lib checks ...
     AC_CACHE_SAVE
     
     dnl Might abort...
     AM_PATH_GTK(1.0.2, , exit 1)
     AM_PATH_GTKMM(0.9.5, , exit 1)


File: autoconf.info,  Node: Printing Messages,  Prev: Caching Results,  Up: Results

Printing Messages
=================

   `configure' scripts need to give users running them several kinds of
information.  The following macros print messages in ways appropriate
for each kind.  The arguments to all of them get enclosed in shell
double quotes, so the shell performs variable and backquote substitution
on them.  You can print a message containing a comma by quoting the
message with the `m4' quote characters:

     AC_MSG_RESULT([never mind, I found the BASIC compiler])

   These macros are all wrappers around the `echo' shell command.
`configure' scripts should rarely need to run `echo' directly to print
messages for the user.  Using these macros makes it easy to change how
and when each kind of message is printed; such changes need only be
made to the macro definitions, and all of the callers change
automatically.

 - Macro: AC_MSG_CHECKING (FEATURE-DESCRIPTION)
     Notify the user that `configure' is checking for a particular
     feature.  This macro prints a message that starts with `checking '
     and ends with `...' and no newline.  It must be followed by a call
     to `AC_MSG_RESULT' to print the result of the check and the
     newline.  The FEATURE-DESCRIPTION should be something like
     `whether the Fortran compiler accepts C++ comments' or `for c89'.

     This macro prints nothing if `configure' is run with the `--quiet'
     or `--silent' option.

 - Macro: AC_MSG_RESULT (RESULT-DESCRIPTION)
     Notify the user of the results of a check.  RESULT-DESCRIPTION is
     almost always the value of the cache variable for the check,
     typically `yes', `no', or a file name.  This macro should follow a
     call to `AC_MSG_CHECKING', and the RESULT-DESCRIPTION should be
     the completion of the message printed by the call to
     `AC_MSG_CHECKING'.

     This macro prints nothing if `configure' is run with the `--quiet'
     or `--silent' option.

 - Macro: AC_MSG_ERROR (ERROR-DESCRIPTION)
     Notify the user of an error that prevents `configure' from
     completing.  This macro prints an error message on the standard
     error output and exits `configure' with a nonzero status.
     ERROR-DESCRIPTION should be something like `invalid value $HOME
     for \$HOME'.

 - Macro: AC_MSG_WARN (PROBLEM-DESCRIPTION)
     Notify the `configure' user of a possible problem.  This macro
     prints the message on the standard error output; `configure'
     continues running afterward, so macros that call `AC_MSG_WARN'
     should provide a default (back-up) behavior for the situations
     they warn about.  PROBLEM-DESCRIPTION should be something like `ln
     -s seems to make hard links'.

   The following two macros are an obsolete alternative to
`AC_MSG_CHECKING' and `AC_MSG_RESULT'.

 - Macro: AC_CHECKING (FEATURE-DESCRIPTION)
     This macro is similar to `AC_MSG_CHECKING', except that it prints a
     newline after the FEATURE-DESCRIPTION.  It is useful mainly to
     print a general description of the overall purpose of a group of
     feature checks, e.g.,

          AC_CHECKING(if stack overflow is detectable)

 - Macro: AC_VERBOSE (RESULT-DESCRIPTION)
     This macro is similar to `AC_MSG_RESULT', except that it is meant
     to follow a call to `AC_CHECKING' instead of `AC_MSG_CHECKING'; it
     starts the message it prints with a tab.  It is considered
     obsolete.


File: autoconf.info,  Node: Writing Macros,  Next: Manual Configuration,  Prev: Results,  Up: Top

Writing Macros
**************

   When you write a feature test that could be applicable to more than
one software package, the best thing to do is encapsulate it in a new
macro.  Here are some instructions and guidelines for writing Autoconf
macros.

* Menu:

* Macro Definitions::           Basic format of an Autoconf macro.
* Macro Names::                 What to call your new macros.
* Quoting::                     Protecting macros from unwanted expansion.
* Dependencies Between Macros::  What to do when macros depend on other macros.

