#include <metacalc.sc>

class: fcalc;

parent: calculator;
-- This class is a subclass of the calculator class.
-- It inherits all of the calculator class's methods and data

release order: Multiply, Divide;

# Data
# This class does not contain any new data
data:

methods:

-- Methods

signed long  Multiply(signed long var1, signed long var2);

#  For simplicity, this method does not check for exceeding
#  maxint of the system
-- Method Name:  Multiply
--   This method returns the product of the two input numbers
--

double Divide(signed long var1, signed long var2);

-- Method Name:  Divide
--   This method returns the result of dividing the first
--   number by the second.  It will return 0 if the second
--   number is 0.
