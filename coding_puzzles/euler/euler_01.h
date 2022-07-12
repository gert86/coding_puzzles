#pragma once

#define CLASSNAME Euler_01

#include "base_header.h"

using namespace std;
using namespace Helper;

// -------------------- Program starts here -------------------------
//
// If we list all the natural numbers below 10 that are multiples of 3 or 5, we get 3, 5, 6 and 9. The sum of these multiples is 23.
// Find the sum of all the multiples of 3 or 5 below 1000.

class CLASSNAME
{
public:
    CLASSNAME()
    {
        cout << "Running " << VERSION_STRING(CLASSNAME) << "..." << endl;
    }

    int sumOfDividablesBy3Or5(int num)
    {
      int sumOfDividables = 0;
      for(int i=0; i < num; i++) {
        if ((i % 3 == 0) || (i % 5 == 0) ) {
          sumOfDividables += i;
        }
      }

      return sumOfDividables;
    }

};

TEST(CLASSNAME, Test1)
{    
    CLASSNAME instance;

    auto sum = instance.sumOfDividablesBy3Or5(1000);
    std::cout << "Found " << sum << " numbers" << std::endl;
    ASSERT_EQ(sum, 233168);
}

#undef CLASSNAME
