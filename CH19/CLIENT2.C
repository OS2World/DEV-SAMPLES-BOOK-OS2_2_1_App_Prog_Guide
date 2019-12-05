/*
 *  CLIENT2.C -- String class client program
 *               using debugging information
 */

#include <stdlib.h>
#include <stdio.h>
#include "strng.h"

extern SOM_TraceLevel;
extern SOM_WarnLevel;

/* All replacement SOM routines must use system linkage */
#pragma linkage(myOutCharRoutine, system)

/*
 * Replacement for SOMOutCharRoutine.
 * Writes SOM output to a log file.
 */
int myOutCharRoutine(char c)
{
   static FILE *log = NULL;

   if (log == NULL) {
      log = fopen("CLIENT2.OUT", "w");
   }

   putc(c, log);
   return(0);
}

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
   int     dumpSelf = 0;
   int     ln;
   char   *pstr, *penv;
   SOMAny *stringObj;

   // Set the value of the SOM_TraceLevel global variable
   penv = getenv("SOM_TRACELEVEL");
   if (penv != NULL) {
      SOM_TraceLevel = atoi(penv);
   } else {
      SOM_TraceLevel = 0;
   }

   // Set the value of the SOM_WarnLevel global variable
   penv = getenv("SOM_WARNLEVEL");
   if (penv != NULL) {
      SOM_WarnLevel = atoi(penv);
   } else {
      SOM_WarnLevel = 0;
   }

   // If the SOM_LOG_OUTPUT environment variable is set,
   // then replace the SOMOutCharRoutine with one that sends
   // output to a file
   penv = getenv("SOM_LOG_OUTPUT");
   if (penv != NULL) {
      SOMOutCharRoutine = myOutCharRoutine;
   }

   // If the SOM_DUMP_SELF environment variable is set,
   // then set a flag
   penv = getenv("SOM_DUMP_SELF");
   if (penv != NULL) {
      dumpSelf = 1;
   }

   StringNewClass(0, 0);        // Instantiate the string
                                // class object, if it does
                                // not already exist

   SOM_WarnMsg("Instantiating object");

   stringObj = StringNew();     // Instantiate a string
                                // object


   SOM_WarnMsg("Setting string");

   _setString(stringObj,        // Set the value of the new
           "This is a string"); // object

   ln = _getStringLen(stringObj);  // Get the string's length
   pstr = _getString(stringObj);   // Get the string's value
   dispString(pstr, ln);           // Display the string's
                                   //    value
   SOMFree(pstr);                  // Free the intermediate
                                   //    buffer

   SOM_WarnMsg("Clearing string");

   _clearString(stringObj);       // Clear the string
   ln = _getStringLen(stringObj); // Get the string's length

       // Two different ways to issue a generic warning
       // message if the string length is 0
   SOM_TestC((ln > 0));
   SOM_Assert((ln > 0), 1000+SOM_Warn);

   pstr = _getString(stringObj);  // Get the string's value
   dispString(pstr, ln);          // Display the string's
                                  //    value

       // Yet another way, unless SOM_Error has been replaced
   if (ln == 0) {
      SOM_Error(2000+SOM_Ignore);
      SOM_Error(3000+SOM_Warn);
      /* SOM_Error(4000+SOM_Fatal); */
   }

   SOM_WarnMsg("Setting string");

   _setString(stringObj,          // Set the value of the
     "Here is a new string");     //    object

   ln = _getStringLen(stringObj); // Get the string's length
   pstr = _getString(stringObj);  // Get the string's value
   dispString(pstr, ln);          // Display the string's
                                  //    value
   SOMFree(pstr);                 // Free the intermediate
                                   //    buffer

   SOM_WarnMsg("Freeing object");

      // Conditional dump object information.  dumpSelf was
      // set above based on an environment variable
   if (dumpSelf) {
      _somDumpSelf(stringObj, 1);  // Dump all object info
                                   // include instance data
      somPrintf("\n");
      _somPrintSelf(stringObj);    // Only dump its class and
                                   // address
   }

   _somFree(stringObj);           // Free the String object
   exit(0);

}
