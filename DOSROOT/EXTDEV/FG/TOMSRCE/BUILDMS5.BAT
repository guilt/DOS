REM ******************************************************************
REM
REM This batch file compiles the Tommy source code using Microsoft C
REM version 5 and links it with Fastgraph/Light.
REM
REM ******************************************************************

CL /AL /G2 /W3 tommy.c char.c effects.c map.c motion.c timer.obj /link /E fgll.lib
