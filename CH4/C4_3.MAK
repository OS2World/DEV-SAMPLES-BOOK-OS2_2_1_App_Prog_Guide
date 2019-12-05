# make file for c4_3.exe

.SUFFIXES:

.SUFFIXES: .c .txt

ALL: stock.dll stock.lib c4_3.exe

stock.dll:  \
  c4_2d.OBJ \
  \
  c4_3.MAK
   @REM @<<c4_2d.@0
     /DE /NOI /NOP /M /PM:VIO /ALIGN:4 /NOE +
     c4_2d.OBJ
     stock.dll


     c4_2d.def;
<<
   LINK386.EXE @c4_2d.@0

c4_2d.lib: c4_2d.def stock.dll
   implib stock.lib c4_2d.def

#   Add /Gd+ to dynamically link to the C runtime functions
#  This will reduce your DLL size from 25762 to 2280
c4_2d.obj: c4_2d.c c4_2d.h
   ICC.EXE /Sm /Ss /Q /Ti /W3 /C /Ge- c4_2d.c

c4_3.exe:  \
  c4_3.OBJ \
  \
  c4_3.MAK
   @REM @<<c4_3.@0
     /DE /NOI /NOP /M /PM:VIO /ALIGN:4 +
     c4_3.OBJ
     c4_3.exe


     c4_3.def;
<<
   LINK386.EXE @c4_3.@0

#   Add /Gd+ to dynamically link to the C runtime functions
#  This will reduce your EXE size from 55161 to 6324
c4_3.obj: c4_3.c c4_2d.h
   ICC.EXE /Sm /Ss /Q /Ti /W3 /C c4_3.c
