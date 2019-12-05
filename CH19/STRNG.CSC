#
# STRNG.CSC -- OIDL file for the string class
#

#include <somobj.sc>

class:   String,
         file stem = strng;
parent:  SOMObject;

passthru: C.ih, before;
   #include <string.h>
endpassthru;

passthru: C.h, after;
   #define INVALID_PARAMETER  1
   #define MEMORY_ERROR       2
endpassthru;

data:
         int str_len;
         -- The string's length

         char * str;
         -- Pointer to the string

methods:
         int setString(char * ps);
         -- Set the string

         char * getString();
         -- Return the string value

         void clearString();
         -- Clear the string

         int getStringLen();
         -- Return the length of the string

         override somInit;
         -- Initialize the object

         override somUninit;
         -- Uninitialize the object

         override somDumpSelfInt;
         -- Dumps object instance data
