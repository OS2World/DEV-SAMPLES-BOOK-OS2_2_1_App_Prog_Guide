/**************************************/
/* Chapter 13.  The DosAsyncTimer API */
/**************************************/

#define INCL_DOS
#include <os2.h>

int main (int argc, void *argv[])
{
   /* This program sounds an alarm after the number */
   /* of seconds input to the program.              */

   HEV    ESem;
   HTIMER Timer;
   ULONG  AlarmTime;
   int    rc;

   /* Convert input to milliseconds */
   AlarmTime  = (ULONG) (1000 * atoi((PSZ) argv[1]));

   /* Create a shared, unnamed event semaphore       */
   DosCreateEventSem (NULL,       /* unnamed         */
                      &ESem,      /* ptr to handle   */
                      DC_SEM_SHARED, /* shared       */
                      0);         /* initially 'set' */

   rc = DosAsyncTimer(AlarmTime, (HSEM) ESem, &Timer);
   if (rc) {
      printf("DosAsyncTimer failed.  RC = %ld\n", rc);
   }

   DosWaitEventSem(ESem, SEM_INDEFINITE_WAIT);
   DosBeep(1300, 0500);
   return 0;
}

