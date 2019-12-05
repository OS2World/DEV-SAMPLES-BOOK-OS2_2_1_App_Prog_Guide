/*************************************************************/
/* Chapter 10.  Program illustrating the use of hypothetical */
/*              ScreenAccess functions                       */
/*************************************************************/

#define INCL_DOSPROCESS
#include <os2.h>
#include <stdlib.h>
#include <stdio.h>

#define STACKSIZE 4096

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
      WaitForScreenAccess();
      printf("A");
      printf("B");
      printf("C\n");
      ReleaseScreenAccess();
      ++i;
   }
}

VOID PrintDEF(PVOID arglist)
{
   USHORT i = 0;

   while (i < 10) {
      WaitForScreenAccess();
      printf("D");
      printf("E");
      printf("F\n");
      ReleaseScreenAccess();
      ++i;
   }
}

