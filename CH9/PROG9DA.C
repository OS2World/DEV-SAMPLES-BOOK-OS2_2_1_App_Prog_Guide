/* PROG9DA.C */
 
#include <os2.h>
#include <stdlib.h>

main (USHORT argc, PCHAR argv[])
{
   /* print character passed in argument string until killed */
   do {
      printf(argv[1]);
   } while (TRUE);
}

