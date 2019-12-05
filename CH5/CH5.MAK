# Builds PROG5F1.EXE, PROG5F3.EXE, PROG5F6.EXE, PROG5F8.EXE,
#        PROG5F9.EXE, PROG5F10.EXE

all:           prog5f1.exe prog5f3.exe prog5f6.exe prog5f8.exe \
               prog5f9.exe prog5f10.exe

prog5f1.exe :  prog5f1.c
               icc prog5f1.c

prog5f3.exe :  prog5f3.c
               icc prog5f3.c

prog5f6.exe :  prog5f6.c
               icc prog5f6.c

prog5f8.exe :  prog5f8.c
               icc prog5f8.c

prog5f9.exe :  prog5f9.c
               icc prog5f9.c

prog5f10.exe:  prog5f10.c
               icc prog5f10.c
