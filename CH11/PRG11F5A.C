/***********************************************************/
/* Chapter 11.  Attaching to a named pipe - server actions */
/***********************************************************/

#define INCL_DOSNMPIPES
#define INCL_DOSFILEMGR
#include <os2.h>

int main (int argc, void *argv[])
{
   #define READBUFSIZE 80
   #define WRITEBUFSIZE 80
   HPIPE   SPipeHndl;               /* Server handle for pipe1*/
   UCHAR   PipeName[80];            /* name of the named pipe */
   ULONG   PipeDir;                 /* direction of dataflow  */
   ULONG   PipeMode;      /* Blocking/nonblocking,  Byte/Msg..*/
   ULONG   ReadBuf[READBUFSIZE];    /* input buffer           */
   ULONG   WriteBuf[WRITEBUFSIZE];  /* output buffer          */
   ULONG   WriteBufSize;            /* size of output buffer  */
   ULONG   DefWaitTimeOut;          /* default timeout for    */

   strcpy(PipeName, "\\PIPE\\MYPIPE");  /* Name of pipe       */
   PipeDir = NP_ACCESS_DUPLEX;      /* Full duplex pipe       */
               /* Nonblocking, message pipe, max 4 instances  */
   PipeMode = NP_WAIT | NP_TYPE_BYTE | 0x04;
   DefWaitTimeOut = 2000;         /* Timeout in 2 seconds     */
          /* i.e. if a client does a DosWaitNPipe without     */
          /* specifying any timeout, it will only wait for    */
          /* 2 seconds before timing out.                     */

   DosCreateNPipe(PipeName,       /* Create one instance of   */
                  &SPipeHndl,     /* the pipe.                */
                  PipeDir,
                  PipeMode,
                  WRITEBUFSIZE,
                  READBUFSIZE,
                  DefWaitTimeOut);

   DosConnectNPipe(SPipeHndl);    /* Connect to server end    */
                                  /* of the pipe, and wait    */
                                  /* for a client to attach   */

   /* The next two lines are cleanup.  A real program would   */
   /* not disconnect right away.  See Figure 12-6.            */
   DosDisConnectNPipe(SPipeHndl);
   DosClose(SPipeHndl);

}

