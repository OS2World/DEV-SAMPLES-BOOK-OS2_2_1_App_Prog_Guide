#include <os2.h>
#include <stdio.h>

VOID GoTrap()
{
   PUSHORT ptr = NULL;

   *ptr = 5;
   printf("pointer assigned");
}

INT main(VOID)
{

   GoTrap();
   return(0L);
}

