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

   mycalc = calculatorNew(); // Instantiates a calculator

}
