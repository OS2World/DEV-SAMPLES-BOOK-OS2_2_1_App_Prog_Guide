/************************************************************/
/* Chapter 10.  Multiple-threaded resource management using */
/*              mutex semaphores                            */
/************************************************************/

#define INCL_DOSSEMAPHORES
#define INCL_DOSPROCESS
#include <os2.h>
#include <stdlib.h>
#include <stdio.h>

#define STACKSIZE 4096

VOID PrintABC(PVOID arglist);
HMTX hmtxMySem = (HMTX)NULL;

INT main(VOID)
{
   USHORT i;

   DosCreateMutexSem((PSZ)NULL, &hmtxMySem, 0, FALSE);
   for ( i = 0; i < 10; ++i)
      _beginthread(PrintABC, NULL, STACKSIZE, NULL);
   DosSleep(5000);
   DosCloseMutexSem(hmtxMySem);
   return(0L);
}

VOID PrintABC(PVOID arglist)
{
   DosRequestMutexSem(hmtxMySem, SEM_INDEFINITE_WAIT);
   printf("A");
   printf("B");
   printf("C ");
   DosReleaseMutexSem(hmtxMySem);
}

