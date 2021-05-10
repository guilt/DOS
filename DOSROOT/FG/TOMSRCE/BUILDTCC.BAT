REM ******************************************************************
REM
REM This batch file compiles the Tommy source code using Turbo C++ and
REM links it with Fastgraph/Light.
REM
REM ******************************************************************

TCC -ml -1 -w tommy.c char.c effects.c map.c motion.c timer.obj fgll.lib
