/* prog16.c - CID Installation Program Example */

#define INCL_DOSMEMMGR   /* Include Memory Management Calls */
#define INCL_DOSFILEMGR      /* File system values         */
#define INCL_DATETIME   
#define INCL_NOPMAPI   /* Since PM APIs are not used, don't include 
                          them */

#include <os2.h>
#include <stdio.h>
#include <bsememf.h>   

/* CID return codes */

#define RC_SUCCESS         0x0000
#define RC_IOERROR         0x1200
#define RC_PARMERROR       0x1600
#define RC_UNEXPECTEDERROR 0x1604

/* Stores command line parameter values */

typedef struct _cmdParms
{
   UCHAR  sourceDir[256];
   UCHAR  clientFile[256];
   UCHAR  groupDir[256];
   UCHAR  log1[256];
   UCHAR  targetDir[256];
   UCHAR  configSysDir[256];
   UCHAR  nodename[9];
} CMDPARMS;

/* Structure for the response file keywords and values */

typedef struct _instParms
{
   UCHAR  bufferStr[55];
   UCHAR  bufferVal[256];
   UCHAR  timeoutStr[55];
   UCHAR  timeoutVal[255];
} INSTPARMS;

/* Allowable command line parameters */

static UCHAR stdCmdLineArg[10][5] = {"/S", "/R", "/G", "/L1", "/T", "/TU"};

/* Pre-declaration of functions */

void trimBlanks(CHAR * );
int splitKeywordValName(UCHAR *, UCHAR *, UCHAR *);
int stringcpyFromTo(PSZ, PSZ, int , int);
BOOL isCommentLine(UCHAR *);

/****************/
/* Main program */
/****************/

