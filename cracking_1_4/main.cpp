#include<QString>

#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>

using namespace std;

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



int main()
{
    string str1 = "aabbbaa";    // true
    string str2 = "aaaabba";    // true
    string str3 = "aabbaac";    // true
    string str4 = "aabbbaaa";   // false
    string str5 = "aabbccca";   // false

    std::cout << "Comparison is " << isPalindromePermutation(str1) << std::endl;
    std::cout << "Comparison is " << isPalindromePermutation(str2) << std::endl;
    std::cout << "Comparison is " << isPalindromePermutation(str3) << std::endl;
    std::cout << "Comparison is " << isPalindromePermutation(str4) << std::endl;
    std::cout << "Comparison is " << isPalindromePermutation(str5) << std::endl;

    return 0;
}
