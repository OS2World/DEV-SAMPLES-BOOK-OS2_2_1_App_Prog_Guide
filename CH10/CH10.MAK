# Builds PROG10F1.EXE, PROG10F5.EXE, PROG10F7.EXE,
#        PRG10F10.EXE, and PRG10F13.EXE

all:           prog10f1.exe prog10f5.exe prog10f7.exe   \
               prg10f10.exe prg10f13.exe

prog10f1.exe : prog10f1.c
               icc -Gm+ prog10f1.c

prog10f5.exe : prog10f5.c
               icc -Gm+ prog10f5.c

prog10f7.exe : prog10f7.c
               icc -Gm+ prog10f7.c

prg10f10.exe : prg10f10.c
               icc -Gm+ prg10f10.c

prg10f13.exe : prg10f13.c
               icc -Gm+ prg10f13.c
