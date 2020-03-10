// Given a list of numbers and a number k, return whether any two numbers from the list add up to k.
//
//For example, given [10, 15, 3, 7] and k of 17, return true since 10 + 7 is 17.

//Bonus: Can you do this in one pass?


#include<QString>
#include<QPair>

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <numeric>
#include <unordered_set>

using namespace std;

typedef QPair<std::vector<int>, int>  TestPair;

// Helper method to print a vector of ints
string printVec(const vector<int> &vec)
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

// Variant 1:
// If we are allowed to sort the array, we can then iterate from the first and last position and move either first ptr (if result too low) or last ptr (if result too high).
// When result matches k we return true; If the pointers meet, we return false;
// This method takes O(NlogN) time but O(1) space.

bool calculateResult1(std::vector<int> array, int k)
{
    // sort array
    std::sort(array.begin(), array.end());

    int i = 0;
    int j = array.size() - 1;

    while(i < j)
    {
        if (array[i] + array[j] == k)
        {
            // found pair
            cout << "Found match of element " << array[i] << " and  " << array[j] << " that sum up to " << k << endl;
            return true;
        }

        if (array[i] + array[j] > k)
        {
            j--;
        }
        else
        {
            i++;
        }
    }

    cout << "Did not find two elements that sum up to " << k << endl;
    return false;
}

// Variant 2:
// Put every element in a hash set on iteration. Before putting it there, check if the complementary element (that adds up with current element to k) exists and return true if so.
// Return false when the end of the array was reached.
// This method takes O(N) time but O(N) space.
bool calculateResult2(std::vector<int> array, int k)
{    
    std::unordered_set<int> hashset;

    for (int i=0; i<array.size(); i++)
    {
        auto got = hashset.find(k - array[i]);
        if (got != hashset.end())
        {
            cout << "Found match of element " << array[i] << " and previously seen element " << *got << " that sum up to " << k << endl;
            return true;
        }

        hashset.insert(array[i]);
    }

    cout << "Did not find two elements that sum up to " << k << endl;
    return false;
}

int main()
{
    int mode = 1; // 1, 2
    cout << "Mode = " << mode << endl;

    vector<int> test01 = {10, 15, 3, 7};
    int         k01    = 17;

    vector<int> test02 = {10, 15, 3, 7};
    int         k02    = 13;

    vector<int> test03 = {10, 15, -1, 0};
    int         k03    = 10;

    vector<int> test04 = {10, 15, -1, 0};
    int         k04    = 9;

    vector<int> test05 = {10, 15, -1, 8};
    int         k05    = 8;

    vector<TestPair>  test_vector;
    test_vector.push_back( TestPair(test01, k01) );   // true
    test_vector.push_back( TestPair(test02, k02) );   // true
    test_vector.push_back( TestPair(test03, k03) );   // true
    test_vector.push_back( TestPair(test04, k04) );   // true
    test_vector.push_back( TestPair(test05, k05) );   // false


    for (int i=0; i<test_vector.size(); i++)
    {
        TestPair pair = test_vector[i];
        int result = 0;
        if (mode == 1)  result = calculateResult1(pair.first, pair.second);
        if (mode == 2)  result = calculateResult2(pair.first, pair.second);

        cout << "Test #" << (i+1) << " Array is " << printVec(pair.first) << "; k = " << pair.second << "; Result = " << (result ? ("true") : ("false")) << endl << endl;
    }
    return 0;
}

