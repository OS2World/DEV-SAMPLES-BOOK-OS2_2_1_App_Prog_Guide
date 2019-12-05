/*************************************************************/
/* Chapter 10.  Example program that uses an event semaphore */
/*************************************************************/

#define INCL_DOSSEMAPHORES
#include <os2.h>
#include <stdlib.h>

#define STACKSIZE 4096

VOID Thread1(PVOID arglist);
HEV hevMyEvent = (HEV)NULL;

INT main(VOID)
{
   ULONG cPosts; /* Count of posts */

   printf("Starting program\n");
   DosCreateEventSem((PSZ)NULL, &hevMyEvent, 0, FALSE);
   _beginthread(Thread1, NULL, STACKSIZE, NULL);
   DosWaitEventSem(hevMyEvent, SEM_INDEFINITE_WAIT);
   printf("Semaphore posted\n");
   DosResetEventSem(hevMyEvent, &cPosts);
   _beginthread(Thread1, NULL, STACKSIZE, NULL);
   DosWaitEventSem(hevMyEvent, SEM_INDEFINITE_WAIT);
   printf("Semaphore posted\n");
   DosCloseEventSem(hevMyEvent);
   return(0L);
}

VOID Thread1(PVOID arglist)
{
   APIRET rc;

   printf("... Posting semaphore\n");
   rc = DosPostEventSem(hevMyEvent);
}

