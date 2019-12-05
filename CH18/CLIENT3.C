#include <stdio.h>
#include <string.h>
#include <os2.h>
#include <lifoq.h>

main(argc, argv, envp)
   int argc;
   char *argv[];
   char *envp[];
{
   LIFOQ   *myq;
   USHORT  mydata[5] = {10, 15, 20, 25, 30};
   int     i;
   int    *j;
   int     rc;

   listsNew();
   myq = LIFOQNew();
   SOM_Test(myq != NULL);

   get_usListItemSize(myq) = sizeof(USHORT);

   /* Now add and remove things from the list */
   for (i=0; i < 2; i++) {
      rc = _AddItem(myq, (PVOID) &mydata[i]);
      SOM_TestC(rc);
   } /* endfor */

   j = _GetItem(myq);
   printf("The first item was:  %d\n", *j);

   for (i=2; i < 4; i++) {
      rc = _AddItem(myq, (PVOID) &mydata[i]);
      SOM_TestC(rc);
   } /* endfor */

   /* Retrieve items */
   for (i=0; i < 2; i++) {
      j = _GetItem(myq);
      printf("The next item was:  %d\n", *j);
   } /* endfor */

   rc = _AddItem(myq, (PVOID) &mydata[4]);

   for (i=0; i < 2; i++) {
      j = _GetItem(myq);
      printf("The next item was:  %d\n", *j);
   } /* endfor */

   _somFree(myq);
}
