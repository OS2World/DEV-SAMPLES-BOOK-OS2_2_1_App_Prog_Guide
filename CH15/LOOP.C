#include <os2.h>
#include <stdio.h>

ULONG loop;

VOID GoLoop()
{
   while (TRUE) {
      loop = loop + 5;
      loop = loop - 2;
   }
   printf("loop = %ld\n", loop);
}

INT main(VOID)
{

   GoLoop();
   return(0L);
}
