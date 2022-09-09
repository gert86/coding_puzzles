#pragma once

#define CLASSNAME Daily_035

#include "base_header.h"

using namespace std;
using namespace Helper;

// -------------------- Program starts here -------------------------
//
// Given an array of strictly the characters 'R', 'G', and 'B', segregate the values of the array so that all the Rs come first, the Gs come second, and the Bs come last.
// You can only swap elements of the array.
// Do this in linear time and in-place.
//
// For example, given the array ['G', 'B', 'R', 'R', 'B', 'R', 'G'], it should become ['R', 'R', 'R', 'G', 'G', 'B', 'B'].


// Strategy:
// First round:  swap non-R vs. R so that all R's are left
// Second round: swap non-G vs. G so that all G's are left (starting at the first non-R position)

class CLASSNAME
{
public:
    CLASSNAME()
    {
        cout << "Running " << VERSION_STRING(CLASSNAME) << "..." << endl;
    }



    void sortElements(vector<char> &container, int mode)
    {
        if (container.size() <= 1)
            return;

        // Mode 1: Using normal access with operator[]
        if (mode==1)
        {
            int lower_idx = 0;
            int upper_idx = container.size() - 1;

            // first round:
            // lower: starts at 0
            // upper: starts at "last element"
            // whenever upper it finds an 'R' and lower it finds anything other than 'R' --> swap
            while(lower_idx < upper_idx)
            {
                if (container[upper_idx]=='R' && container[lower_idx]!='R')
                {
                    container[upper_idx] = container[lower_idx];
                    container[lower_idx] = 'R';
                }

                // find upper R
                if (container[upper_idx]!='R')
                    --upper_idx;

                // find lower non-R
                if (container[lower_idx]=='R')
                    ++lower_idx;
            }

            // all 'R' are now before all other elements


            // second round:
            // lower: starts "after" last 'R'
            // upper: starts at "last element"
            // whenever upper it finds an 'G' and lower it finds anything other than 'G' --> swap
            if (container[lower_idx] == 'R')
                ++lower_idx;
            upper_idx = container.size() - 1;
            while(lower_idx < upper_idx)
            {
                if (container[upper_idx]=='G' && container[lower_idx]!='G')
                {
                    container[upper_idx] = container[lower_idx];
                    container[lower_idx] = 'G';
                }

                // find upper G
                if (container[upper_idx]!='G')
                    --upper_idx;

                // find lower non-G
                if (container[lower_idx]=='G')
                    ++lower_idx;
            }
        }

        // Mode 2: Using STL iterators
        if (mode==2)
        {
            auto lower_it = container.begin();
            auto upper_it = container.end() - 1;

            // Note to myself: The need to set the upper iterator one element after the end is only necessary if we use
            //                 STL functions like find or max_element, that assume an interval of [lower_it, upper_it)  !!!

            // first round:
            // lower: starts at 0
            // upper: starts at "last element"
            // whenever upper it finds an 'R' and lower it finds anything other than 'R' --> swap
            while(lower_it < upper_it)
            {
                if (*upper_it=='R' && *lower_it!='R')
                {
                    char temp = *lower_it;
                    *lower_it = *upper_it;
                    *upper_it = temp;
                }

                // find upper R
                if (*upper_it!='R')
                    --upper_it;

                // find lower non-R
                if (*lower_it=='R')
                    ++lower_it;
            }

            // second round:
            // lower: starts "after last 'R'"
            // upper: starts at "last element"
            // whenever upper it finds an 'G' and lower it finds anything other than 'G' --> swap
            if (*lower_it == 'R')
                ++lower_it;
            upper_it = container.end() - 1;
            while(lower_it < upper_it)
            {
                if (*upper_it=='G' && *lower_it!='G')
                {
                    char temp = *lower_it;
                    *lower_it = *upper_it;
                    *upper_it = temp;
                }

                // find upper G
                if (*upper_it!='G')
                    --upper_it;

                // find lower non-G
                if (*lower_it=='G')
                    ++lower_it;
            }
        }
    }
};

TEST(CLASSNAME, Test1)
{    
    CLASSNAME instance;

    vector< vector<char> > test_vector;
    test_vector.push_back({'G', 'B', 'R', 'R', 'B', 'R', 'G'});
    test_vector.push_back({'G', 'B', 'R', 'R', 'B', 'R', 'G', 'G', 'B', 'R', 'R', 'B', 'R', 'G', 'G', 'B', 'R', 'R', 'B', 'R', 'G'});

    vector< vector<char> > result_vector;
    result_vector.push_back({'R', 'R', 'R', 'G', 'G', 'B', 'B'});
    result_vector.push_back({'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'G', 'G', 'G', 'G', 'G', 'G', 'B', 'B', 'B', 'B', 'B', 'B'});

    for (int i=0; i<test_vector.size(); i++)
    {
        vector<char> current_vector_mode1 = test_vector[i];
        vector<char> current_vector_mode2 = test_vector[i];

        // Mode 1
        cout << "Before sorting: " << printVec(current_vector_mode1) << endl;
        instance.sortElements(current_vector_mode1, 1);
        cout << "After sorting: " << printVec(current_vector_mode1) << endl;
        ASSERT_EQ(result_vector[i], current_vector_mode1);

        // Mode 2
        instance.sortElements(current_vector_mode2, 2);
        ASSERT_EQ(result_vector[i], current_vector_mode2);
        cout << "--> same for mode 2" << endl << endl;
    }
}

#undef CLASSNAME
