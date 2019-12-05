/* prog8ca.c - Uses shared memory.
prog8c.c is the companion program. */

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
   APIRET   rc;          /* Return code */
   UCHAR SharedMemName[20]; /* Shared memory name */
   UCHAR SemEventName[20];  /* Semaphore created by prog8c.exe */
   UCHAR SemEventName2[20]; /* Semaphore created by prog8ca.exe */
   HEV  hev, hev2;          /* Semaphore handles */
   ULONG flAttr = 0;        /* Semaphore flags = none */
   BOOL32 fState = FALSE;   /* Semaphore initial state = set */

   /* Initialize names */
   strcpy(SharedMemName,"\\SHAREMEM\\MEMEX.DAT");
   strcpy(SemEventName,"\\SEM32\\MEMEX1");
   strcpy(SemEventName2,"\\SEM32\\MEMEX2");
   hev = 0;
   hev2 = 0;

   rc = DosCreateEventSem(SemEventName2, &hev2, flAttr, fState);

   if (rc == 0) {
      printf("DosCreateEventSem for %s executed successfully.\n",
        SemEventName2);
   } else {
      printf("Error:  DosCreateEventSem for %s with rc = %ld\n",rc);
      return;
   }

   /* Try to open the semaphore created by the first program */
   rc = DosOpenEventSem(SemEventName,&hev);
   if (rc == 0) {
      printf("DosOpenEventSem for %s executed successfully.\n",
        SemEventName);
   } else {
      /* This program expects the first semaphore to exist.
      You could set it up to loop until it does. */
      printf("Error:  DosOpenEventSem for %s with rc = %ld\n", 
        SemEventName,rc);
      DosCloseEventSem(hev2);
      return;
   }

   /* Wait for the first semaphore to be posted */
   DosWaitEventSem(hev, SEM_INDEFINITE_WAIT);

   AllocFlags = PAG_WRITE;

   rc = DosGetNamedSharedMem(&ObjAlloc,SharedMemName,AllocFlags);

   if (rc == 0) {
      printf("DosGetNamedSharedMem for %s executed successfully.\n",
        SharedMemName);
   } else {
      printf("Error:  DosGetNamedSharedMem for %s with rc = %ld\n",
        SharedMemName,rc);
   }

   printf("ObjAlloc = %s\n",ObjAlloc);

   rc = DosFreeMem(ObjAlloc);

   if (rc == 0) {
      printf("DosFreeMem for %s executed successfully.\n",
        SharedMemName);
   } else {
      printf("Error:  DosFreeMem for %s with rc = %ld\n",
        SharedMemName,rc);
   }

   DosPostEventSem(hev2);

   /* pause to let the other program catch the semaphore 
      before closing it */
   printf("Pausing...\n");
   DosSleep(2);

   /* Now close the semaphores and leave */
   DosCloseEventSem(hev);
   DosCloseEventSem(hev2);

   return;
}
