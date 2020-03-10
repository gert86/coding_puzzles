//Given an array of numbers, find the maximum sum of any contiguous subarray of the array.

//For example, given the array [34, -50, 42, 14, -5, 86], the maximum sum would be 137, since we would take elements 42, 14, -5, and 86.

//Given the array [-5, -1, -8, -9], the maximum sum would be 0, since we would not take any elements.

//Do this in O(N) time.

#include<QString>
#include<QStringList>

#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
#include <sstream>

// common includes


using namespace std;

int findMaxSubarray(const vector<int> &array)
{
    vector< pair<int, int> > maxima;
    maxima.resize( array.size() );

    for (int i=0; i<array.size(); i++)
    {
        if (i==0)
        {
            maxima[0] = std::make_pair<int,int>((int)array[0], 0);
        }
        else
        {
            if (maxima[i-1].first <= 0)
            {
                maxima[i] = std::make_pair<int, int>((int)array[i], (int)i);
            }
            else
            {
                maxima[i] = std::make_pair<int, int>((int)(maxima[i-1].first + array[i]), (int)(maxima[i-1].second));
            }
        }
    }

    int curr_max = 0;
    int curr_max_idx = -1;
    for (int i=0; i<maxima.size(); i++)
    {
        if (maxima[i].first > 0)
        {
            if (maxima[i].first > curr_max)
            {
                curr_max = maxima[i].first;
                curr_max_idx = i;
            }
        }
    }

    if (curr_max_idx >= 0)
    {
        cout << "The max sum is " << curr_max << " and it goes from " << maxima[curr_max_idx].second << " to " << curr_max_idx << endl;
    }
    else
    {
         cout << "The max sum is " << curr_max << endl;
    }

    return curr_max;
}



int main(int argc, char *argv[])
{        
    vector<int> vec1 = {34, -50, 42, 14, -5, 86};
    int result1 = findMaxSubarray(vec1);
    cout << "The max subarray sum is " << result1 << endl << endl;   // 137 -> 42 + 14 - 5 + 86

    vector<int> vec2 = {-5, -1, -8, -9};
    int result2 = findMaxSubarray(vec2);
    cout << "The max subarray sum is " << result2 << endl << endl;   // 0

    vector<int> vec3 = {34, -1, -33, 42, -1, -3, -30, 40, -1};
    int result3 = findMaxSubarray(vec3);
    cout << "The max subarray sum is " << result3 << endl << endl;   // 48 -> 42 - 1 - 3 - 30 + 40

    return 0;
}
