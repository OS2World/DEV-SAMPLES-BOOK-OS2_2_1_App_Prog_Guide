# Builds PROG13F1.EXE, PROG13F2.EXE, PROG13F3.EXE, PROG13F4.EXE,
#        PROG13F5.EXE

all:            prog13f1.exe prog13f2.exe prog13f3.exe prog13f4.exe \
                prog13f5.exe

prog13f1.exe :  prog13f1.c
                icc prog13f1.c

prog13f2.exe :  prog13f2.c
                icc prog13f2.c

prog13f3.exe :  prog13f3.c
                icc prog13f3.c

prog13f4.exe :  prog13f4.c
                icc prog13f4.c

prog13f5.exe :  prog13f5.c
                icc prog13f5.c
