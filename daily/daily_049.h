#pragma once

#define CLASSNAME Daily_049

#include "base_header.h"

using namespace std;
using namespace Helper;

// -------------------- Program starts here -------------------------
//
// Given an array of numbers, find the maximum sum of any contiguous subarray of the array.
// For example, given the array [34, -50, 42, 14, -5, 86], the maximum sum would be 137, since we would take elements 42, 14, -5, and 86.
// Given the array [-5, -1, -8, -9], the maximum sum would be 0, since we would not take any elements.
// Do this in O(N) time.


// Strategy:
// 34, -50, 42, 14, -5, 86
// 34:        -> 34 -> store as max. series: [0,0]
//-50: 34-50  -> <0 forget
//       -50  -> <0 do not consider as new start
// 42:        -> 42 best so far -> store as max. series: [2,2]
// 14:        -> 42+14=56 even better -> store as max. series: [2,3]
// -5:        -> 42+14-5=51 -> not max, but still > 0 so continue with this series
// 86:        -> 42+14-5+86 -> 137 new max


class CLASSNAME
{
public:
    CLASSNAME()
    {
        cout << "Running " << VERSION_STRING(CLASSNAME) << "..." << endl;
    }

    int findMaxSubarray(const vector<int>& array)
    {
      int currSum = 0;
      int bestSum = 0;
      for (int i=0; i<array.size(); i++) {
        //std::cout << "val = " << array[i] << std::endl;
        currSum += array[i];
        if (currSum > bestSum) {
          bestSum = currSum;
          //std::cout << "  bestSum increased to  " << bestSum << std::endl;
        }
        else if (currSum < 0) {
          //std::cout << "  currSum reset to  0" << std::endl;
          currSum = 0;
        }
      }

      return bestSum;
    }
};

TEST(CLASSNAME, Test1)
{    
    CLASSNAME instance;

    vector< vector<int> > test_vector;                             vector<int> result_vector;
    test_vector.push_back({34, -50, 42, 14, -5, 86});              result_vector.push_back(137);  // 42 + 14 - 5 + 86
    test_vector.push_back({-5, -1, -8, -9});                       result_vector.push_back(0);
    test_vector.push_back({34, -1, -33, 42, -1, -3, -30, 40, -1}); result_vector.push_back(48);   // 42 - 1 - 3 - 30 + 40

    for (int i=0; i<test_vector.size(); i++)
    {
        int max_sum = instance.findMaxSubarray(test_vector[i]);
        cout << "The max subarray sum is " << max_sum << endl << endl;
        ASSERT_EQ(result_vector[i], max_sum);
    }
}

#undef CLASSNAME
