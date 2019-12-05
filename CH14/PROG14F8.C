/********************************************************/
/* Chapter 14.  Program illustrating OS/2 message APIs  */
/********************************************************/

#define INCL_DOSMISC
#define INCL_DOSNLS
#define INCL_DOSDATETIME
#include <os2.h>

#include <stdlib.h>

VOID DispMessage(PDATETIME pdt, ULONG msgno, PSZ string)
{
   CHAR buffer1[3], buffer2[3], buffer3[4], outbuff[100];
   ULONG ulMsglen;
   PSZ apszMsginsrts[3];

   memset(outbuff, '\0', sizeof(outbuff));

   switch (msgno) {
   case 100:
            apszMsginsrts[0] = string;
            DosGetMessage(apszMsginsrts, 1, outbuff, 100,
                          msgno, "SHOWDATE.MSG", &ulMsglen);
            break;
   case 101:
            apszMsginsrts[0] = _itoa(pdt->day, buffer1, 10);
            apszMsginsrts[1] = _itoa(pdt->month, buffer2,
                                     10);
            apszMsginsrts[2] = _itoa(pdt->year-1900, buffer3,
                                     10);
            DosGetMessage(apszMsginsrts, 3, outbuff, 100,
                          msgno, "SHOWDATE.MSG", &ulMsglen);
            break;
   case 102:
   case 103:
            DosGetMessage(NULL, 0, outbuff, 100,
                          msgno, "SHOWDATE.MSG", &ulMsglen);
            break;
   }

   DosPutMessage((HFILE)1, strlen(outbuff), outbuff);
}

BOOL IsCodePage(CHAR * buffer, ULONG curCP)
{
   PUSHORT pbuf;
   USHORT msgCPcnt, i;
   BOOL cpOK = FALSE;

   pbuf = (PUSHORT)buffer;
   msgCPcnt = *pbuf;
   if (msgCPcnt == 0) return(TRUE);
   pbuf++;
   for (i = 0; i < msgCPcnt; ++i) {
      if (*pbuf == curCP) {
         cpOK = TRUE;
         break;
      }
      pbuf++;
   }
   return(cpOK);
}

INT main( INT argc, CHAR *argv[], CHAR *envp[] )
{
   DATETIME dt;
   CHAR buffer[200];
   BOOL cpOK = FALSE;
   ULONG cplist[3], cpsize, altcp, ulMsglen, i;
   PSZ apszMsginsrts[2];
   CHAR buffer1[4], buffer2[4], outbuff[100];

   /* Make sure the program can display the messages */
   /* given the code pages installed in the system.  */

   DosQueryCp(sizeof(cplist), cplist, &cpsize);
   DosQueryMessageCP(buffer, 200, "SHOWDATE.MSG", &ulMsglen);
   if (!IsCodePage(buffer, cplist[0])) {
      altcp = ((cplist[0] == cplist[1]) ? cplist[2] :
                                          cplist[1]);
      if (IsCodePage(buffer, altcp)) {
         /* Change the process to use this code page */
         /* such that the messages are displayed as  */
         /* expected.                                */
         DosSetProcessCp(altcp);
      } else {
         /* Message file is not valid for the */
         /* available system code pages.      */
         apszMsginsrts[0] = _itoa(cplist[1], buffer1, 10);
         apszMsginsrts[1] = _itoa(cplist[2], buffer2, 10);
         DosInsertMessage(apszMsginsrts, 2,
                          "CODEPAGE=%1,%2", 14,
                          outbuff, 100, &ulMsglen);
         DosPutMessage((HFILE)1, strlen(outbuff), outbuff);
         return(1L);
      }
   }

   for (i = 1;  i < argc;  i++) {
      if (argv[i][0] == '?') {
         /* Display program information */
         DispMessage(NULL, 103, NULL);
      } else {
         /* Display unknown parameter */
         DispMessage(NULL, 100, argv[i]);
      }
   }

   DosGetDateTime(&dt);

   /* Display today's date */
   DispMessage(&dt, 101, NULL);

   /* Check for Friday the 13th */
   if ((dt.weekday == 5) && (dt.day == 13)) {
      DispMessage(&dt, 102, NULL);
   }

   return(0L);
}

