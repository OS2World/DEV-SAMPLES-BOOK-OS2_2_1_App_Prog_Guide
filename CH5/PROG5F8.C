/************************************************/
/* Chapter 5.  DosCopy, DosMove, and DosDelete. */
/************************************************/
#include <stdio.h>

#define INCL_DOSFILEMGR
#include <os2.h>

INT main(VOID)
{
   APIRET rc;

   rc = DosCopy("C:\\CONFIG.SYS", ".\\CONFIG.BAK",
                DCPY_EXISTING | DCPY_FAILEAS);

   if (!rc) {
      DosDelete("C:\\CONFIG.SYS");

      rc = DosMove(".\\CONFIG.BAK", "C:\\CONFIG.SYS");

      if (!rc) {
         DosDelete(".\\CONFIG.BAK");
      } else {
         printf("Unable to move file.  RC = %d\n", rc);
         return(1L);
      }
   } else {
      printf("Unable to copy CONFIG.SYS to CONFIG.BAK");
      printf(" rc = %d\n", rc);
      return(1L);
   }
   printf("CONFIG.SYS copied and replaced!\n");

   return(0L);
}
