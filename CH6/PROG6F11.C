/********************************/
/* Chapter 6.  DosSetFileInfo   */
/********************************/

#define INCL_DOSFILEMGR        /* File system values       */
#include <os2.h>
#include <stdio.h>

VOID main (USHORT argc, PCHAR argv[])
{
   HFILE FileHandle;           /*  File handle             */
   ULONG  Action;
   ULONG FileInfoLevel;        /*  Level of info to return */
   ULONG ActionTaken;
   APIRET rc;                    /*  Return code           */
   UCHAR FileName[20];
   FILESTATUS  FileInfoBuf;      /* File info buffer       */
   ULONG       FileInfoBufSize;  /* File info buffer size  */
   DATETIME    DateTimeBuf;      /* Date/Time buffer       */

   strcpy(FileName,"TEST.OUT");

   rc = DosOpen(FileName,
            &FileHandle,
            &ActionTaken,
            0,  /* File Size */
            FILE_NORMAL,
            OPEN_ACTION_CREATE_IF_NEW |
             OPEN_ACTION_REPLACE_IF_EXISTS,
            OPEN_SHARE_DENYREADWRITE | 
             OPEN_ACCESS_READWRITE,
            0L );                /* No extended attributes */

   if (rc == 0) {
      printf("DosOpen for %s executed successfully.\n", FileName);
   } else {
      printf("Error:  DosOpen for %s with rc = %ld\n", FileName,rc);
      return;
   }

   FileInfoLevel = 1;             /* Return Level 1 info   */
   FileInfoBufSize = sizeof(FILESTATUS); /* Set size       */

   rc = DosQueryFileInfo(FileHandle, FileInfoLevel,
                          &FileInfoBuf, FileInfoBufSize);

   if (rc == 0) {
      printf("DosQueryFileInfo for %s executed successfully.\n",FileName);
   } else {
        printf("Error:  DosQueryFileInfo for %s with rc = %ld\n",FileName,rc);         return;
   }

   FileInfoBuf.fdateLastWrite.year = 1;
   FileInfoBuf.fdateLastWrite.month = 1;
   FileInfoBuf.fdateLastWrite.day = 1;
   FileInfoBuf.ftimeLastWrite.hours = 1;
   FileInfoBuf.ftimeLastWrite.minutes = 1;
   FileInfoBuf.ftimeLastWrite.twosecs = 1;

   /*   Update the Level 1 information block associated    */
   /*   with the file.                                     */

   rc = DosSetFileInfo(FileHandle,
                       FileInfoLevel,
                       &FileInfoBuf,
                       FileInfoBufSize);

   if (rc == 0) {
      printf("DosSetFileInfo for %s executed successfully.\n",FileName);
   } else {
      printf("Error:  DosSetFileInfo for %s with rc = %ld\n",FileName,rc);
   }

   rc = DosClose(FileHandle);

   if (rc == 0) {
      printf("DosClose for %s executed successfully.\n", FileName);
   } else {
      printf("Error:  DosClose for %s with rc = %ld\n", FileName,rc);
   }

   return;
}
