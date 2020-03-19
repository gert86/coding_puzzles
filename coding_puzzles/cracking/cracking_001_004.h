#pragma once

#define CLASSNAME Cracking_1_4

#include "base_header.h"

using namespace std;
using namespace Helper;

// -------------------- Program starts here -------------------------
//
// Palindrome Permutation: Given a string, write a function to check if it is a permutation of a palindrome.
// A palindrome is a word or phrase that is the same forwards and backwards. A permutation is a rearrangement of letters.
// The palindrome does not need to be limited to just dictionary words.
//
// EXAMPLE:
// Input: Tact Coa
// Output: True (permutations:"taco cat'; "atco cta'; etc.)

class CLASSNAME
{
public:
    CLASSNAME()
    {
        cout << "Running " << VERSION_STRING(CLASSNAME) << "..." << endl;
    }

    bool isPalindromePermutation(string str)
    {
        // Assumption: Only ASCII characters (otherwise use hash table instead of bitvector)

        // If only lowercase letters a-z, then one int can be used as bv instead (has 32 bits)

        bool bv[128];
        for (int i=0; i<128; i++)
            bv[i] = false;

        for (int i=0; i<str.length(); i++)
        {
            int char_as_int = static_cast<int>(str.at(i));
            if (char_as_int < 0 || char_as_int > 127)
            {
                cerr << "The given string contains non-ASCII characters. Returning false." << endl;
                return false;
            }

            bv[char_as_int] = !bv[char_as_int];  // toggle
        }

        bool found_one = false;
        for (int i=0; i<128; i++)
        {
            if (bv[i])
            {
                if(!found_one)
                    found_one = true;
                else
                    return false;  // found the second, so it cannot be a palindrome
            }
        }

        return true;
    }
};

TEST(CLASSNAME, Test1)
{    
    CLASSNAME instance;

    vector<string>  test_vector;        vector<int>  result_vector;
    test_vector.push_back("aabbbaa");   result_vector.push_back(true);
    test_vector.push_back("aaaabba");   result_vector.push_back(true);
    test_vector.push_back("aabbaac");   result_vector.push_back(true);
    test_vector.push_back("aabbbaaa");  result_vector.push_back(false);
    test_vector.push_back("aabbccca");  result_vector.push_back(false);

    for (int i=0; i<test_vector.size(); i++)
    {
        bool is_pal_perm = instance.isPalindromePermutation( test_vector[i] );
        std::cout << "Result for " << test_vector[i] << " is " << is_pal_perm << std::endl;
        ASSERT_EQ(result_vector[i], is_pal_perm);
    }
}

#undef CLASSNAME
