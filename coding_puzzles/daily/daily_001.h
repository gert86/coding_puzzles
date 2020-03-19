#pragma once

#define CLASSNAME Daily_001

#include "base_header.h"

using namespace std;
using namespace Helper;

// -------------------- Program starts here -------------------------
//
// Given a list of numbers and a number k, return whether any two numbers from the list add up to k.
// For example, given [10, 15, 3, 7] and k of 17, return true since 10 + 7 is 17.
// Bonus: Can you do this in one pass?

#include<QString>
#include<QPair>

using TestPair = QPair< std::vector<int>, int >;

class CLASSNAME
{
public:
    CLASSNAME()
    {
        cout << "Running " << VERSION_STRING(CLASSNAME) << "..." << endl;
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

};

TEST(CLASSNAME, Mode1)
{
    CLASSNAME instance;

    // Note: Using 2 vectors instead of a map, to keep the insertion order
    std::vector<TestPair>  test_vector;                                         vector<bool>  result_vector;
    test_vector.push_back(TestPair({10, 15, 3, 7}, 17));        result_vector.push_back(true);
    test_vector.push_back(TestPair({10, 15, 3, 7}, 13));        result_vector.push_back(true);
    test_vector.push_back(TestPair({10, 15, -1, 0},10));        result_vector.push_back(true);
    test_vector.push_back(TestPair({10, 15, -1, 0}, 9));        result_vector.push_back(true);
    test_vector.push_back(TestPair({10, 15, -1, 8}, 8));        result_vector.push_back(false);

    for (int i=0; i<test_vector.size(); i++)
    {
        TestPair pair = test_vector[i];
        bool result = instance.calculateResult1(pair.first, pair.second);
        cout << "Test #" << i << " Array is " << printVec(pair.first) << "; k = " << pair.second << "; Result = " << (result ? ("true") : ("false")) << endl << endl;
        ASSERT_EQ(result_vector[i], result);
    }
}
#undef CLASSNAME
