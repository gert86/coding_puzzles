#pragma once

#define CLASSNAME Cracking_1_1

#include "base_header.h"

using namespace std;
using namespace Helper;

// -------------------- Program starts here -------------------------
//
// Is Unique: Implement an algorithm to determine if a string has all unique characters

class CLASSNAME
{
public:
    CLASSNAME()
    {
        cout << "Running " << VERSION_STRING(CLASSNAME) << "..." << endl;
    }

    bool hasAllUniqueCharacters(const string &str)
    {
        // TODO: Check if only ASCII characters  (assume this is true)

        // init
        bool bv[128];
        for (int i=0; i<128; i++)
        {
            bv[i] = false;
        }

        for (int i=0; i<str.length(); ++i)
        {
            char current_char = str.at(i);
            int char_as_int = static_cast<int>( current_char );

            if (char_as_int < 0 || char_as_int >= 128)
            {
                cerr << "The character " << current_char << " is not an ASCII character. Ignoring it." << endl;
            }

            if (bv[char_as_int]==true)
            {
                cout << "Character " << current_char << " occuring at least twice." << endl;
                return false;
            }

            bv[char_as_int]=true;
        }

        return true;
    }

    bool hasAllUniqueCharactersWithoutAdditionalData(string str)
    {
        std::sort(str.begin(), str.end());

        for (int i=0; i<str.length(); ++i)
        {
            if (i==0)
                continue;

            if (str.at(i) == str.at(i-1))
            {
                cout << "Character " << str.at(i) << " occuring at least twice." << endl;
                return false;
            }
        }

        return true;
    }

    bool hasAllUniqueCharactersUsingSTL(string str)
    {
        int orig_size = str.size();

        std::sort(str.begin(), str.end());
        str.erase( std::unique(str.begin(), str.end()), str.end() );  // remove duplicates

        int unique_size = str.size();

        if (orig_size != unique_size)
        {
            cout << "Found " << (orig_size- unique_size) << " duplicate(s) in the string." << endl;
            return false;
        }

        return true;
    }
};

TEST(CLASSNAME, TestTrue)
{    
    CLASSNAME instance;

    string example_str = "abcdefgzyxwv123459876";   // true

    bool str_unique_normal  = instance.hasAllUniqueCharacters(example_str);
    bool str_unique_inplace = instance.hasAllUniqueCharactersWithoutAdditionalData(example_str);
    bool str_unique_stl     = instance.hasAllUniqueCharactersUsingSTL(example_str);

    cout << "String has " << (str_unique_normal ? "ALL UNIQUE" : "NOT UNIQUE") << " characters" << endl;

    ASSERT_EQ(true, str_unique_normal);
    ASSERT_EQ(true, str_unique_inplace);
    ASSERT_EQ(true, str_unique_stl);
}

TEST(CLASSNAME, TestFalse)
{
    CLASSNAME instance;

    string example_str = "abcdefgzyxwv1234598c6";   // false

    bool str_unique_normal  = instance.hasAllUniqueCharacters(example_str);
    bool str_unique_inplace = instance.hasAllUniqueCharactersWithoutAdditionalData(example_str);
    bool str_unique_stl     = instance.hasAllUniqueCharactersUsingSTL(example_str);

    cout << "String has " << (str_unique_normal ? "ALL UNIQUE" : "NOT UNIQUE") << " characters" << endl;

    ASSERT_EQ(false, str_unique_normal);
    ASSERT_EQ(false, str_unique_inplace);
    ASSERT_EQ(false, str_unique_stl);
}

#undef CLASSNAME
