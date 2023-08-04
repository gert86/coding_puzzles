#pragma once

#define CLASSNAME Daily_069

#include "base_header.h"

using namespace std;
using namespace Helper;

// -------------------- Program starts here -------------------------
//
// Given a list of integers, return the largest product that can be made by multiplying any three integers.
// For example, if the list is [-10, -10, 5, 2], we should return 500, since that's -10 * -10 * 5.
// You can assume the list has at least three integers.


// Strategy:
//
// Sorted List
// [-Z, -Y, -X, ...., A, B, C]
//
// In normal case the largest result is:
// max(-Z*-Y*C,  A*B*C)
//
// Bordercases:
// Zeros:
// Less than 3 values greater zero:

// Less than 2 Negatives
// POS * POS * POS (could be zero)

// No Positives
// Has zeros? -> 0
// else       -> smallest 3 negatives

// 1 Positive
// At least 2 negatives? -> NEG * NEG * POS
// else                  -> 0

// 2 Positive
// At least 2 negatives? -> NEG * NEG * POS

// 2 Positives, less than 2 negatives
// Has zeros? -> 0
// else       -> smallest neg * POS * POS (only possibility)



class CLASSNAME
{
public:
    CLASSNAME()
    {
        cout << "Running " << VERSION_STRING(CLASSNAME) << "..." << endl;
    }

    int calcMaximumProductOfThree(std::vector<int> numbers)
    {
      size_t N = numbers.size();
      if (N < 3)
        return 0;

      int numPos = 0;
      int numNeg = 0;
      int numZero = 0;
      for (const auto &number : numbers) {
        if (number > 0)
          numPos++;
        else if (number < 0)
          numNeg++;
        else
          numZero++;
      }


      auto numbersSortedByAbs = numbers;

      std::sort(numbers.begin(), numbers.end());
      std::sort(numbersSortedByAbs.begin(), numbersSortedByAbs.end(), [](int a, int b) {
        return std::abs(a) < std::abs(b);
      });


      // normal case
      // max(NEG*NEG*POS, POS*POS*POS)
      if (numPos >=3 && numNeg >= 2) {
        return std::max(numbers[0]*numbers[1]*numbers[N-1], numbers[N-1]*numbers[N-2]*numbers[N-3]);
      }

      // less than 2 negatives
      // POS*POS*POS (could be 0)
      if (numNeg < 2) {
        return numbers[N-1]*numbers[N-2]*numbers[N-3];
      }

      // no positives
      // 0 or neg*neg*neg
      if (numPos == 0) {
        if (numZero>0)
          return 0;
        return numbersSortedByAbs[0]*numbersSortedByAbs[1]*numbersSortedByAbs[2];
      }

      // 1 positive
      // 0 or NEG*NEG*POS
      if (numPos == 1) {
        if (numNeg>=1)
          return numbers[0]*numbers[1]*numbers[N-1];
        return 0;
      }


      // 2 positives
      // NEG * NEG * POS or
      // 0 or
      // neg*POS*POS
      if (numPos == 2) {
        if (numNeg>=1)
          return numbers[0]*numbers[1]*numbers[N-1];
        if (numZero>0)
          return 0;
        return numbers[0]*numbers[1]*numbers[2];
      }

      return -1;
    }
};

TEST(CLASSNAME, Test1)
{    
    CLASSNAME instance;

    vector< vector<int> > test_vector;                      vector<int> result_vector;
    test_vector.push_back({-2,-8,-1});                      result_vector.push_back(-16);
    test_vector.push_back({0, 0, -1, 0, 0});                result_vector.push_back(0);
    test_vector.push_back({0, 0, 55, 0, 0});                result_vector.push_back(0);
    test_vector.push_back({0,0,-1, -3, 0});                 result_vector.push_back(0);
    test_vector.push_back({0, 0, 55, 5, 0});                result_vector.push_back(0);
    test_vector.push_back({0, 0, -1, 5, 0});                result_vector.push_back(0);
    test_vector.push_back({-1, 0, 9, 3, 8, 4, 7});          result_vector.push_back(504);
    test_vector.push_back({-9, -8, 8, 7, 6, 0, 3, -5});     result_vector.push_back(576);

    test_vector.push_back({1, 10, 10, 9, 0, 3});              result_vector.push_back(900);  // 0 neg
    test_vector.push_back({0, 3, 5});                         result_vector.push_back(0);    // 0 neg, but zero
    test_vector.push_back({-9, 10, 10, 8, 0, 3});             result_vector.push_back(800);  // 1 neg
    test_vector.push_back({-7, -10, 10, 5, 0, 3});            result_vector.push_back(700);  // 2 neg
    test_vector.push_back({-2,-8,-2,-10,-17,-9});             result_vector.push_back(-32);  // no pos, no zeros
    test_vector.push_back({-2,-8,-2,-10, 0,-9});              result_vector.push_back(0);    // no pos, with zeros
    test_vector.push_back({8,-8,-2,-10, 0,-9});               result_vector.push_back(720);  // 1 pos, with >=2 neg
    test_vector.push_back({8,-8, 0, 0, 0});                   result_vector.push_back(0);    // 1 pos, 1 neg, with zeros

    test_vector.push_back({-1, 10,  8, -9, 0, 0});            result_vector.push_back(90);   // 2 pos, 2 neg
    test_vector.push_back({-2, 10, 10, 0, 0, 0});             result_vector.push_back(0);    // 2 pos, 1 neg, with zeros
    test_vector.push_back({ 0, 10, 10, 0, 0, 0});             result_vector.push_back(0);    // 2 pos, 0 neg, with zeros
    test_vector.push_back({-2, 10, 10});                      result_vector.push_back(-200); // 2 pos, 1 neg, no zeros (only 3 win)

    for (int i=0; i<test_vector.size(); i++)
    {
        int largest_product = instance.calcMaximumProductOfThree(test_vector[i]);
        cout << "The vector " << printVec(test_vector[i]) << " has largest product " << largest_product << endl;
        EXPECT_EQ(result_vector[i], largest_product);
    }
}

#undef CLASSNAME
