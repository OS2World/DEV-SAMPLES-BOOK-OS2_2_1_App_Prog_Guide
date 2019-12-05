/* prog9b.c */

#define INCL_DOSPROCESS     /* Include process and thread APIs */
#include <os2.h>
#include <stdio.h>   /* for the printf functions */

VOID main (void)
{
   CHAR        ProgramLoadError[100];
   PSZ         ProgramArgs=NULL;
   PSZ         ProgramEnvs;
   CHAR        ProgramName[20];
   RESULTCODES ReturnCodes;
   APIRET      rc;
   PTIB        pptib;
   PPIB        pppib;
   INT i;

   strcpy(ProgramName,"PROG9BA.EXE"); /* Program to create */

   /* Start Program */
   rc = DosExecPgm(ProgramLoadError,          /* Load Error Msg Buffer */
                   sizeof(ProgramLoadError),  /* Size of Load Error Msg Buffer */
                   EXEC_SYNC,          /* Execute synchronously */
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
   for (i=1; i<100;i++) {
      printf("B");
   } /* endfor */
   printf("\n");


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