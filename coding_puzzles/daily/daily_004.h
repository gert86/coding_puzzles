#pragma once

#define CLASSNAME Daily_004

#include "base_header.h"

using namespace std;
using namespace Helper;

// -------------------- Program starts here -------------------------
//
// Given an array of integers, find the first missing positive integer in linear time and constant space.
// In other words, find the lowest positive integer that does not exist in the array.
// The array can contain duplicates and negative numbers as well.
//
// For example, the input [3, 4, -1, 1] should give 2. The input [1, 2, 0] should give 3.
//
// You can modify the input array in-place.

class CLASSNAME
{
public:
    CLASSNAME()
    {
        cout << "Running " << VERSION_STRING(CLASSNAME) << "..." << endl;
    }

    int find_missing_int_simple(std::vector<int> array)
    {
        // edge case
        if (array.empty())
            return 1;

        // sort the array
        std::sort(array.begin(), array.end());

        for (int i=0; i<array.size(); i++)
        {
            if (i==0)
            {
                // if we start >1, then 1 is obviously missing
                if (array[0] > 1)
                    return 1;
            }
            else
            {
                // values <= 0 are not of interest
                // we can also skip 1, because if 1 is missing this will be detected in the next step
                if (array[i] <= 1)
                    continue;

                // we found a gap
                if ( (array[i] != array[i-1]) && (array[i] != array[i-1] + 1) )
                {
                    return array[i-1] + 1;
                }
            }
        }

        int last = array.back();
        if (last <= 0)
        {
            // array contains no positive ints, so 1 is already missing
            return 1;
        }

        // there was no gap, so the next number is the first missing one
        return last + 1;
    }
};

TEST(CLASSNAME, Test1)
{    
    CLASSNAME instance;

    vector< vector<int> >  test_vector;                                                 vector<int>  result_vector;
    test_vector.push_back({3, 4, -1, 1});                                               result_vector.push_back(2);
    test_vector.push_back({1, 2, 0});                                                   result_vector.push_back(3);
    test_vector.push_back({9, 8, -1, 6, 13, 0, 2, 1, 3, 4, 5, 5, 7, -6, 12, -9, 11});   result_vector.push_back(10);
    test_vector.push_back({2,1,100,-1,-1,-1,3,5,4});                                    result_vector.push_back(6);
    test_vector.push_back({});                                                          result_vector.push_back(1);
    test_vector.push_back({-1});                                                        result_vector.push_back(1);
    test_vector.push_back({0});                                                         result_vector.push_back(1);
    test_vector.push_back({1});                                                         result_vector.push_back(2);
    test_vector.push_back({1,2});                                                       result_vector.push_back(3);
    test_vector.push_back({1,-2});                                                      result_vector.push_back(2);

    for (int i=0; i<test_vector.size(); i++)
    {
        int missing_int = instance.find_missing_int_simple( test_vector[i] );
        cout << "Test #" << (i+1) << " results in " << missing_int << endl << endl;
        ASSERT_EQ(result_vector[i], missing_int);
    }
}

#undef CLASSNAME
