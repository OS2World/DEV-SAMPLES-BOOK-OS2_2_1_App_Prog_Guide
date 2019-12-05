/***********************************************************/
/* Chapter 12.  Program illustrating waiting on an event   */
/*              semaphore that gets posted when an element */
/*              is written to a queue                      */
/***********************************************************/

#define INCL_ERRORS
#define INCL_DOSSEMAPHORES
#define INCL_DOSPROCESS
#define INCL_DOSQUEUES
#include <os2.h>
#include <stdlib.h>
#include <stdio.h>

#define STACKSIZE 4096
#define KILLQUEUE 1000

VOID WriteQueue(PVOID arglist);
HQUEUE hqQueue;

INT main(VOID)
{
   REQUESTDATA reqData;
   PVOID pMsg;
   ULONG cbLen, ulItem = 1;
   BYTE Prio;
   HEV hevMySem;

   DosCreateQueue(&hqQueue, QUE_FIFO, "\\QUEUES\\myqueue");

   DosCreateEventSem((PSZ)NULL, (PHEV)&hevMySem,
                     0, FALSE);
   DosReadQueue(hqQueue, &reqData, &cbLen, &pMsg, 0,
                DCWW_NOWAIT, &Prio, (HEV)hevMySem);

   _beginthread(WriteQueue, NULL, STACKSIZE, (PVOID)NULL);

   while (!DosWaitEventSem(hevMySem, SEM_INDEFINITE_WAIT)) {
      while (DosReadQueue(hqQueue, &reqData, &cbLen,
                          &pMsg, 0, DCWW_NOWAIT, &Prio,
                          (HEV)hevMySem)
             != ERROR_QUE_EMPTY) {
         printf("Reading element #%d, ulUser %d\n", ulItem++,
                reqData.ulData);
         if (reqData.ulData == KILLQUEUE) {
            break;
         }
      }
      if (reqData.ulData == KILLQUEUE) {
         break;
      }
   }

   DosCloseEventSem(hevMySem);
   DosCloseQueue(hqQueue);
   return(0L);
}

VOID WriteQueue(PVOID arglist)
{
   USHORT i;
   ULONG item;

   for (i = 0; i < 10; ++i) {
      if (i != 9) {
         item = i;
      } else {
         item = KILLQUEUE;
      }
      printf("Writing element %d\n", item);
      DosWriteQueue(hqQueue, item, 0, (PSZ)NULL, 0);
      DosSleep(1);
   }
}

