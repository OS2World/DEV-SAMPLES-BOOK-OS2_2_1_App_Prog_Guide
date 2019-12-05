/* c4_2.c - calls a DLL, using LIB files. */

#define INCL_DOSFILEMGR  /* File system values     */
#include <os2.h>
#include <stdio.h>
#include "c4_2.h"

VOID main (void)
{
HFILE        FileHandle;   /* File handle to create   */
ULONG       Action;    /* Results of action     */
UCHAR       filename[20], line[50];
ULONG       bytesRead;  /* number of bytes read from the file */
ULONG       filePtr;
BYTE        buffer[200];
int         i,j,index;  /* counters */
int         date, price;
STOCKPARMS  stockparms;  /* Main data structure */
STOCKRETURN stockreturn;  /* returned structure from high/lowPrice */
double      average;  /* returned value from averagePrice */
APIRET      rc;    /* Return code      */

   strcpy(filename,"STOCK.TXT");
   rc = DosOpen(filename,      /* Name of file to create  */
      &FileHandle,  /* Address of file handle  */
      &Action,   /* Pointer to action     */
      0,
      FILE_NORMAL,
      FILE_OPEN,
      OPEN_ACCESS_READONLY | OPEN_SHARE_DENYNONE,
      NULL);

   if (rc == 0) {
      printf("Opened file %s.\n", filename);
   } else {
      printf("DosOpen failed for %s with rc = %ld.\n",filename,rc);
      return;
   }

   /* Unnecessary, since initially opening the file will set the
   file pointer to the beginning, but used here as an illustration. */

   rc = DosSetFilePtr(FileHandle, 0, FILE_BEGIN, &filePtr);

   if (rc == 0) {
      printf("Set the file pointer to the beginning of the file.\n");
   } else {
      printf("DosSetFilePtr failed with rc = %ld\n", rc);
      DosClose(FileHandle);
      return;
   }

   /* Read, display, and parse the contents of the data file */
   rc = DosRead(FileHandle, buffer, sizeof(buffer), &bytesRead);

   if (rc == 0) {
      printf("Read %d bytes from the file.\n",bytesRead);
      printf("Contents:\n%s\n", (CHAR *) buffer);
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
      DosClose(FileHandle);
      return;
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

   highPrice(stockparms,&stockreturn);
   printf("High price on %d with value %d.\n",stockreturn.date,stockreturn.price);

   lowPrice(stockparms,&stockreturn);
   printf("Low price on %d with value %d.\n",stockreturn.date,stockreturn.price);

   averagePrice(stockparms,&average);
   printf("Average price value %f.\n",average);

   return;
}
