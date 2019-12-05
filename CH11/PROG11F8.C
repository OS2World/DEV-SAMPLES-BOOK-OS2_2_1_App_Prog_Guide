/*************************************/
/* Chapter 11.  Use of DosCallNPipe  */
/*************************************/

#define INCL_DOSNMPIPES
#define INCL_DOSFILEMGR
#define INCL_ERRORS
#include <os2.h>

int main (int argc, void *argv[])
{
   #define MAX_NAME_LEN   80
   #define REQ_BUF_SIZE   80
   #define REPLY_BUF_SIZE 80
   UCHAR   PipeName[MAX_NAME_LEN];  /* name of the named pipe */
   UCHAR   Request[REQ_BUF_SIZE];   /* Buffer Client's request*/
   UCHAR   Reply[REPLY_BUF_SIZE];   /* Buffer Server's reply  */
   ULONG   num;
   ULONG   len;
   APIRET  rc;

   strcpy(PipeName, "\\PIPE\\MYPIPE");  /* Name of pipe       */
   strcpy(Request, "How much did I spend at the vet last year?");
   len = strlen(Request) + 1;

   /* This client sends one requests to the server   */

   rc = DosCallNPipe( PipeName,
                 Request,        /* Client's request      */
                 len,            /* len of request        */
                 Reply,          /* where to put response */
                 REPLY_BUF_SIZE, /* max length of response*/
                 &num,           /* actual len of response*/
                 2000            /* timeout in 2 seconds  */
                );
   if (!rc) printf("Response was:  %s\n", Reply);
   else     printf("DosCallNPIpe failed\n");

}

