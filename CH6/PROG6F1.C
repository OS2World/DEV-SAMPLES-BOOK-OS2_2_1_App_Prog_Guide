/********************************/
/* Chapter 6.  DosQueryFileInfo */
/********************************/

#define INCL_DOSFILEMGR      /* File system values         */
#include <os2.h>
#include <stdio.h>

VOID main (USHORT argc, PCHAR argv[])
{
   HFILE FileHandle;            /*  File handle            */
   ULONG FileInfoLev;           /*  Level of info to return*/
   FILESTATUS FileInfoBuffer;   /*  Buffer for information */
   ULONG FileInfoBufferSize;    /*  Size of the buffer     */
   ULONG ActionTaken;
   APIRET rc;                   /*  Return code            */
   UCHAR FileName[20];

   FileInfoLev = 1;             /* Return Level 1 info     */
   FileInfoBufferSize = sizeof(FILESTATUS); /* Set size    */
   strcpy(FileName,"D:\\CONFIG.SYS");

   rc = DosOpen(FileName,
                &FileHandle,
                &ActionTaken,
                0,              /* File Size */
                FILE_NORMAL,
                FILE_OPEN,
                OPEN_SHARE_DENYNONE | OPEN_ACCESS_READWRITE,
                0L );           /* No extended attributes */

   if (rc == 0) {
      printf("DosOpen for %s executed successfully.\n", FileName);
   } else {
      printf("Error:  DosOpen for %s with rc = %ld\n", FileName,rc);
      return;
   }

   rc = DosQueryFileInfo(FileHandle,
                         FileInfoLev,
                         &FileInfoBuffer,
                         FileInfoBufferSize);

   if (rc == 0) {
      printf("DosQueryFileInfo for %s executed successfully.\n",FileName);
      printf("  File size is %d.\n",FileInfoBuffer.cbFile);
   } else {
      printf("Error:  DosQueryFileInfo for %s with rc = %ld\n",FileName,rc);
   }

   rc = DosClose(FileHandle);

   if (rc == 0) {
      printf("DosClose for %s executed successfully.\n",FileName);
   } else {
      printf("Error:  DosClose for %s with rc = %ld\n", FileName,rc);
   }

   return;
}
