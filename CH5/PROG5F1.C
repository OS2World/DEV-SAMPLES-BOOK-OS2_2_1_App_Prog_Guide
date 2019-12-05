/************************************************************/
/* Chapter 5.  This program opens a file named FILECODE.TXT */
/************************************************************/

#define INCL_DOSFILEMGR    /* File system values      */
#include <os2.h>
#include <stdio.h>

VOID main (USHORT argc, PCHAR argv[])
{
   HFILE FileHandle;          /* File handle to create   */
   ULONG Action;                /* Results of action     */
   APIRET rc;                        /* Return code      */
   UCHAR buffer[100], filename[20];
   ULONG bytesWritten;
   ULONG filePtr;

   strcpy(filename,"FILECODE.TXT");
   rc = DosOpen(filename,   /* Name of file to create */
      &FileHandle,         /* Address of file handle  */
      &Action,               /* Pointer to action     */
      0,                      /* Size of new file     */
      FILE_NORMAL,         /* Attribute of new file   */
      FILE_OPEN | OPEN_ACTION_CREATE_IF_NEW,
      OPEN_ACCESS_WRITEONLY | OPEN_SHARE_DENYNONE,
      NULL);

   if (rc == 0) {
      printf("Opened file %s.\n", filename);
   } else {
      printf("DosOpen failed with rc = %ld.\n", rc);
      return;
   }

   rc = DosSetFilePtr(FileHandle, 0, FILE_END, &filePtr);

   if (rc == 0) {
      printf("Set the file pointer at the end of the file.\n");
   } else {
      printf("DosSetFilePtr failed with rc = %ld\n", rc);
   }

   /* write a string to the file */
   strcpy(buffer,
     "It is good that war is so terrible - we should grow too fond of it.\r\n");
   rc = DosWrite(FileHandle, buffer, strlen(buffer), &bytesWritten);

   if (rc == 0) {
      printf("Wrote %d bytes to the file.\n",bytesWritten);
   } else {
      printf("DosWrite failed with rc = %ld.\n", rc);
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