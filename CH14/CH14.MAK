# Builds PROG14F1.EXE, PROG14F3.EXE, PROG11F5.EXE, PROG11F8.EXE

all:           prog14f1.exe prog14f3.exe prog14f5.exe prog14f6.exe  \
               prog14f9.exe showdate.msg

prog14f1.exe : prog14f1.c
               icc prog14f1.c

prog14f3.exe : prog14f3.c
               icc prog14f3.c

prog14f5.exe : prog14f5.c
               icc prog14f5.c

prog14f6.exe : prog14f6.c
               icc prog14f6.c

prog14f9.exe : prog14f9.c
               icc prog14f9.c

showdate.msg : showdate.txt
               mkmsgf showdate.txt showdate.msg
