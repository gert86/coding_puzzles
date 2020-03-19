#pragma once

#define CLASSNAME Cracking_10_2

#include "base_header.h"

using namespace std;
using namespace Helper;

// -------------------- Program starts here -------------------------
//
// Group Anagrams: Write a method to sort an array of strings so that all the anagrams are next to
// each other.

class CLASSNAME
{
public:
    CLASSNAME()
    {
        cout << "Running " << VERSION_STRING(CLASSNAME) << "..." << endl;
    }

    void sortByAnagrams(const vector<string> &original, vector<string> &sorted_vector)
    {
        sorted_vector = original;

        std::sort(sorted_vector.begin(), sorted_vector.end(),
                  [](string a, string b)
                    {
                        sort(a.begin(),a.end());
                        sort(b.begin(), b.end());
                        return a < b;
                    } );
    }
};

TEST(CLASSNAME, Test1)
{    
    CLASSNAME instance;

    vector<string> original = {"A", "ABBA", "CCD","AA", "BAAB", "DCC", "AABB", "FF", "", "ABAB", "CC", "", "D", "AB"};
    cout << "The original vector is: " << printVec(original) << endl;

    vector<string> sorted_by_anagrams;
    instance.sortByAnagrams(original, sorted_by_anagrams);
    cout << "The vector sorted by anagram is: " << printVec(sorted_by_anagrams) << endl;

    vector<string> expected_result{"", "", "A", "AA", "ABBA", "BAAB", "AABB", "ABAB", "AB", "CC", "CCD", "DCC", "D", "FF"};
    ASSERT_EQ(expected_result, sorted_by_anagrams);
}

#undef CLASSNAME
