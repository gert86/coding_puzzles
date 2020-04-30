#pragma once

#define CLASSNAME Daily_126                //< specify class name here

#include "base_header.h"

using namespace std;
using namespace Helper;

// -------------------- Program starts here -------------------------
//
// Write a function that rotates a list by k elements.
// For example, [1, 2, 3, 4, 5, 6] rotated by two becomes [3, 4, 5, 6, 1, 2].
// Try solving this without creating a copy of the list. How many swap or move operations do you need?

class CLASSNAME
{
public:
    CLASSNAME()
    {
        cout << "Running " << VERSION_STRING(CLASSNAME) << "..." << endl;
    }

    template<typename T>
    void rotateByK(std::deque<T> &vec, int k)
    {
        // Error case
        if (k<0 || k>vec.size())
        {
            cout << "Error: k out of bounds. Must be k>=0 and k<=vector.size()." << endl;
            return;
        }

        // normal case with nothing to do
        if (k==0 || k==vec.size())
        {
            return;
        }

        // pop from front and insert to back. All operations in O(1).
        for (int i=0; i<k; i++)
        {
            int curr = vec.front();
            vec.pop_front();
            vec.push_back(curr);
        }
    }
};

TEST(CLASSNAME, Test1)
{    
    CLASSNAME instance;

    // NOTE: I am using a deque, because this is the best suited data structure for this problem.
    //       If necessary convert from and to vector
    int k = 0;
    std::deque<int> original_array{1, 2, 3, 4, 5, 6};
    std::deque<int> array;
    std::deque<int> expected_result;

    k = 0;
    expected_result = {1, 2, 3, 4, 5, 6};
    array = original_array;
    instance.rotateByK(array, k);
    cout << "The resulting deque with k = " << k << " is " << printDeque(array)  << endl;
    ASSERT_EQ(expected_result, array);

    k = 1;
    expected_result = {2, 3, 4, 5, 6, 1};
    array = original_array;
    instance.rotateByK(array, k);
    cout << "The resulting deque with k = " << k << " is " << printDeque(array)  << endl;
    ASSERT_EQ(expected_result, array);

    k = 2;
    expected_result = {3, 4, 5, 6, 1, 2};
    array = original_array;
    instance.rotateByK(array, k);
    cout << "The resulting deque with k = " << k << " is " << printDeque(array)  << endl;
    ASSERT_EQ(expected_result, array);

    k = 3;
    expected_result = {4, 5, 6, 1, 2, 3};
    array = original_array;
    instance.rotateByK(array, k);
    cout << "The resulting deque with k = " << k << " is " << printDeque(array)  << endl;
    ASSERT_EQ(expected_result, array);

    k = 4;
    expected_result = {5, 6, 1, 2, 3, 4};
    array = original_array;
    instance.rotateByK(array, k);
    cout << "The resulting deque with k = " << k << " is " << printDeque(array)  << endl;
    ASSERT_EQ(expected_result, array);

    k = 5;
    expected_result = {6, 1, 2, 3, 4, 5};
    array = original_array;
    instance.rotateByK(array, k);
    cout << "The resulting deque with k = " << k << " is " << printDeque(array)  << endl;
    ASSERT_EQ(expected_result, array);

    k = 6;
    expected_result = {1, 2, 3, 4, 5, 6};
    array = original_array;
    instance.rotateByK(array, k);
    cout << "The resulting deque with k = " << k << " is " << printDeque(array)  << endl;
    ASSERT_EQ(expected_result, array);

    k = 7;
    expected_result = {1, 2, 3, 4, 5, 6};
    array = original_array;
    instance.rotateByK(array, k);
    cout << "The resulting deque with k = " << k << " is " << printDeque(array)  << endl;
    ASSERT_EQ(expected_result, array);

}

#undef CLASSNAME
