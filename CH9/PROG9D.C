/* PROG9D.C */

#define INCL_DOSPROCESS     /* Include process and thread APIs */
#include <os2.h>
#include <stdio.h>  /* for the printf functions */

VOID main (void)
{
   CHAR        ProgramLoadError[100];
   CHAR        ProgramArgs[100];
   PSZ         ProgramEnvs=NULL;
   CHAR        ProgramName[20];
   RESULTCODES ReturnCodes, ReturnCodes2;
   ULONG       ActionCode;
   APIRET      rc, rc2;
   PTIB        pptib;
   PPIB        pppib;
   ULONG       Pid;          
   INT i;    /* counter */

   strcpy(ProgramName,"PROG9DA.EXE"); /* Program to spawn */
   memset(ProgramArgs,'\0',sizeof(ProgramArgs));
   strcpy(ProgramArgs,ProgramName);
   strcat(ProgramArgs,"  A");
   ProgramArgs[11] = '\0';

   /* Start Program */
   rc = DosExecPgm(ProgramLoadError,          /* Load Error Msg Buffer */
                   sizeof(ProgramLoadError),  /* Size of Load Error Msg Buffer */
                   EXEC_ASYNCRESULT,          /* Execute asynchronously */
                   ProgramArgs,               /* Program Argument String */
                   ProgramEnvs,               /* Program Environment String */
                   &ReturnCodes,       /* Execution Termination codes */
                   ProgramName);     /* Program File Name */

   /* if DosExecPgm executed successfully, print return code info. */
   if (rc == 0) {
      printf("DosExecPgm called successfully.\n");
      printf("Termination Code = %d\n",ReturnCodes.codeTerminate);
      printf("Return Code = %d\n",ReturnCodes.codeResult);
   } else {
      printf("DosExecPgm ended with error code: %d\n", rc);
      return;
   }

   /* print characters */
   for (i=1;i<4000;i++) {
      printf("B");
   } /* endfor */
   printf("\n");

   ActionCode = 1;    /* Kill the process */
   Pid = ReturnCodes.codeTerminate;
   rc2 = DosKillProcess(ActionCode, Pid);

   if (rc2 == 0) {
      printf("DosKillProcess called successfully.\n");
   } else {
      printf("DosKillProcess error: return code = %ld",rc2);
      return;
   }

   /* Print the TIB and PIB blocks for thread 1 of this process. */
   rc = DosGetInfoBlocks(&pptib,&pppib);
   if (rc == 0) {
      printf("\nDosGetInfoBlocks called successfully.\n");
      print_tib_pib_info(pptib,pppib);
   } else {
      printf("\nDosGetInfoBlocks ended with error code: %d\n", rc);
      return;
   }

   return;
}

/*** print_tib_pib_info - Prints a subset of the information in the 
TIB and PIB structures ***/

int print_tib_pib_info (PTIB pptib, PPIB pppib)
{
   printf("\n*** Thread Information Block (TIB) Information ***\n");
   printf("TIB version number = %d\n",pptib->tib_version);
   printf("Thread ordinal number = %d\n",pptib->tib_ordinal);

   printf("\n*** Thread Information Block 2 (TIB2) Information ***\n");
   printf("Thread ID (TID) = %d\n",pptib->tib_ptib2->tib2_ultid);
   printf("Thread priority = %d\n",pptib->tib_ptib2->tib2_ulpri);
   printf("TIB2 version number = %d\n",pptib->tib_ptib2->tib2_version);

   printf("\n*** Process Information Block (PIB) Information ***\n");
   printf("Process ID (PID) = %d\n",pppib->pib_ulpid);
   printf("Parent Process ID (PPID) = %d\n",pppib->pib_ulppid);
   printf("Module Handle of Process = %d\n",pppib->pib_hmte);
   printf("Command Line String = %s\n",pppib->pib_pchcmd);
   printf("Environment String = %s\n",pppib->pib_pchenv);
   printf("Process Status Bits = %d\n",pppib->pib_flstatus);
   printf("Process Type = %d\n",pppib->pib_ultype);
}

