
#include <somobj.sc>

class: calculator;

## This is where to put comments that describe
## the class
-- This class is for a calculator that can add
-- and subtract

parent: SOMObject;
-- This is a comment about the parent section

release order: Add, Subtract, Register1,
               Register2;

passthru:  C.ih, before;
   #include <stdio.h>
endpassthru;

passthru:  C.h, after;
   #define ERROR_OVERFLOW
   #define ERROR_UNDERFLOW
endpassthru;


-- Data
data:

     signed long    Register1,  private;
--                    A general-use register.
     signed long    Register2,  private;
--                    A general-use register.


methods:

-- Methods

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
