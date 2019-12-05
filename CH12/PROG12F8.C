/************************************************************/
/* Chapter 12.  Program illustrating waiting on a queue for */
/*              something to be written to it               */
/************************************************************/

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

   DosCreateQueue(&hqQueue, QUE_FIFO, "\\QUEUES\\myqueue");

   _beginthread(WriteQueue, NULL, STACKSIZE, (PVOID)NULL);

   /* Wait until an element is found on the queue and*/
   /* then read it from the queue.                   */
   while (!DosReadQueue(hqQueue, &reqData, &cbLen,
                        &pMsg, 0, DCWW_WAIT, &Prio,
                        (HEV)NULL)) {
      printf("Reading element #%d, ulUser %d\n", ulItem++,
             reqData.ulData);
      if (reqData.ulData == KILLQUEUE) {
         break;
      }
   }

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