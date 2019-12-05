/*********************************************************/
/* Chapter 5.  DosSetFileLocks                           */
/* This program opens a file (creating it if it doesn't  */
/* exist), locks the file, sets the file pointer to the  */
/* end of the file, writes a text string, and closes the */
/* file.                                                 */
/*********************************************************/

#define INCL_DOSFILEMGR        /* File system values     */
#include <os2.h>
#include <stdio.h>

VOID main (USHORT argc, PCHAR argv[])
{
   HFILE FileHandle;             /* File handle to create   */
   ULONG Action;                   /* Results of action     */
   APIRET rc;                           /* Return code      */
   UCHAR x[20], filename[20];
   ULONG bytesWritten;
   ULONG filePtr;
   ULONG timeout = 3000;
   FILELOCK area;

   strcpy(filename,"FILECODE.TXT");
   rc = DosOpen(filename,      /* Name of file to create */
      &FileHandle,            /* Address of file handle  */
      &Action,                  /* Pointer to action     */
      0,                         /* Size of new file     */
      FILE_NORMAL,            /* Attribute of new file   */
      FILE_OPEN | OPEN_ACTION_CREATE_IF_NEW,
      OPEN_ACCESS_WRITEONLY | OPEN_SHARE_DENYNONE,
      NULL);

   if (rc == 0) {
      printf("Opened file %s.\n", filename);
   } else {
      printf("DosOpen failed with rc = %ld.\n", rc);
      return;
   }

  /* Lock a region of the file so other processes can't  */
  /* get to it.                                          */

  area.lOffset = 0;  /* Where to begin the locked range. */
  area.lRange = 20;                /* Range to lock out. */

  rc = DosSetFileLocks(FileHandle,     /* File handle    */
         0L,                         /* Unlock range (0) */
         (PFILELOCK) &area,            /* Lock range     */
         timeout,                      /* Lock timeout   */
         0);                           /* Share request  */

  if (rc == 0) {
      printf("DosSetFileLocks succeeded in locking bytes %d to %d.\n",
         area.lOffset,area.lOffset+area.lRange);
   } else {
      printf("DosSetFileLocks failed with rc = %ld,\n", rc);
  }

   rc = DosSetFilePtr(FileHandle, 0, FILE_END, &filePtr);

   if (rc == 0) {
      printf("Set the file pointer at the end of the file.\n");
   } else {
      printf("DosSetFilePtr failed with rc = %ld\n", rc);
   }

   strcpy(x,"--General Robert E. Lee\r\n");
   rc = DosWrite(FileHandle, x, strlen(x), &bytesWritten);

   if (rc == 0) {
      printf("Wrote %d bytes to the file.\n",bytesWritten);
   } else {
      printf("DosWrite failed with rc = %ld.\n", rc);
   }

   rc = DosSetFilePtr(FileHandle, 0, FILE_BEGIN, &filePtr);

   if (rc == 0) {
      printf("Set the file pointer at the beginning of the file.\n");
   } else {
      printf("DosSetFilePtr failed with rc = %ld\n", rc);
   }

   rc = DosClose(FileHandle);

   if (rc == 0) {
      printf("Closed file %s.\n",filename);
   } else {
      printf("DosClose failed with rc = %ld.\n", rc);
   }

   return;
}
