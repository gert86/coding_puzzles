#pragma once

#define CLASSNAME Euler_10

#include "base_header.h"

using namespace std;
using namespace Helper;

// -------------------- Program starts here -------------------------
//
// The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.
// Find the sum of all the primes below two million.
//
// STATUS: Solved, but needs performance improvement!

class CLASSNAME
{
public:
    CLASSNAME()
    {
        cout << "Running " << VERSION_STRING(CLASSNAME) << "..." << endl;
    }

    std::vector<long long> _alreadKnownPrimes;

    long long getSumOfPrimesBelow(long long num)
    {
      if (num <= 0) {
        std::cerr << "Error " << std::endl;
        return 0;
      }


      // check if we already have it stored!
      auto it = std::lower_bound(_alreadKnownPrimes.begin(), _alreadKnownPrimes.end(), num);
      if (it != _alreadKnownPrimes.end()) {
        std::cout << "The first prime number >= " << num  << " is " << *it << std::endl;
        return std::accumulate(_alreadKnownPrimes.begin(), it, 0);
      }



      std::cout << "Did not find a prime number < " << num << " - building it!" << std::endl;
      auto isRelativePrime = [this](long long primeCanditate)
      {
        for (const auto& p : _alreadKnownPrimes) {
          if (primeCanditate % p == 0) {
            return false;
          }
        }
        return true;
      };

      long long currentNumToCheck = (_alreadKnownPrimes.empty() ? 2 : _alreadKnownPrimes[_alreadKnownPrimes.size() - 1]+1);
      long long largestStoredPrime = 0;
      while (largestStoredPrime <= num) {
        if (isRelativePrime(currentNumToCheck)) {
          //std::cout << "#### Found another prime number: " << currentNumToCheck<< std::endl;
          _alreadKnownPrimes.push_back(currentNumToCheck);
          largestStoredPrime = currentNumToCheck;
        }
        currentNumToCheck++;
      }

      it = std::lower_bound(_alreadKnownPrimes.begin(), _alreadKnownPrimes.end(), num);
      std::cout << "FINALLY: The first prime number >= " << num  << " is " << *it << " (num primes so far: " << _alreadKnownPrimes.size() << ")" << std::endl;
      return std::accumulate(_alreadKnownPrimes.begin(), it, 0);;
    }

};

TEST(CLASSNAME, Test1)
{
    CLASSNAME instance;

    // pre-init for testing
    //instance._alreadKnownPrimes         = {2,3, 5, 7, 11};

    int param = 10;
    auto result = instance.getSumOfPrimesBelow(param);
    std::cout << "Cum-Sum of primes < " << param << " is " << result << std::endl;
    ASSERT_EQ(result, 17);

    param = 2e6;
    result = instance.getSumOfPrimesBelow(param);
    std::cout << "Cum-Sum of primes < " << param << " is " << result << std::endl;
    ASSERT_EQ(result, 1179908154);
}

#undef CLASSNAME
