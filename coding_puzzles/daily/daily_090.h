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

    // Option 1:
    // if the list is small compared to N and/or l changes often, consider to retry until number not in l is drawn

    // Option 2:
    // if the number of possible options is very sparse and/or l never changes, consider to draw from N-uniqElem(l)
    // and have a mapping to the correct available number


    // N=7
    // l=1,2,6
    //mapping[0] = 0
    //mapping[1] = 3
    //mapping[2] = 4
    //mapping[3] = 5

    void printMap(const std::map<int, int> &myMap)
    {
      for (const auto &[key,val] : myMap) {
        std::cout << "map[" << key << "] = " << val << std::endl;
      }
    }

    int randomNumberNotFromList(int N, std::vector<int> l)
    {
      // Optimization: The mapping needs to be calculated only once
      std::map<int, int> mapping;
      std::set<int> mySet(l.begin(), l.end());
      int numInvalids = 0;
      for (size_t i=0; i<N; i++) {
        if (mySet.find(i) != mySet.end())
          numInvalids++;
        else
          mapping[i-numInvalids] = i;
      }
      //printMap(mapping);

      // get random value between 0 and N-l.sze()
      static std::default_random_engine generator;
      generator.seed(std::chrono::system_clock::now().time_since_epoch().count());
      static std::uniform_int_distribution<int> distribution(0,N-mySet.size()-1);
      int randomVal = distribution(generator);

      return mapping[randomVal];
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
