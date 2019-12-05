#
# CALC.MAK
# Makefile for calculator class.
# metacalc.csc also defines a calculator class, with the same name
# metacalc.csc contains the calc class used in the latter part of the chapter
#

SC_OPTS=-sdef;ih;ph;h;c;sc
CF_DLL=-c -Ti+ -Ge- -Ss+
CF_EXE=-c -Ti+ -Ge+ -Ss+
LF=$(LF) /noi /pm:vio /debug /stack:8192
IMP_LIBS=som.lib
CLI_LIBS1=som.lib+calc.lib

all        :  calc.dll pch18f6.exe pch18f7.exe

calc.ih   :  calc.csc
              sc $(SC_OPTS) calc.csc

calc.obj  :  calc.c calc.ih
              icc $(CF_DLL) calc.c

calc.dll  :  calc.obj
              link386 $(LF) calc.obj,calc.dll,NUL, \
                      $(IMP_LIBS),calc.def;
              implib calc.lib calc.def


pch18f6.obj :  pch18f6.c calc.ih
               icc $(CF_EXE) pch18f6.c

pch18f6.exe :  pch18f6.obj
               link386 $(LF) pch18f6.obj,pch18f6.exe,NUL, \
                       $(CLI_LIBS1);

pch18f7.obj :  pch18f7.c calc.ih
               icc $(CF_EXE) pch18f7.c

pch18f7.exe :  pch18f7.obj
               link386 $(LF) pch18f7.obj,pch18f7.exe,NUL, \
                       $(CLI_LIBS1);