int main (USHORT argc, PCHAR argv[])
{
   int i, j, k,charPos;
   UCHAR cmdLineArg[10][50], tempStr[300], fileStr[256], dirStr[256];
   UCHAR keywordStr[100], valueStr[100];
   UCHAR lineStr[300];
   CMDPARMS cmdLineParms;
   INSTPARMS instParms;
   PSZ currparm;
   ULONG parmfound;
   ULONG keywordfound;
   ULONG ObjSize=3000;     
   DATETIME DateTime;
   APIRET rc;              

   /* File variables */
   HFILE FileHandle,log1FileHandle,dupFileHandle;
   ULONG bytesRead, bytesWritten;
   ULONG ActionTaken;
   UCHAR filename[20];
   ULONG filePtr;
   UCHAR *rspFileBuffer;

   /* Initialize strings and buffers */

   strcpy(fileStr,"");
   strcpy(dirStr,"");
   strcpy(keywordStr,"");
   strcpy(valueStr,"");
   strcpy(instParms.bufferStr,"BUFFER");
   strcpy(instParms.bufferVal,"");
   strcpy(instParms.timeoutStr,"TIMEOUT");
   strcpy(instParms.timeoutVal,"");

   /* set up the command line defaults */
   strcpy(cmdLineParms.sourceDir,"Y:\\CID\\IMG\\PROD\\");
   strcpy(cmdLineParms.clientFile,"");
   strcpy(cmdLineParms.groupDir,"");
   strcpy(cmdLineParms.log1,"");
   strcpy(cmdLineParms.targetDir,"");
   strcpy(cmdLineParms.configSysDir,"C:\\");
   strcpy(cmdLineParms.nodename,"NODE0001");

   /* get the command line parameters */

   for (i=1;i < argc;++i) {
      parmfound = FALSE;

      currparm = argv[i];

      /* /S:sourceDirectory */
      if (strnicmp(currparm,"/S:",3) == 0) {
        stringcpyFromTo(currparm,&cmdLineParms.sourceDir,3,strlen(currparm));
        parmfound = TRUE;
      }
      /* /R:clientFilename */
      if (strnicmp(currparm,"/R:",3) == 0) {
        stringcpyFromTo(currparm,&cmdLineParms.clientFile,3,strlen(currparm));
        parmfound = TRUE;
      }
      /* /G:groupDirectory */
      if (strnicmp(currparm,"/G:",3) == 0) {
        stringcpyFromTo(currparm,&cmdLineParms.groupDir,3,strlen(currparm));
        parmfound = TRUE;
      }
      /* /L1:historyAndErrorLogFile */
      if (strnicmp(currparm,"/L1:",4) == 0) {
        stringcpyFromTo(currparm,&cmdLineParms.log1,4,strlen(currparm));
        parmfound = TRUE;
      }
      /* /T:targetDirectory */
      if (strnicmp(currparm,"/T:",3) == 0) {
        stringcpyFromTo(currparm,&cmdLineParms.targetDir,3,strlen(currparm));
        parmfound = TRUE;
     }
      /* /T:configsysDirectory */
      if (strnicmp(currparm,"/TU:",4) == 0) {
        stringcpyFromTo(currparm,&cmdLineParms.configSysDir,4,strlen(currparm));
        parmfound = TRUE;
     }
      /* /N:nodename */
      if (strnicmp(currparm,"/N:",3) == 0) {
        stringcpyFromTo(currparm,&cmdLineParms.nodename,3,strlen(currparm));
        parmfound = TRUE;
     }
     if (parmfound == FALSE) {
        printf("Error:  Invalid parameter: %s\n",currparm);
        exit(RC_PARMERROR);
     } 

   }

   /* Put default values in that need to be calculated from other values,
   if they weren't specified on the command line. */

   if (strcmp(cmdLineParms.clientFile,"") == 0) {
      strcpy(tempStr,"");
      strcat(tempStr,cmdLineParms.nodename);
      strcat(tempStr,".RSP");
      strcpy(cmdLineParms.clientFile,tempStr);
   } 

   /* log file */
   if (strcmp(cmdLineParms.log1,"") == 0) {
      strcpy(tempStr,"");
      strcat(tempStr,cmdLineParms.nodename);
      strcat(tempStr,".LOG");
      strcpy(cmdLineParms.log1,tempStr);
   }

   /* Put header in log file. */

   rc = DosOpen(cmdLineParms.log1,
                &log1FileHandle,
                &ActionTaken,
                0L,  /* File Size */
                FILE_NORMAL,
                FILE_OPEN | OPEN_ACTION_CREATE_IF_NEW,
                OPEN_ACCESS_WRITEONLY | OPEN_SHARE_DENYNONE,
                NULL ); /* No extended attributes */

   if (rc != 0) {
      printf("Error:  DosOpen for cmdLineParms.log1 with rc = %ld\n",rc);
      exit(RC_IOERROR);
   }

   rc = DosSetFilePtr(log1FileHandle, 0, FILE_END, &dupFileHandle);

   if (rc != 0) {
      printf("Error:  DosSetFilePtr for cmdLineParms.log1 with rc = %ld\n",rc);
      exit(RC_IOERROR);
   }

   DosGetDateTime(&DateTime);
   sprintf(tempStr,"\n\r%2.2d-%2.2d-%2.2d %2.2d:%2.2d:%2.2d - Started installation for node %s.\n\r",
        DateTime.month,DateTime.day,DateTime.year,DateTime.hours,
        DateTime.minutes,DateTime.seconds,cmdLineParms.nodename);
   rc = DosWrite(log1FileHandle,tempStr,strlen(tempStr),&bytesWritten);
   sprintf(tempStr,"   Source Directory - %s\n\r",cmdLineParms.sourceDir);
   rc = DosWrite(log1FileHandle,tempStr,strlen(tempStr),&bytesWritten);
   sprintf(tempStr,"   Client Filename - %s\n\r",cmdLineParms.clientFile);
   rc = DosWrite(log1FileHandle,tempStr,strlen(tempStr),&bytesWritten);
   sprintf(tempStr,"   Group Directory - %s\n\r",cmdLineParms.groupDir);
   rc = DosWrite(log1FileHandle,tempStr,strlen(tempStr),&bytesWritten);
   sprintf(tempStr,"   Error Log Filename (L1) - %s\n\r",cmdLineParms.log1);
   rc = DosWrite(log1FileHandle,tempStr,strlen(tempStr),&bytesWritten);
   sprintf(tempStr,"   History Log Filename (L2) - %s\n\r",cmdLineParms.log1);
   rc = DosWrite(log1FileHandle,tempStr,strlen(tempStr),&bytesWritten);
   sprintf(tempStr,"   Target Directory - %s\n\r",cmdLineParms.targetDir);
   rc = DosWrite(log1FileHandle,tempStr,strlen(tempStr),&bytesWritten);
   sprintf(tempStr,"   CONFIG.SYS Directory - %s\n\r",cmdLineParms.configSysDir);
   rc = DosWrite(log1FileHandle,tempStr,strlen(tempStr),&bytesWritten);
   sprintf(tempStr,"   Nodename - %s\n\r",cmdLineParms.nodename);
   rc = DosWrite(log1FileHandle,tempStr,strlen(tempStr),&bytesWritten);

   /* read in the response file */

   strcpy(filename,cmdLineParms.clientFile);

   rc = DosOpen(filename,
                &FileHandle,
                &ActionTaken,
                0L,  /* File Size */
                FILE_NORMAL,
                FILE_OPEN,
                OPEN_ACCESS_READONLY | OPEN_SHARE_DENYNONE,
                NULL ); /* No extended attributes */

   if (rc != 0) {
      sprintf(tempStr,"Error:  Could not open response file %s with rc = %ld\n\r",
         filename,rc);
      rc = DosWrite(log1FileHandle,tempStr,strlen(tempStr),&bytesWritten);
      rc = DosClose(log1FileHandle);
      exit(RC_IOERROR);
   }

   if ((rspFileBuffer = (UCHAR *) malloc(ObjSize)) == NULL) {
      /* memory allocation error */
      exit(RC_UNEXPECTEDERROR);
   }

   strcpy(rspFileBuffer,"");
   rc = DosRead(FileHandle,rspFileBuffer,ObjSize,&bytesRead);

   if (rc != 0) {
      sprintf(tempStr,"Error:  Could not read response file %s with rc = %ld\n\r",
         filename,rc);
      rc = DosWrite(log1FileHandle,tempStr,strlen(tempStr),&bytesWritten);
      rc = DosClose(log1FileHandle);
      free(rspFileBuffer);
      exit(RC_IOERROR);
   }

   rc = DosClose(FileHandle);

   if (rc != 0) {
      sprintf(tempStr,"Error:  Could not close response file %s with rc = %ld\n\r",
         filename,rc);
      rc = DosWrite(log1FileHandle,tempStr,strlen(tempStr),&bytesWritten);
      rc = DosClose(log1FileHandle);
      free(rspFileBuffer);
      exit(RC_IOERROR);
   }

   /* parse each line in the response file */

   charPos = 0;
   while (charPos <= bytesRead) {
      i = 0;
      strcpy(tempStr,"");
      while (rspFileBuffer[charPos] != '\n') {
         if (charPos == bytesRead)
            break;
         tempStr[i++] = rspFileBuffer[charPos++];
      }
      charPos++;
      tempStr[i] = '\0';

      /* If the line is not a comment, get its keyword and value strings */

      if  (isCommentLine(tempStr) == FALSE) {
         splitKeywordValName(tempStr,&keywordStr,&valueStr);

         keywordfound = FALSE;
         if (strcmp(keywordStr,"BUFFER") == 0) {
            strcpy(instParms.bufferVal,valueStr);
            sprintf(tempStr,"   Setting BUFFER to %s\n\r",valueStr);
            rc = DosWrite(log1FileHandle,tempStr,strlen(tempStr),&bytesWritten);
            keywordfound = TRUE;
         } 

         if (strcmp(keywordStr,"TIMEOUT") == 0) {
            strcpy(instParms.timeoutVal,valueStr);
            sprintf(tempStr,"   Setting TIMEOUT to %s\n\r",valueStr);
            rc = DosWrite(log1FileHandle,tempStr,strlen(tempStr),&bytesWritten);
            keywordfound = TRUE;
         } 

         if ((keywordfound == FALSE) && (strlen(keywordStr) != 0)) {
           sprintf(tempStr,"   Warning:  Invalid keyword: %s\n\r",keywordStr);
           rc = DosWrite(log1FileHandle,tempStr,strlen(tempStr),&bytesWritten);
           sprintf(tempStr,"      Processing continues\n\r",keywordStr);
           rc = DosWrite(log1FileHandle,tempStr,strlen(tempStr),&bytesWritten);
         }
      }
   }

   /* Use default values if the user didn't specify any */

   if (strcmp(instParms.bufferVal,"") == 0) {
      strcpy(tempStr,"   Using default value 100 for BUFFER.\n\r");
      rc = DosWrite(log1FileHandle,tempStr,strlen(tempStr),&bytesWritten);
      strcpy(instParms.bufferVal,"100");
   } 
   if (strcmp(instParms.timeoutVal,"") == 0) {
      strcpy(tempStr,"   Using default value 5 for TIMEOUT.\n\r");
      rc = DosWrite(log1FileHandle,tempStr,strlen(tempStr),&bytesWritten);
      strcpy(instParms.timeoutVal,"5");
   } 

   /* write out the ini file */
   strcpy(filename,cmdLineParms.targetDir);
   strcat(filename,"CIDEXMP.INI");

   /* delete the old one first */

   rc = DosDelete(filename);
 
   rc = DosOpen(filename,      /* Name of file to create  */
      &FileHandle,  /* Address of file handle  */
      &ActionTaken,   /* Pointer to action     */
      0,   /* Size of new file     */
      FILE_NORMAL,  /* Attribute of new file   */
      FILE_OPEN | OPEN_ACTION_CREATE_IF_NEW,
      OPEN_ACCESS_WRITEONLY | OPEN_SHARE_DENYNONE,
      NULL);

   if (rc != 0) {
      sprintf(tempStr,"Error:  Could not open INI file %s with rc = %ld\n\r",
         filename,rc);
      rc = DosWrite(log1FileHandle,tempStr,strlen(tempStr),&bytesWritten);
      rc = DosClose(log1FileHandle);
      free(rspFileBuffer);
      exit(RC_IOERROR);
      return;
   }

   /* Write out the INI lines */

   strcpy(lineStr,"*** CID EXAMPLE INI FILE  ***");
   strcat(lineStr,"\n\r");
   rc = DosWrite(FileHandle, lineStr, strlen(lineStr), &bytesWritten);

   strcpy(lineStr,instParms.bufferStr);
   strcat(lineStr," ");
   strcat(lineStr,instParms.bufferVal);
   strcat(lineStr,"\n\r");
   rc = DosWrite(FileHandle, lineStr, strlen(lineStr), &bytesWritten);

   strcpy(lineStr,instParms.timeoutStr);
   strcat(lineStr," ");
   strcat(lineStr,instParms.timeoutVal);
   strcat(lineStr,"\n\r");
   rc = DosWrite(FileHandle, lineStr, strlen(lineStr), &bytesWritten);

   rc = DosClose(FileHandle);

   if (rc != 0) {
      sprintf(tempStr,"Error:  Could not close INI file %s with rc = %ld\n\r",
         filename,rc);
      rc = DosWrite(log1FileHandle,tempStr,strlen(tempStr),&bytesWritten);
      rc = DosClose(log1FileHandle);
      free(rspFileBuffer);
      exit(RC_IOERROR);
      return;
   }

   /* Free dynamically allocated memory and close the log file */

   free(rspFileBuffer);

   DosGetDateTime(&DateTime);
   sprintf(tempStr,"%2.2d-%2.2d-%2.2d %2.2d:%2.2d:%2.2d - Completed installation for node %s.\n\r",
        DateTime.month,DateTime.day,DateTime.year,DateTime.hours,
        DateTime.minutes,DateTime.seconds,cmdLineParms.nodename);
   rc = DosWrite(log1FileHandle,tempStr,strlen(tempStr),&bytesWritten);

   rc = DosClose(log1FileHandle);
   if (rc != 0) {
      printf("Error:  Could not close log file %s with rc = %ld\n",cmdLineParms.log1,rc);
      exit(RC_IOERROR);
   }

   exit(RC_SUCCESS);
}

