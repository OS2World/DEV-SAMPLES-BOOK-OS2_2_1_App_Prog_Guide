#
# CLIENT5.MAK
# Makefile for client using classes in Chapter 18
# You will need to copy the files for those classes
#    from the subdirectory for Chapter18
#

SC_OPTS=-sdef;ih;ph;h;c;sc
CF_DLL=-c -Ti+ -Ge- -Ss+
CF_EXE=-c -Ti+ -Ge+ -Ss+
LF=$(LF) /noi /pm:vio /debug /stack:8192
IMP_LIBS=som.lib
CLI_LIBS=som.lib+metacalc.lib+fanccalc.lib+dumbcalc.lib
CLI_LIBS2=som.lib+metacalc.lib
CLI_LIBS3=som.lib+metacalc.lib+fanccalc.lib

all        :  metacalc.dll fanccalc.dll dumbcalc.dll client5.exe

metacalc.ih   :  metacalc.csc
              sc $(SC_OPTS) metacalc.csc

metacalc.obj  :  metacalc.c metacalc.ih
              icc $(CF_DLL) metacalc.c

metacalc.dll  :  metacalc.obj
              link386 $(LF) metacalc.obj,metacalc.dll,NUL, \
                      $(IMP_LIBS),metacalc.def;
              implib metacalc.lib metacalc.def

fanccalc.ih   :  fanccalc.csc
              sc $(SC_OPTS) fanccalc.csc

fanccalc.obj  :  fanccalc.c fanccalc.ih
              icc $(CF_DLL) fanccalc.c

fanccalc.dll  :  fanccalc.obj
              link386 $(LF) fanccalc.obj,fanccalc.dll,NUL, \
                      $(CLI_LIBS2),fanccalc.def;
              implib fanccalc.lib fanccalc.def

dumbcalc.ih   :  dumbcalc.csc
              sc $(SC_OPTS) dumbcalc.csc

dumbcalc.obj  :  dumbcalc.c dumbcalc.ih
              icc $(CF_DLL) dumbcalc.c

dumbcalc.dll  :  dumbcalc.obj
              link386 $(LF) dumbcalc.obj,dumbcalc.dll,NUL, \
                      $(CLI_LIBS3),dumbcalc.def;
              implib dumbcalc.lib dumbcalc.def

client5.obj :  client5.c metacalc.h fanccalc.h dumbcalc.h 
               icc $(CF_EXE) client5.c

client5.exe :  client5.obj
               link386 $(LF) client5.obj,client5.exe,NUL, $(CLI_LIBS);
