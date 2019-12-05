# Builds PROG9B.EXE
# Invoke with:  NMAKE PROG9B.MAK

PROG=PROG9B
PROG2=PROG9BA
# Debug flags:  /W3 /Ti+
CFLAGS=/C+ /Q+ /Sm /Gm+ /Ge+ /Gd- /Ss+ /W3 /Ti+
# Debug flag:  /DE
LFLAGS=/ST:24000 /NOL /NOI /L /M:FULL /PM:VIO /DE
# Taking the default libraries

.SUFFIXES:

.SUFFIXES: .c

ALL: $(PROG).EXE $(PROG2).EXE

$(PROG).EXE:  \
  $(PROG).OBJ \
  $(PROG).DEF \
  $(PROG).MAK
   @REM @<<$(PROG).@0
     $(LFLAGS)+
     $(PROG).OBJ
     $(PROG).EXE


     $(PROG).DEF;
<<
   LINK386.EXE @$(PROG).@0

$(PROG2).EXE:  \
  $(PROG2).OBJ \
  $(PROG2).DEF \
  $(PROG).MAK
   @REM @<<$(PROG2).@0
     $(LFLAGS)+
     $(PROG2).OBJ
     $(PROG2).EXE


     $(PROG2).DEF;
<<
   LINK386.EXE @$(PROG2).@0

{.}.c.obj:
   ICC.EXE $(CFLAGS) .\$*.c

