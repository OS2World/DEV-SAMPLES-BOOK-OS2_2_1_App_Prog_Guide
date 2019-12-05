/* c4_4.c - Calls a DLL using the OS/2 APIs. */

#define INCL_DOSFILEMGR   /* File System APIs */
#define INCL_DOSMODULEMGR /* DLL APIs */
#define INCL_DOSMISC      /* For DoSearchPath */
#include <os2.h>
#include <stdio.h>
#include "c4_2d.h"  /* can use the H file from the previous example */

VOID main (void)
{
HFILE       FileHandle;   /* File handle to create   */
ULONG       Action;    /* Results of action     */
UCHAR       filename[20], line[50], dllPath[256];
UCHAR       dllName[]="STOCK.DLL";
ULONG       bytesRead;
ULONG       filePtr;
BYTE        buffer[300];
int         i,j,index;  /* counters */
int         date, price;
STOCKPARMS  stockparms;  /* Main data structure */
STOCKRETURN stockreturn;  /* returned structure from high/lowPrice */
double      average;  /* returned value from averagePrice */
HMODULE     dllHandle;
PFN         faddr;
CHAR        loadErrorStr[200];
CHAR        retDLLName[256];  /* returned DLL name */
ULONG       dllType;  /* Attributes of the DLL */
ULONG       procType;  /* Attributes of the function */
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

   rc = DosLoadModule(
           loadErrorStr,
           sizeof(loadErrorStr),
           dllPath,
           &dllHandle);
   if (rc == 0) {
      printf("Loaded %s with handle %ld.\n",dllName,dllHandle);
   } else {
      printf("DosLoadModule failed for %s with rc = %ld.\n",dllPath,rc);
      printf("%s\n",loadErrorStr);
      return;
   }

   /* Although redundant, query the DLL name for illustrative purposes.
   Also, query application type information for the DLL. */

   DosQueryModuleName(dllHandle,sizeof(retDLLName),retDLLName);
   printf("Status about %s.\n",retDLLName);
   if (rc = DosQueryAppType(dllName,&dllType)) {
       if ((dllType & FAPPTYP_PROTDLL) != 0)
          printf("   %s is a protected DLL.\n",dllName);
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

   /* Checks could be done after the other DosQueryProcAddr calls too */

   rc = DosQueryProcAddr(dllHandle, 0, "highPrice", &faddr);
   if (rc == 0) {
      printf("Retrieved address for the highPrice function.\n");
      DosQueryProcType(dllHandle,0,"highPrice",&procType);
      if (procType == PT_32BIT)
         printf("   Function highPrice is 32-bit.\n");
      else
         printf("   Function highPrice is 16-bit.\n");
   } else {
      printf("DosQueryProcAddr failed with rc = %ld.\n", rc);
      rc = DosFreeModule(dllHandle);
      if (rc == 0) {
         printf("Freed %s handle %ld.\n",dllName,dllHandle);
      } else {
         printf("DosFreeModule failed with rc = %ld.\n", rc);
         return;
      }
      return;
   }

   faddr(stockparms,&stockreturn);
   printf("High price on %d with value %d.\n",stockreturn.date,stockreturn.price);

   DosQueryProcAddr(dllHandle, 0, "lowPrice", &faddr);
   faddr(stockparms,&stockreturn);
   printf("Low price on %d with value %d.\n",stockreturn.date,stockreturn.price);

   /* Call the ordinal number instead of the function name */

   DosQueryProcAddr(dllHandle, 3, "", &faddr);
   faddr(stockparms,&average);
   printf("Average price value %f.\n", average);

   /* Free the DLL handle. */

   rc = DosFreeModule(dllHandle);
   if (rc == 0) {
      printf("Freed %s handle %ld.\n",dllName,dllHandle);
   } else {
      printf("DosFreeModule failed with rc = %ld.\n", rc);
      return;
   }

   return;
}
