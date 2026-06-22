REM ******************************************************************
REM
REM This batch file compiles the Tommy source code using Microsoft C
REM version 6, Microsoft C/C++ version 7, or Microsoft Visual C++ and
REM links it with Fastgraph/Light.
REM
REM ******************************************************************

CL /AL /qc /G2 /W4 tommy.c char.c effects.c map.c motion.c timer.obj /link /E fgll.lib
