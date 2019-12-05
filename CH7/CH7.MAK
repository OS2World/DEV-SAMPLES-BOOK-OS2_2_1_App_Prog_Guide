# Builds EASET.EXE, EAVIEW.EXE

all:         easet.exe eaview.exe

easet.exe :  easet.c
             icc easet.c

eaview.exe:  eaview.c
             icc eaview.c
