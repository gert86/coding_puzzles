#pragma once

#define CLASSNAME Euler_07

#include "base_header.h"

using namespace std;
using namespace Helper;

// -------------------- Program starts here -------------------------
//
// By listing the first six prime numbers: 2, 3, 5, 7, 11, and 13, we can see that the 6th prime is 13.
// What is the 10 001st prime number?

class CLASSNAME
{
public:
    CLASSNAME()
    {
        cout << "Running " << VERSION_STRING(CLASSNAME) << "..." << endl;
    }

    std::vector<long long> _alreadKnownPrimes;

    long long getPrimeNumber(int num)
    {
      if (num <= 0) {
        std::cerr << "Error " << std::endl;
        return 0;
      }

      // check if we already have it stored!
      if (_alreadKnownPrimes.size() >= num) {
        std::cout << "Prime #" << num << " already known." << std::endl;
        return _alreadKnownPrimes[num-1];
      }


      //std::cout << "Prime #" << num << " not known - building it" << std::endl;
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
      while (_alreadKnownPrimes.size() < num) {
        if (isRelativePrime(currentNumToCheck)) {
          //std::cout << "#### Found another prime number: " << currentNumToCheck<< std::endl;
          _alreadKnownPrimes.push_back(currentNumToCheck);
        }
        currentNumToCheck++;
      }

      return _alreadKnownPrimes[num-1];
    }

};

TEST(CLASSNAME, Test1)
{    
    CLASSNAME instance;

    // pre-init
    //instance._alreadKnownPrimes = {2,3,5,7,11,13};

    int param = 6;
    auto result = instance.getPrimeNumber(param);
    std::cout << "The prime number #" << param << " is " << result << std::endl;
    ASSERT_EQ(result, 13);

    param = 10001;
    result = instance.getPrimeNumber(param);
    std::cout << "The prime number #" << param << " is " << result << std::endl;
    ASSERT_EQ(result, 104743);
}

#undef CLASSNAME
