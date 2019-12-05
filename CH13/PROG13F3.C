/**********************************/
/* Chapter 13.  The DosSleep API  */
/**********************************/

#define INCL_DOS
#include <os2.h>

int main (int argc, void *argv[])
{
   /* This program sleeps for 2 seconds of scheduled time */

   ULONG sleepTime;

   sleepTime = 2000;     /* 2 seconds, in milliseconds */
   DosSleep(sleepTime);  /* Sleep for 2 seconds        */
   printf("Yaaawwwn.  That was a nice nap!\n");

   return 0;
}

