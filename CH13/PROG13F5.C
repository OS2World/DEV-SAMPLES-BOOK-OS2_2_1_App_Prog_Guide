/***************************************/
/* Chapter 13.  The DosStartTimer API  */
/***************************************/

#define INCL_DOS
#include <os2.h>

int main (int argc, void *argv[])
{
   /* This program sounds an alarm every 5 seconds, */
   /* for 30 seconds.                               */

   HEV    ESem;
   HTIMER Timer;
   ULONG  AlarmTime;
   int    i;
   ULONG  j;
   int    rc;

   /* Set time in milliseconds */
   AlarmTime  = 5000;

   /* Create a shared, unnamed event semaphore       */
   DosCreateEventSem (NULL,       /* unnamed         */
                      &ESem,      /* ptr to handle   */
                      DC_SEM_SHARED, /* shared       */
                      0);         /* initially 'set' */

   rc = DosStartTimer(AlarmTime, (HSEM) ESem, &Timer);
   if (rc) {
      printf("DosStartTimer failed.  RC = %ld\n", rc);
   }

   j = 0;
   /* In this loop, we increment the number of alarms */
   /* sounded not by 1 but by the number of times     */
   /* the semaphore was posted.  This is in case 10   */
   /* seconds or more passes before the program is    */
   /* scheduled to run again.                         */

   for (i=0; i<6 ; i++ ) {
      DosWaitEventSem(ESem, SEM_INDEFINITE_WAIT);
      DosResetEventSem(ESem, &j);   /* Find # times posted */
      for (; j>0 ; j--) {
         DosBeep(1300, 0500);
      } /* endfor */
   } /* endfor */

   DosStopTimer(Timer);
   return 0;
}

