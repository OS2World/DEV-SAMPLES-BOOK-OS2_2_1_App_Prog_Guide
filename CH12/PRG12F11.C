/*********************************************************/
/* Chapter 12.  Program illustrating waiting on multiple */
/*              queues                                   */
/*********************************************************/

#define INCL_ERRORS
#define INCL_DOSPROCESS
#define INCL_DOSSEMAPHORES
#define INCL_DOSQUEUES
#include <os2.h>
#include <stdlib.h>
#include <stdio.h>

#define QCOUNT 4
#define STACKSIZE 4096

VOID WriteQueue(PVOID arglist);

INT main(VOID)
{
   SEMRECORD hevMyEvents[QCOUNT];
   REQUESTDATA reqData;
   CHAR qname[20], qnamesuf[5];
   HQUEUE qa[QCOUNT];
   USHORT cWrites[QCOUNT];
   ULONG i, ulUser, cbLen, cPosts;
   PVOID pMsg;
   HMUX hmuxMyMuxwait;
   BOOL bRaceOver;
   BYTE Prio;

   /* Create QCOUNT number of queues and event semaphores*/
   /* and associate the event semaphore with the queue   */
   for (i = 0; i < QCOUNT; ++i) {

      /* Create a unique queue name */
      memset(&qname, '\0', sizeof(qname));
      strcpy(qname, "\\queues\\multq");
      memset(qnamesuf, '\0', sizeof(qnamesuf));
      _itoa(i, qnamesuf, 10);
      strcat(qname, qnamesuf);

      DosCreateQueue(&qa[i], QUE_FIFO, qname);
      DosCreateEventSem((PSZ)NULL,
                        (PHEV)&hevMyEvents[i].hsemCur,
                        0, FALSE);
      hevMyEvents[i].ulUser = i;
      DosReadQueue(qa[i], &reqData, &cbLen, &pMsg, 0,
                   DCWW_NOWAIT, &Prio,
                   (HEV)hevMyEvents[i].hsemCur);
   }

   /* Create the muxwait semaphore so you can wait on    */
   /* any of the event semaphore getting posted.         */
   DosCreateMuxWaitSem((PSZ)NULL, &hmuxMyMuxwait, QCOUNT,
                       hevMyEvents, DCMW_WAIT_ANY);

   /* Create the QCOUNT number of threads that will at   */
   /* random times write an element to the queue.        */
   for (i = 0; i < QCOUNT; ++i) {
      _beginthread(WriteQueue, NULL, STACKSIZE,
                   (PVOID)qa[i]);
   }

   /* Loop until one of the queues has been written to   */
   /* QCOUNT times.                                      */
   bRaceOver = FALSE;
   memset(cWrites, '\0', sizeof(cWrites));
   while (!bRaceOver) {

      /* Wait until one of the queues is written to     */
      DosWaitMuxWaitSem(hmuxMyMuxwait, SEM_INDEFINITE_WAIT,
                        &ulUser);

      /* Read everything off the queue, increment the   */
      /* count for this queue and reset the event sem.  */
      while (DosReadQueue(qa[ulUser], &reqData, &cbLen,
                          &pMsg, 0, DCWW_NOWAIT, &Prio,
                          (HEV)hevMyEvents[ulUser].hsemCur)
             != ERROR_QUE_EMPTY) {
         cWrites[ulUser]++;
         printf("Reading from Queue #%d, write #%d\n", ulUser,
                cWrites[ulUser]);
      }
      DosResetEventSem((HEV)hevMyEvents[ulUser].hsemCur, &cPosts);

      if (cWrites[ulUser] == QCOUNT) {
         bRaceOver = TRUE;
      }
   }

   /* Destroy the queue and semaphore resources this     */
   /* program used.                                      */
   for (i = 0; i < QCOUNT; ++i) {
      DosCloseQueue(qa[i]);
      DosCloseEventSem((HEV)hevMyEvents[i].hsemCur);
   }
   DosCloseMuxWaitSem(hmuxMyMuxwait);
   return(0L);
}

VOID WriteQueue(PVOID arglist)
{
   USHORT i;
   APIRET rc;
   ULONG x;

   /* Issue QCOUNT number of writes to the queue whose   */
   /* handle was passed when creating the thread at      */
   /* random intervals of time less than a second.       */
   for (i = 0; i < QCOUNT; ++i) {
      x = rand();
      DosSleep(x % 1000);
      rc = DosWriteQueue((HQUEUE)arglist, 0, 0, (PSZ)NULL,
                         0);

      /* If the handle is invalid the program must have  */
      /* closed the queue therefore fall out of the      */
      /* thread.                                         */
      if (rc == ERROR_QUE_INVALID_HANDLE) {
         break;
      }
   }
}

