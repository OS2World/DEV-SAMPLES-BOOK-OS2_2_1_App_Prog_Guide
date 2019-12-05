/********************************************************/
/* Chapter 5.  This program opens the file FILECODE.TXT,*/
/* which can be created by running program PROG5F1.C.   */
/* It sets the file pointer to the beginning of the     */
/* file, reads and prints the contents of the file,     */
/* and closes the file.                                 */
/********************************************************/

#define INCL_DOSFILEMGR       /* File system values     */
#include <os2.h>
#include <stdio.h>

VOID main (USHORT argc, PCHAR argv[])
{
   HFILE FileHandle;            /* File handle to create   */
   ULONG Action;                  /* Results of action     */
   APIRET rc;                          /* Return code      */
   UCHAR filename[20];
   ULONG bytesWritten, bytesRead;
   ULONG filePtr;
   BYTE buffer[200];

   strcpy(filename,"FILECODE.TXT");
   rc = DosOpen(filename,    /* Name of file to create  */
      &FileHandle,           /* Address of file handle  */
      &Action,               /* Pointer to action       */
      0,
      FILE_NORMAL,           /* Attribute of new file   */
      FILE_OPEN,
      OPEN_ACCESS_READONLY | OPEN_SHARE_DENYNONE,
      NULL);

   if (rc == 0) {
      printf("Opened file %s.\n", filename);
   } else {
      printf("DosOpen failed with rc = %ld.\n", rc);
      return;
   }

   /* Not really necessary, since initially opening the file
   will set the file pointer to the beginning. */

   rc = DosSetFilePtr(FileHandle, 0, FILE_BEGIN, &filePtr);

   if (rc == 0) {
      printf("Set the file pointer to the beginning of the file.\n");
   } else {
      printf("DosSetFilePtr failed with rc = %ld\n", rc);
   }

   rc = DosRead(FileHandle, buffer, sizeof(buffer), &bytesRead);

   if (rc == 0) {
      printf("Read %d bytes from the file.\n",bytesRead);
      printf("Contents:\n%s\n", (CHAR *) buffer);
   } else {
      printf("DosRead failed with rc = %ld.\n", rc);
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