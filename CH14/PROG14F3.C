/***************************************************************/
/* Chapter 14.  Program illustrating the registration of an    */
/*              exception handler to manage signal exceptions  */
/***************************************************************/

#define INCL_DOSEXCEPTIONS
#define INCL_DOSERRORS
#define INCL_DOSSEMAPHORES
#include <os2.h>

HEV mysem;
SHORT count = 0;

ULONG _System MySignalHandler(PEXCEPTIONREPORTRECORD,
               PEXCEPTIONREGISTRATIONRECORD,
               PCONTEXTRECORD, PVOID);

ULONG _System MySignalHandler(PEXCEPTIONREPORTRECORD pRepRec,
               PEXCEPTIONREGISTRATIONRECORD pRegRec,
               PCONTEXTRECORD pConRec, PVOID pDispCon)
{
   if (pRepRec->ExceptionNum == XCPT_SIGNAL) {
      if (pRepRec->ExceptionInfo[0] == XCPT_SIGNAL_INTR) {
         printf("Ctrl+C occured!!!\n");
         if (count == 2) {
            DosPostEventSem(mysem);
         }
         count++;
         return(XCPT_CONTINUE_EXECUTION);
      } else {
         return(XCPT_CONTINUE_SEARCH);
      }
   } else {
      return(XCPT_CONTINUE_SEARCH);
   }
}

INT main(VOID)
{
   EXCEPTIONREGISTRATIONRECORD ERegRec;
   ULONG count;

   DosCreateEventSem((PSZ)NULL, &mysem, 0, FALSE);
   ERegRec.prev_structure = NULL;
   ERegRec.ExceptionHandler = MySignalHandler;
   DosSetExceptionHandler(&ERegRec);
   DosSetSignalExceptionFocus(SIG_SETFOCUS, &count);

   while (DosWaitEventSem(mysem, SEM_INDEFINITE_WAIT) ==
          ERROR_INTERRUPT);

   DosSetSignalExceptionFocus(SIG_UNSETFOCUS, &count);
   DosUnsetExceptionHandler(&ERegRec);
   DosCloseEventSem(mysem);

   return(0);
}


