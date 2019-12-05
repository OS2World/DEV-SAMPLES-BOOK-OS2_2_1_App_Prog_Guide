/*
 *  CLIENT3.C -- String class client program
 */

#include <stdlib.h>
#include <stdio.h>
#include "strng.h"

extern SOMClassMgr *SOMClassMgrObject;

/*
 * Generic object state display routine.
 */
void dispString(SOMAny *obj)
{
   int     ln;
   char   *pstr, *s = "";

   ln = _getStringLen(obj);      // Get the string's length
   pstr = _getString(obj);       // Get the string's value
   if (pstr != NULL) {
       s = pstr;
   }
   somPrintf("\nThe string is '%s'\n", s);
   somPrintf("The string length is %d characters\n\n", ln);
   SOMFree(pstr);             // Free the intermediate buffer
}

/*
 *  Instantiate a new object from a existing one.
 */

SOMAny * objectFromObject(SOMAny * obj)
{
   SOMAny *newobj;
   SOMClass *classObj;

   classObj = _somGetClass(obj);    // Get the class object

   newobj   = _somNew(classObj);    // Create a new instance
                                    // of the class
   return(newobj);

}

/*
 *  Instantiate a new object from a class name.
 */

SOMAny * objectFromClassName(char * className)
{
   SOMAny *newobj;
   SOMClass *classObj;
   somId    classId;

   // Convert classname to Id
   classId  = SOM_IdFromString(className);

   //Find the class object
   classObj = _somFindClass(SOMClassMgrObject,
                            classId,
                            0, 0);

   // Create a new instance of the class
   newobj   = _somNew(classObj);
   return(newobj);

}

/*
 * MAINLINE
 */

main (long argc, char **argv)
{
   SOMAny *stringObj1, *stringObj2, *stringObj3;

   // Instantiate the class object
   StringNewClass(0, 0);

   // Instantiate a string object
   stringObj1 = StringNew();

   // Set the value of the object
   _setString(stringObj1, "Original object");

   // Display the object
   dispString(stringObj1);

   // Make a new object
   stringObj2 = objectFromObject(stringObj1);

     // Set the value of the object
   _setString(stringObj2,
               "This is an object from an object");

     // Display the new object
   dispString(stringObj2);

     // Display the original object
   dispString(stringObj1);

   // Make a new object
   stringObj3 = objectFromClassName("String");

    // Set the value of the object
   _setString(stringObj3,
              "This is an object from a class name");

   // Display the new object
   dispString(stringObj3);

   // Display the original object
   dispString(stringObj1);

   exit(0);
}
