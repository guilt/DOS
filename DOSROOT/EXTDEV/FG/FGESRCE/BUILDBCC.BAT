REM ******************************************************************
REM
REM This batch file compiles the Fastgraph Game Editor source code
REM using Borland C++ and links it with Fastgraph/Light.
REM
REM ******************************************************************

BCC -ml -1 -w fge.c char.c common.c menu.c level.c ripper.c sprite.c tile.c fgll.lib
