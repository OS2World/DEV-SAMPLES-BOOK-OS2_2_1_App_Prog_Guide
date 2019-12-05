/******************************/
/* Chapter 5. DosSearchPath   */
/******************************/

#include <stdio.h>

#define INCL_DOSMISC
#include <os2.h>

VOID SearchPath(CHAR * file, CHAR * path)
{
   APIRET rc;
   CHAR buffer[200];

   rc = DosSearchPath(SEARCH_ENVIRONMENT |
                      SEARCH_IGNORENETERRS,
                      path, file, buffer, sizeof(buffer));
   if (!rc) {
      printf("Your file was found within your %s!\n", path);
   }
}

INT main( INT argc, CHAR *argv[], CHAR *envp[] )
{

   if (argc < 2) {
      printf("Please pass a file name\n");
      return(1L);
   }

   SearchPath(argv[1], "DPATH");
   SearchPath(argv[1], "PATH");
   SearchPath(argv[1], "HELP");

   return(0L);
}

