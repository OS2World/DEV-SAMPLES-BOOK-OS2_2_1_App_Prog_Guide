/***********************************************************/
/* Chapter 11.  Common usage scenario 1 - client side      */
/***********************************************************/

#define INCL_DOSNMPIPES
#define INCL_DOSFILEMGR
#define INCL_ERRORS
#include <os2.h>

int main (int argc, void *argv[])
{
   #define MAX_NAME_LEN   80
   #define REQ_BUF_SIZE   80
   #define REPLY_BUF_SIZE 80
   HPIPE   CPipeHndl;               /* Client handle for pipe1*/
   UCHAR   PipeName[MAX_NAME_LEN];  /* name of the named pipe */
   UCHAR   Request[REQ_BUF_SIZE];   /* Buffer Client's request*/
   UCHAR   Reply[REPLY_BUF_SIZE];   /* Buffer Server's reply  */
   ULONG   num;
   APIRET  rc;

   /* The next variables are for the DosOpen call     */
   ULONG    Action;

   strcpy(PipeName, "\\PIPE\\MYPIPE");  /* Name of pipe       */
   strcpy(Request, "How much did I spend on catfood last year?");

   /* This client only sends one request to the server        */
   /* It will try twice to connect to the server, and give up */
   /* if still unsuccessful.                                  */

   do {

      rc = DosOpen(PipeName,
              &CPipeHndl,
              &Action,               /* output status     */
              0,                     /* ignored           */
              0,                     /*                   */
              FILE_OPEN,
              OPEN_ACCESS_READWRITE | OPEN_SHARE_DENYNONE,
              0);                    /* No extended attrs */

      if (rc == ERROR_PIPE_BUSY) {   /* Try one more time */
         /* Use the default timeout  */
         rc = DosWaitNPipe(PipeName, 0);
         if ( rc ) break;
         rc = DosOpen(PipeName, &CPipeHndl, &Action, 0, 0,
              FILE_OPEN,
              OPEN_ACCESS_READWRITE | OPEN_SHARE_DENYNONE, 0);
      } /* endif */

      if (rc) {
         printf("Could not open the pipe\n");
         break;
      }

      DosWrite(CPipeHndl, Request, 80, &num);  /* Send request */
      DosRead( CPipeHndl, Reply, 80, &num);    /* Get response */

      printf("Reply from the server is:  %s\n", Reply);

      DosClose(CPipeHndl);

   } while (0 ); /* enddo - fall out of loop */

}

