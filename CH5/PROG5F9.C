/************************************************************/
/* Chapter 5.  Program illustrating searching for multiple  */
/*             files using DosFindFirst, DosFindNext, and   */
/*             DosClose.                                    */
/************************************************************/

#include <stdio.h>

#define INCL_DOSFILEMGR
#include <os2.h>

INT main( INT argc, CHAR *argv[], CHAR *envp[] )
{
   APIRET rc;
   HDIR handleFileFirst = 0x0001;
   ULONG count = 1, numfiles = 0;
   FILEFINDBUF3 findbuf;

   if (argc < 2) {
      printf("Please pass file search string\n");
      return(1L);
   }

   rc = DosFindFirst(argv[1], &handleFileFirst, 0,
                     (PVOID)&findbuf, sizeof(findbuf),
                     &count, FIL_STANDARD);
   while (!rc) {
      printf("Matching file %s found\n", findbuf.achName);
      numfiles++;
      rc = DosFindNext(handleFileFirst, (PVOID)&findbuf,
                       sizeof(findbuf), &count);
   }
   DosFindClose(handleFileFirst);

   printf("There were %d matching files.\n", numfiles);

   return(0L);
}

