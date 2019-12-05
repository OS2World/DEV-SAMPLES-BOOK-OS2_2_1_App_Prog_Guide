/*******************************************/
/* Chapter 11:  HIWORLD.C                  */
/*******************************************/

#include <os2.h>
#include <stdio.h>

main(argc, argv, envp)
   int argc;
   char *argv[];
   char *envp[];
{
   char buf1[100];
   scanf("%[^\n]", buf1);
   printf("%s\n", buf1);

}

