/* PROG9E.C */

#define INCL_DOSDATETIME   /* Date and time values */
#define INCL_DOSPROCESS     /* Include process and thread APIs */
#include <os2.h>
#include <stdio.h>   /* for the printf functions */
#include <ctype.h>  /* for the toascii function */
#include <stdlib.h>  /* for the rand functions */

#define NUMTHREADS 4

VOID thread_func (ULONG); /* thread function declaration */

VOID main (void)
{
   APIRET rc;
   INT   i;
   INT   rnum;         /* random number */
   ULONG seed; /* random number seed */
   ULONG threadArgs;
   ULONG threadFlags;    
   ULONG threadStackSize;
   TID   thread_id[NUMTHREADS];  /* array of createdthread IDs */
   DATETIME  DateTime;
   ULONG   priScope;  /* scope of priority change */
   ULONG   priClass;  /* class to set priority by */
   LONG    priDelta;  /* delta to change priority by */

   threadArgs = 0L;  /* No arguments */
   threadFlags = 1L;  /* Start the thread in a suspended state */
   threadStackSize = 4096;  /* Make the stack size a 4K block */

   /* first seed the random number generator */
   rc = DosGetDateTime(&DateTime);        /* Date/Time structure */
   seed = DateTime.hundredths;
   srand(seed);
   printf("Random seed = %d.\n",(seed*-1));

   for (i=0;i<NUMTHREADS;i++) {
      rc = DosCreateThread(&thread_id[i],    /* TID returned */
         (PFNTHREAD)thread_func, /* Address of thread function */
         threadArgs, /* Arguments to pass to the thread */
         threadFlags, /* Flags to start the thread running or suspended */
         threadStackSize);

      if (rc != 0) {
         printf("Error calling DosCreateThread with return code = %ld", rc);
         return;
      }

      printf("#%d : TID = %d\n", i, thread_id[i]);
   }

   /* Randomly set priorities */
   for (i=0;i<NUMTHREADS;i++) {
      do {
         rnum = rand() - 31;
      } while ((rnum > 31) || (rnum < -31));

      printf("Rand = %d\n",rnum);
      priScope = PRTYS_THREAD;   /* Only change the thread's priority */
      priClass = PRTYC_NOCHANGE;   /* Keep thread in the same class */
      priDelta = rnum;   /* Modify the priority with a delta */
 
      rc = DosSetPriority(priScope, priClass, priDelta, thread_id[i]);
 
      if (rc != 0) {
         printf("DosSetPriority error: return code = %ld", rc);
         return;
      }
   }

   /* Start all threads that were created and suspended */
   for (i=0;i<NUMTHREADS;i++) {
      DosResumeThread(thread_id[i]);
   }

   /* Wait for the threads to complete */
   for (i=0;i<NUMTHREADS;i++) {
      printf("\nWaiting for thread #%d.\n",thread_id[i]);
      DosWaitThread(&thread_id[i], 0);
   }

   return;
}

VOID thread_func (ULONG Parm)
{
   int i,j;
   TID tid;
   APIRET rc;
   PTIB    pptib;      /* Pointer to the TIB */
   PPIB    pppib;      /* Pointer to the PIB */
   UCHAR ch;

   /* find out what thread it is and the character used */
   rc = DosGetInfoBlocks(&pptib,&pppib);
   tid = pptib->tib_ptib2->tib2_ultid;  /* thread id */
   ch = toascii(32+tid);  /* unique character to print out */
   printf("\nStarting TID #%d with character %c.\n",tid,ch);

   /* print out characters with a slight pause in between */
   for (i=1;i<1000;i++) {
      DosSleep(10);  /* 10 millisecond delay */
      printf("%c",ch);
   }

   /* Herald the end */
   printf("\nTID #%d Complete\n",tid);
   DosExit(EXIT_THREAD, 0);  /* Exit thread with result 0 */
}

