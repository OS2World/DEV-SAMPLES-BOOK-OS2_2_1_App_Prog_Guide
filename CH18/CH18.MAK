#
# CH18.MAK
# Makefile for classes and clients in Chapter 18
#

SC_OPTS=-sdef;ih;ph;h;c;sc
CF_DLL=-c -Ti+ -Ge- -Q+
CF_EXE=-c -Ti+ -Ge+ -Q+
LF=$(LF) /noi /pm:vio /debug /stack:8192
IMP_LIBS=som.lib
CLI_LIBS1=som.lib+metacalc.lib
CLI_LIBS2=som.lib+fifoq_1.lib
CLI_LIBS3=som.lib+fifoq.lib+lifoq.lib
CLI_LIBS4=som+metacalc+fanccalc
CLI_LIBS5=som+lists
CLI_LIBS6=som+metacalc+fanccalc+dumbcalc+lifoq+fifoq+lists

all        :  metacalc.dll fanccalc.dll dumbcalc.dll lists.dll fifoq.dll \
              lifoq.dll fifoq_1.dll client.exe client2.exe client3.exe   \
              client4.exe pch18f16.exe

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
                      $(CLI_LIBS1),fanccalc.def;
              implib fanccalc.lib fanccalc.def

dumbcalc.ih   :  dumbcalc.csc
              sc $(SC_OPTS) dumbcalc.csc

dumbcalc.obj  :  dumbcalc.c dumbcalc.ih
              icc $(CF_DLL) dumbcalc.c

dumbcalc.dll  :  dumbcalc.obj
              link386 $(LF) dumbcalc.obj,dumbcalc.dll,NUL, \
                      $(CLI_LIBS4),dumbcalc.def;
              implib dumbcalc.lib dumbcalc.def

lists.ih   :  lists.csc
              sc $(SC_OPTS) lists.csc

lists.obj  :  lists.c lists.ih
              icc $(CF_DLL) lists.c

lists.dll  :  lists.obj
              link386 $(LF) lists.obj,lists.dll,NUL, \
                      som,lists.def;
              implib lists.lib lists.def

fifoq.ih   :  fifoq.csc
              sc $(SC_OPTS) fifoq.csc

fifoq.obj  :  fifoq.c fifoq.ih
              icc $(CF_DLL) fifoq.c

fifoq.dll  :  fifoq.obj
              link386 $(LF) fifoq.obj,fifoq.dll,NUL, $(CLI_LIBS5),fifoq.def;
              implib fifoq.lib fifoq.def

fifoq_1.ih   :  fifoq_1.csc
              sc $(SC_OPTS) fifoq_1.csc

fifoq_1.obj  :  fifoq_1.c fifoq_1.ih
              icc $(CF_DLL) fifoq_1.c

fifoq_1.dll  :  fifoq_1.obj
              link386 $(LF) fifoq_1.obj,fifoq_1.dll,NUL, \
                      som,fifoq_1.def;
              implib fifoq_1.lib fifoq_1.def

lifoq.ih   :  lifoq.csc
              sc $(SC_OPTS) lifoq.csc

lifoq.obj  :  lifoq.c lifoq.ih
              icc $(CF_DLL) lifoq.c

lifoq.dll  :  lifoq.obj
              link386 $(LF) lifoq.obj,lifoq.dll,NUL, $(CLI_LIBS5),lifoq.def;
              implib lifoq.lib lifoq.def

client.obj :  client.c metacalc.ih
               icc $(CF_EXE) client.c

client.exe :  client.obj
               link386 $(LF) client.obj,client.exe,NUL, $(CLI_LIBS1);

client2.obj :  client2.c fifoq_1.ih
               icc $(CF_EXE) client2.c

client2.exe :  client2.obj
               link386 $(LF) client2.obj,client2.exe,NUL, $(CLI_LIBS2);

client3.obj :  client3.c lifoq.ih
               icc $(CF_EXE) client3.c

client3.exe :  client3.obj
               link386 $(LF) client3.obj,client3.exe,NUL, $(CLI_LIBS6);

client4.obj :  client4.c lifoq.ih
               icc $(CF_EXE) client4.c

client4.exe :  client4.obj
               link386 $(LF) client4.obj,client4.exe,NUL, $(CLI_LIBS6);

pch18f16.obj :  pch18f16.c lifoq.ih
               icc $(CF_EXE) pch18f16.c

pch18f16.exe :  pch18f16.obj
               link386 $(LF) pch18f16.obj,pch18f16.exe,NUL, $(CLI_LIBS6);
