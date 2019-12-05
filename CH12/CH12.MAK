# Builds PROG12F8.EXE, PROG12F9.EXE, PRG11F10.EXE, PRG11F11.EXE

all:           prog12f8.exe prog12f9.exe prg12f10.exe prg12f11.exe

prog12f8.exe : prog12f8.c
               icc -Gm+ prog12f8.c

prog12f9.exe : prog12f9.c
               icc -Gm+ prog12f9.c

prg12f10.exe : prg12f10.c
               icc -Gm+ prg12f10.c

prg12f11.exe : prg12f11.c
               icc -Gm+ prg12f11.c
