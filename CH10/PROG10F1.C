/****************************************************************/
/* Chapter 10.  Program illustrating using a global variable to */
/*              protect a resource                              */
/****************************************************************/

#define INCL_DOSPROCESS
#include <os2.h>
#include <stdlib.h>
#include <stdio.h>

#define STACKSIZE 4096

ULONG ulScreenFlag = 0;

VOID PrintABC(PVOID arglist);
VOID PrintDEF(PVOID arglist);

INT main(VOID)
{

   _beginthread(PrintABC, NULL, STACKSIZE, NULL);
   _beginthread(PrintDEF, NULL, STACKSIZE, NULL);
   DosSleep(5000);
   return(0L);
}

VOID PrintABC(PVOID arglist)
{
   USHORT i = 0;

   while (i < 10) {
      if (ulScreenFlag == 0) {
         DosSleep(1);
         ulScreenFlag = 1;
         printf("A");
         DosSleep(1);
         printf("B");
         DosSleep(1);
         printf("C\n");
         ulScreenFlag = 0;
         ++i;
      }
   }
}

VOID PrintDEF(PVOID arglist)
{
   USHORT i = 0;

   while (i < 10) {
      if (ulScreenFlag == 0) {
         DosSleep(1);
         ulScreenFlag = 1;
         printf("D");
         DosSleep(1);
         printf("E");
         DosSleep(1);
         printf("F\n");
         ulScreenFlag = 0;
         ++i;
      }
   }
}

