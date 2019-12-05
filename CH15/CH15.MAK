# Builds TRAP.EXE, LOOP.EXE

all:        trap.exe loop.exe

trap.exe :  trap.c
            icc trap.c

loop.exe :  loop.c
            icc loop.c
