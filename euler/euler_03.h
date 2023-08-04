#pragma once

#define CLASSNAME Euler_03

#include "base_header.h"

using namespace std;
using namespace Helper;

// -------------------- Program starts here -------------------------
//
// The prime factors of 13195 are 5, 7, 13 and 29.
// What is the largest prime factor of the number 600851475143 ?

class CLASSNAME
{
public:
    CLASSNAME()
    {
        cout << "Running " << VERSION_STRING(CLASSNAME) << "..." << endl;
    }

    long long largestPrimeFactor(long long num)
    {
      long long n = num;
      long long largestFactor = -1;

      // This was my pathetic try on the problem...
      /*
      for(int i = 1; i < num-1; i ++) {
        if (n % i == 0) {
          largestFactor = i;
        }
      }*/


      // Thats what I found on the internet and what succeeded...
      //
      // Print the number of 2s that divide n      
      while (n % 2 == 0) {
          largestFactor = 2;
          n >>= 1; // equivalent to n /= 2
      }

      // n must be odd at this point
       while (n % 3 == 0) {
          largestFactor = 3;
          n=n/3;
      }

      // now we have to iterate only for integers
      // who does not have prime factor 2 and 3
      for (int i = 5; i <= sqrt(n); i += 6) {
          while (n % i == 0) {
              largestFactor = i;
              n = n / i;
          }
          while (n % (i+2) == 0) {
              largestFactor = i+2;
              n = n / (i+2);
          }
      }

      // This condition is to handle the case
      // when n is a prime number greater than 4
      if (n > 4)
          largestFactor = n;

      return largestFactor;
    }

};

TEST(CLASSNAME, Test1)
{    
    CLASSNAME instance;

    long long num = 13195;  // good verification: if you use 13195*2*2*2 instead, the result must remain equal
    auto result = instance.largestPrimeFactor(num);
    std::cout << "Largest primefactor of " << num << " is " << result << std::endl;
    ASSERT_EQ(result, 29);

    num = 600851475143;
    result = instance.largestPrimeFactor(num);
    std::cout << "Largest primefactor of " << num << " is " << result << std::endl;
    ASSERT_EQ(result, 6857);
}

#undef CLASSNAME
