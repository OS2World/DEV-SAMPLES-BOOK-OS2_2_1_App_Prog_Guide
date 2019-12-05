/* prog8b.c - Allocate, but commit memory later. 
Query the allocated object too.*/

#define INCL_DOSMEMMGR   /* Include Memory Management Calls */
#define INCL_NOPMAPI     /* Don't include PM APIs */
#include <os2.h>
#include <stdio.h>
#include <bsememf.h>   /* Flags for memory management */

VOID main (USHORT argc, PCHAR argv[])
{
   PVOID  ObjAlloc;    /* Pointer to memory object */
   ULONG  ObjSize;     /* Size of memory object */
   ULONG  AllocFlags;  /* Attributes of the memory object */
   ULONG  MemSize;     /* Size of memory region */
   ULONG  MemFlags;    /* Attribute flags of the memory region */
   APIRET rc;          /* Return code */

   ObjSize = 500;     /* Will be rounded up to 4KB */
   AllocFlags = PAG_WRITE; /* page is read/writeable */

   rc = DosAllocMem(&ObjAlloc, ObjSize, AllocFlags);

   if (rc == 0) {
      printf("DosAllocMem for ObjAlloc executed successfully.\n");
   } else {
      printf("Error:  DosAllocMem for ObjAlloc with rc = %ld\n",rc);
      return;
   }

   /* Query the page attributes in which the object is located. */
   MemSize = ObjSize;
   rc = DosQueryMem(ObjAlloc, &MemSize, &MemFlags);
   if (rc == 0) {
      printf("   DosQueryMem for ObjAlloc executed successfully.\n");
      printf("   MemSize = %ld\n", MemSize);
      if (MemFlags & PAG_COMMIT) {
         printf("   Page Memory has been committed.\n");
      } else {
         printf("   Page Memory has not been committed.\n");
      } /* endif */
   } else {
      printf("Error:  DosQueryMem for ObjAlloc with rc = %ld\n",rc);

      /* It's good practice to free the memory before you leave, 
      even though your process' memory will be freed by OS/2 when 
      the process terminates. */
      rc = DosFreeMem(ObjAlloc);
      return;
   }

   /* Commit the pages for the memory object */
   AllocFlags = PAG_DEFAULT | PAG_COMMIT ;
   rc = DosSetMem(ObjAlloc, ObjSize, AllocFlags );

   if (rc == 0) { 
      printf("DosSetMem for ObjAlloc executed successfully.\n");
   } else { 
      printf("Error:  DosSetMem for ObjAlloc with rc = %ld\n",rc);
      rc = DosFreeMem(ObjAlloc);
      return;
   }

   strcpy(ObjAlloc,
    "\"There is a simple explanation for why this has happened.\"");
   printf("ObjAlloc = %s\n",ObjAlloc);

   /* Again, query the page attributes in which the object is 
   located. */
   MemSize = ObjSize;
   rc = DosQueryMem(ObjAlloc, &MemSize, &MemFlags);
   if (rc == 0) {
      printf("   DosQueryMem for ObjAlloc executed successfully.\n");
      printf("   MemSize = %ld\n", MemSize);
      if (MemFlags & PAG_COMMIT) {
         printf("   Page Memory has been committed.\n");
      } else {
         printf("   Page Memory has not been committed.\n");
      } /* endif */
   } else {
      printf("Error:  DosQueryMem for ObjAlloc with rc = %ld\n",rc);
   }

   rc = DosFreeMem(ObjAlloc);

   if (rc == 0) {
      printf("DosFreeMem for ObjAlloc executed successfully.\n");
   } else {
      printf("Error:  DosFreeMem for ObjAlloc with rc = %ld\n",rc);
   }

   return;
}
