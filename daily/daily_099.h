#pragma once

#define CLASSNAME Daily_099

#include "base_header.h"

using namespace std;
using namespace Helper;

// -------------------- Program starts here -------------------------
//
// Given an unsorted array of integers, find the length of the longest consecutive elements sequence.
// For example, given [100, 4, 200, 1, 3, 2], the longest consecutive element sequence is [1, 2, 3, 4]. Return its length: 4.
// Your algorithm should run in O(n) complexity.


// Strategy:
// Iterate over each value and insert into hash map with value 1 if not yet exists (or continue if exists).
// If it has no predecessor, the value 1 is already correct (new sequence)
// If there is a predecessor, then set value to the predecessors value + 1 (sequence was extended by 1)
// Then find existing successors and set their value to (val+1), (val+2), ...

bool compare(const pair<int, int>&a, const pair<int, int>&b)
{
   return a.second < b.second;
}


class CLASSNAME
{
public:
    CLASSNAME()
    {
        cout << "Running " << VERSION_STRING(CLASSNAME) << "..." << endl;
    }

    int getLongestConsecutiveSequence(const vector<int> &array)
    {
        if (array.size() == 0)
            return 0;

        unordered_map<int, int> hash_map;
        for (int key : array) {
            if (hash_map.find(key) != hash_map.end()) {
                continue;
            }
            else {
                hash_map[key] = 1;

                // if this value has a predecessor, then the current value extended this sequence by 1
                // otherwise its a new sequence that starts here
                if(hash_map.find(key-1) != hash_map.end()) {
                  hash_map[key] = hash_map[key-1] + 1;
                }


                // iterate over all direct successors and increment their value to val + i
                int curr_successor_key = key + 1;
                int index_diff = 1;
                while(hash_map.find(curr_successor_key) != hash_map.end())
                {
                    hash_map[curr_successor_key] = hash_map[key] + index_diff;
                    curr_successor_key++;
                    index_diff++;
                }
            }
        }

        // return max. value from hash map
        return max_element(hash_map.begin(), hash_map.end(), compare)->second;
    }

};

TEST(CLASSNAME, Test1)
{    
    CLASSNAME instance;

    vector<int> array = {100, 4, 200, 1, 3, 2};
    int longest_seq = instance.getLongestConsecutiveSequence(array);
    cout << "The longest consecutive sequence is " << longest_seq << endl;
    ASSERT_EQ(4, longest_seq);
}

#undef CLASSNAME
