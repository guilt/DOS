REM ******************************************************************
REM
REM This batch file compiles the Tommy source code using Borland C++
REM and links it with Fastgraph/Light.
REM
REM ******************************************************************

BCC -ml -1 -w tommy.c char.c effects.c map.c motion.c timer.obj fgll.lib
