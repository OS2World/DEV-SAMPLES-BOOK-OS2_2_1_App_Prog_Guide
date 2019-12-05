/**************************************/
/* Chapter 11.  Use of DosSetNPHState */
/**************************************/

#define INCL_DOSNMPIPES
#define INCL_DOSFILEMGR
#define INCL_ERRORS
#include <os2.h>

int main (int argc, void *argv[])
{
   #define REQ_BUF_SIZE   80
   #define REPLY_BUF_SIZE 80

   HPIPE   CPipeHndl;               /* Client handle for pipe */
   UCHAR   PipeName[80];            /* name of the named pipe */
   UCHAR   Request[REQ_BUF_SIZE];   /* Buffer Client's request*/
   UCHAR   Reply[REPLY_BUF_SIZE];   /* Buffer Server's reply  */
   ULONG   len;
   ULONG   num;
   APIRET  rc;

   /* The next variables are for the DosOpen call     */
   ULONG    Action;

   strcpy(PipeName, "\\PIPE\\MYPIPE");  /* Name of pipe  */
   strcpy(Request, "How much did I spend at the vet last year?");
   len = strlen(Request) + 1;

   do {

      /* Open the pipe       */
      rc = DosOpen(PipeName,
              &CPipeHndl,
              &Action,               /* output status     */
              0,                     /* ignored           */
              0,                     /*                   */
              FILE_OPEN,
              OPEN_ACCESS_READWRITE | OPEN_SHARE_DENYNONE,
              0);                    /* No extended attrs */

      if (rc) break;
      DosWrite(CPipeHndl, Request, len, &num); /* Send request */
      DosSleep(1000);   /* Give the server time to respond     */
                        /* If the client has higher priority,  */
                        /* then DosRead should get an error    */

      /* Set the pipe to read in message mode, and to not block*/
      rc = DosSetNPHState(CPipeHndl, NP_RMESG | NP_NOWAIT);

      rc = DosRead( CPipeHndl, Reply, 80, &num);/*Get response */
      if (!rc) printf("Reply was:  %s\n", Reply);
      else     printf("Did not have any data to read\n");
      DosClose(CPipeHndl);
   } while (0 ); /* enddo */
}

