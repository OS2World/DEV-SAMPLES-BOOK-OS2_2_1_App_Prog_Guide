/* PROG9BA.C */

#define INCL_DOSPROCESS       /* Include process and thread APIs */
#include <os2.h>

main (void)
{
   int i;

   printf("I'm alive!\n");
   for (i=1;i<100;i++ ) {
      printf("A");
   }

   DosExit(EXIT_PROCESS,0); /* Exit process with result 0 */
} 
