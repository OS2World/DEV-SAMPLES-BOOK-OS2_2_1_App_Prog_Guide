/***********************************************************/
/* Chapter 11.  Common usage scenario - server side        */
/*              (same for both scenarios)                  */
/***********************************************************/

#define INCL_DOSNMPIPES
#define INCL_DOSFILEMGR
#include <os2.h>

int main (int argc, void *argv[])
{

   HPIPE   SPipeHndl;               /* Server handle for pipe1*/
   UCHAR   PipeName[80];            /* name of the named pipe */
   ULONG   PipeDir;                 /* direction of dataflow  */
   ULONG   PipeMode;      /* Blocking/nonblocking,  Byte/Msg..*/
   ULONG   ReadBufSize;             /* size of input buffer   */
   ULONG   WriteBufSize;            /* size of output buffer  */
   ULONG   DefWaitTimeOut;          /* default timeout for    */
                                    /*     DosWaitNPipe API   */
   UCHAR   Request[80];
   UCHAR   Reply[80];
              /* Loop through a given set of responses */
   PSZ     Myrep[5]= {"1", "2", "3", "4", "5"};
   ULONG   len;
   ULONG   num;
   ULONG   i;
   ULONG   j;
   APIRET  rc;

   /* For initializations, see Figure 12-5 */
   strcpy(PipeName, "\\PIPE\\MYPIPE");  /* Name of pipe       */
   PipeDir = NP_ACCESS_DUPLEX;      /* Full duplex pipe       */
               /* Nonblocking, message pipe, max 4 instances  */
   PipeMode = NP_WAIT | NP_WMESG | NP_RMESG | 0x04;
   ReadBufSize = 4096;
   WriteBufSize = 4096;
   DefWaitTimeOut = 2000;         /* Timeout in 2 seconds     */

   rc=DosCreateNPipe(PipeName,       /* Create one instance of   */
                  &SPipeHndl,     /* the pipe.                */
                  PipeDir,
                  PipeMode,
                  WriteBufSize,
                  ReadBufSize,
                  DefWaitTimeOut);

   j = 5;
   for   (i=0; i<5; i++) {        /* Connect up to 5 times    */
      rc=DosConnectNPipe(SPipeHndl);    /* Connect to server end */
                                     /* of the pipe, and wait    */
                                     /* for a client to attach   */

      rc= DosRead( SPipeHndl, Request, 80, &num); /* Get request */

      while (num != 0) {       /* Client sent another request */
         printf("The request is:  %s\n", Request);
         if (j == 5) j=0;         /* Only 5 hard-coded responses   */
         strcpy(Reply, Myrep[j++]);                 /* handle it   */
         len = strlen(Reply) + 1;
         rc=DosWrite(SPipeHndl, Reply, len, &num);  /* Send reply  */
         rc=DosRead( SPipeHndl, Request, 80, &num); /* Get request  */
      }   /* endwhile */

      rc=DosDisConnectNPipe(SPipeHndl);

      rc=DosClose(SPipeHndl);
   };     /* end outer loop */

}
