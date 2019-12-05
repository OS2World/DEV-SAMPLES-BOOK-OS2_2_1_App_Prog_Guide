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

all        :  strng.dll client.exe

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
