#pragma once

#define CLASSNAME Daily_009

#include "base_header.h"

using namespace std;
using namespace Helper;

// -------------------- Program starts here -------------------------
//
//Given a list of integers, write a function that returns the largest sum of non-adjacent numbers. Numbers can be 0 or negative.
//For example, [2, 4, 6, 2, 5] should return 13, since we pick 2, 6, and 5. [5, 1, 1, 5] should return 10, since we pick 5 and 5.
//Follow-up: Can you do this in O(N) time and constant space?

class CLASSNAME
{
public:
    CLASSNAME()
    {
        cout << "Running " << VERSION_STRING(CLASSNAME) << "..." << endl;
    }

    int maximumSum(const std::vector<int> &vec)
    {
        if (vec.size() == 0)
            return 0;

        if (vec.size() == 1)
            return vec[0];

        if (vec.size() == 2)
            return max(vec[0], vec[1]);

        int max_prev_prev = vec[0];               // maximum that can be reached without prev. element
        int max_prev      = max(vec[0], vec[1]);  // maximum that can be reached with prev. element


        int max_to_here = 0;
        for (int i=2; i<vec.size(); i++)
        {
            max_to_here = max(max_prev, max_prev_prev + vec[i]);

            // next iteration
            max_prev_prev = max_prev;
            max_prev = max_to_here;
        }

        return max_to_here;
    }
};

TEST(CLASSNAME, Test1)
{    
    CLASSNAME instance;

    vector< vector<int> > test_vector;          vector<int> result_vector;
    test_vector.push_back({2, 4, 6, 2, 5});     result_vector.push_back(13);
    test_vector.push_back({5, 1, 1, 5});        result_vector.push_back(10);
    test_vector.push_back({5, 1, 1, 20, 100});  result_vector.push_back(106);
    test_vector.push_back({10, 100, 10});       result_vector.push_back(100);
    test_vector.push_back({100, 50, -4, 20});   result_vector.push_back(120);

    for(int i=0; i<test_vector.size(); i++)
    {
        int max_sum = instance.maximumSum(test_vector[i]);
        cout << "Test #" << (i+1) << " gives result: " << max_sum << endl;
        ASSERT_EQ(result_vector[i], max_sum);
    }
}

#undef CLASSNAME
