#pragma once

#define CLASSNAME Euler_04

#include "base_header.h"

using namespace std;
using namespace Helper;

// -------------------- Program starts here -------------------------
//
// A palindromic number reads the same both ways. The largest palindrome made from the product of two 2-digit numbers is 9009 = 91 × 99.
// Find the largest palindrome made from the product of two 3-digit numbers.

class CLASSNAME
{
public:
    CLASSNAME()
    {
        cout << "Running " << VERSION_STRING(CLASSNAME) << "..." << endl;
    }

    int getDigitNum(int num, size_t digitPos)
    {
      if (num <= 0) {
        std::cerr << "getDigitNum only works for positive numbers" << std::endl;
        return 0;
      }

      if (digitPos==0) {
        return num % (int)std::pow(10, digitPos+1);   // return mod 10
      }
      return (num % (int)std::pow(10, digitPos+1)) / (int)std::pow(10, digitPos);
    }

    bool isNumberPalindrome(int num)
    {
      if (num < 10) {
        return true;
      }
      else if (num < 100) {
        // 2 digits
        return getDigitNum(num, 0) == getDigitNum(num, 1);
        //return ((num % 10)'/1' == (num '% 100') / 10));  // Einer und Zehnerstelle müssen matchen, ' ' highlights unnecessary parts
      }
      else if (num < 1000) {
        // 3 digits
        return getDigitNum(num, 0) == getDigitNum(num, 2);
        //return ((num % 10)'/1' == (num '% 1000')/ 100));  // Einer und Hunderterstelle müssen matchen, ' ' highlights unnecessary parts
      }
      else if (num < 10000) {
        // 4 digits
        return (getDigitNum(num, 0) == getDigitNum(num, 3)) && (getDigitNum(num, 1) == getDigitNum(num, 2));
        //bool firstLastMatch = ((num % 10)'/1' == (num '%10000' / 1000));         // Einer und Tausenderstelle müssen matchen...
        //bool middleTwoMatch = ((num%100)/10) == ((num%1000)/100);                // ...UND Zehner und hunderterstelle müssen matchen
        //return firstLastMatch && middleTwoMatch;
      }
      else if (num < 100000) {
        // 5 digits
        return (getDigitNum(num, 0) == getDigitNum(num, 4)) && (getDigitNum(num, 1) == getDigitNum(num, 3));
      }
      else if (num < 1000000) {
        // 6 digits
        return (getDigitNum(num, 0) == getDigitNum(num, 5)) && (getDigitNum(num, 1) == getDigitNum(num, 4)) && (getDigitNum(num, 2) == getDigitNum(num, 3));
      }

      // 7 digits not possible by 3-digit x 3-digit multiplication

      return false;
    }

    int findLargestPalindromeProduct(int numDigits)
    {
      if (numDigits < 1) {
        std::cerr << "numDigits must be >=1" << std::endl;
        return 0;
      }


      int largestPalindromeNumber = 0;
      for (int i=std::pow(10, numDigits-1); i < std::pow(10, numDigits); i++) {
        for (int j=std::pow(10, numDigits-1); j < std::pow(10, numDigits); j++) {
          auto currProduct = i*j;
          if (isNumberPalindrome(currProduct) && currProduct > largestPalindromeNumber)
            largestPalindromeNumber = currProduct;
        }
      }

      return largestPalindromeNumber;
    }

};

TEST(CLASSNAME, Test1)
{    
    CLASSNAME instance;

    int numDigits = 2;
    auto largestPalindromeProduct = instance.findLargestPalindromeProduct(numDigits);
    std::cout << "THE LARGEST PALINDROME PRODUCT FROM " << numDigits << " DIGIT NUMBERS IS " << largestPalindromeProduct << std::endl;
    ASSERT_EQ(largestPalindromeProduct, 9009);

    numDigits = 3;
    largestPalindromeProduct = instance.findLargestPalindromeProduct(numDigits);
    std::cout << "THE LARGEST PALINDROME PRODUCT FROM " << numDigits << " DIGIT NUMBERS IS " << largestPalindromeProduct << std::endl;
    ASSERT_EQ(largestPalindromeProduct, 906609);
}

#undef CLASSNAME
