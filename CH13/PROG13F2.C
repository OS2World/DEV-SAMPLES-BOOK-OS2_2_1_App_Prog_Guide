/***************************************/
/* Chapter 13.  Using the system clock */
/***************************************/

#define INCL_DOS
#include <os2.h>

int main (int argc, void *argv[])
{
   /* This program has two parameters, the first is a month*/
   /* and the second is a day                              */

   DATETIME DateTime;          /* DATETIME structure       */
   int      BirthMonth;
   int      BirthDay;

   BirthMonth = atoi((PSZ) argv[1]);
   BirthDay =   atoi((PSZ) argv[2]);

   DosGetDateTime(&DateTime);  /* Get the current date */

   /* Compare the current date to the input day and month */
   if ((DateTime.month == (UCHAR) BirthMonth) &&
       (DateTime.day   == (UCHAR) BirthDay)) {
       printf("Happy Birthday!\n");
   } else if (DateTime.month == BirthMonth) {
      if (DateTime.day > BirthDay) {
         printf("Happy Belated Birthday!\n");
      } else {
         printf("Your birthday is this month!\n");
      }
   } else if (DateTime.month < BirthMonth) {
      printf("Your birthday is in another %d months.\n",
             BirthMonth - DateTime.month);
   } else {
      printf("Your birthday is in another %d months.\n",
             BirthMonth + 12 - DateTime.month);
   }
   return 0;
}

