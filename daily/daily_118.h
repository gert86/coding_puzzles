#pragma once

#define CLASSNAME Daily_118                //< specify class name here

#include "base_header.h"

using namespace std;
using namespace Helper;

// -------------------- Program starts here -------------------------
//
// Given a sorted list of integers, square the elements and give the output in sorted order.
// For example, given [-9, -2, 0, 2, 3], return [0, 4, 4, 9, 81].

class CLASSNAME
{
public:
    CLASSNAME()
    {
        cout << "Running " << VERSION_STRING(CLASSNAME) << "..." << endl;
    }

    // Note: All implementation in test itself
};

TEST(CLASSNAME, TestVariant1)
{    
    vector<int> my_vec = {-9, -2, 0, 2, 3};

    std::transform(my_vec.begin(), my_vec.end(), my_vec.begin(), [](int x){return x*x;});                   // variant 1 with unary operator (=lambda)
    std::sort(my_vec.begin(), my_vec.end());

    cout << "The squared and sorted vector is " << printVec(my_vec)  << endl;

    vector<int> expected_result_vector = {0, 4, 4, 9, 81};
    ASSERT_EQ(expected_result_vector, my_vec);
}


TEST(CLASSNAME, TestVariant2)
{
    vector<int> my_vec = {-9, -2, 0, 2, 3};

    std::transform(my_vec.begin(), my_vec.end(), my_vec.begin(), my_vec.begin(), std::multiplies<int>());   // variant 2 with binary operator (multiply)
    std::sort(my_vec.begin(), my_vec.end());

    cout << "The squared and sorted vector is " << printVec(my_vec)  << endl;

    vector<int> expected_result_vector = {0, 4, 4, 9, 81};
    ASSERT_EQ(expected_result_vector, my_vec);
}
#undef CLASSNAME
