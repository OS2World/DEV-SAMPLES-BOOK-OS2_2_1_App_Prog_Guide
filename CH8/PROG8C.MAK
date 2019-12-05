# Builds PROG8C.EXE and PROG8CA.EXE
# Invoke with:  NMAKE PROG8C.MAK
# Run PROG8C.EXE in one OS/2 session and then run PROG8CA.EXE in 
#  another OS/2 session.

PROG=PROG8C
PROGA=PROG8CA
# Debug flags:  /W3 /Ti+
CFLAGS=/C+ /Q+ /Sm /Gm+ /Ge+ /Gd- /Ss+ /W3 /Ti+
# Debug flag:  /DE
LFLAGS=/ST:24000 /NOL /NOI /L /M:FULL /PM:VIO /DE
# Taking the default libraries

.SUFFIXES:

.SUFFIXES: .c

ALL: $(PROG).EXE $(PROGA).EXE

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

$(PROGA).EXE:  \
  $(PROGA).OBJ \
  $(PROGA).DEF \
  $(PROG).MAK
   @REM @<<$(PROGA).@0
     $(LFLAGS)+
     $(PROGA).OBJ
     $(PROGA).EXE
    
    
     $(PROGA).DEF;
<<
   LINK386.EXE @$(PROGA).@0

{.}.c.obj:
   ICC.EXE $(CFLAGS) .\$*.C

