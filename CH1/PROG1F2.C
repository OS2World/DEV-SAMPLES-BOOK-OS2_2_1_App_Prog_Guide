/***************************************************************/
/* Chapter 1.  Program illustrating 32-bit to 16-bit thunking. */
/***************************************************************/

#include <os2.h>
#include <string.h>

USHORT _Far16 _Pascal Dos16Write(SHORT, PVOID, USHORT,
                                 PUSHORT);

int main()
{
   char * _Seg16 string;
   USHORT cb;

   string = "Hello hello!\n";
   Dos16Write(0, string, strlen((char *)string), &cb);
}

