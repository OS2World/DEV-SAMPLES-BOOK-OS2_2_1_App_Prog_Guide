# make file for c4_4.exe

.SUFFIXES:

.SUFFIXES: .c .txt

ALL: stock.dll c4_4.exe

stock.dll:  \
  c4_2d.OBJ \
  \
  c4_4.MAK
   @REM @<<c4_2d.@0
     /DE /NOI /NOP /M /PM:VIO /ALIGN:4 /NOE +
     c4_2d.OBJ
     stock.dll


     c4_2d.def;
<<
   LINK386.EXE @c4_2d.@0

#   Add /Gd+ to dynamically link to the C runtime functions
c4_2d.obj: c4_2d.c c4_2d.h
   ICC.EXE /Sm /Ss /Sp1 /Q /Ti /W3 /C /Ge- c4_2d.c

c4_4.exe:  \
  c4_4.OBJ \
  \
  c4_4.MAK
   @REM @<<c4_4.@0
     /DE /NOI /NOP /M /PM:VIO /ALIGN:4 +
     c4_4.OBJ
     c4_4.exe
     c4_4.map

     c4_4.def;
<<
   LINK386.EXE @c4_4.@0

#   Add /Gd+ to dynamically link to the C runtime functions
c4_4.obj: c4_4.c c4_3.h
   ICC.EXE /Sm /Ss /Q /Ti /W3 /C c4_4.c