/**********************************************************/
/* stringcpyFromTo                                           */
/* - Copy a string between the from and to ranges.        */
/**********************************************************/

int stringcpyFromTo(PSZ source, PSZ target, int from, int to)
{
   int i,j,k,len;

   i = j = k = 0;
   strcpy(target,"");
   if (to < from)
     return(-1);
   len = strlen(source);
   while (i < len) {
      if ((i >= from) && (i <= to)) {
         target[j++] = source[i++];
      } else {
         i++;
      } 
   } 
   target[j] = '\0';
   return(0);
}

/**********************************************************/
/* isCommentLine                                          */
/* - Determine if the input line is a comment             */
/**********************************************************/

BOOL isCommentLine(UCHAR *source)
{
   int i = 0;

   /* Consider blank lines comments to ignore them. */

   if ((strlen(source) == 0) |  ((strcmp(source,"\r") == 0) |
        (strcmp(source,"\n") == 0))) {
      return(TRUE);
   } 

   i = 0;
   while ( (source[i] == ' ') && (i <= strlen(source)) ) {
      i++;
   }

   /* If a line begins with a ; or *, it's a comment line */

   if ((source[i] == ';') || (source[i] == '*')) {
      return(TRUE);
   } else {
      return(FALSE);
   } /* endif */
}

