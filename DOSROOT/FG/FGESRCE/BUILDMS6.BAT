REM ******************************************************************
REM
REM This batch file compiles the Fastgraph Game Editor source code
REM using Microsoft C version 6, Microsoft C/C++ version 7, or Visual
REM C++ and links it with Fastgraph/Light.
REM
REM ******************************************************************

CL /AL /qc /G2 /W4 fge.c char.c common.c menu.c level.c ripper.c sprite.c tile.c /link /E fgll.lib
