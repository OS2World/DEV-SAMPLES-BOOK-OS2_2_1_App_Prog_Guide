#include <os2.h>
#include <stdio.h>
#include <signal.h>
#include <setjmp.h>

#define CODE_PSZ 1
#define CODE_NUM 2
INT ExternalFunction(PVOID, USHORT);

INT main(VOID)
{
   INT iRC;

   iRC = ExternalFunction("mystr", CODE_PSZ);
   iRC = ExternalFunction((PVOID)1, CODE_NUM);
   iRC = ExternalFunction((PVOID)1, CODE_PSZ);

   return(0L);
}

static jmp_buf SigBuffer;

VOID SEGV_Handler(int sig)
{
   longjmp(SigBuffer, -1);
}

INT ExternalFunction(PVOID p, USHORT usCode)
{
   PVOID pPrevExceptionHandler;
   INT iRC;

   /* Register signal handler */
   pPrevExceptionHandler = signal(SIGSEGV, SEGV_Handler);
   if (setjmp(SigBuffer) != 0) {
      iRC = 1; /* Bad parameter */
      printf("Signal occurred!!!\n");
      goto errorexit;
   }

   /* Access pointers passed in */
   switch (usCode) {
   case CODE_PSZ:
      printf("This string is %s with length %d\n",
             (PSZ)p, strlen((PSZ)p));
      break;
   case CODE_NUM:
      printf("This number is %d\n", (INT)p);
      break;
   default: ;
   }

   /* Deregister signal handler */
   signal(SIGSEGV, pPrevExceptionHandler);
   iRC = 0;

   errorexit:

   return(iRC);
}
