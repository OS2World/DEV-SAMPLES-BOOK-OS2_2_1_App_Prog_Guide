/* c4_3.c - loads a DLL using the C library functions */

#define INCL_DOSFILEMGR   /* File System APIs */
#define INCL_DOSMODULEMGR /* DLL APIs */
#define INCL_DOSMISC      /* For DoSearchPath */
#include <os2.h>
#include <stdio.h>
#include <errno.h>
#include "c4_2d.h"

void main (void)
{
HFILE       FileHandle;   /* File handle to create   */
ULONG       Action;    /* Results of action     */
UCHAR       filename[20], line[50], dllPath[256];
UCHAR       dllName[]="STOCK.DLL";
ULONG       bytesRead;
ULONG       filePtr;
BYTE        buffer[200];
int         i,j,index;  /* counters */
int         date, price;
STOCKPARMS  stockparms;  /* Main data structure */
STOCKRETURN stockreturn;  /* returned structure from high/lowPrice */
double      average;  /* returned value from averagePrice */
HMODULE     dllHandle;
PFN         faddr;   /* function address */
APIRET      rc;    /* Return code      */

   /* Get the path to the DLL */

   rc = DosSearchPath(SEARCH_ENVIRONMENT,"PATH",dllName,
          dllPath,sizeof(dllPath));

   if (rc != 0) {
      printf("Error:  Could not find %s.  DosSearchPath rc=%d",
         dllName,rc);
      return;
   }

   /* Get the handle of the DLL */

   rc = _loadmod(dllPath,&dllHandle);
   if (rc != 0) {
      printf("_loadmod failed for %s with rc = %ld.\n",dllPath,rc);
      if (errno == EMODNAME)
         printf("Module name is not valid.");
      if (errno == EOS2ERR)
         printf("System Error: %d.",_doserrno);
      return;
   } else {
      printf("Loaded %s with handle %ld.\n",dllPath,dllHandle);
   }

   /* Open and read the data in the file. */

   strcpy(filename,"STOCK.TXT");
   rc = DosOpen(filename,      /* Name of file to create  */
      &FileHandle,  /* Address of file handle  */
      &Action,   /* Pointer to action     */
      0,
      FILE_NORMAL,  /* Attribute of new file   */
      FILE_OPEN,
      OPEN_ACCESS_READONLY | OPEN_SHARE_DENYNONE,
      NULL);

   if (rc == 0) {
      printf("Opened file %s.\n", filename);
   } else {
      printf("DosOpen failed with rc = %ld.\n", rc);
      return;
   }

   /* Read, display, and parse the contents of the data file */

   rc = DosRead(FileHandle, buffer, sizeof(buffer), &bytesRead);

   if (rc == 0) {
      printf("Read %d bytes from the file.\n",bytesRead);
      index = -1;
      i = 0;
      while (i<(bytesRead-1)) {
         j = 0;
         strcpy(line,"");
         while (buffer[i] != '\n') {
            line[j++] = buffer[i++];
         }
         line[j] = buffer[i];
         index++; i++;
         sscanf(line,"%d %d\n",&date,&price);
         stockparms.date[index] = date;
         stockparms.price[index] = price;
       }
       stockparms.numentries = index;
   } else {
      printf("DosRead failed with rc = %ld.\n", rc);
   }

   rc = DosClose(FileHandle);

   if (rc == 0) {
      printf("Closed file %s.\n",filename);
   } else {
      printf("DosClose failed with rc = %ld.\n", rc);
   }

   /* Calculate and display values */

   printf("Printing out values:\n");
   for (i=0;i<stockparms.numentries;i++) {
      printf("Date: %d Price: %d\n",stockparms.date[i],stockparms.price[i]);
   }

  /* Retrieve function addresses.  The return code is checked for
  only the first DosQueryProcAddr call. */

   rc = DosQueryProcAddr(dllHandle, 0, "highPrice", &faddr);
   if (rc == 0) {
      printf("Retrieved address for the highPrice function.\n");
   } else {
      printf("DosQueryProcAddr failed with rc = %ld.\n", rc);
      if (rc = _freemod(dllHandle)) {
         printf("_freemod failed with rc = %ld\n", rc);
      }
      return;
   }
   faddr(stockparms,&stockreturn);
   printf("High price on %d with value %d.\n",stockreturn.date,stockreturn.price);

   DosQueryProcAddr(dllHandle, 0, "lowPrice", &faddr);
   faddr(stockparms,&stockreturn);
   printf("Low price on %d with value %d.\n",stockreturn.date,stockreturn.price);

   DosQueryProcAddr(dllHandle, 0, "averagePrice", &faddr);
   faddr(stockparms,&average);
   printf("Average price value %f.\n", average);

   /* Free the DLL handle. */

   if (rc = _freemod(dllHandle)) {
      printf("_freemod failed with rc = %ld\n", rc);
   }

   return;
}
