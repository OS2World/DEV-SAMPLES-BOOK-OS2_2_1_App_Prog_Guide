# Builds HIWORLD.EXE, HIWORLD2.EXE, PROG11F1.EXE, PROG11F2.EXE,
#        PROG11F3.EXE, PROG11F4.EXE, PRG11F5A.EXE, PRG11F5B.EXE,
#        PRG11F6A.EXE, PRG11F6B.EXE, PRG11F6C.EXE, PROG11F7.EXE,
#        PROG11F8.EXE, PROG11F9.EXE, PRG11F11.EXE

all:           hiworld.exe hiworld2.exe                       \
               prog11f1.exe prog11f2.exe prog11f3.exe prog11f4.exe  \
               prg11f5a.exe prg11f5b.exe prg11f6a.exe prg11f6b.exe  \
               prg11f6c.exe prog11f7.exe prog11f8.exe prog11f9.exe  \
               prg11f11.exe

hiworld.exe :  hiworld.c
               icc hiworld.c

hiworld2.exe:  hiworld2.c
               icc hiworld2.c

prog11f1.exe:  prog11f1.c
               icc prog11f1.c

prog11f2.exe:  prog11f2.c
               icc prog11f2.c

prog11f3.exe:  prog11f3.c
               icc prog11f3.c

prog11f4.exe:  prog11f4.c
               icc prog11f4.c

prg11f5a.exe:  prg11f5a.c
               icc prg11f5a.c

prg11f5b.exe:  prg11f5b.c
               icc prg11f5b.c

prg11f6a.exe:  prg11f6a.c
               icc prg11f6a.c

prg11f6b.exe:  prg11f6b.c
               icc prg11f6b.c

prg11f6c.exe:  prg11f6c.c
               icc prg11f6c.c

prog11f7.exe:  prog11f7.c
               icc prog11f7.c

prog11f8.exe:  prog11f8.c
               icc prog11f8.c

prog11f9.exe:  prog11f9.c
               icc prog11f9.c

prg11f11.exe:  prg11f11.c
               icc prg11f11.c
