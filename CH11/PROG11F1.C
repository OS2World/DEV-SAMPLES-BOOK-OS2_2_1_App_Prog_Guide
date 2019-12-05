/***********************************************************/
/* Chapter 11.  Replacing a child process's stdin with     */
/*              an unnamed pipe                            */
/***********************************************************/

#define INCL_DOSQUEUES
#define INCL_DOSFILEMGR
#define INCL_DOSPROCESS
#define PIPESIZE  4096
#define OBJBUFLEN  100
#include <os2.h>

int main (int argc, void *argv[])
{

   /* The next variables are for the pipe calls          */
   HFILE MyIn     = 0;         /* Handle of original std in   */
   HFILE SaveMyIn = -1;        /* Handle for saving std in    */
   HFILE PipeRead;             /* Read handle for the pipe    */
   HFILE PipeWrite;            /* Write handle for the pipe   */
   APIRET rc;

   /* The next variables are for the DosExecPgm call     */
   char  ObjNameBuf[OBJBUFLEN];
   ULONG ExecFlags = EXEC_ASYNC;
   RESULTCODES kidrc;
   ULONG       byteswritten = 0;
   ULONG       bytesread    = 0;
   char        buf[PIPESIZE];


   memset(&buf, '\0', PIPESIZE);       /* Initialize the buffr*/
   DosDupHandle(MyIn, &SaveMyIn);      /* Save original std in*/

   rc = DosCreatePipe(&PipeRead,       /* Read Handle         */
                    &PipeWrite,        /* Write Handle        */
                    PIPESIZE);         /* pipe size           */

   DosDupHandle(PipeRead, &MyIn);      /* Replaces std in     */
      /* Start the child process */
   rc = DosExecPgm(ObjNameBuf,         /* Buffer if failure   */
        OBJBUFLEN,
        ExecFlags,                     /* Asynch operation    */
        NULL,                          /* child has no parms  */
        NULL,                          /* Inherit environment */
        &kidrc,
        "HIWORLD.EXE");                /* Name of child pgm   */
          /* Child inherits current std in and std out    */
          /* Current std in is the unnamed pipe           */

   DosDupHandle(SaveMyIn, &MyIn);      /* Restore orig std in */

   /* Now send input to the child process                     */
   rc = DosWrite(PipeWrite,            /* Child's stdin       */
        "Hello, world!\n",             /* data                */
        14,                            /* length of data      */
        &byteswritten);

   DosSleep(5000);                     /* Let child complete  */
   DosClose(PipeRead);                 /* Close the pipe      */
   DosClose(PipeWrite);
}
