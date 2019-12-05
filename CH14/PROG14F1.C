/***************************************************************/
/* Chapter 14.  Program using DosErrClass in an error logging  */
/*              facility                                       */
/***************************************************************/

#define INCL_DOSMISC
#define INCL_DOSDATETIME
#include <os2.h>

#include <stdio.h>

VOID LogError(APIRET APIrc, ULONG ulSourceLine,
              PSZ pszSourceFile)
{
   FILE * logfile;
   ULONG Class, Action, Locus;
   DATETIME dt;

   if ((logfile = fopen("ERROR.LOG", "a")) == NULL) {
      printf("Couldn't open log file ERROR.LOG\n");
      return;
   }
   DosErrClass(APIrc, &Class, &Action, &Locus);
   DosGetDateTime(&dt);
   fprintf(logfile, "Code Module %s, line %ld ",
           pszSourceFile, ulSourceLine);
   fprintf(logfile, "logged error %ld ", APIrc);
   fprintf(logfile, "with error class = %ld, ", Class);
   fprintf(logfile, "error action = %ld, ", Action);
   fprintf(logfile, "and originator = %ld ", Locus);
   fprintf(logfile, "on date %d/%d/%d ", dt.month,
           dt.day, dt.year - 1900);
   fprintf(logfile, "at time %d:%d:%d.\n", dt.hours,
           dt.minutes, dt.seconds);
   fclose(logfile);
}

INT main(VOID)
{
   APIRET APIrc;

   APIrc = DosDeleteDir("THISDIR");
   if (APIrc != 0) LogError(APIrc, __LINE__, __FILE__);

   APIrc = DosDelete("THISFILE.TXT");
   if (APIrc != 0) LogError(APIrc, __LINE__, __FILE__);

   return(0L);
}
