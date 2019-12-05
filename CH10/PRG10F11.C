/*************************************************************/
/* Chapter 10.  Program illustrating the use of an exit list */
/*              for closing semaphores                       */
/*************************************************************/

#define INCL_DOSPROCESS
#define INCL_DOSSEMAPHORES
#include <os2.h>

HMTX hmtxMySem = (HMTX)NULL;

VOID APIENTRY CleanResources();

INT main(VOID)
{
   DosCreateMutexSem("\\SEM32\\MYSEMTEST", &hmtxMySem, 0,
                     FALSE);
   DosExitList(EXLST_ADD, (PFNEXITLIST)CleanResources);
   return(0L);
}

VOID APIENTRY CleanResources()
{
   DosCloseMutexSem(hmtxMySem);
   DosExitList(EXLST_EXIT, (PFNEXITLIST)CleanResources);
}

