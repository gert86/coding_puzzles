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

    bool isNumberPalindrome(int number)
    {
      if (number < 0)
        return true;

      auto numberStr = std::to_string(number);
      int lowerPos = 0;
      int upperPos = numberStr.size() - 1;
      while (lowerPos < upperPos) {
        if (numberStr[lowerPos] != numberStr[upperPos])
          return false;
        lowerPos++;
        upperPos--;
      }
      return true;
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
