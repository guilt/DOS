------------------------------------------------------------------------------
--                                                                          --
--                         GNAT COMPILER COMPONENTS                         --
--                                                                          --
--                  S Y S T E M . O S _ C O N S T A N T S                   --
--                                                                          --
--                                 S p e c                                  --
--                                                                          --
--          Copyright (C) 2000-2019, Free Software Foundation, Inc.         --
--                                                                          --
-- GNAT is free software;  you can  redistribute it  and/or modify it under --
-- terms of the  GNU General Public License as published  by the Free Soft- --
-- ware  Foundation;  either version 3,  or (at your option) any later ver- --
-- sion.  GNAT is distributed in the hope that it will be useful, but WITH- --
-- OUT ANY WARRANTY;  without even the  implied warranty of MERCHANTABILITY --
-- or FITNESS FOR A PARTICULAR PURPOSE.                                     --
--                                                                          --
-- As a special exception under Section 7 of GPL version 3, you are granted --
-- additional permissions described in the GCC Runtime Library Exception,   --
-- version 3.1, as published by the Free Software Foundation.               --
--                                                                          --
-- You should have received a copy of the GNU General Public License and    --
-- a copy of the GCC Runtime Library Exception along with this program;     --
-- see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see    --
-- <http://www.gnu.org/licenses/>.                                          --
--                                                                          --
-- GNAT was originally developed  by the GNAT team at  New York University. --
-- Extensive contributions were provided by Ada Core Technologies Inc.      --
--                                                                          --
------------------------------------------------------------------------------

pragma Style_Checks ("M32766");
--  Allow long lines

--  This package provides target dependent definitions of constant for use
--  by the GNAT runtime library. This package should not be directly with'd
--  by an application program.

--  This file is generated automatically, do not modify it by hand! Instead,
--  make changes to s-oscons-tmplt.c and rebuild the GNAT runtime library.
--  This is the version for i586-pc-msdosdjgpp

