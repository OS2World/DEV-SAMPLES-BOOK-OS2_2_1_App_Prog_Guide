#include <stdio.h>
#include <string.h>
#include <os2.h>
#include <lifoq.h>
#include <metacalc.h>

main (argc, argv, envp)
   int argc;
   char *argv[];
   char *envp[];
{
     LIFOQ      *myq;
    calculator  *mycalc;
    signed long  sum;
    PVOID        tbuf;
    int          rc;

    listsNewClass(0,0);
    myq = LIFOQNew();
    SOM_Test(myq != NULL);

    get_usListItemSize(myq) = sizeof(PVOID);
    /* The list is now a list of pointers */

    /* Create two calculators and put them in the list */
    mycalc = calculatorNew();
    SOM_Test(mycalc != NULL);

    rc = _AddItem(myq, (PVOID) &mycalc);
    SOM_TestC(rc);

    /* That was one, now for the next */
    mycalc = calculatorNew();
    SOM_Test(mycalc != NULL);

    rc = _AddItem(myq, (PVOID) &mycalc);
    SOM_TestC(rc);

    /* Now use the calculators, first getting them off the list */
    tbuf = _GetItem(myq);
    SOM_Test(tbuf != NULL);
    mycalc = *((calculator **) tbuf);

    sum = _Add(mycalc, 5, 10);
    printf("The sum from the first calculator is:  %ld\n", sum);
    _somFree(mycalc);

    tbuf = _GetItem(myq);
    SOM_Test(tbuf != NULL);
    mycalc = *((calculator **) tbuf);

    sum = _Add(mycalc, 1, 18);
    printf("The sum from the first calculator is:  %ld\n", sum);
    _somFree(mycalc);

    _somFree(myq);
}
