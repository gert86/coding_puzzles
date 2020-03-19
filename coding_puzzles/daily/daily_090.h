#pragma once

#define CLASSNAME Daily_090

#include "base_header.h"

using namespace std;
using namespace Helper;

// -------------------- Program starts here -------------------------
//
// Given an integer n and a list of integers l, write a function that randomly generates
// a number from 0 to n-1 that isn't in l (uniform).

class CLASSNAME
{
public:
    CLASSNAME()
    {
        cout << "Running " << VERSION_STRING(CLASSNAME) << "..." << endl;
    }


    int randomNumberNotFromList(int N, const vector<int> &l)
    {
        // Put all forbidden vals into a hash-set...
        std::unordered_set<int> forbidden_values;
        for (int i : l)
            forbidden_values.insert(i);

        // ... OR ...

        // ...make a unique vector (must be sorted first!)
        // HOWEVER, THIS SHOULD NOT BE USED BECAUSE FIND OPERATION WOULD TAKE LINEAR TIME (AND NEEDS MANUAL IMPLEMENTATION)!
        //std::vector<int> forbidden_values = l;
        //std::sort(forbidden_values.begin(), forbidden_values.end());
        //std::unique(forbidden_values.begin(), forbidden_values.end());


        // Calc. how many numbers can be omitted in random number generation
        int num_forbidden = forbidden_values.size();
        int N_reduced = N - num_forbidden;

        // Calculate random number
        random_device generator;              // this one uses "real" randomness but is not supported on all platforms
        std::uniform_int_distribution<int> distribution(0, N_reduced - 1);
        int rand_num = distribution(generator);


        // Map back the random number to its original range (excluding forbidden values)
        int num_valid = -1;
        for (int i=0; i<N; i++)
        {
            if (forbidden_values.find(i) == forbidden_values.end())
                num_valid++;

            if (num_valid == rand_num)
                return i;
        }

        cerr << "This should not happen..." << endl;
        return -1;
    }
};

TEST(CLASSNAME, Test1)
{    
    CLASSNAME instance;

    vector<int> l = {1,2,3,1};
    int N = 10;

    vector<int> histogram;
    histogram.resize(N);

    int NUM_RUNS = 100000;
    for (int i=0; i<NUM_RUNS; i++)
    {
        int num = instance.randomNumberNotFromList(N, l);
        //cout << "The random number is " << num << endl;
        ASSERT_TRUE(num >= 0);
        ASSERT_TRUE(num < N);
        ASSERT_TRUE(std::find(l.begin(), l.end(), num) == l.end());  // must not be from list
        histogram[num]++;
    }

    // Check overall result
    cout << "----" << endl;
    for (int i=0; i<N; i++)
    {
        cout << "The value " << i << " was returned " << histogram[i] << " times." << endl;

        if (std::find(l.begin(), l.end(), i) != l.end())
        {
            // values from list must never occur
            ASSERT_EQ(0, histogram[i]);
        }
        else
        {
            // other values must occur approx. equally often.
            int num_excluded_numbers = 3;  // Note: It is surprisingly complicated to determine the number of unique elements in l!!!
            int num_remaining_numbers = N - num_excluded_numbers;
            int expected_occurrences = static_cast<int>(NUM_RUNS/num_remaining_numbers);
            ASSERT_NEAR(expected_occurrences, histogram[i], expected_occurrences*0.05);  // allow 5% deviation
        }
    }
    cout << "----" << endl;
}

#undef CLASSNAME
