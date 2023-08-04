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
    void rotateByK(std::queue<T> &vec, int k)
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
            vec.pop();
            vec.push(curr);
        }
    }
};

TEST(CLASSNAME, Test1)
{    
    CLASSNAME instance;

    // NOTE: I am using a queue or deque, because this is the best suited data structure for this problem.
    //       If necessary convert from and to vector
    int k = 0;
    std::queue<int> original_array;
    for (auto &i : {1, 2, 3, 4, 5, 6})  original_array.push(i);
    std::queue<int> array;
    std::queue<int> expected_result;

    k = 0;
    while(!expected_result.empty()) expected_result.pop();
    for (auto &i : {1, 2, 3, 4, 5, 6})  expected_result.push(i);
    array = original_array;
    instance.rotateByK(array, k);
    cout << "The resulting queue with k = " << k << " is " << printQueue(array)  << endl;
    ASSERT_EQ(expected_result, array);

    k = 1;
    while(!expected_result.empty()) expected_result.pop();
    for (auto &i : {2, 3, 4, 5, 6, 1})  expected_result.push(i);
    array = original_array;
    instance.rotateByK(array, k);
    cout << "The resulting queue with k = " << k << " is " << printQueue(array)  << endl;
    ASSERT_EQ(expected_result, array);

    k = 2;
    while(!expected_result.empty()) expected_result.pop();
    for (auto &i : {3, 4, 5, 6, 1, 2})  expected_result.push(i);
    array = original_array;
    instance.rotateByK(array, k);
    cout << "The resulting queue with k = " << k << " is " << printQueue(array)  << endl;
    ASSERT_EQ(expected_result, array);

    k = 3;
    while(!expected_result.empty()) expected_result.pop();
    for (auto &i : {4, 5, 6, 1, 2, 3})  expected_result.push(i);
    array = original_array;
    instance.rotateByK(array, k);
    cout << "The resulting queue with k = " << k << " is " << printQueue(array)  << endl;
    ASSERT_EQ(expected_result, array);

    k = 4;
    while(!expected_result.empty()) expected_result.pop();
    for (auto &i : {5, 6, 1, 2, 3, 4})  expected_result.push(i);
    array = original_array;
    instance.rotateByK(array, k);
    cout << "The resulting queue with k = " << k << " is " << printQueue(array)  << endl;
    ASSERT_EQ(expected_result, array);

    k = 5;
    while(!expected_result.empty()) expected_result.pop();
    for (auto &i : {6, 1, 2, 3, 4, 5})  expected_result.push(i);
    array = original_array;
    instance.rotateByK(array, k);
    cout << "The resulting queue with k = " << k << " is " << printQueue(array)  << endl;
    ASSERT_EQ(expected_result, array);

    k = 6;
    while(!expected_result.empty()) expected_result.pop();
    for (auto &i : {1, 2, 3, 4, 5, 6})  expected_result.push(i);
    array = original_array;
    instance.rotateByK(array, k);
    cout << "The resulting queue with k = " << k << " is " << printQueue(array)  << endl;
    ASSERT_EQ(expected_result, array);

    k = 7;
    while(!expected_result.empty()) expected_result.pop();
    for (auto &i : {1, 2, 3, 4, 5, 6})  expected_result.push(i);
    array = original_array;
    instance.rotateByK(array, k);
    cout << "The resulting queue with k = " << k << " is " << printQueue(array)  << endl;
    ASSERT_EQ(expected_result, array);

}

#undef CLASSNAME
