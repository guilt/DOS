REM ******************************************************************
REM
REM This batch file compiles the Fastgraph Game Editor source code
REM using Microsoft C version 5 and links it with Fastgraph/Light.
REM
REM ******************************************************************

CL /AL /G2 /W3 fge.c char.c common.c menu.c level.c ripper.c sprite.c tile.c /link /E fgll.lib
