/* prog8a.c - Show how page memory is allocated */

#define INCL_DOSMEMMGR   /* Include Memory Management Calls */
#define INCL_NOPMAPI     /* Don't include PM APIs */
#include <os2.h>
#include <stdio.h>
#include <bsememf.h>   /* Flags for memory management */

VOID main (USHORT argc, PCHAR argv[])
{
   PVOID    ObjAlloc;    /* Pointer to memory object */
   ULONG    ObjSize;     /* Size of memory object */
   ULONG    PageSize;    /* Size of a page */
   ULONG    AllocFlags;  /* Attributes of the memory object */
   APIRET   rc;          /* Return code */
   int i;                /* Counter */

   ObjSize = 500;     /* Will be rounded up to 4KB (1 page) */
   PageSize = 4096;

   /* Read/write access and precommit */
   AllocFlags = PAG_WRITE | PAG_COMMIT;

   rc = DosAllocMem(&ObjAlloc, ObjSize, AllocFlags);

   if (rc == 0) {
      printf("DosAllocMem for ObjAlloc executed successfully.\n");
   } else {
      printf("Error:  DosAllocMem for ObjAlloc with rc = %ld\n",rc);
      return;
   }

   /* Fill and exceed the size of the memory object */
   strcpy(ObjAlloc,"A");
   for (i=1;i<(PageSize - 1);i++) {
      strcat(ObjAlloc,"A");
   }
   printf("ObjAlloc = %s\n",ObjAlloc);

   rc = DosFreeMem(ObjAlloc);

   if (rc == 0) {
      printf("DosFreeMem for ObjAlloc executed successfully.\n");
   } else {
      printf("Error:  DosFreeMem for ObjAlloc with rc = %ld\n",rc);
   }

   return;
}
