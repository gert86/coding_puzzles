#pragma once

#define CLASSNAME Daily_013

#include "base_header.h"

using namespace std;
using namespace Helper;

// -------------------- Program starts here -------------------------
//
//Given an integer k and a string s, find the length of the longest substring that contains at most k distinct characters.
//
//For example, given s = "abcba" and k = 2, the longest substring with k distinct characters is "bcb".

class CLASSNAME
{
public:
    CLASSNAME()
    {
        cout << "Running " << VERSION_STRING(CLASSNAME) << "..." << endl;
    }

    uint lengthOfLongestSubstring(string str, uint k)
    {
        if (k==0 || str.size() == 0)
            return 0;

        if (str.size() == 1)
            return 1;

        // Note: str.size() is at least 2, k is at least 1



        int left_idx = 0;
        int right_idx = 1;
        std::unordered_set<char> distinct_chars;
        distinct_chars.insert( str[0] );

        int curr_max_length = 1;
        int curr_max_left_idx = 0;
        int curr_max_right_idx = 1;

        while (right_idx < str.length())
        {
            // 1: proceed forward with right_idx as long as k is not exceeded
            distinct_chars.insert( str[right_idx] );
            if (distinct_chars.size() <= k)
            {
                // still ok, memo max values
                if (right_idx - left_idx > curr_max_length)
                {
                    curr_max_length = right_idx - left_idx + 1;
                    curr_max_left_idx = left_idx;
                    curr_max_right_idx = right_idx;
                }
                ++right_idx;
                continue;
            }


            // 2a: Right index went too far; proceed backward with left_idx from there as far as possible
            distinct_chars.clear();
            left_idx = right_idx;
            distinct_chars.insert( str[left_idx] );

            char last_added_char = str[left_idx];
            while (distinct_chars.size() <= k)
            {
                --left_idx;
                distinct_chars.insert( str[left_idx] );
                last_added_char = str[left_idx];
            }

            // 2b: revert the very last step of left_idx so there is no violation and front can proceed
            distinct_chars.erase( distinct_chars.find(last_added_char) );
            ++left_idx;
        }

        cout << "The longest substring goes from " <<  curr_max_left_idx << " to " << curr_max_right_idx
             << " and has length " << curr_max_length << " --> " << QString(str.c_str()).mid(curr_max_left_idx, curr_max_length).toStdString() << endl;

        return curr_max_length;
    }

    // Note: If we used set instead of unordered_set, the complexity for insert and find would be O(logN) instead of O(1).
    //       Since we need no ordering, unordered set is preferred.
};

TEST(CLASSNAME, Test1)
{    
    CLASSNAME instance;

    vector< std::pair<string, uint> > test_vector;                                  vector<uint>  result_vector;
    test_vector.push_back( make_pair<string,int>("abcbbbcccba", 1u) );              result_vector.push_back(3);  // (bbb) or (ccc)
    test_vector.push_back( make_pair<string,int>("abcbbbcccba", 2u) );              result_vector.push_back(9);  // (bcbbbcccb)
    test_vector.push_back( make_pair<string,int>("abcbbbcccba", 3u) );              result_vector.push_back(11); // (abcbbbcccba)

    test_vector.push_back( make_pair<string,int>("DDDabcxDDDxyzxyzxyzdd", 2u) );    result_vector.push_back(5);  // (xDDDx)
    test_vector.push_back( make_pair<string,int>("DDDabcxDDDxyzxyzxyzdd", 3u) );    result_vector.push_back(9);  // (xyzxyzxyz)
    test_vector.push_back( make_pair<string,int>("DDDabcxDDDxyzxyzxyzdd", 4u) );    result_vector.push_back(13); // (xDDDxyzxyzxyz)


    for(int i=0; i<test_vector.size(); i++)
    {
        string str = test_vector[i].first;
        uint k = test_vector[i].second;
        uint longest_substring = instance.lengthOfLongestSubstring(str, k);
        cout << "For str=" << str << " and k=" << k << " the longest substring is " << longest_substring << endl << endl;
        ASSERT_EQ(result_vector[i], longest_substring);
    }
    cout << "----------------------------" << endl;
}

#undef CLASSNAME
