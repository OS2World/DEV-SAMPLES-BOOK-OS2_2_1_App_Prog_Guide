#
# MAK19_1.MAK
# Makefile for String class example 1
#

SC_OPTS=-sdef;ih;h;c;sc
CF_DLL=-c -Ti+ -Ge- -Ss+
CF_EXE=-c -Ti+ -Ge+ -Ss+
LF=$(LF) /noi /pm:vio /debug /stack:8192
IMP_LIBS=som.lib
CLI_LIBS=som.lib+strng.lib

all        :  strng.dll client.exe client2.exe client3.exe client4.exe

strng.ih   :  strng.csc
              sc $(SC_OPTS) strng.csc

strng.obj  :  strng.c strng.ih
              icc $(CF_DLL) strng.c

strng.dll  :  strng.obj
              link386 $(LF) strng.obj,strng.dll,NUL, $(IMP_LIBS),strng.def;
              implib strng.lib strng.def

client.obj :  client.c strng.ih
              icc $(CF_EXE) client.c

client.exe :  client.obj
              link386 $(LF) client.obj,client.exe,NUL, $(CLI_LIBS);

client2.obj :  client2.c strng.ih
               icc $(CF_EXE) client2.c

client2.exe :  client2.obj
               link386 $(LF) client2.obj,client2.exe,NUL, $(CLI_LIBS);

client3.obj :  client3.c strng.ih
               icc $(CF_EXE) client3.c

client3.exe :  client3.obj
               link386 $(LF) client3.obj,client3.exe,NUL, $(CLI_LIBS);

client4.obj :  client4.c strng.ih
               icc $(CF_EXE) client4.c

client4.exe :  client4.obj
               link386 $(LF) client4.obj,client4.exe,NUL, $(CLI_LIBS);
