/*****************************************/
/* Chapter 13.  Setting the system clock */
/*****************************************/

#define INCL_DOS
#include <os2.h>

int main (int argc, void *argv[])
{

   DATETIME DateTime;          /* DATETIME structure    */
   APIRET rc;

   /* First we must set up the structure */

   /* 1 PM is 13 hours, 0 minutes  */
   DateTime.hours =      (UCHAR) 13;
   DateTime.minutes =    (UCHAR) 0;
   DateTime.seconds =    (UCHAR) 0;
   DateTime.hundredths = (UCHAR) 0;

   /* April 1, 1993 is day 1, month 4, year 1993  */
   DateTime.day =        (UCHAR) 1;
   DateTime.month =      (UCHAR) 4;
   DateTime.year =      (USHORT) 1993;

   /* CST is 6 hours off GMT */
   DateTime.timezone =   (SHORT) 6;

   /* April 1, 1993 is a Thursday */
   DateTime.weekday =  (UCHAR) 4;

   /* Now we can use the API to set the current date */
   rc = DosSetDateTime(&DateTime);

   return 0;
}

