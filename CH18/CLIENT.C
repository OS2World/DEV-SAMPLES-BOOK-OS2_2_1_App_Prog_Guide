/* This is the listing of client.c */
#include <stdio.h>
#include <string.h>
#include "metacalc.h"

main(argc, argv, envp)
   int argc;
   char *argv[];
   char *envp[];
{
   signed long sum;
   calculator *mycalc;
   calculator *mycalc2;

   mycalc = calculatorNew();
   mycalc2 = calculatorNew();
   sum = _Add(mycalc, 5, 10);

   printf("The number of calculators is: %d\n",
            get_NumCalcs(_calculator));
   printf("The number of times add was called is: %d\n",
            get_NumAddCalls(_calculator));
}