with Interfaces.C;
package System.OS_Constants is

   pragma Pure;

   ---------------------------------
   -- General platform parameters --
   ---------------------------------

   type OS_Type is (Windows, Other_OS);
   Target_OS                     : constant OS_Type := Other_OS;
   pragma Warnings (Off, Target_OS);
   --  Suppress warnings on Target_OS since it is in general tested for
   --  equality with a constant value to implement conditional compilation,
   --  which normally generates a constant condition warning.

   Target_Name                   : constant String  := "i586-pc-msdosdjgpp";
   SIZEOF_unsigned_int           : constant := 4;          --  Size of unsigned int

   -------------------
   -- System limits --
   -------------------

   IOV_MAX                       : constant := 2147483647; --  Maximum writev iovcnt
   NAME_MAX                      : constant := 12;         --  Maximum file name length

   ---------------------
   -- File open modes --
   ---------------------

   O_RDWR                        : constant := 2;          --  Read/write
   O_NOCTTY                      : constant := 1024;       --  Don't change ctrl tty
   O_NDELAY                      : constant := -1;         --  Nonblocking

   ----------------------
   -- Fcntl operations --
   ----------------------

   F_GETFL                       : constant := 3;          --  Get flags
   F_SETFL                       : constant := 6;          --  Set flags

   -----------------
   -- Fcntl flags --
   -----------------

   FNDELAY                       : constant := -1;         --  Nonblocking

   ----------------------
   -- Ioctl operations --
   ----------------------

   subtype IOCTL_Req_T is Interfaces.C.int;
   FIONBIO                       : constant := -1;         --  Set/clear non-blocking io
   FIONREAD                      : constant := -1;         --  How many bytes to read

   ------------------
   -- Errno values --
   ------------------

   --  The following constants are defined from <errno.h>

   EAGAIN                        : constant := 5;          --  Try again
   ENOENT                        : constant := 22;         --  File not found
   ENOMEM                        : constant := 25;         --  Out of memory
   EACCES                        : constant := 4;          --  Permission denied
   EADDRINUSE                    : constant := -1;         --  Address already in use
   EADDRNOTAVAIL                 : constant := -1;         --  Cannot assign address
   EAFNOSUPPORT                  : constant := -1;         --  Addr family not supported
   EALREADY                      : constant := -1;         --  Operation in progress
   EBADF                         : constant := 6;          --  Bad file descriptor
   ECONNABORTED                  : constant := -1;         --  Connection aborted
   ECONNREFUSED                  : constant := -1;         --  Connection refused
   ECONNRESET                    : constant := -1;         --  Connection reset by peer
   EDESTADDRREQ                  : constant := -1;         --  Destination addr required
   EFAULT                        : constant := 11;         --  Bad address
   EHOSTDOWN                     : constant := -1;         --  Host is down
   EHOSTUNREACH                  : constant := -1;         --  No route to host
   EINPROGRESS                   : constant := -1;         --  Operation now in progress
   EINTR                         : constant := 13;         --  Interrupted system call
   EINVAL                        : constant := 14;         --  Invalid argument
   EIO                           : constant := 15;         --  Input output error
   EISCONN                       : constant := -1;         --  Socket already connected
   ELOOP                         : constant := 39;         --  Too many symbolic links
   EMFILE                        : constant := 17;         --  Too many open files
   EMSGSIZE                      : constant := -1;         --  Message too long
   ENAMETOOLONG                  : constant := 19;         --  Name too long
   ENETDOWN                      : constant := -1;         --  Network is down
   ENETRESET                     : constant := -1;         --  Disconn. on network reset
   ENETUNREACH                   : constant := -1;         --  Network is unreachable
   ENOBUFS                       : constant := -1;         --  No buffer space available
   ENOPROTOOPT                   : constant := -1;         --  Protocol not available
   ENOTCONN                      : constant := -1;         --  Socket not connected
   ENOTSOCK                      : constant := -1;         --  Operation on non socket
   EOPNOTSUPP                    : constant := -1;         --  Operation not supported
   EPIPE                         : constant := 33;         --  Broken pipe
   EPFNOSUPPORT                  : constant := -1;         --  Unknown protocol family
   EPROTONOSUPPORT               : constant := -1;         --  Unknown protocol
   EPROTOTYPE                    : constant := -1;         --  Unknown protocol type
   ERANGE                        : constant := 2;          --  Result too large
   ESHUTDOWN                     : constant := -1;         --  Cannot send once shutdown
   ESOCKTNOSUPPORT               : constant := -1;         --  Socket type not supported
   ETIMEDOUT                     : constant := -1;         --  Connection timed out
   ETOOMANYREFS                  : constant := -1;         --  Too many references
   EWOULDBLOCK                   : constant := -1;         --  Operation would block
   E2BIG                         : constant := 3;          --  Argument list too long
   EILSEQ                        : constant := 41;         --  Illegal byte sequence

   ----------------------
   -- Terminal control --
   ----------------------

   TCSANOW                       : constant := 3;          --  Immediate
   TCIFLUSH                      : constant := 1;          --  Flush input
   IXON                          : constant := 131072;     --  Output sw flow control
   CLOCAL                        : constant := 256;        --  Local
   CRTSCTS                       : constant := 4294967295; --  Output hw flow control
   CREAD                         : constant := 512;        --  Read
   CS5                           : constant := 0;          --  5 data bits
   CS6                           : constant := 1024;       --  6 data bits
   CS7                           : constant := 2048;       --  7 data bits
   CS8                           : constant := 3072;       --  8 data bits
   CSTOPB                        : constant := 4096;       --  2 stop bits
   PARENB                        : constant := 16384;      --  Parity enable
   PARODD                        : constant := 32768;      --  Parity odd
   B0                            : constant := 0;          --  0 bps
   B50                           : constant := 1;          --  50 bps
   B75                           : constant := 2;          --  75 bps
   B110                          : constant := 3;          --  110 bps
   B134                          : constant := 4;          --  134 bps
   B150                          : constant := 5;          --  150 bps
   B200                          : constant := 6;          --  200 bps
   B300                          : constant := 7;          --  300 bps
   B600                          : constant := 8;          --  600 bps
   B1200                         : constant := 9;          --  1200 bps
   B1800                         : constant := 10;         --  1800 bps
   B2400                         : constant := 11;         --  2400 bps
   B4800                         : constant := 12;         --  4800 bps
   B9600                         : constant := 13;         --  9600 bps
   B19200                        : constant := 14;         --  19200 bps
   B38400                        : constant := 15;         --  38400 bps
   B57600                        : constant := 4294967295; --  57600 bps
   B115200                       : constant := 4294967295; --  115200 bps
   B230400                       : constant := 4294967295; --  230400 bps
   B460800                       : constant := 4294967295; --  460800 bps
   B500000                       : constant := 4294967295; --  500000 bps
   B576000                       : constant := 4294967295; --  576000 bps
   B921600                       : constant := 4294967295; --  921600 bps
   B1000000                      : constant := 4294967295; --  1000000 bps
   B1152000                      : constant := 4294967295; --  1152000 bps
   B1500000                      : constant := 4294967295; --  1500000 bps
   B2000000                      : constant := 4294967295; --  2000000 bps
   B2500000                      : constant := 4294967295; --  2500000 bps
   B3000000                      : constant := 4294967295; --  3000000 bps
   B3500000                      : constant := 4294967295; --  3500000 bps
   B4000000                      : constant := 4294967295; --  4000000 bps

   ---------------------------------
   -- Terminal control characters --
   ---------------------------------

   VINTR                         : constant := 4;          --  Interrupt
   VQUIT                         : constant := 7;          --  Quit
   VERASE                        : constant := 3;          --  Erase
   VKILL                         : constant := 5;          --  Kill
   VEOF                          : constant := 1;          --  EOF
   VTIME                         : constant := 11;         --  Read timeout
   VMIN                          : constant := 6;          --  Read min chars
   VSWTC                         : constant := -1;         --  Switch
   VSTART                        : constant := 8;          --  Flow control start
   VSTOP                         : constant := 9;          --  Flow control stop
   VSUSP                         : constant := 10;         --  Suspend
   VEOL                          : constant := 2;          --  EOL
   VREPRINT                      : constant := -1;         --  Reprint unread
   VDISCARD                      : constant := -1;         --  Discard pending
   VWERASE                       : constant := -1;         --  Word erase
   VLNEXT                        : constant := -1;         --  Literal next
   VEOL2                         : constant := -1;         --  Alternative EOL

   -----------------------------
   -- Pseudo terminal library --
   -----------------------------

   PTY_Library                   : constant String  := "";           --  for g-exptty

   ---------------------
   -- Threads support --
   ---------------------

   --  Clock identifier definitions

   CLOCK_REALTIME                : constant := -1;         --  System realtime clock
   CLOCK_THREAD_CPUTIME_ID       : constant := -1;         --  Thread CPU clock
   CLOCK_RT_Ada                  : constant := CLOCK_REALTIME;

   --------------------------------
   -- File and directory support --
   --------------------------------

   SIZEOF_struct_file_attributes : constant := 24;         --  struct file_attributes
   SIZEOF_struct_dirent_alloc    : constant := 14;         --  struct dirent allocation

end System.OS_Constants;
