/*********************************************************/
/* CHAPTER 7.  A program for setting extended attributes */
/* on any file given that the attribute is of type       */
/* EAT_ASCII                                             */
/*********************************************************/

#define INCL_DOS
#define INCL_NOPM
#include <os2.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/***********************/
/* structures          */
/***********************/
typedef struct _FEAlist
{
   ULONG   oNextEntryOffset;         /* New field */
   BYTE       fEA;                   /* Flag byte */
   BYTE       cbName;
   USHORT     cbValue;
   CHAR      *szName;
   CHAR      *aValue;
   struct _FEAlist *next;
} FEA_list;

/***********************/
/* function prototypes */
/***********************/
HFILE openFile(char *filename);
VOID allocMem(PVOID *pvMessage, ULONG ulSize);
void SetEAOnFile(HFILE FileHandle, char *name, char *value);

/***********************/
/* globals             */
/***********************/
FEA_list *FEA_list_begin;

/***********************/
/* defines             */
/***********************/
#define MAX_EAS 500L

/***********************/
/* begin program       */
/***********************/
int main (int argc, char **argv)
{
    HFILE FileHandle;
    char *name;
    char *value;

    if (argc < 4)  {   /* default: current directory */
        printf("usage: %s <filename> <EA name> <EA value> \
           [<EA name> <EA value>] ...\n", *argv);
        return(1);
    } else {
        argc--;  /* decrement for filename open */
        if(FileHandle = openFile(*++argv)) {  /* returns
                           HFILE on success, 0 on failure */
            printf("filename: %s\n",*argv);
            while ((argc-=2) > 0) {
                name = *++argv;
                value= *++argv;
                SetEAOnFile(FileHandle, name, value);
            }
            DosClose(FileHandle);
        } else {
            printf("could not open file %s\n",*argv);
            return (1);
        }
    }
    return 0;
}

void SetEAOnFile(HFILE FileHandle, char *name, char *value)
{
    EAOP2       eaop2;
    APIRET      rc = 0;
    ULONG       ulEASize;
    USHORT    * pEAData;

  /*****************************************************/
  /* the factor 8 in the following ulEASize assignment */
  /* is from the following:                            */
  /*            4 bytes for oNextEntryOffset           */
  /*            1 byte for usFlags                     */
  /*            1 byte for cbName                      */
  /*            2 bytes for cbValue                    */
  /********************************************************/

  /********************************************************/
  /* the ulEASize is big enough for the name, the value   */
  /* the 8 bytes listed above                             */
  /* 4 bytes that go with the attribute value.            */ 
  /********************************************************/

    ulEASize = 8 + strlen(name) + 1 + strlen(value) + 4;
    eaop2.fpFEA2List = malloc(ulEASize);
    eaop2.fpFEA2List->list->oNextEntryOffset = 0;
    eaop2.fpFEA2List->list->cbName = strlen(name);
    eaop2.fpFEA2List->list->cbValue = strlen(value)+4;


  /* set the pointer to a location one byte beyond the end*/
  /* of the 'name' field                                 */

    pEAData = (USHORT *)
                    ((PBYTE)eaop2.fpFEA2List->list->szName +
                    eaop2.fpFEA2List->list->cbName + 1);

  /* now set the data related to the attribute value: the */
  /* type, the size, and valueData                        */

    *pEAData = EAT_ASCII;    /* the EA type is always
                                    ASCII in this example */
    pEAData = (USHORT *)((PBYTE)pEAData + 2);
    *pEAData = strlen(value);
    pEAData = (USHORT *)((PBYTE)pEAData + 2);
    memcpy(pEAData, value, strlen(value));

    strcpy(eaop2.fpFEA2List->list->szName, name);  /* NULL
                                              termination */
    eaop2.fpFEA2List->cbList = ulEASize;

    rc = DosSetFileInfo(FileHandle, FIL_QUERYEASIZE, &eaop2, ulEASize);
    if(rc) {
        printf("unable to set EA on this file. RC=%d\n", rc);
    } else {
        printf("successfully set EA \"%s\"  to ASCII value of: \"%s\"\n",
           name, value);
    }
    return;
}

VOID allocMem (PVOID *ppv, ULONG cb)
{
    BOOL failed;

    failed =(BOOL) DosAllocMem(ppv, cb, fPERM|PAG_COMMIT);
    if (failed) {
        fprintf(stderr,"ERROR: Memory is full\n");
        *ppv = NULL;
        exit(1);
    }
    return;
}

/******************************************/
/* openFile                               */
/* returns file handle on successful open */
/*     or returns 0L on failure           */
/******************************************/

HFILE openFile(char *filename)
{
    ULONG       ulActionTaken;
    APIRET      rc;
    HFILE        hfile;

/***********************************************************/
/* Open the file for Extended Attribute access.  The file  */
/* must be opened for read access with a deny-write        */
/* sharing mode.                                           */
/***********************************************************/

    rc = DosOpen(filename,
                 &hfile,
                 &ulActionTaken,
                 100L,
                 FILE_NORMAL,  /* was READONLY */
                 OPEN_ACTION_FAIL_IF_NEW
                    | OPEN_ACTION_OPEN_IF_EXISTS,
                 OPEN_SHARE_DENYWRITE
                    | OPEN_ACCESS_READWRITE,
                 0L);
    return(rc?0L:hfile); /* reverse the logic of the Dos  */
                         /* API so that a return of true  */
                         /* indicates success             */
}
