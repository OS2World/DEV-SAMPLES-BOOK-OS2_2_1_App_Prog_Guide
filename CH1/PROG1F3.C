/****************************************************************/
/* Chapter 1.  Program illustrating 16-bit to 32-bit thunking.  */
/****************************************************************/

#define INCL_DOSPROCESS
#include <os2.h>
#include <stdio.h>

typedef VOID ( * _Far16 _Pascal PFNEXITL)(USHORT);
USHORT _Far16 _Pascal DOS16EXITLIST(
        USHORT fFnCode,
        PFNEXITL pfnFunction);


VOID _Far16 _Pascal ExitList(USHORT usCode)
{
   printf("Exit list processing\n");
   DOS16EXITLIST(EXLST_EXIT, ExitList);
}

INT main(void)
{
   printf("Installing exit list\n");
   DOS16EXITLIST(EXLST_ADD, ExitList);
   return (0);
}

