ECHO OFF
REM Using the ATI VESA TSR with Microsoft C/C++ 7.0:

REM The following switch is recommended to ensure correct behavior with the
REM Microsoft C/C++ 7.0 graphics library.  This forces single-window mode
REM on newer ATI video cards that support and default to dual-window mode.

VVESA 55rw

REM The following option can be used to remove the ATI TSR from memory:
REM VVESA OFF
