#include <somobj.sc>

class: calculator,
   function prefix = calcpre,
   class prefix =    metacalc;

-- The class prefix option is required when the metaclass
--    is included in the same csc file.
-- The function prefix option is used here just to
--    illustrate it.

parent: SOMObject;
-- Notice that the parent and the metaclass are different!

release order: Add, Subtract, Register1,
               Register2, NumCalcs, NumAddCalls;
-- Notice that the overridden method, somNew, is not
-- listed in the release order!


         -- Data
data:

     signed long    Register1,  private;
--                    A general-use register.
     signed long    Register2,  private;
--                    A general-use register.
     short          NumCalcs, class, public;
--                    A running total.
     short          NumAddCalls, class, public;
--                    Also a running total.



-- Methods
methods:

signed long  Add(signed long var1,
                 signed long var2);

         #  Put comments here that describe the Add method
-- Method Name:  Add
--   This method returns the sum of the two input
--   numbers.
--

signed long  Subtract(signed long var1,
                      signed long var2);

-- Method Name:  Subtract
//   This method returns the value of
//   var1 minus var2
//

override somNew, class;
-- Override it to increment NumCalcs

override somInit, class;
-- Override it to initialize data variables
