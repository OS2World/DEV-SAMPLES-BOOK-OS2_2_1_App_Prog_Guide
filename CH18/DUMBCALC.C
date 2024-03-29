/*
 * This file was generated by the SOM Compiler.
 * FileName: dumbcalc.c.
 * Generated using:
 *     SOM Precompiler spc: 1.22
 *     SOM Emitter emitc: 1.24
 */

#define dumbcalc_Class_Source
#include "dumbcalc.ih"

/*
 *  Method Name:  Multiply
 *
 */

SOM_Scope signed long   SOMLINK Multiply(dumbcalc *somSelf,
                signed long var1,
                signed long var2)
{
   signed long counter = 0;
   signed long sum = 0;

   /* dumbcalcData *somThis = dumbcalcGetData(somSelf); */
   dumbcalcMethodDebug("dumbcalc","Multiply");

   while (counter < var1) {
      sum = _Add(somSelf, sum, var2);
      counter++;
   }
   return sum;
}
