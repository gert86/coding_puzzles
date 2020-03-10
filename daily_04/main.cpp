// Given an array of integers, find the first missing positive integer in linear time and constant space.
// In other words, find the lowest positive integer that does not exist in the array.
// The array can contain duplicates and negative numbers as well.
//
// For example, the input [3, 4, -1, 1] should give 2. The input [1, 2, 0] should give 3.
//
// You can modify the input array in-place.

#include<QString>
#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>

using namespace std;



// Note to myself: Why did I make this so complicetd???
// The simplified version does the job better, so forget about this one...
int find_missing_int(std::vector<int> array)
{

    // first run: find out min, max, num_elements and whether 0 is contained. Also set all negative elements to zero
    int num_elements = 0;
    int min_el = std::numeric_limits<int>::max();
    int max_el = std::numeric_limits<int>::min();
    bool found_one = false;
    for (auto it=array.begin(); it != array.end(); ++it)
    {
        num_elements++;
        int num = *it;

        if( num==1 )
        {
            found_one = true;
            continue;
        }

        if (num <= 0)
        {
            *it = 0;
            continue;
        }

        if (num < min_el)
        {
            min_el = num;
        }

        if (num > max_el)
        {
            max_el = num;
        }
    }
    cout << "After first run: num_elements=" << num_elements << ", min=" << min_el << ", max=" << max_el << ", found_one=" << found_one << endl;
    if (!found_one)         return 1;   // trivial case
    if (num_elements <= 1)  return 2;   // trivial case


    // second run: We now have all positive integers and we can ignore values 0 and 1 because they were already found.
    // for every positive integer N, mark it as found by setting array[N] to -array[N] (or to -1 if array[N] is 0).
    for (auto it=array.begin(); it != array.end(); ++it)
    {
        int num = abs(*it);

        if (num <= 1)               continue; // we know that 0 and 1 exists already
        if (num >= num_elements)    continue; // too big

        // mark position by setting entry negative
        //cout << "#### Marking array[" << num << "] as negative  --> ";
        if (array[num]==0)
        {
            array[num]=-1;
        }
        else if (array[num] > 0)
        {
            array[num] = -array[num];
        }
        //cout << " is now " << array[num] << " ####" << endl;
    }


    // third run: Find the first index with a non negative number
    int index = -1;
    for (auto it=array.begin(); it != array.end(); ++it)
    {
        index++;
        if (index==0 || index==1)
        {
           continue;
        }

        if (*it >= 0)
        {
            return index;
        }
    }

    return num_elements;   // found no missing number so it must be num_elements
}



int find_missing_int_simple(std::vector<int> array)
{
    // edge case
    if (array.empty())
        return 1;

    // sort the array
    std::sort(array.begin(), array.end());

    for (int i=0; i<array.size(); i++)
    {
        if (i==0)
        {
            // if we start >1, then 1 is obviously missing
            if (array[0] > 1)
                return 1;
        }
        else
        {
            // values <= 0 are not of interest
            // we can also skip 1, because if 1 is missing this will be detected in the next step
            if (array[i] <= 1)
                continue;

            // we found a gap
            if ( (array[i] != array[i-1]) && (array[i] != array[i-1] + 1) )
            {
                return array[i-1] + 1;
            }
        }
    }

    int last = array.back();
    if (last <= 0)
    {
        // array contains no positive ints, so 1 is already missing
        return 1;
    }

    // there was no gap, so the next number is the first missing one
    return last + 1;

}


int main()
{
    vector<int> test01 = {3, 4, -1, 1};                                                         // 2
    vector<int> test02 = {1, 2, 0};                                                             // 3
    vector<int> test03 = {9, 8, -1, 6, 13, 0, 2, 1, 3, 4, 5, 5, 7, -6, 12, -9, 11};             // 10
    vector<int> test04 = {2,1,100,-1,-1,-1,3,5,4};                                              // 6
    vector<int> test05 = {};                                                                    // 1
    vector<int> test06 = {-1};                                                                  // 1
    vector<int> test07 = {0};                                                                   // 1
    vector<int> test08 = {1};                                                                   // 2
    vector<int> test09 = {1,2};                                                                 // 3  --> hier ist noch ein Fehler in find_missing_int!
    vector<int> test10 = {1,-2};                                                                // 2


    vector< vector<int>>  test_vector;
    test_vector.push_back(test01);
    test_vector.push_back(test02);
    test_vector.push_back(test03);
    test_vector.push_back(test04);
    test_vector.push_back(test05);
    test_vector.push_back(test06);
    test_vector.push_back(test07);
    test_vector.push_back(test08);
    test_vector.push_back(test09);
    test_vector.push_back(test10);


    for (int i=0; i<test_vector.size(); i++)
    {
        int missing_int = find_missing_int_simple( test_vector[i] );
        cout << "Test #" << (i+1) << " results in " << missing_int << endl << endl;
    }

    return 0;
}

