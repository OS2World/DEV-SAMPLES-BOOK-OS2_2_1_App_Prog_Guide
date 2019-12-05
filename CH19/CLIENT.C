/*
 *  CLIENT1.C -- String class client program
 */

#include <stdlib.h>
#include <stdio.h>
#include "strng.h"

/*
 * Generic object state display routine.
 */
void dispString(char *s, int l)
{
   char *sp = "";

   if (s != NULL) {
      sp = s;
   }
   somPrintf("\nThe string is '%s'\n", sp);
   somPrintf("The string length is %d characters\n\n", l);
}

/*
 * MAINLINE
 */
main (long argc, char **argv)
{
   int     ln;
   char   *pstr;
   SOMAny *stringObj;

   StringNewClass(0, 0);        // Instantiate the string
                                // class object, if it does
                                // not already exist

   stringObj = StringNew();     // Instantiate a string
                                // object

   _setString(stringObj,        // Set the value of the new
           "This is a string"); // object

   ln = _getStringLen(stringObj);  // Get the string's length
   pstr = _getString(stringObj);   // Get the string's value
   dispString(pstr, ln);           // Display the string's
                                   //    value
   SOMFree(pstr);                  // Free the intermediate
                                   //    buffer

   _clearString(stringObj);       // Clear the string
   ln = _getStringLen(stringObj); // Get the string's length
   pstr = _getString(stringObj);  // Get the string's value
   dispString(pstr, ln);          // Display the string's
                                  //    value

   _setString(stringObj,          // Set the value of the
     "Here is a new string");     //    object

   ln = _getStringLen(stringObj); // Get the string's length
   pstr = _getString(stringObj);  // Get the string's value
   dispString(pstr, ln);          // Display the string's
                                  //    value
   SOMFree(pstr);                 // Free the intermediate
                                   //    buffer

   _somFree(stringObj);           // Free the String object

   exit(0);

}
