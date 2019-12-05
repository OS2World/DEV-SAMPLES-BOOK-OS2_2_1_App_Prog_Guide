#  C4_2*.* calls a DLL, using DEF files.

ALL: stock.dll stock.lib c4_2.exe

# Create DLL and LIB files.

stock.dll: c4_2d.obj
   LINK386.EXE /DE /ALIGN:4 \
         c4_2d.obj,stock.dll,,,c4_2d.def

stock.lib: c4_2d.def stock.dll
   implib stock.lib c4_2d.def

c4_2d.obj: c4_2d.c c4_2d.h
   ICC.EXE /Sm /Ss /Q /Ti /W3 /C /Ge- c4_2d.c

# Create EXE file.

c4_2.exe: c4_2.obj
   LINK386.EXE /DE /ALIGN:4 \
         c4_2.obj,c4_2.exe,,stock.lib,c4_2.def

c4_2.obj: c4_2.c c4_2.h
   ICC.EXE /Sm /Ss /Q /Ti /W3 /C c4_2.c