/**********************************************************/
/* splitKeywordValName                                    */
/* - Split the input string into keyword and value names  */
/**********************************************************/

int splitKeywordValName(UCHAR *inputStr, UCHAR *keywordStr, UCHAR *valueStr)
{
   PSZ tempStr;
   int chr = '=';
   int i,j,k;

   i = j = k = 0;
   tempStr = strrchr(inputStr,chr);
   if (tempStr == NULL) {
      strcpy(keywordStr,"");
      strcpy(valueStr,"");
      return(0);
   } /* endif */
   j = strlen(inputStr) - strlen(tempStr) - 1;
   for (i=0;i<=j;i++) {
      keywordStr[i] = inputStr[i];
   } /* endfor */
   keywordStr[i] = '\0';
   j = strlen(inputStr);

   i++;  /* skip over the equals sign */
   for (i;i<=j;i++ ) {
      valueStr[k++] = inputStr[i];
   } /* endfor */
   trimBlanks(keywordStr);
   trimBlanks(valueStr);
   return(0);
}

/**********************************************************/
/* trimBlanks                                             */
/* - Remove blanks from the input string                  */
/**********************************************************/

void trimBlanks(CHAR *inputStr)
{
   CHAR tempStr[300];
   int i,j,max;

   i = j = 0;
   strcpy(tempStr,"");
   max = strlen(inputStr);

   while (((inputStr[i] == ' ') |
              ((inputStr[i] == '\r') | (inputStr[i] == '\n')))
              && (i <= max)) {
      i++;
   }
   while ((inputStr[i] != ' ') && (i <= max)) {
      tempStr[j++] = inputStr[i++];
   }
   tempStr[j] ='\0';
   strcpy(inputStr,tempStr);
   return;
}

