/****************************************************************/
/* Chapter 14.  Program illustrating the registration of an     */
/*              exception handler to manage uncommitted memory  */
/*              object access violations                        */
/****************************************************************/

#define INCL_DOSMEMMGR
#define INCL_DOSEXCEPTIONS
#include <os2.h>

#include <stdlib.h>

ULONG _System MyMemoryHandler(PEXCEPTIONREPORTRECORD,
               PEXCEPTIONREGISTRATIONRECORD,
               PCONTEXTRECORD, PVOID);

ULONG _System MyMemoryHandler(PEXCEPTIONREPORTRECORD pRepRec,
               PEXCEPTIONREGISTRATIONRECORD pRegRec,
               PCONTEXTRECORD pConRec, PVOID pDispCon)
{
   ULONG ulSize, ulAttributes;
   APIRET rc;

   /* Check for Read/Write access violations that pass */
   /* a known memory address.                          */
   if ((pRepRec->ExceptionNum == XCPT_ACCESS_VIOLATION) &&
       (pRepRec->ExceptionAddress !=
                               (PVOID)XCPT_DATA_UNKNOWN)) {
      if (((pRepRec->ExceptionInfo[0] == XCPT_READ_ACCESS) ||
           (pRepRec->ExceptionInfo[0] == XCPT_WRITE_ACCESS))
          && (pRepRec->ExceptionInfo[1] !=
                                       XCPT_DATA_UNKNOWN)) {
         /* Find out if the memory just needs to be    */
         /* committed by checking the attributes.      */
         ulSize = 1;
         rc = DosQueryMem((PVOID)pRepRec->ExceptionInfo[1],
                     &ulSize, &ulAttributes);
         if (!rc &&
             !(ulAttributes & (PAG_COMMIT | PAG_FREE))) {
            /* Commit the memory and return indicating */
            /* the exception has been processed and the*/
            /* program can continue execution.         */
            rc = DosSetMem((PVOID)pRepRec->ExceptionInfo[1],
                           0x1000, PAG_COMMIT | PAG_DEFAULT);
            if (!rc) {
               printf("Page committed!!!\n");
               return(XCPT_CONTINUE_EXECUTION);
            }
         }
      }
   }
   return(XCPT_CONTINUE_SEARCH);
}

INT main(VOID)
{
   EXCEPTIONREGISTRATIONRECORD ERegRec;
   PVOID memobj;
   ULONG count;

   ERegRec.prev_structure = NULL;
   ERegRec.ExceptionHandler = MyMemoryHandler;
   DosSetExceptionHandler(&ERegRec);

   DosAllocMem(&memobj, 6000, PAG_READ|PAG_WRITE);

   memset(memobj, '\0', 6000);

   DosFreeMem(memobj);

   DosUnsetExceptionHandler(&ERegRec);

   return(0);
}

