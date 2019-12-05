/********************************/
/* Chapter 6.  DosResetBuffer   */
/********************************/

#define INCL_DOSFILEMGR      /* File system values         */
#define INCL_DOSERRORS       /* Base error codes           */
#include <os2.h>
#include <stdio.h>

VOID main (USHORT argc, PCHAR argv[])
{
   HFILE  FileHandle;
   UCHAR FileName[20];
   ULONG  Action;
   ULONG ActionTaken;
   UCHAR writeBuffer[50];
   ULONG bytesWritten;
   ULONG FileInfoLev;          /*  Level of info to return */
   FILESTATUS FileInfoBuffer;  /*  Buffer for information  */
   ULONG FileInfoBufferSize;   /*  Size of the buffer      */
   APIRET rc;
   ULONG i;

   strcpy(FileName,"TEST.OUT");

   rc = DosOpen(FileName,
                &FileHandle,
                &ActionTaken,
                4000,          /* File Size                */
                FILE_NORMAL,
                OPEN_ACTION_CREATE_IF_NEW,
                OPEN_SHARE_DENYNONE | OPEN_ACCESS_READWRITE,
                0L );          /* No extended attributes   */

   if (rc == 0) {
      printf("DosOpen for %s executed successfully.\n",
         FileName);
   } else {
      printf("Error:  DosOpen for %s with rc = %ld\n",
         FileName,rc);
      if (rc == ERROR_OPEN_FAILED) {
         printf("   Check to see if the file already exists or is write protected.\n");
      }
      return;
   }

   strcpy(writeBuffer, "All work and no play makes Jack a dull boy.");

   for (i=1;i<1000;i++) {
      rc = DosWrite(FileHandle,
                    writeBuffer,
                    sizeof(writeBuffer),
                    &bytesWritten);
      if (rc != 0) {
         printf("Error:  DosWrite for %s with rc = %ld\n",
            FileName,rc);
         break;
      }
   }

   rc = DosResetBuffer(FileHandle);

   if (rc == 0) {
      printf("DosResetBuffer for %s executed successfully.\n",FileName);
   } else {
      printf("Error:  DosResetBuffer for %s with rc = %ld\n",
         FileName,rc);
   }

   FileInfoLev = 1;             /* Return Level 1 info     */
   FileInfoBufferSize = sizeof(FILESTATUS); /* Set size    */

   rc = DosQueryFileInfo(FileHandle,
                         FileInfoLev,
                         &FileInfoBuffer,
                         FileInfoBufferSize);

   if (rc == 0) {
      printf("DosQueryFileInfo for %s executed successfully.\n",FileName);
      printf("   File size is %d.\n",FileInfoBuffer.cbFile);
   } else {
      printf("Error:  DosQueryFileInfo for %s with rc = %ld\n",FileName,rc);
   }

   rc = DosClose(FileHandle);

   if (rc == 0) {
      printf("DosClose for %s executed successfully.\n",
         FileName);
   } else {
      printf("Error:  DosClose for %s with rc = %ld\n",
         FileName,rc);
   }

   return;
}

