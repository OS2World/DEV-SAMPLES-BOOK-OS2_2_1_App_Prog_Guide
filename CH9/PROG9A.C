/* PROG9A.C */

#define INCL_DOSSESMGR      /* Include Session Manager Calls */
#include <os2.h>
#include <stdio.h>

VOID main (void)
{
   STARTDATA   StartData;    /* Start Session Data Structure */
   ULONG       SessID;       /* Returned Session ID */
   PID         PID;          /* Returned Process ID */
   UCHAR       PgmTitle[40];
   UCHAR       PgmInputs[40];
   UCHAR       PgmName[80];
   UCHAR       ObjBuf[100];
   APIRET      rc;

    /*  Specify the various session start parameters  */
   printf("Starting program.\n");

   /* Fill out the Session Data Structure */

   /* structure size */
   StartData.Length = sizeof(STARTDATA);

   /* Independent Session */
   StartData.Related = SSF_RELATED_INDEPENDENT;

   /* Start in background */
   StartData.FgBg = SSF_FGBG_BACK;

   /* Do not include trace information */
   StartData.TraceOpt = SSF_TRACEOPT_NONE;

   /* Title of Program in Session */
   strcpy(PgmTitle,"Command Line Program");
   StartData.PgmTitle = PgmTitle;

   /* Name of program to be executed in session */
   strcpy(PgmName,"CMD.EXE");
   StartData.PgmName = PgmName;

   /* Arguments to pass to program */
   strcpy(PgmInputs,"/C DIR > \"DIR.OUT\"");
   StartData.PgmInputs = PgmInputs;

   /* No termination queue */
   StartData.TermQ = 0;

   /* No environment string */
   StartData.Environment = 0;

   /* Inherit environment from parent */
   StartData.InheritOpt = SSF_INHERTOPT_PARENT;

   /* Use the shell's default session type */
   StartData.SessionType = SSF_TYPE_DEFAULT;

   /* No icon file */
   StartData.IconFile = 0;

   /* No Program handle */
   StartData.PgmHandle = 0;

   /* Program starts invisible and minimized */
   StartData.PgmControl = SSF_CONTROL_INVISIBLE | SSF_CONTROL_MINIMIZE;
   StartData.InitXPos = 0;
   StartData.InitYPos = 0;
   StartData.InitXSize = 0;
   StartData.InitYSize = 0;

   /* Reserved word set to zero */
   StartData.Reserved = 0;

   /* Holds DosExecPgm failure message */
   StartData.ObjectBuffer = ObjBuf;
   StartData.ObjectBuffLen = sizeof(ObjBuf);

   printf("Starting the session.\n");

   rc = DosStartSession(&StartData, &SessID, &PID);

   if (rc != 0) {
      printf("DosStartSession error: return code = %ld\n", rc);
      printf("Object Buffer = %s\n", StartData.ObjectBuffer);
   } else {
      printf("DosStartSession executed successfully.\n");
      printf("Created Session ID = %ld\n", SessID);
      printf("Created Process ID in session = %ld\n", PID);
   }
   return;
}
