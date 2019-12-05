#include <dumbcalc.h>

main(argc, argv, envp)
   int argc;
   char *argv[];
   char *envp[];
{
   signed long sum;
   signed long num1 = 4;
   signed long num2 = 6;
   calculator  *calc1;
   fcalc       *calc2;
   dumbcalc    *calc3;

      /* Create the calculator objects  */

   calc1 = calculatorNew();
   calc2 = fcalcNew();
   calc3 = dumbcalcNew();

      /* The following are all valid method invocations */
   sum = _Add(calc1, num1, num2);
   sum = calculator_Add(calc2, num1, num2);
   sum = _Add(calc3, num1, num2);
   sum = _Multiply(calc2, num1, num2);
   sum = fcalc_Multiply(calc3, num1, num2);
   sum = _Multiply(calc3, num1, num2);

   _somFree(calc1);
   _somFree(calc2);
   _somFree(calc3);
}
