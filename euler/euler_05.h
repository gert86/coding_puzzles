#pragma once

#define CLASSNAME Euler_05

#include "base_header.h"

using namespace std;
using namespace Helper;

// -------------------- Program starts here -------------------------
//
// 2520 is the smallest number that can be divided by each of the numbers from 1 to 10 without any remainder.
// What is the smallest positive number that is evenly divisible by all of the numbers from 1 to 20?

class CLASSNAME
{
public:
    CLASSNAME()
    {
        cout << "Running " << VERSION_STRING(CLASSNAME) << "..." << endl;
    }

    bool isDivisibleUpTo(long num, int divisableUpTo)
    {
      if (divisableUpTo <= 1)
        return true;

      for (int i=2; i <=divisableUpTo; i++) {
        if (num % i != 0)
          return false;
      }
      return true;
    }
};

TEST(CLASSNAME, Test1)
{
    CLASSNAME instance;

    // divisible up to 10
    int divUpTo = 10;
    long solution = -1;
    for (long i=divUpTo; i < std::numeric_limits<long>::max(); i++) {
      if (instance.isDivisibleUpTo(i, divUpTo)) {
        std::cout << "Found first number that is divisable up to " << divUpTo << " to be: " << i << std::endl;
        solution = i;
        break;
      }
    }
    ASSERT_EQ(solution, 2520);

    // divisible up to 20
    divUpTo = 20;
    solution = -1;
    for (long i=divUpTo; i < std::numeric_limits<long>::max(); i++) {
      if (instance.isDivisibleUpTo(i, divUpTo)) {
        std::cout << "Found first number that is divisable up to " << divUpTo << " to be: " << i << std::endl;
        solution = i;
        break;
      }
    }
    ASSERT_EQ(solution, 232792560);
}

#undef CLASSNAME
