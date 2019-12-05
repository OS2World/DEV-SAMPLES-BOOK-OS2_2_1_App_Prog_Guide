/*
 *  CLIENT4.C -- Class Hierarchy Methods client program
 */

#include <stdlib.h>
#include <stdio.h>
#include "metacalc.h"
#include "fanccalc.h"
#include "dumbcalc.h"

extern SOMClassMgr *SOMClassMgrObject;

/* All replacement SOM routines must use system linkage */
#pragma linkage(myOutCharRoutine, system)

/*
 * Replacement for SOMOutCharRoutine.
 * Writes SOM output to stdout
 */
int myOutCharRoutine(char c)
{

   printf("%c", c);
   return(0);
}

/*
 *  Display the name of an existing object's parent class
 */

void dispParentClass(SOMAny * obj)
{
   // One way to get the name of an object's parent class
   // using class hierarchy methods is:
   // 1. Create an instance of the object's parent class
   //    To do this, get the class object for the object's
   //        parent class and invoke somNew on it.
   // 2. Get the class name from the new instance
   // 3. Destroy the instance created in step 1.

   SOMClass *objClass;
   SOMAny   *parentObj;
   SOMClass *parentClassObj;
   char     *parentClassName;
   char     *objClassName;

   objClass = _somGetClass(obj);
   parentClassObj = _somGetParent(objClass);      // Step 1
   parentObj =      _somNew(parentClassObj);

   parentClassName = _somGetClassName(parentObj); // Step 2

   objClassName = _somGetClassName(obj);
   printf("The %s class's parent is the %s class\n",
            objClassName,  parentClassName);

   _somFree(parentObj);                           // Step 3
}


/*
 * MAINLINE
 */

