// Given an array of strictly the characters 'R', 'G', and 'B', segregate the values of the array so that all the Rs come first, the Gs come second, and the Bs come last.
// You can only swap elements of the array.
// Do this in linear time and in-place.
//
// For example, given the array ['G', 'B', 'R', 'R', 'B', 'R', 'G'], it should become ['R', 'R', 'R', 'G', 'G', 'B', 'B'].


#include<QString>

#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
#include <sstream>

// common includes


using namespace std;


// Helper method to print a vector of chars
string printVec(const vector<char> &vec)
{
    stringstream ss;
    ss << "[";
    for (int i=0; i<vec.size(); i++)
    {
        ss << vec[i];
        if (i != vec.size()-1)
        {
            ss << ", ";
        }
    }
    ss << "]";

    return ss.str();
}


void sortElements(vector<char> &container, int mode)
{
    if (container.size() <= 1)
        return;


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


int main(int argc, char *argv[])
{    
    int mode = 2; // 1, 2
    cout << "Mode = " << mode << endl << endl;

    vector< vector<char> > test_vectors;
    vector<char> curr = {'G', 'B', 'R', 'R', 'B', 'R', 'G'};       test_vectors.push_back(curr);
    curr = {'G', 'B', 'R', 'R', 'B', 'R', 'G', 'G', 'B', 'R', 'R', 'B', 'R', 'G', 'G', 'B', 'R', 'R', 'B', 'R', 'G'};       test_vectors.push_back(curr);

    for (int i=0; i<test_vectors.size(); i++)
    {
        vector<char> current_vector = test_vectors[i];
        cout << "Before sorting: " << printVec(current_vector) << endl;
        sortElements(current_vector, mode);
        cout << "After sorting: " << printVec(current_vector) << endl << endl;
    }

    return 0;
}
