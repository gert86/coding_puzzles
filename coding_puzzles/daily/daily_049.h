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

class CLASSNAME
{
public:
    CLASSNAME()
    {
        cout << "Running " << VERSION_STRING(CLASSNAME) << "..." << endl;
    }


    int findMaxSubarray(const vector<int> &array)
    {
        vector< pair<int, int> > maxima;
        maxima.resize( array.size() );

        for (int i=0; i<array.size(); i++)
        {
            if (i==0)
            {
                maxima[0] = std::make_pair<int,int>((int)array[0], 0);
            }
            else
            {
                if (maxima[i-1].first <= 0)
                {
                    maxima[i] = std::make_pair<int, int>((int)array[i], (int)i);
                }
                else
                {
                    maxima[i] = std::make_pair<int, int>((int)(maxima[i-1].first + array[i]), (int)(maxima[i-1].second));
                }
            }
        }

        int curr_max = 0;
        int curr_max_idx = -1;
        for (int i=0; i<maxima.size(); i++)
        {
            if (maxima[i].first > 0)
            {
                if (maxima[i].first > curr_max)
                {
                    curr_max = maxima[i].first;
                    curr_max_idx = i;
                }
            }
        }

        if (curr_max_idx >= 0)
        {
            cout << "The max sum is " << curr_max << " and it goes from " << maxima[curr_max_idx].second << " to " << curr_max_idx << endl;
        }
        else
        {
             cout << "The max sum is " << curr_max << endl;
        }

        return curr_max;
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
