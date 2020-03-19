#pragma once

#define CLASSNAME Cracking_8_4

#include "base_header.h"

using namespace std;
using namespace Helper;

// -------------------- Program starts here -------------------------
//
// Power Set: Write a method to return all subsets of a set.

class CLASSNAME
{
public:
    CLASSNAME()
    {
        cout << "Running " << VERSION_STRING(CLASSNAME) << "..." << endl;
    }

    // TODO: Use std::set instead of vector (duplicates!!!)

    vector< vector<int> > powerSets01(const vector<int> &set)
    {
        vector< vector<int> > power_sets;

        // empty set is always in power set
        vector<int> curr_subset = {};
        power_sets.push_back(curr_subset);

        // duplication approach: For each entry in the set, copy all current subsets and add the current element to the sets from the copy
        for (int i=0; i<set.size(); i++)
        {
            vector< vector<int>>  curr_powerset_copy = power_sets;
            for (int j=0; j<curr_powerset_copy.size(); j++)
            {
                curr_powerset_copy[j].push_back(set[i]);
                //sort(curr_subset_copy.begin(), curr_subset_copy.end());
                power_sets.push_back(curr_powerset_copy[j]);
            }

        }

        return power_sets;
    }

    vector< vector<int> > powerSets02(const vector<int> &set)
    {
        vector< vector<int> > power_sets;

        // binary approach: treat each set element as a bit in a number from 0 to 2^N - 1. Add it only if bit is 1.
        int num_subsets = pow(2,set.size());
        for (int i=0; i<num_subsets; i++)
        {
            vector<int> curr_subset = {};

            int num = i;
            int set_index = 0;
            while(num > 0)
            {
                if (num%2)
                {
                    curr_subset.push_back(set[set_index]);
                }
                set_index++;
                num = num >> 1;
            }

            power_sets.push_back(curr_subset);
        }


        return power_sets;
    }
};

TEST(CLASSNAME, Test1)
{    
    CLASSNAME instance;

    vector< vector<int> > test_vector;                  vector<size_t>  result_vector;
    test_vector.push_back( {} );                        result_vector.push_back(1);
    test_vector.push_back( {1} );                       result_vector.push_back(2);
    test_vector.push_back( {1, 2} );                    result_vector.push_back(4);
    test_vector.push_back( {1, 2, 3} );                 result_vector.push_back(8);
    test_vector.push_back( {1, 2, 3, 4} );              result_vector.push_back(16);
    test_vector.push_back( {1, 2, 3, 4, 5} );           result_vector.push_back(32);
    test_vector.push_back( {1, 2, 3, 4, 5, 6} );        result_vector.push_back(64);

    for(int i=0; i<test_vector.size(); i++)
    {
        auto curr_power_set_mode_1 = instance.powerSets01(test_vector[i]);
        cout << "For set " << printVec(test_vector[i]) << " there are " << curr_power_set_mode_1.size() << " subsets. " << endl;
        ASSERT_EQ(result_vector[i], curr_power_set_mode_1.size());

        auto curr_power_set_mode_2 = instance.powerSets02(test_vector[i]);
        ASSERT_EQ(result_vector[i], curr_power_set_mode_2.size());
        cout << "--> Same for other calculation method!" << endl << endl;
    }
}

#undef CLASSNAME
