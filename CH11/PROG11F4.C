/***************************************************************/
/* Chapter 11.  Setting two children to read and write to each */
/*              other                                          */
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
   HFILE Child1sInput;         /* Read handle for pipe 1      */
   HFILE Child2sOutput;        /* Write handle for pipe 1     */
   HFILE Child2sInput;         /* Read handle for pipe 2      */
   HFILE Child1sOutput;        /* Write handle for pipe 2     */
   ULONG byteswritten;
   APIRET rc;

   /* The next variables are for the DosExecPgm call     */
   char  ObjNameBuf[OBJBUFLEN];
   ULONG ExecFlags = EXEC_ASYNC;
   RESULTCODES kidrc;


   DosDupHandle(MyIn, &SaveMyIn);      /*Save original std in */
   DosDupHandle(MyOut, &SaveMyOut);    /*Save original std out*/

                   /* Create two pipes for the communication  */
   DosCreatePipe(&Child1sInput,        /* PIPE 1   */
                 &Child2sOutput,
                 PIPESIZE);
   DosCreatePipe(&Child2sInput,        /* PIPE 2   */
                 &Child1sOutput,
                 PIPESIZE);

                   /* Setup Child1                */
   DosDupHandle(Child1sInput, &MyIn);   /* Replace std in     */
   DosDupHandle(Child1sOutput,&MyOut);  /* Replace std out    */

                   /* Start the child process */
   rc = DosExecPgm(ObjNameBuf,         /* Buffer if failure   */
        OBJBUFLEN,
        ExecFlags,                     /* Asynch operation    */
        NULL,                          /* child has no parms  */
        NULL,                          /* Inherit environment */
        &kidrc,
        "HIWORLD.EXE");                /* Name of child pgm   */

                   /* Setup Child2                */
   DosDupHandle(Child2sInput, &MyIn);   /* Replace std in     */
   DosDupHandle(Child2sOutput,&MyOut);  /* Replace std out    */

                   /* Start the child process */
   rc = DosExecPgm(ObjNameBuf,         /* Buffer if failure   */
        OBJBUFLEN,
        ExecFlags,                     /* Asynch operation    */
        NULL,                          /* child has no parms  */
        NULL,                          /* Inherit environment */
        &kidrc,
        "HIWORLD2.EXE");               /* Name of child pgm   */

                   /* Restore stdin and stdout */
   DosDupHandle(SaveMyIn,  &Child2sInput);
   DosDupHandle(SaveMyOut, &Child2sOutput);

   /* Send input to child1   */
   rc = DosWrite(Child1sInput,
        "Hello, world\n",
        14,
        &byteswritten);

                   /* Continue with parent program         */
}

