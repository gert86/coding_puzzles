#pragma once

#define CLASSNAME Cracking_10_3

#include "base_header.h"

using namespace std;
using namespace Helper;

// -------------------- Program starts here -------------------------
//
// Search in Rotated Array: Given a sorted array of n integers that has been rotated an unknown
// number of times, write code to find an element in the array. You may assume that the array was
// originally sorted in increasing order.
// EXAMPLE:
// Input:find 5 in{15, 16, 19, 20, 25, 1, 3,4,5,7, 10, 14}
// Output: 8 (the index of 5 in the array)

class CLASSNAME
{
public:
    CLASSNAME()
    {
        cout << "Running " << VERSION_STRING(CLASSNAME) << "..." << endl;
    }

    int findInRotatedArray(const vector<int> &array, int value, int start_idx, int end_idx)
    {
        // not found
        if (start_idx > end_idx)
            return -1;

        // implement special variant of binary search
        int mid_idx = (start_idx + end_idx)/2;

        if (array[mid_idx] == value)
        {
            // found
            return mid_idx;
        }

        if (value < array[mid_idx] || (value > array[mid_idx] && value > array[end_idx]))
        {
            // search left
            return findInRotatedArray(array, value, start_idx, mid_idx - 1);
        }

        if (value > array[mid_idx] || (value < array[mid_idx] && value < array[start_idx]))
        {
            // search right
            return findInRotatedArray(array, value, mid_idx + 1, end_idx);
        }

        // will never be reached
        return -2;
    }
};

TEST(CLASSNAME, Test1)
{    
    CLASSNAME instance;

    vector<int> array = {15,16,19,20,25,1,3,4,5,7,10,14};
    int search_value = 5;
    cout << "The vector is: " << printVec(array) << ". Searching for index of value " << search_value << "." << endl;

    int index = instance.findInRotatedArray(array, search_value, 0, array.size() - 1);
    cout << "The index of value " << search_value << " is " << index << "." << endl;
    ASSERT_EQ(8, index);
}

#undef CLASSNAME
