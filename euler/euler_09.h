#pragma once

#define CLASSNAME Euler_09

#include "base_header.h"

using namespace std;
using namespace Helper;

// -------------------- Program starts here -------------------------
//
// A Pythagorean triplet is a set of three natural numbers, a < b < c, for which,
// a^2 + b^2 = c^2
// For example, 3^2 + 4^2 = 9 + 16 = 25 = 5^2.
// There exists exactly one Pythagorean triplet for which a + b + c = 1000.
// Find the product abc.
//
// Clarify if "natrural numbers" are suppossed to contain zero or not.
// Here it seems to be without zero, otherwise the optimized solution finds 0^2 + 500^2 = 500^2
class CLASSNAME
{
public:
    CLASSNAME()
    {
        cout << "Running " << VERSION_STRING(CLASSNAME) << "..." << endl;
    }

    // There is surely lots of potential for optimizations
    // First, the range of a,b,c can surely be restricted to a smaller range than [0, 1000]
    // Second, we can reduce the innermost loop and instead check after the second loop
    // if sqrt(a^2 + b^2) is an integer -> as shown in the optimized variant below.
    int findMagicTripleProduct()
    {
      for(int a=1; a < 1000; a++) {
        for (int b=a+1; b < 1000; b++) {
          for (int c = b+1; c < 1000; c++) {
            if (std::pow(a,2) + std::pow(b,2) == std::pow(c,2)) {
              std::cout << "Found a triple: " << a << "^2 + " << b << "^2 = " << c << "^2" << std::endl;

              if (a+b+c == 1000)
                return a*b*c;
            }
          }
        }
      }
      return 0;
    }

    // From O(N^3) to O(N^2): 6s to 0.02s
    int findMagicTripleProductOptimized()
    {
      for(int a=1; a < 1000; a++) {
        for (int b=a+1; b < 1000; b++) {
          int squaredSum = std::pow(a,2) + std::pow(b,2);
          int c = std::sqrt(squaredSum);
          if (c*c == squaredSum) {
            std::cout << "## Found a triple: " << a << "^2 + " << b << "^2 = " << c << "^2" << std::endl;

            if (a+b+c == 1000)
              return a*b*c;
          }
        }
      }
      return 0;
    }

};

TEST(CLASSNAME, Test1)
{
    CLASSNAME instance;

    auto result = instance.findMagicTripleProductOptimized();
    std::cout << "Result is " << result << std::endl;
    ASSERT_EQ(result, 31875000);
}

#undef CLASSNAME
