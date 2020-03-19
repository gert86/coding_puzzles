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

class CLASSNAME
{
public:
    CLASSNAME()
    {
        cout << "Running " << VERSION_STRING(CLASSNAME) << "..." << endl;
    }

    // Case 1: It is possible to achieve a positive result
    //   --> either use 2 largest negative values plus 1 largest positive or the 3 largest positive ones
    // Case 2: It is not possible to achieve a positive result
    //   --> If a zero exists, use this one for result 0.
    //   --> If exactly three values, use them as they are (covers case of 2 positive and 1 negative numbers)
    //   --> If only negative numbers, use the three smallest ones
    // While iterating over whole array, store the 2 largest negative, the 3 largest positive, the 3 smallest negative and if there is a zero.




    int calcMaximumSumOfThree(const vector<int> &array)
    {

        if (array.size() < 3)
        {
            cerr << "Array size must be >=3" << endl;
            exit(-1);
        }

        if (array.size() == 3)
        {
            return array[0] * array[1] * array[2];
        }


        bool has_zero = false;
        int largest_positive_1 = std::numeric_limits<int>::min();
        int largest_positive_2 = std::numeric_limits<int>::min();
        int largest_positive_3 = std::numeric_limits<int>::min();

        int largest_negative_abs_1 = std::numeric_limits<int>::min();
        int largest_negative_abs_2 = std::numeric_limits<int>::min();
        int largest_negative_abs_3 = std::numeric_limits<int>::min();

        int smallest_negative_abs_1 = std::numeric_limits<int>::max();
        int smallest_negative_abs_2 = std::numeric_limits<int>::max();
        int smallest_negative_abs_3 = std::numeric_limits<int>::max();

        int num_positive = 0;
        int num_negative = 0;


        for(int val : array)
        {
            if (val == 0)
            {
                has_zero = true;
                continue;
            }

            if (val > 0)
            {
                num_positive++;
                if (val > largest_positive_1)
                {
                    largest_positive_3 = largest_positive_2;
                    largest_positive_2 = largest_positive_1;
                    largest_positive_1 = val;
                }
                else if (val > largest_positive_2)
                {
                    largest_positive_3 = largest_positive_2;
                    largest_positive_2 = val;
                }
                else if (val > largest_positive_3)
                {
                    largest_positive_3 = val;
                }
                continue;
            }

            if (val < 0)
            {
                num_negative++;

                // update largest vals
                if (abs(val) > largest_negative_abs_1)
                {
                    largest_negative_abs_3 = largest_negative_abs_2;
                    largest_negative_abs_2 = largest_negative_abs_1;
                    largest_negative_abs_1 = abs(val);
                }
                else if (abs(val) > largest_negative_abs_2)
                {
                    largest_negative_abs_3 = largest_negative_abs_2;
                    largest_negative_abs_2 = abs(val);
                }
                else if (abs(val) > largest_negative_abs_3)
                {
                    largest_negative_abs_3 = abs(val);
                }

                // update smallest vals
                if (abs(val) < smallest_negative_abs_1)
                {
                    smallest_negative_abs_3 = smallest_negative_abs_2;
                    smallest_negative_abs_2 = smallest_negative_abs_1;
                    smallest_negative_abs_1 = abs(val);
                }
                else if (abs(val) < smallest_negative_abs_2)
                {
                    smallest_negative_abs_3 = smallest_negative_abs_2;
                    smallest_negative_abs_2 = abs(val);
                }
                else if (abs(val) < smallest_negative_abs_3)
                {
                    smallest_negative_abs_3 = abs(val);
                }

                continue;
            }
        }

        if (num_positive == 0)
        {
            // we cannot return a positive result
            if (has_zero)
                return 0;

            return (-1)*smallest_negative_abs_3*smallest_negative_abs_2*smallest_negative_abs_1;
        }

        if (num_negative < 2)
        {
            // we cannot use the negative values in the result calculation
            if (num_positive <= 3)
            {
                if (!has_zero)
                {
                    cerr << "This should not happen!" << endl;
                    exit(-1);
                }
                else
                {
                    return 0;
                }
            }
            else
            {
                return largest_positive_3*largest_positive_2*largest_positive_1;
            }
        }

        if (num_positive < 2)
        {
            if (num_positive < 1)
            {
                if (!has_zero)
                {
                    cerr << "This should not happen!" << endl;
                    exit(-1);
                }
                else
                {
                    return 0;
                }
            }

            return largest_positive_1*largest_negative_abs_1*largest_negative_abs_2;
        }

        if(largest_positive_1*largest_positive_2 > largest_negative_abs_1*largest_negative_abs_2)
        {
            return largest_positive_1*largest_positive_2*largest_positive_3;
        }
        else
        {
            return largest_negative_abs_1*largest_negative_abs_2*largest_positive_1;
        }
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

    for (int i=0; i<test_vector.size(); i++)
    {
        int largest_product = instance.calcMaximumSumOfThree(test_vector[i]);
        cout << "The vector " << printVec(test_vector[i]) << " has largest product " << largest_product << endl;
        ASSERT_EQ(result_vector[i], largest_product);
    }
}

#undef CLASSNAME
