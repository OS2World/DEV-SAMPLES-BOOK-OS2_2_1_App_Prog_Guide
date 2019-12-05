/***********************************************************/
/* Chapter 11.  Attaching to a named pipe - client actions */
/***********************************************************/

#define INCL_DOSNMPIPES
#define INCL_DOSFILEMGR
#define INCL_ERRORS
#include <os2.h>

int main (int argc, void *argv[])
{

   HPIPE   CPipeHndl;               /* Client handle for pipe1*/
   UCHAR   PipeName[80];            /* name of the named pipe */
   ULONG   DefWaitTimeOut;          /* default timeout for    */
                                    /*     DosWaitNPipe API   */
   /* The next variables are for the DosOpen call     */
   ULONG    Action;
   APIRET  rc;

   strcpy(PipeName, "\\PIPE\\MYPIPE");  /* Name of pipe       */
   rc = ERROR_PIPE_BUSY;                /* Start the loop     */

   while (rc == ERROR_PIPE_BUSY) {
      rc = DosWaitNPipe(PipeName,
                        -1);             /* Wait indefinitely */
      if (!rc) {                /* Pipe instance is available */
         rc = DosOpen(PipeName,
                 &CPipeHndl,
                 &Action,               /* output status     */
                 0,                     /* ignored           */
                 0,                     /*                   */
                 FILE_OPEN,
                 OPEN_ACCESS_READWRITE | OPEN_SHARE_DENYNONE,
                 0);                    /* No extended attrs */
      } else {
         printf("rc from doswait is: %ld\n", (long) rc);
      } /* endif */
   }
   printf("final rc is: %ld\n", (long) rc);

   DosClose(CPipeHndl);
}

