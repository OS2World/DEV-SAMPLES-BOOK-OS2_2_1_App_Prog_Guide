/* PROG9CA.C */
 
#define INCL_DOSPROCESS       /* Include process and thread APIs */
#include <os2.h>
 
main (USHORT argc, PCHAR argv[])
{
   INT i;
   
   for (i=1;i<1000;i++) {
      printf(argv[1]);
   } /* endfor */

   DosExit(EXIT_PROCESS,0); /* Exit process with result 0 */
} 
