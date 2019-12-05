#include <lists.sc>

class: FIFOQ;

parent:  lists;

release order:  pListHead, pListTail,
    usListItemSize, AddItem, GetItem;

passthru: C.ih, before;
   #include <os2.h>
endpassthru;

passthru: C.h, after;
endpassthru;

data:

methods:

override AddItem;
