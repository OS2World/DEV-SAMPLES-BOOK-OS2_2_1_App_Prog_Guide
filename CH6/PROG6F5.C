/********************************/
/* Chapter 6.  DosQueryFSInfo   */
/********************************/

#define INCL_DOSFILEMGR      /* File system values         */
#include <os2.h>
#include <stdio.h>

typedef struct _FSInfoStruct
{
   ULONG filesysid;
   ULONG sectornum;
   ULONG unitnum;
   ULONG unitavail;
   USHORT bytesnum;
} FSInfoStruct;

VOID main (USHORT argc, PCHAR argv[])
{
   ULONG DriveNum;          /* Drive number                */
   ULONG FSInfoLev;         /* File system data            */
   ULONG BufSize = 80;      /* Size of file sys buffer     */
   UCHAR FileSysBuf[80];    /* Buffer for file sys info    */
   APIRET rc;               /* Return code                 */

   DriveNum = 4;            /* Drive D (A=1, B=2, C=3)     */

   FSInfoLev = FSIL_ALLOC;  /* File system allocation info */

   rc = DosQueryFSInfo(DriveNum,
                       FSInfoLev,
                       FileSysBuf,
                       BufSize);

   if (rc == 0) {
      printf("DosQueryFSInfo executed successfully.\n");
      printf("   File system ID is %d.\n",
        ((FSInfoStruct *) FileSysBuf)->filesysid);
      printf("   Number of sectors per allocation unit is %d.\n",
        ((FSInfoStruct *) FileSysBuf)->sectornum);
      printf("   Number of allocation units is %d.\n",
        ((FSInfoStruct *) FileSysBuf)->unitnum);
      printf("   Number of allocation units available %d.\n",
        ((FSInfoStruct *) FileSysBuf)->unitavail);
      printf("   Number of bytes per sector is %u.\n",
        ((FSInfoStruct *) FileSysBuf)->bytesnum);
   } else {
      printf("Error:  DosQueryFSInfo with rc = %ld\n",rc);
   }

   return;
}

