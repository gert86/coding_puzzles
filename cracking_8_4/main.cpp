#include<QString>

#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
#include <sstream>
#include <cmath>

// common includes
#include "stack.h"
#include "queue.h"
#include "linkedlist.h"
#include "doublylinkedlist.h"
#include "binarytree.h"
#include "graph.h"

using namespace std;

// Helper method to print a vector of ints
string printVec(const vector<int> &vec)
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


int main(int argc, char *argv[])
{    
    int mode = 1; // 1, 2
    cout << "Mode = " << mode << endl;

    vector< vector<int> > test_vector;
    test_vector.push_back( {} );
    test_vector.push_back( {1} );
    test_vector.push_back( {1, 2} );
    test_vector.push_back( {1, 2, 3} );
    test_vector.push_back( {1, 2, 3, 4} );
    test_vector.push_back( {1, 2, 3, 4, 5} );
    test_vector.push_back( {1, 2, 3, 4, 5, 6} );

    for(int i=0; i<test_vector.size(); i++)
    {


        vector< vector<int> > curr_power_set;
        if (mode == 1) curr_power_set = powerSets01(test_vector[i]);
        if (mode == 2) curr_power_set = powerSets02(test_vector[i]);

        cout << "For set " << printVec(test_vector[i]) << " there are " << curr_power_set.size() << " subsets: " << endl;
        for (int j=0; j<curr_power_set.size(); j++)
        {
            //cout << "####  " << printVec(curr_power_set[j]) << endl;
        }
        cout << endl << endl;
    }
    return 0;
}
