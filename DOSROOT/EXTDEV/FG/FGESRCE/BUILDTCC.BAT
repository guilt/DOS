REM ******************************************************************
REM
REM This batch file compiles the Fastgraph Game Editor source code
REM using Turbo C++ and links it with Fastgraph/Light.
REM
REM ******************************************************************

TCC -ml -1 -w fge.c char.c common.c menu.c level.c ripper.c sprite.c tile.c fgll.lib
