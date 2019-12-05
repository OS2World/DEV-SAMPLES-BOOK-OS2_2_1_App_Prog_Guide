/***************************************************************/
/* Chapter 11.  Passing information from one child to another, */
/*              through the parent                             */
/***************************************************************/

#define INCL_DOSQUEUES
#define INCL_DOSFILEMGR
#define INCL_DOSPROCESS
#define PIPESIZE  4096
#define OBJBUFLEN  100
#include <os2.h>

int main (int argc, void *argv[])
{

   HFILE MyIn     = 0;         /* Handle of original std in   */
   HFILE SaveMyIn = -1;        /* Handle for saving std in    */
   HFILE MyOut    = 1;         /* Handle of original std out  */
   HFILE SaveMyOut= -1;        /* Handle for saving std out   */
   HFILE C1RPW;                /* Read handle for pipe  1     */
   HFILE PWC1R;                /* Write handle for pipe 1     */
   HFILE PRC1W;                /* Read handle for pipe  2     */
   HFILE C1WPR;                /* Write handle for pipe 2     */
   HFILE C2RPW;                /* Read handle for pipe  3     */
   HFILE PWC2R;                /* Write handle for pipe 3     */
   HFILE PRC2W;                /* Read handle for pipe  4     */
   HFILE C2WPR;                /* Write handle for pipe 4     */

   ULONG       byteswritten = 0;
   ULONG       bytesread    = 0;
   char        buf[PIPESIZE];

   APIRET rc;

   /* The next variables are for the DosExecPgm call     */
   char  ObjNameBuf[OBJBUFLEN];
   ULONG ExecFlags = EXEC_ASYNC;
   RESULTCODES kidrc;


   DosDupHandle(MyIn, &SaveMyIn);      /*Save original std in */
   DosDupHandle(MyOut, &SaveMyOut);    /*Save original std out*/

                  /* Create four pipes for the communication  */
   DosCreatePipe(&C1RPW,               /* PIPE 1, read  handle*/
                 &PWC1R,               /* PIPE 1, write handle*/
              PIPESIZE);
   DosCreatePipe(&PRC1W,               /* PIPE 2              */
                 &C1WPR,
                 PIPESIZE);
   DosCreatePipe(&C2RPW,               /* PIPE 3              */
                 &PWC2R,
                 PIPESIZE);
   DosCreatePipe(&PRC2W,               /* PIPE 4              */
                 &C2WPR,
                 PIPESIZE);

                   /* Setup Child1                */
   DosDupHandle(C1RPW, &MyIn);          /* Replace std in     */
   DosDupHandle(C1WPR, &MyOut);         /* Replace std out    */

                   /* Start the child process */
   rc = DosExecPgm(ObjNameBuf,         /* Buffer if failure   */
        OBJBUFLEN,
        ExecFlags,                     /* Asynch operation    */
        NULL,                          /* child has no parms  */
        NULL,                          /* Inherit environment */
        &kidrc,
        "HIWORLD.EXE");                /* Name of child pgm   */

                   /* Setup Child2                */
   DosDupHandle(C2RPW, &MyIn);          /* Replace std in     */
   DosDupHandle(C2WPR, &MyOut);         /* Replace std out    */

                   /* Start the child process */
   rc = DosExecPgm(ObjNameBuf,          /* Buffer if failure   */
        OBJBUFLEN,
        ExecFlags,                     /* Asynch operation    */
        NULL,                          /* child has no parms  */
        NULL,                          /* Inherit environment */
        &kidrc,
        "HIWORLD2.EXE");               /* Name of child pgm   */

                   /* Restore stdin and stdout */
   DosDupHandle(SaveMyIn,  &MyIn);
   DosDupHandle(SaveMyOut, &MyOut);

   /* Send input to child1   */
   rc = DosWrite(PWC1R,
        "Hello, world\n",
        14,
        &byteswritten);

   /* In this case, both programs read and write once */
   DosSleep(1000);
   rc = DosRead (PRC1W,              /* Read data from child1 */
        &buf,                        /* data                  */
        PIPESIZE,                    /* max length of data    */
        &bytesread);
   printf("we read ---- %s\n", buf);
   DosWrite(PWC2R,                   /* Write it to child2    */
        &buf,                        /* data                  */
        bytesread,                   /* length of data        */
        &byteswritten);

   DosRead(PRC2W,                    /* Read data from child2 */
        &buf,                        /* data                  */
        PIPESIZE,                    /* max length of data    */
        &bytesread);
   printf("we read ---- %s\n", buf);
   DosWrite(PWC1R,                   /* Write it to child1    */
        buf,                         /* data                  */
        bytesread,                   /* length of data        */
        &byteswritten);

   DosClose(PRC1W);
   DosClose(PRC2W);
   DosClose(PWC1R);
   DosClose(PWC2R);
   DosClose(C1RPW);
   DosClose(C1WPR);
   DosClose(C2RPW);
   DosClose(C2WPR);

}
