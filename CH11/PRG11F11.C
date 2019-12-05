/********************************************************/
/* Chapter 11.  Creating two instances of a named pipe  */
/********************************************************/

#define INCL_DOSNMPIPES
#define INCL_ERRORS
#include <os2.h>

int main (int argc, void *argv[])
{

   #define READBUFSIZE  400
   #define WRITEBUFSIZE  400
   HPIPE   SPipeHndl1;   /* Server handle for pipe, instance 1*/
   HPIPE   SPipeHndl2;   /* Server handle for pipe, instance 2*/
   UCHAR   PipeName[80];            /* name of the named pipe */
   ULONG   PipeDir;                 /* direction of dataflow  */
   ULONG   PipeMode;      /* Blocking/nonblocking,  Byte/Msg..*/
   ULONG   ReadBuf[READBUFSIZE];      /* input buffer         */
   ULONG   WriteBufSize[WRITEBUFSIZE];/* output buffer        */
   ULONG   DefWaitTimeOut;          /* default timeout for    */
                                    /*     DosWaitNPipe API   */
   APIRET  rc;

   strcpy(PipeName, "\\PIPE\\MYPIPE");  /* Name of pipe       */
   printf("pipename is %s\n", PipeName);
   PipeDir = NP_ACCESS_DUPLEX;      /* Full duplex pipe       */
               /* Nonblocking, message pipe, max 4 instances  */
   PipeMode = NP_NOWAIT | NP_WMESG | NP_RMESG | 0x04;
   DefWaitTimeOut = 2000;         /* Timeout in 2 seconds     */
          /* i.e. if a client does a DosWaitNPipe without     */
          /* specifying any timeout, it will only wait for    */
          /* 2 seconds before timing out.                     */

   DosCreateNPipe(PipeName,       /* Create one instance of   */
                  &SPipeHndl1,    /* the pipe.                */
                  PipeDir,
                  PipeMode,
                  WRITEBUFSIZE,
                  READBUFSIZE,
                  DefWaitTimeOut);
   DosCreateNPipe(PipeName,       /* Create second instance   */
                  &SPipeHndl2,    /* of the pipe.             */
                  PipeDir,
                  PipeMode,
                  WRITEBUFSIZE,
                  READBUFSIZE,
                  DefWaitTimeOut);

   DosConnectNPipe(SPipeHndl1);   /* Connect to instances     */
   DosConnectNPipe(SPipeHndl2);

}
