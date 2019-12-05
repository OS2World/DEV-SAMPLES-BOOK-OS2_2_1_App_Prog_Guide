# Builds PROG5F1.EXE, PROG6F5.EXE, PROG6F7.EXE, 
#        PROG6F8.EXE PROG6F11.EXE PROG6F13.EXE

all:           prog6f1.exe prog6f5.exe prog6f7.exe   \
               prog6f8.exe prog6f11.exe prog6f13.exe

prog6f1.exe :  prog6f1.c
               icc prog6f1.c

prog6f5.exe :  prog6f5.c
               icc prog6f5.c

prog6f7.exe :  prog6f7.c
               icc prog6f7.c

prog6f8.exe:  prog6f8.c
               icc prog6f8.c

prog6f11.exe:  prog6f11.c
               icc prog6f11.c

prog6f13.exe:  prog6f13.c
               icc prog6f13.c
