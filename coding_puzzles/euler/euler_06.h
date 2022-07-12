#pragma once

#define CLASSNAME Euler_06

#include "base_header.h"

using namespace std;
using namespace Helper;

// -------------------- Program starts here -------------------------
//
// The sum of the squares of the first ten natural numbers is, (1²+2²+...+10²) = 385
// The square of the sum of the first ten natural numbers is, (1+2+...10)² = 3025
// Hence the difference between the sum of the squares of the first ten natural numbers and the square of the sum is 3025 - 385 = 2640.
// Find the difference between the sum of the squares of the first one hundred natural numbers and the square of the sum.

class CLASSNAME
{
public:
    CLASSNAME()
    {
        cout << "Running " << VERSION_STRING(CLASSNAME) << "..." << endl;
    }

    long long getDifference(int highestNum)
    {
      long long sum = 0;
      long long sumOfSquares = 0;
      for(int i=1; i <= highestNum; i++) {
        sum += i;
        sumOfSquares += (i*i);
      }

      return (sum*sum) - sumOfSquares;
    }

};

TEST(CLASSNAME, Test1)
{    
    CLASSNAME instance;

    int highest = 10;
    auto diff = instance.getDifference(highest);
    std::cout << "The difference up to  " << highest << " is: " << diff << std::endl;
    ASSERT_EQ(diff, 2640);


    highest = 100;
    diff = instance.getDifference(highest);
    std::cout << "The difference up to  " << highest << " is: " << diff << std::endl;
    ASSERT_EQ(diff, 25164150);
}

#undef CLASSNAME
