# Builds PROG1F2.EXE and PROG1F3.EXE

all:           prog1f2.exe prog1f3.exe

prog1f2.exe :  prog1f2.c
               icc prog1f2.c

prog1f3.exe :  prog1f3.c
               icc prog1f3.c

