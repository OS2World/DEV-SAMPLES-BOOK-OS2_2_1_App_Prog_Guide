/************************************************************/
/* Chapter 12.  Program illustrating passing a data pointer */
/*              with the data written with a queue element  */
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
   PSZ string;
   ULONG cbLen, ulItem = 1;
   BYTE Prio;

   DosCreateQueue(&hqQueue, QUE_FIFO, "\\QUEUES\\myqueue");

   _beginthread(WriteQueue, NULL, STACKSIZE, (PVOID)NULL);

   /* Wait until an element is found on the queue and*/
   /* then read it from the queue.                   */
   while (!DosReadQueue(hqQueue, &reqData, &cbLen,
                        &pMsg, 0, DCWW_WAIT, &Prio,
                        (HEV)NULL)) {
      string = (PSZ)pMsg;
      printf("Reading element #%d string \"%s\"\n", ulItem++,
             string);
      free(string);
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
   PSZ str;

   for (i = 0; i < 10; ++i) {
      if (i != 9) {
         item = i;
      } else {
         item = KILLQUEUE;
      }
      str = (PSZ)malloc(15);
      strcpy(str, "dynamic buffer");
      printf("Writing element %d\n", item);
      DosWriteQueue(hqQueue, item, strlen(str), (PVOID)str,
                    0);
      DosSleep(1);
   }
}

