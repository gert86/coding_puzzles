#include<QString>

#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
#include <sstream>

using namespace std;

// Helper method to print a vector of strings
string printVec(const vector<string> &vec)
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


int main(int argc, char *argv[])
{    
    vector<string> original = {"A", "ABBA", "CCD","AA", "BAAB", "DCC", "AABB", "FF", "", "ABAB", "CC", "", "D", "AB"};
    cout << "The original vector is: " << printVec(original) << endl;

    vector<string> sorted_by_anagrams;
    sortByAnagrams(original, sorted_by_anagrams);

    cout << "The sorted vector is: " << printVec(sorted_by_anagrams) << endl;


    return 0;
}
