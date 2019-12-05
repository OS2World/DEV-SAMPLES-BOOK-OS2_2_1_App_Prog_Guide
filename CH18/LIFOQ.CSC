#include <lists.sc>

class: LIFOQ;

parent:  lists;

release order:  AddItem;

passthru: C.ih, before;
   #include <os2.h>
endpassthru;

passthru: C.h, after;
endpassthru;

data:

methods:

override AddItem;
