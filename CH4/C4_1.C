/* c4_1.c - Pick the winning numbers. */

#define INCL_DOSDATETIME   /* Date and time values */
#include <os2.h>
#include <stdio.h>   /* for the printf functions */
#include <stdlib.h>  /* for the rand functions */

#define TRUE  1
#define FALSE 0

VOID main (void)
{
   INT rnum;         /* random number */
   ULONG seed; /* random number seed */
   DATETIME  DateTime;  /* Date and time structure */
   INT num[6];
   INT i,j,goOn;
   APIRET rc;

   /* Seed the random number generator */
   rc = DosGetDateTime(&DateTime);
   seed = DateTime.hundredths;
   srand(seed);
   printf("Random seed = %d.\n",seed);

   /* initialize the numbers array */
   for (i=0;i<6;i++)
      num[i] = 0;

   /* Choose Numbers */
   for (i=0;i<6;i++) {
      do {
         goOn = TRUE;
         rnum = rand();
         if ((rnum > 50) || (rnum < 1))
             goOn = FALSE;
         else
            for (j=0;j<6;j++)
               if (num[j] == rnum)
                   goOn = FALSE;
      } while (goOn == FALSE);
      num[i] = rnum;
   }

   /* Print the results */
   printf("The winning numbers are: ");
   for (i=0;i<6;i++)
      printf("%d ",num[i]);
   printf("\nGood luck!\n");
}

