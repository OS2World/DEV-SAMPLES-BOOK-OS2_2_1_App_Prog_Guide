/**********************************************************/
/* Chapter 10.  Program illustrating the use of a muxwait */
/*              semaphore                                 */
/**********************************************************/


#define INCL_DOSSEMAPHORES
#include <os2.h>
#include <stdlib.h>
#include <stdio.h>

#define STACKSIZE 4096

VOID PrintABC(PVOID arglist);
HMTX hmtxMySem = (HMTX)NULL;
HMUX hmuxMyMuxwait;

SEMRECORD hevMyEvents[10];

INT main(VOID)
{
   ULONG ulUser;
   USHORT i;

   DosCreateMutexSem((PSZ)NULL, &hmtxMySem, 0, FALSE);
   memset(hevMyEvents, '\0', sizeof(hevMyEvents));
   for ( i = 0; i < 10; ++i) {
      DosCreateEventSem((PSZ)NULL,
                        (PHEV)&hevMyEvents[i].hsemCur,
                        0, FALSE);
      hevMyEvents[i].ulUser = i;
   }
   DosCreateMuxWaitSem((PSZ)NULL, &hmuxMyMuxwait, 10,
                       hevMyEvents, DCMW_WAIT_ALL);
   for ( i = 0; i < 10; ++i)
      _beginthread(PrintABC, NULL, STACKSIZE,
                   (PVOID)hevMyEvents[i].hsemCur);
   DosWaitMuxWaitSem(hmuxMyMuxwait, SEM_INDEFINITE_WAIT,
                     &ulUser);
   DosCloseMuxWaitSem(hmuxMyMuxwait);
   for ( i = 0; i < 10; ++i)
      DosCloseEventSem((HEV)hevMyEvents[i].hsemCur);
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
   DosPostEventSem((HEV)arglist);
}

