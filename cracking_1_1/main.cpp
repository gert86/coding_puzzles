#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>

using namespace std;


// Implement an algorithm to determine if a string has all unique characters



string example_str1 = "abcdefgzyxwv123459876";   // true
string example_str2 = "abcdefgzyxwv1234598c6";   // false


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

int main(int argc, char *argv[])
{    
    //bool str1_unique = hasAllUniqueCharacters(example_str1);
    //bool str1_unique = hasAllUniqueCharactersWithoutAdditionalData(example_str1);
    bool str1_unique = hasAllUniqueCharactersUsingSTL(example_str1);
    cout << "String 1 has " << (str1_unique ? "ALL UNIQUE" : "NOT UNIQUE") << " characters" << endl;


    //bool str2_unique = hasAllUniqueCharacters(example_str2);
    //bool str2_unique = hasAllUniqueCharacters(example_str2);
    bool str2_unique = hasAllUniqueCharactersUsingSTL(example_str2);
    cout << "String 2 has " << (str2_unique ? "ALL UNIQUE" : "NOT UNIQUE") << " characters" << endl;


    return 0;
}
