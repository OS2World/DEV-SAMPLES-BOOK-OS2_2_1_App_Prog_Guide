/*
 * This file was generated by the SOM Compiler.
 * FileName: lifoq.c.
 * Generated using:
 *     SOM Precompiler spc: 1.22
 *     SOM Emitter emitc: 1.24
 */

#define LIFOQ_Class_Source
#include "lifoq.ih"

SOM_Scope INT   SOMLINK AddItem(LIFOQ *somSelf,
       PVOID *pItem)
{
    INT rc;

    /* LIFOQData *somThis = LIFOQGetData(somSelf); */
     LIFOQMethodDebug("LIFOQ","AddItem");

    rc = _AddPos(somSelf, pItem, 'H');
    return rc;
}
