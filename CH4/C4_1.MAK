# C4_1.MAK

ALL:  c4_1.exe

c4_1.exe: c4_1.obj
   LINK386.EXE /DE /ALIGN:4 \
         c4_1.obj,c4_1.exe,,,c4_1.def

c4_1.obj: c4_1.c
   ICC.EXE /Sm /Ss /Q /Ti /W2 /C c4_1.c
