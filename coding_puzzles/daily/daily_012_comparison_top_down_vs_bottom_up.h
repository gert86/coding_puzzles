#pragma once

#define CLASSNAME Daily_012_Comparison_Top_Down_vs_Bottom_Up

#include "base_header.h"

using namespace std;
using namespace Helper;

// -------------------- Program starts here -------------------------
//
// There exists a staircase with N steps, and you can climb up either 1 or 2 steps at a time.
// Given N, write a function that returns the number of unique ways you can climb the staircase. The order of the steps matters.

// For example, if N is 4, then there are 5 unique ways:
//     1, 1, 1, 1
//     2, 1, 1
//     1, 2, 1
//     1, 1, 2
//     2, 2

// What if, instead of being able to climb 1 or 2 steps at a time, you could climb any number from a set of positive integers X?
// For example, if X = {1, 3, 5}, you could climb 1, 3, or 5 steps at a time.


// NOTE: Tried to solve the problem top-down (=from destination back to start) and bottom-up (=from start to destination).
// CONCLUSION: Works both ways almost the same way (additional parameter needed for bottom-up).
// However, the BEST solution here is a non-recursive approach.
//
// Note that we want to find ALL possible solutions but do not need to store each possible solution (count is sufficient).
// --> Compare with cracking_008_002, where we want only 1 possible solution but also print this solution.


class CLASSNAME
{
public:
    CLASSNAME()
    {
        cout << "Running " << VERSION_STRING(CLASSNAME) << "..." << endl;
    }




    ////////////////////////////////////////////////////////////////////////////////////////
    /// 01: Top-Down approach (=from dest backwards to start field)
    ///
    ////////////////////////////////////////////////////////////////////////////////////////
    int numPossibilities01(int N, const std::vector<int> &valid_step_counts, std::vector<int> &memo)
    {
        if (N < 0)
        {
            return 0;
        }
        else if (N == 0)
        {
            return 1;
        }
        else
        {
            int count = 0;
            for (int step_amount : valid_step_counts)
            {
                int next_idx = N - step_amount;
                if (next_idx >= 0 && next_idx < memo.size() && memo[next_idx] != -1)
                    count += memo[next_idx];    // avoid recursion through memoization
                else
                    count += numPossibilities01(next_idx, valid_step_counts, memo);
            }
            return count;
        }
    }




    ////////////////////////////////////////////////////////////////////////////////////////
    /// 02: Bottom-Up approach (=from start field forwards to dest field)
    ///
    ////////////////////////////////////////////////////////////////////////////////////////
    int numPossibilities02(int N, const std::vector<int> &valid_step_counts, std::vector<int> &memo, int N_current)
    {
        if (N_current > N)
        {
            return 0;
        }
        else if (N_current == N)
        {
            return 1;
        }
        else
        {
            int count = 0;
            for (int step_amount : valid_step_counts)
            {
                int next_idx = N_current + step_amount;
                if (next_idx >= 0 && next_idx < memo.size() && memo[next_idx] != -1)
                    count += memo[next_idx];   // avoid recursion through memoization
                else
                    count += numPossibilities02(N, valid_step_counts, memo, next_idx);
            }
            return count;
        }

        // We need an additional variable to store N (=last step) in addition to the current step N_current.
        // Top-down does not have this problem because 0 is per definition the base step.
    }




    ////////////////////////////////////////////////////////////////////////////////////////
    /// 03: Non-recursive approach
    /// We can do so, because we figured out the systematics of the problem
    ////////////////////////////////////////////////////////////////////////////////////////


    int numPossibilities03(int N, const std::vector<int> &valid_step_counts)
    {
        vector<int> possibilities;
        possibilities.resize(N+1);
        possibilities[0] = 1; //base case

        for (int i=1; i<=N; i++)
        {
            int num = 0;
            for (int j=0; j<valid_step_counts.size(); j++)
            {
                if (valid_step_counts[j] <= i)
                {
                    num += possibilities[ i-valid_step_counts[j] ];
                }
            }
            possibilities[i] = num;
        }

        return possibilities[N];
    }
};

TEST(CLASSNAME, Test1)
{    
    CLASSNAME instance;    

    // Test case A: 1 or 2 steps at a time
    vector<int> valid_steps_01 = {1, 2};
    vector<int> test_vector_01;     vector<int> result_vector_01;
    test_vector_01.push_back(1);    result_vector_01.push_back(1);
    test_vector_01.push_back(2);    result_vector_01.push_back(2);
    test_vector_01.push_back(3);    result_vector_01.push_back(3);
    test_vector_01.push_back(4);    result_vector_01.push_back(5);
    test_vector_01.push_back(5);    result_vector_01.push_back(8);
    test_vector_01.push_back(6);    result_vector_01.push_back(13);
    for(int i=0; i<test_vector_01.size(); i++)
    {
        // memo for mode 1 and 2
        vector<int> memo(test_vector_01[i], -1);

        int num_possibilities_mode_01 = -1;  int num_possibilities_mode_02 = -1;  int num_possibilities_mode_03 = -1;
        num_possibilities_mode_01 = instance.numPossibilities01(test_vector_01[i], valid_steps_01, memo);
        num_possibilities_mode_02 = instance.numPossibilities02(test_vector_01[i], valid_steps_01, memo, 0);
        num_possibilities_mode_03 = instance.numPossibilities03(test_vector_01[i], valid_steps_01);
        cout << "Testcase A: For N=" << test_vector_01[i] << " the number of possibilities is " << num_possibilities_mode_01 << endl;
        ASSERT_EQ(result_vector_01[i], num_possibilities_mode_01);
        ASSERT_EQ(result_vector_01[i], num_possibilities_mode_02);
        ASSERT_EQ(result_vector_01[i], num_possibilities_mode_03);
    }
    cout << "----------------------------" << endl;

    // Test case B: 1, 3 or 5 steps at a time
    vector<int> valid_steps_02 = {1, 3, 5};
    vector<int> test_vector_02;     vector<int> result_vector_02;
    test_vector_02.push_back(1);    result_vector_02.push_back(1);
    test_vector_02.push_back(2);    result_vector_02.push_back(1);
    test_vector_02.push_back(3);    result_vector_02.push_back(2);
    test_vector_02.push_back(4);    result_vector_02.push_back(3);
    test_vector_02.push_back(5);    result_vector_02.push_back(5);
    test_vector_02.push_back(6);    result_vector_02.push_back(8);
    for(int i=0; i<test_vector_02.size(); i++)
    {
        // memo for mode 1 and 2
        vector<int> memo(test_vector_02[i], -1);

        int num_possibilities_mode_01 = -1;  int num_possibilities_mode_02 = -1;  int num_possibilities_mode_03 = -1;
        num_possibilities_mode_01 = instance.numPossibilities01(test_vector_02[i], valid_steps_02, memo);
        num_possibilities_mode_02 = instance.numPossibilities02(test_vector_02[i], valid_steps_02, memo, 0);
        num_possibilities_mode_03 = instance.numPossibilities03(test_vector_02[i], valid_steps_02);
        cout << "Testcase B: For N=" << test_vector_02[i] << " the number of possibilities is " << num_possibilities_mode_01 << endl;
        ASSERT_EQ(result_vector_02[i], num_possibilities_mode_01);
        ASSERT_EQ(result_vector_02[i], num_possibilities_mode_02);
        ASSERT_EQ(result_vector_02[i], num_possibilities_mode_03);
    }

}

#undef CLASSNAME
