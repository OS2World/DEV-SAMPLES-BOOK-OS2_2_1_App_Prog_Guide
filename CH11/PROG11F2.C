/***************************************************************/
/* Chapter 11.  Replacing a child process's stdin with a file, */
/*              and replacing its stdout with a pipe           */
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
   HFILE PipeRead;             /* Read handle for the pipe    */
   HFILE PipeWrite;            /* Write handle for the pipe   */
   HFILE FileReadWrite;        /* Handle for a file           */
                               /* -- A file only has 1 handle */
   APIRET rc;

   /* The next variables are for the DosExecPgm call     */
   char  ObjNameBuf[OBJBUFLEN];
   ULONG ExecFlags = EXEC_ASYNC;
   RESULTCODES kidrc;
   ULONG       byteswritten = 0;
   ULONG       bytesread    = 0;
   char        buf[PIPESIZE];

   /* The next variables are for the DosOpen call     */
   ULONG    Action;
   ULONG    OpenFlag = OPEN_ACTION_FAIL_IF_NEW |
                       OPEN_ACTION_OPEN_IF_EXISTS;
   ULONG    OpenMode = OPEN_FLAGS_SEQUENTIAL |
                       OPEN_FLAGS_NOINHERIT  |
                       OPEN_SHARE_DENYWRITE  |
                       OPEN_ACCESS_READONLY;

   memset(&buf, '\0', PIPESIZE);       /* Initialize the buffr*/
   DosDupHandle(MyIn, &SaveMyIn);      /*Save original std in */
   DosDupHandle(MyOut, &SaveMyOut);    /*Save original std out*/

                     /* Prepare to replace the child's std in */
                     /* with the file:                        */
      /* Open the file, since stdin is always initially open  */
   rc = DosOpen("d:\\myprogs\\aninfile", /* Name of the file  */
           &FileReadWrite,        /* File handle       */
           &Action,               /* output status     */
           0,                     /* ignored           */
           0,                     /* ignored           */
           OpenFlag,
           OpenMode,
           0);                    /* No extended attrs */

   DosDupHandle(FileReadWrite, &MyIn); /* Replace std in      */

                     /* Prepare to replace the child's std out*/
                     /* with a pipe:                          */
   DosCreatePipe(&PipeRead,            /* Create the pipe    */
                 &PipeWrite,
                 PIPESIZE);
   DosDupHandle(PipeWrite, &MyOut);    /* Replace std out    */

   /* Start the child process */
   DosExecPgm(ObjNameBuf,              /* Buffer if failure   */
        OBJBUFLEN,
        ExecFlags,                     /* Asynch operation    */
        NULL,                          /* child has no parms  */
        NULL,                          /* Inherit environment */
        &kidrc,
        "HIWORLD.EXE");                /* Name of child pgm   */
              /* Child inherits current std in and std out    */
              /* Current std in is the file                   */
              /* Current std out is the unnamed pipe          */

                      /* Restore stdin and stdout */
   DosDupHandle(SaveMyIn,  &MyIn);
   DosDupHandle(SaveMyOut, &MyOut);

   DosSleep(2000);

   /* Process child's results   */
   DosRead(PipeRead, buf, PIPESIZE, &bytesread);
   if (bytesread != 0) {
      printf("%s", buf);
   }

   DosClose(PipeRead);
   DosClose(PipeWrite);
}