main (long argc, char **argv)
{
   calculator *calc1;    // An object of the calc class
   fcalc      *calc2;    // An object of the fcalc class
   dumbcalc   *calc3;    // An object of the dumbcalc class
   SOMAny     *anyObj;   // An object of any class

   SOMOutCharRoutine = myOutCharRoutine;
   // Instantiate three calculator objects
   calculatorNewClass(0, 0);
   fcalcNewClass(0, 0);
   dumbcalcNewClass(0, 0);

   // Display the addresses of the SOM runtime class objects
   printf("The four objects created by the SOM runtime are:\n");
   printf("     1. The SOMObject class object: \n        ");
   _somPrintSelf(_SOMObject);
   printf("\n   2. The SOMClass class object: \n        ");
   _somPrintSelf(_SOMClass);
   printf("\n   3. The SOMClassMgr class object: \n        ");
   _somPrintSelf(_SOMClassMgr);
   printf("\n   4. The SOMClassMgr object: \n        ");
   _somPrintSelf(SOMClassMgrObject);

   // Display information about the calculator, fcalc,
   // and dumbcalc class objects
   printf("\n\n");
   printf("The three calculator-related class objects are:\n\n");
   printf("   5. For the \"calculator\" class:  \n        ");
   _somPrintSelf(_calculator);
   printf("\n   6. For the \"fcalc\" class:  \n        ");
   _somPrintSelf(_fcalc);
   printf("\n   7. For the \"dumbcalc\" class:  \n        ");
   _somPrintSelf(_dumbcalc);

   printf("\n\n\nThey are descended from the following classes:\n\n");
   printf("   8. For the \"calculator\" class:  \n         ");
   dispParentClass(_calculator);
   printf("\n   9. For the \"fcalc\" class:     \n         ");
   dispParentClass(_fcalc);
   printf("\n   10. For the \"dumbcalc\" class:  \n         ");
   dispParentClass(_dumbcalc);

   // Now create three calculators, one for each class
   calc1 = calculatorNew();
   calc2 = fcalcNew();
   calc3 = dumbcalcNew();

   // Display information about them
   printf("\n\nThe three calculator objects are:\n\n");
   printf("calc1:    ");
   _somPrintSelf(calc1);
   printf("          ");
   dispParentClass(calc1);
   printf("\ncalc2:  ");
   _somPrintSelf(calc2);
   printf("          ");
   dispParentClass(calc2);
   printf("\ncalc3:  ");
   _somPrintSelf(calc3);
   printf("          ");
   dispParentClass(calc3);

   // Determine the hierarchy relationships between the
   // three calculator objects, calc1, calc2, and calc3,
   // and the three calculator classes, calculator,
   // fanccalc, and dumbcalc

   printf("\n\nResults of somIsA, somIsInstanceOf, and somDescendedFrom calls:\n\n");
   printf("calc1 and the calculator class:\n");
   printf("     calc1  somIsA   \"calculator\" class?                %s\n",
                _somIsA(calc1, _calculator) ? "Yes" : "No");
   printf("     calc1  somIsInstanceOf   \"calculator\"  class?      %s\n",
                _somIsInstanceOf(calc1, _calculator) ? "Yes" : "No");
   printf("     calc1  somDescendedFrom  \"calculator\"  class?      %s\n\n",
                _somDescendedFrom(_calculator, _calculator) ? "Yes" : "No");

   printf("calc1 and the fcalc class:\n");
   printf("     calc1  somIsA   \"fcalc\" class?                     %s\n",
                _somIsA(calc1, _fcalc) ? "Yes" : "No");
   printf("     calc1  somIsInstanceOf   \"fcalc\" class?            %s\n",
                _somIsInstanceOf(calc1, _fcalc) ? "Yes" : "No");
   printf("     calc1  somDescendedFrom  \"fcalc\" class?            %s\n\n",
                _somDescendedFrom(_calculator, _fcalc) ? "Yes" : "No");

   printf("calc1 and the dumbcalc class:\n");
   printf("     calc1  somIsA   \"dumbcalc\" class?                  %s\n",
                _somIsA(calc1, _dumbcalc) ? "Yes" : "No");
   printf("     calc1  somIsInstanceOf   \"dumbcalc\" class?         %s\n",
                _somIsInstanceOf(calc1, _dumbcalc) ? "Yes" : "No");
   printf("     calc1  somDescendedFrom  \"dumbcalc\" class?         %s\n\n",
                _somDescendedFrom(_calculator, _dumbcalc) ? "Yes" : "No");

   printf("calc2 and the calculator class:\n");
   printf("     calc2  somIsA   \"calculator\" class?                %s\n",
                _somIsA(calc2, _calculator) ? "Yes" : "No");
   printf("     calc2  somIsInstanceOf   \"calculator\"     class?   %s\n",
                _somIsInstanceOf(calc2, _calculator) ? "Yes" : "No");
   printf("     calc2  somDescendedFrom  \"calculator\"     class?   %s\n\n",
                _somDescendedFrom(_fcalc, _calculator) ? "Yes" : "No");

   printf("calc2 and the fcalc class:\n");
   printf("     calc2  somIsA   \"fcalc\" class?                     %s\n",
                _somIsA(calc2, _fcalc) ? "Yes" : "No");
   printf("     calc2  somIsInstanceOf   \"fcalc\" class?            %s\n",
                _somIsInstanceOf(calc2, _fcalc) ? "Yes" : "No");
   printf("     calc2  somDescendedFrom  \"fcalc\" class?            %s\n\n",
                _somDescendedFrom(_fcalc, _fcalc) ? "Yes" : "No");

   printf("calc2 and the dumbcalc class:\n");
   printf("     calc2  somIsA   \"dumbcalc\" class?                  %s\n",
                _somIsA(calc2, _dumbcalc) ? "Yes" : "No");
   printf("     calc2  somIsInstanceOf   \"dumbcalc\" class?         %s\n",
                _somIsInstanceOf(calc2, _dumbcalc) ? "Yes" : "No");
   printf("     calc2  somDescendedFrom  \"dumbcalc\" class?         %s\n\n",
                _somDescendedFrom(_fcalc, _dumbcalc) ? "Yes" : "No");

   printf("calc3 and the calculator class:\n");
   printf("     calc3  somIsA   \"calculator\" class?                %s\n",
                _somIsA(calc3, _calculator) ? "Yes" : "No");
   printf("     calc3  somIsInstanceOf   \"calculator\"     class?   %s\n",
                _somIsInstanceOf(calc3, _calculator) ? "Yes" : "No");
   printf("     calc3  somDescendedFrom  \"calculator\"     class?   %s\n\n",
                _somDescendedFrom(_dumbcalc, _calculator) ? "Yes" : "No");

   printf("calc3 and the fcalc class:\n");
   printf("     calc3  somIsA   \"fcalc\" class?                     %s\n",
                _somIsA(calc3, _fcalc) ? "Yes" : "No");
   printf("     calc3  somIsInstanceOf   \"fcalc\" class?            %s\n",
                _somIsInstanceOf(calc3, _fcalc) ? "Yes" : "No");
   printf("     calc3  somDescendedFrom  \"fcalc\" class?            %s\n\n",
                _somDescendedFrom(_dumbcalc, _fcalc) ? "Yes" : "No");

   printf("calc3 and the dumbcalc class:\n");
   printf("     calc3  somIsA   \"dumbcalc\" class?                  %s\n",
                _somIsA(calc3, _dumbcalc) ? "Yes" : "No");
   printf("     calc3  somIsInstanceOf   \"dumbcalc\" class?         %s\n",
                _somIsInstanceOf(calc3, _dumbcalc) ? "Yes" : "No");
   printf("     calc3  somDescendedFrom  \"dumbcalc\" class?         %s\n\n",
                _somDescendedFrom(_dumbcalc, _dumbcalc) ? "Yes" : "No");

   // Destroy the calculator objects
   _somFree(calc1);
   _somFree(calc2);
   _somFree(calc3);

   exit(0);
}
