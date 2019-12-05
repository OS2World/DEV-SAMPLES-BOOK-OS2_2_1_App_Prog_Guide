# Builds PROG8B.EXE
# Invoke with:  NMAKE PROG8B.MAK

PROG=PROG8B
# Debug flags:  /W3 /Ti+
CFLAGS=/C+ /Q+ /Sm /Gm+ /Ge+ /Gd- /Ss+ /W3 /Ti+
# Debug flag:  /DE
LFLAGS=/ST:24000 /NOL /NOI /L /M:FULL /PM:VIO /DE
# Taking the default libraries

.SUFFIXES:

.SUFFIXES: .c

ALL: $(PROG).EXE

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

{.}.c.obj:
   ICC.EXE $(CFLAGS) .\$*.c

