/********************************/
/* Chapter 6.  DosFSAttach      */
/********************************/

#define INCL_DOSFILEMGR      /* File system values         */
#include <os2.h>
#include <stdio.h>

VOID main (USHORT argc, PCHAR argv[])
{
   UCHAR DriveName[3];          /* Drive letter               */
   UCHAR FileSysDriver[30];     /* File system driver         */
   PVOID AttachDataBuf;         /* Data for attach argument   */
   ULONG AttachDataBufLen;      /* Length of the buffer       */
   ULONG Flag;                  /* Set to attach or detach    */
   APIRET rc;                   /* Return code                */

   strcpy(DriveName, "Z:");     /* Drive to attach            */

   strcpy(FileSysDriver,"\\netlan\\src");

   AttachDataBuf = NULL;        /* User does not supply data  */

   AttachDataBufLen = 0;        /* Zero length                */

   Flag = 0;                    /* Attach (1=detach)          */

   rc = DosFSAttach(DriveName,
                    FileSysDriver,
                    AttachDataBuf,
                    AttachDataBufLen,
                    Flag);

   if (rc != 0) {
       printf("DosFSAttach rc = %ld", rc);
   }
}
