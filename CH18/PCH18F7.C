/*************************************************/
/* Chapter 18. Instantiating a calculator object */
/*************************************************/

#include <calc.h>
main (void)
{
   /* Declare "mycalc" to be a pointer to a calculator
    * object.  Whenever you want to use a calculator
    * object, use "mycalc", NOT "*mycalc"
    */
   calculator  *mycalc;

   // Be sure the class object exists
   calculatorNewClass(0,0);

   // Invoke the somNew method on the class object
   mycalc = _somNew(_calculator);

}
