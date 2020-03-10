// You are given an array of non-negative integers that represents a two-dimensional elevation map where each element is unit-width wall and the integer is the height.
// Suppose it will rain and all spots between two walls get filled up.
// Compute how many units of water remain trapped on the map in O(N) time and O(1) space.
// For example, given the input [2, 1, 2], we can hold 1 unit of water in the middle.
// Given the input [3, 0, 1, 3, 0, 5], we can hold 3 units in the first index, 2 in the second, and 3 in the fourth index
// (we cannot hold 5 since it would run off to the left), so we can trap 8 units of water.


#include<QString>

#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
#include <sstream>

// common includes


using namespace std;


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

int calculateVolume(const vector<int> &elevation_vector, int start_index, int end_index)
{
    int count = 0;

    int start = (start_index<end_index) ? start_index : end_index;
    int end   = (start_index<end_index) ? end_index : start_index;
    int min_height = min(elevation_vector[start], elevation_vector[end]);

    for (int i=start+1; i<end; i++)
    {
        if (elevation_vector[i] > min_height)
        {
            cerr << "calculateVolume has wrong data." << endl;
            exit(-1);
        }
        count += (min_height - elevation_vector[i]);
    }

    return count;
}


int searchRight(const vector<int> &elevation_vector, int start_idx)
{
    // This is the STL way
    if (start_idx<0 || start_idx>=elevation_vector.size())
        return -1;

    auto it_from = elevation_vector.begin() + start_idx + 1;
    auto it_to   = elevation_vector.end();   // end is always one too far!
    auto it = max_element(it_from, it_to);

    if (it == it_to)    // the SPECIFIED last iterator is the "not found" indicator!
        return -1;

    //return (it - elevation_vector.begin());           // these two are...
    return distance(elevation_vector.begin(), it);      // ...equivalent

    // Note that in the last statement we need to refer to the absolute begin (not it_from) because we return the absolute index!!!


//    // This is the manual way
//    if (start_idx<0 || start_idx>=elevation_vector.size())
//        return -1;

//    // Find the largest element
//    int largest_val = -1;
//    int largest_idx = -1;
//    for (int i=start_idx+1; i<elevation_vector.size(); i++)
//    {
//        if (elevation_vector[i] >= largest_val)
//        {
//            largest_val = elevation_vector[i];
//            largest_idx = i;
//        }
//    }
//    cout << "For start index " << start_idx << " - Returning " << largest_idx << endl;
//    return largest_idx;
}

int searchLeft(const vector<int> &elevation_vector, int start_idx)
{
    // This is the STL way
    if (start_idx<0 || start_idx>=elevation_vector.size())
        return -1;

    auto it_from = elevation_vector.begin();
    auto it_to   = elevation_vector.begin() + start_idx;   // end is always one too far!
    auto it = max_element(it_from, it_to);

    if (it == it_to)    // the SPECIFIED last iterator is the "not found" indicator!
        return -1;

    //return (it - elevation_vector.begin());           // these two are...
    return distance(elevation_vector.begin(), it);      // ...equivalent

    // Note that in the last statement we need to refer to the absolute begin (not it_from) because we return the absolute index!!!


//    //This is the manual way
//    if (start_idx<0 || start_idx>=elevation_vector.size())
//        return -1;
//
//    // Find the largest element
//    int largest_val = -1;
//    int largest_idx = -1;
//    for (int i=start_idx-1; i>=0; i--)
//    {
//        if (elevation_vector[i] >= largest_val)
//        {
//            largest_val = elevation_vector[i];
//            largest_idx = i;
//        }
//    }
//    return largest_idx;
}


int getNumWaterUnits(const vector<int> &elevation_vector)
{
    if (elevation_vector.size() <= 2)
        return 0;

    int num_units = 0;

    // find the largest element
    int largest_idx = searchRight(elevation_vector, 0);
    int low_idx = largest_idx;
    int high_idx = largest_idx;

    // continuously search to the right side for the next biggest index and calc. volume in between
    while (true)
    {
        int next_high_idx = searchRight(elevation_vector, high_idx);
        if (next_high_idx == -1)
            break;

        num_units += calculateVolume(elevation_vector, high_idx, next_high_idx);
        high_idx = next_high_idx;
    }

    // continuously search to the left side for the next biggest index and calc. volume in between
    while (true)
    {
        int next_low_idx = searchLeft(elevation_vector, low_idx);
        if (next_low_idx == -1)
            break;

        num_units += calculateVolume(elevation_vector, low_idx, next_low_idx);
        low_idx = next_low_idx;
    }

    return num_units;
}

int main(int argc, char *argv[])
{    
    vector< vector<int> > test_vectors;
    vector<int> curr = {2, 1, 2};       test_vectors.push_back(curr);       // 1
    curr = {3, 0, 1, 3, 0, 5};          test_vectors.push_back(curr);       // 8
    curr = {5, 7, 5, 3, 7, 5, 6, 5, 7}; test_vectors.push_back(curr);       // 11
    curr = {};                          test_vectors.push_back(curr);       // 0
    curr = {1, 2, 3};                   test_vectors.push_back(curr);       // 0
    curr = {1, 2, 3, 2};                test_vectors.push_back(curr);       // 0
    curr = {3, 1, 2, 3, 2};             test_vectors.push_back(curr);       // 3

    for (int i=0; i<test_vectors.size(); i++)
    {
        vector<int> current_vector = test_vectors[i];
        int num_water_units = getNumWaterUnits(current_vector);

        cout << "The vector " << printVec(current_vector) << " can trap " << num_water_units << " units of water." << endl;
    }

    return 0;
}
