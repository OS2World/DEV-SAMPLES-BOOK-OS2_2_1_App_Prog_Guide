/*************************************************************/
/* Chapter 10.  A program illustrating a potential dead lock */
/*              situation                                    */
/*************************************************************/

#define INCL_DOSSEMAPHORES
#define INCL_DOSPROCESS
#include <os2.h>
#include <stdlib.h>
#include <stdio.h>

#define STACKSIZE 4096

VOID Thread2(PVOID arglist);
VOID Thread3(PVOID arglist);
HMTX hmtxScreen = (HMTX)NULL,
     hmtxArray = (HMTX)NULL;
USHORT myarray[10];

INT main(VOID)
{
   USHORT i;

   DosCreateMutexSem((PSZ)NULL, &hmtxScreen, 0, FALSE);
   DosCreateMutexSem((PSZ)NULL, &hmtxArray, 0, FALSE);
   memset(myarray, '\0', sizeof(myarray));
   _beginthread(Thread2, NULL, STACKSIZE, NULL);
   _beginthread(Thread3, NULL, STACKSIZE, NULL);
   DosSleep(5000);
   DosCloseMutexSem(hmtxScreen);
   DosCloseMutexSem(hmtxArray);
   return(0L);
}

VOID Print0to9()
{
   USHORT i;

   for (i=0; i < 10; ++i) printf("i = %d ", i);
   printf("\n");
}

VOID UpdateArray()
{
   USHORT i;

   for (i=0; i < 10; ++i) myarray[i]++;
}

VOID Thread2(PVOID arglist)
{
   USHORT i;

   for (i=0; i < 10; ++i) {
      DosRequestMutexSem(hmtxScreen, SEM_INDEFINITE_WAIT);
      Print0to9();
      DosRequestMutexSem(hmtxArray, SEM_INDEFINITE_WAIT);
      UpdateArray();
      DosReleaseMutexSem(hmtxArray);
      DosReleaseMutexSem(hmtxScreen);
   }
}

VOID Thread3(PVOID arglist)
{
   USHORT i;

   for (i=0; i < 10; ++i) {
      DosRequestMutexSem(hmtxArray, SEM_INDEFINITE_WAIT);
      UpdateArray();
      DosRequestMutexSem(hmtxScreen, SEM_INDEFINITE_WAIT);
      Print0to9();
      DosReleaseMutexSem(hmtxArray);
      DosReleaseMutexSem(hmtxScreen);
   }
}

