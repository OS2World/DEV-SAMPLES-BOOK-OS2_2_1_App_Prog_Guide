#include <somobj.sc>

class: lists;

parent:  SOMObject;

release order:  pListHead, pListTail,
    usListItemSize, AddItem, GetItem, AddPos;

passthru: C.ih, before;
   #include <string.h>
   #include <os2.h>

   typedef struct ListItem {
                struct ListItem  *pNext;
                struct ListItem  *pPrev;
                UCHAR            cData;
           } ListItem, *pListItem;
endpassthru;

passthru: C.h, after;
   #define MEMORY_ERROR    1
   #define LIST_IS_EMPTY   2
   #define LIST_NOT_EMPTY  3
endpassthru;

data:
  pListItem    pListHead, private;
  pListItem    pListTail, private;
  USHORT       usListItemSize, public;
  BOOL         bListEmptyFlag, public;

methods:
     INT     AddItem(PVOID *pItem);
     --                  Adds an item to the list

     PVOID   GetItem();
     --                  Removes the current item from
     --                  the list and returns it

     INT     AddPos(PVOID *pItem, UCHAR pos);
     --                  Add to head or tail of list

     override somInit;

     override somUninit;
