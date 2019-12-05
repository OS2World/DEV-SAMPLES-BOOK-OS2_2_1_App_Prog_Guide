/* prog8c.c - Uses shared memory.  
prog8ca.c is the companion program. */

#define INCL_DOSMEMMGR   /* Include Memory Management APIs */
#define INCL_DOSSEMAPHORES  /* Include Semaphore APIs */
#define INCL_NOPMAPI     /* Don't include PM APIs */
#include <os2.h>
#include <stdio.h>  
#include <bsememf.h>   /* Flags for memory management */

VOID main (USHORT argc, PCHAR argv[])
{
   PVOID    ObjAlloc;    /* Pointer to memory object */
   ULONG    ObjSize;     /* Size of memory object */
   ULONG    AllocFlags;  /* Attributes of the memory object */
   APIRET   rc;          /* API return code */
   UCHAR SharedMemName[20]; /* Shared memory name */
   UCHAR SemEventName[20];  /* Semaphore created by prog8c.exe */
   UCHAR SemEventName2[20]; /* Semaphore created by prog8ca.exe */
   HEV  hev, hev2;          /* Semaphore handles */
   ULONG flAttr = 0;        /* Semaphore flags = none */
   BOOL32 fState = FALSE;   /* Semaphore initial state = set */
   int i;                /* Counter */

   strcpy(SharedMemName,"\\SHAREMEM\\MEMEX.DAT");
   ObjSize = 500;     /* Will be rounded up to 4KB */

   /* Can't specify the OBJ_GETTABLE flag since the memory       
   object is named, however, commit it and give it write access */
   AllocFlags = PAG_WRITE | PAG_COMMIT;  

   rc = DosAllocSharedMem(&ObjAlloc, SharedMemName, ObjSize, 
           AllocFlags);

   if (rc == 0) {
      printf("DosAllocSharedMem for %s executed successfully.\n",
        SharedMemName);
   } else {
      printf("Error:  DosAllocSharedMem for %s with rc = %ld\n",
        SharedMemName,rc);
      return;
   }

   /* Name the two semaphores */
   strcpy(SemEventName,"\\SEM32\\MEMEX1");
   strcpy(SemEventName2,"\\SEM32\\MEMEX2");
   hev = 0;  
 
   /* Create the first semaphore */
   rc = DosCreateEventSem(SemEventName, &hev, flAttr, fState);

   if (rc == 0) {
      printf("DosCreateEventSem for %s executed successfully.\n",
        SemEventName);
   } else {
      printf("Error:  DosCreateEventSem for %s with rc = %ld\n",
        SemEventName,rc);
      return;
   }
 
   /* Fill the shared memory object with data */
   strcpy(ObjAlloc,"A");
   for (i=1;i<ObjSize;i++) {
      strcat(ObjAlloc,"A");
   }
   printf("ObjAlloc = %s\n",ObjAlloc);

   /* Signal the first semaphore */
   DosPostEventSem(hev);
   hev2 = 0;

   do {
      /* Loop until semaphore 2 can be opened */
      rc = DosOpenEventSem(SemEventName2,&hev2);

      if (rc == 0) {
          printf("DosOpenEventSem for %s executed successfully.\n",
            SemEventName2);
       } else {
          printf("Error:  DosOpenEventSem for %s with rc = %ld\n",
            SemEventName2,rc);
          printf("Still waiting...\n");
          DosSleep(1);
       }
   } while (rc != 0);
   printf("\n");

   /* Wait until semaphore 2 is signaled */
   DosWaitEventSem(hev2, SEM_INDEFINITE_WAIT);

   /* Close access to both semaphores */
   DosCloseEventSem(hev);
   DosCloseEventSem(hev2);

   /* Free the shared memory object */
   rc = DosFreeMem(ObjAlloc);

   if (rc == 0) {
      printf("DosFreeMem for %s executed successfully.\n",
        SharedMemName);
   } else {
      printf("Error:  DosFreeMem for %s with rc = %ld\n",
        SharedMemName,rc);
   }

   return;
}
