/* prog8d.c - Demonstrate pool memory. */

#define INCL_DOSMEMMGR   /* Include Memory Management Calls */
#define INCL_DOSERRORS   /* Include OS/2 Error #defines */
#define INCL_NOPMAPI     /* Don't include PM APIs */
#include <os2.h>
#include <stdio.h>
#include <bsememf.h>   /* Flags for memory management */

VOID main (USHORT argc, PCHAR argv[])
{
   PVOID  PoolAlloc;  /* Pointer to pool memory object */
   PVOID  ObjAlloc1, ObjAlloc2; /* Pointer to  subobjects
                                   in the pool memory object */
   ULONG  PoolSize; /* Size of the pool memory object */
   ULONG  ObjSize1, ObjSize2;   /* Size of the memory subobjects */
                         /* Attributes of the memory subobjects */
   ULONG  AllocFlags1, AllocFlags2; 
   APIRET rc;       /* Return code */
   int i;           /* Counter */

   /* Will be rounded up to the nearest 8 bytes - to 4008 */
   PoolSize = 4002; 
   ObjSize1 = 500; /* Size of subobject 1 */
   ObjSize2 = 1000;  /* Size of subobject 2 */
 
   /* Precommit the pages */
   AllocFlags1 = PAG_WRITE | PAG_READ | PAG_COMMIT;

   rc = DosAllocMem(&PoolAlloc, PoolSize, AllocFlags1);

   if (rc == 0) {
      printf("DosAllocMem for PoolAlloc executed successfully.\n");
   } else {
      printf("Error:  DosAllocMem for PoolAlloc with rc = %ld\n",rc);
      return;
   }

   AllocFlags2 = DOSSUB_INIT;

   /* Only allocate 1000 bytes of the memory object as an available
   pool */
   rc = DosSubSetMem(PoolAlloc, AllocFlags2, (PoolSize - 3000));
 
   if (rc == 0) {
      printf("DosSubSetMem for PoolAlloc executed successfully.\n");
   } else {
      printf("Error:  DosSubSetMem for PoolAlloc with rc = %ld\n",
        rc);
      return;
   }

   rc = DosSubAllocMem(PoolAlloc, &ObjAlloc1, ObjSize1);
 
   if (rc == 0) {
      printf("DosSubAllocMem for ObjAlloc1 executed successfully.\n");
   } else {
      printf("Error:  DosSubAllocMem for ObjAlloc1 with rc = %ld\n",
        rc);
      DosFreeMem(PoolAlloc);
      return;
   }

   /* Fill subobject 1 */
   strcpy(ObjAlloc1,"A");
   for (i=1;i<ObjSize1;i++) {
      strcat(ObjAlloc1,"A");
   }
   printf("ObjAlloc1 = %s\n",ObjAlloc1);

   rc = DosSubAllocMem(PoolAlloc, &ObjAlloc2, ObjSize2);
 
   if (rc == 0) {
      printf("DosSubAllocMem for ObjAlloc2 executed successfully.\n");
   } else {
      printf("Error:  DosSubAllocMem for ObjAlloc2 with rc = %ld\n",
        rc);

      /* Check if the error was not enough room in the pool */
      if (rc == ERROR_DOSSUB_NOMEM) {
         printf("Increasing size of the memory pool.\n");
         AllocFlags2 = DOSSUB_GROW ;
         rc = DosSubSetMem(PoolAlloc, AllocFlags2, 2000);
         if (rc == 0) {
            /* Allocate memory for subobject 2 */
            printf("DosSubSetMem executed successfully.\n");
            DosSubAllocMem(PoolAlloc, &ObjAlloc2, ObjSize2);
         } else {
            printf("DosSubSetMem error: return code = %ld\n",rc);
            printf("Exiting program.\n");
            return;
         }

      }
   }

   /* Fill subobject 2 */
   strcpy(ObjAlloc2,"B");
   for (i=1;i<ObjSize2;i++) {
      strcat(ObjAlloc2,"B");
   }
   printf("ObjAlloc2 = %s\n",ObjAlloc2);

   /* Free subobjects */
   DosSubFreeMem(PoolAlloc, ObjAlloc1, ObjSize1);
   DosSubFreeMem(PoolAlloc, ObjAlloc2, ObjSize2);

   /* Free Memory Pool */
   rc = DosSubUnsetMem(PoolAlloc);

   if (rc == 0) {
      printf("DosSubUnsetMem for PoolAlloc executed successfully.\n");
   } else {
      printf("Error:  DosSubUnsetMem for PoolAlloc with rc = %ld\n",
        rc);
   }

   /* Free Memory Pool Allocation */
   rc = DosFreeMem(PoolAlloc);

   if (rc == 0) {
      printf("DosFreeMem for PoolAlloc executed successfully.\n");
   } else {
      printf("Error:  DosFreeMem for PoolAlloc with rc = %ld\n",rc);
   }

   return;
}
