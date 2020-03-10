#include<QString>

#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
#include <sstream>

using namespace std;

// Helper method to print a vector of strings
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

int findInRotatedArray(const vector<int> &array, int value, int start_idx, int end_idx)
{
    // not found
    if (start_idx > end_idx)
        return -1;

    // implement special variant of binary search
    int mid_idx = (start_idx + end_idx)/2;

    if (array[mid_idx] == value)
    {
        // found
        return mid_idx;
    }

    if (value < array[mid_idx] || (value > array[mid_idx] && value > array[end_idx]))
    {
        // search left
        return findInRotatedArray(array, value, start_idx, mid_idx - 1);
    }

    if (value > array[mid_idx] || (value < array[mid_idx] && value < array[start_idx]))
    {
        // search right
        return findInRotatedArray(array, value, mid_idx + 1, end_idx);
    }


    // will never be reached
    return -2;
}


int main(int argc, char *argv[])
{    
    vector<int> array = {15,16,19,20,25,1,3,4,5,7,10,14};
    cout << "The original vector is: " << printVec(array) << endl;

    int search_value = 5;
    int index = findInRotatedArray(array, search_value, 0, array.size() - 1);

    cout << "The index of value " << search_value << " is " << index << endl;


    return 0;
}
