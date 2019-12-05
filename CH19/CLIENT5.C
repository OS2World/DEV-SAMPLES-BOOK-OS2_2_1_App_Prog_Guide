/*
 *  CLIENT5.C -- String class client program
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
   int     rc;
   int     ln;
   char   *pstr;
   SOMAny *stringObj;

   StringNewClass(0,0);      // Instantiate the class object
   stringObj = StringNew();  // Instantiate a string object

         // Set the value of the object - invoke _setString
   rc   = _somDispatchL(stringObj,
                SOM_IdFromString("setString"),
                NULL,
                "This is a string");

         // Get the string's value - invoke _getString
   pstr = _somDispatchA(stringObj,
                SOM_IdFromString("getString"),
                NULL);

         // Get the string's length - invoke _getStringLen
   ln   = _somDispatchL(stringObj,
                SOM_IdFromString("getStringLen"),
                NULL);

   dispString(pstr, ln);      // Display the string's data
   SOMFree(pstr);             // Free the intermediate buffer


         // Clear the string - invoke _clearString
   _somDispatchV(stringObj,
                 SOM_IdFromString("clearString"),
                 NULL);

         // Get the string's value - invoke _getString
   pstr = _somDispatchA(stringObj,
                SOM_IdFromString("getString"),
                NULL);

         // Get the string's length - invoke _getStringLen
   ln   = _somDispatchL(stringObj,
                SOM_IdFromString("getStringLen"),
                NULL);

   dispString(pstr, ln);       // Display the string's data

         // Set the string's value - invoke _setString
   rc   = _somDispatchL(stringObj,
                    SOM_IdFromString("setString"),
                    NULL,
                    "Here is a new string");

         // Get the string's value - invoke _getString
   pstr = _somDispatchA(stringObj,
                SOM_IdFromString("getString"),
                NULL);

         // Get the string's length - invoke _getStringLen
   ln   = _somDispatchL(stringObj,
                SOM_IdFromString("getStringLen"),
                NULL);

   dispString(pstr, ln);    // Display the string's data
   SOMFree(pstr);           // Free the intermediate buffer

   _somFree(stringObj);     // Free the String object
   exit(0);
}
