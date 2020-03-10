// Given a sorted list of integers, square the elements and give the output in sorted order.
// For example, given [-9, -2, 0, 2, 3], return [0, 4, 4, 9, 81].



#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
#include <sstream>


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

int main(int argc, char *argv[])
{
    int mode = 2; // 1, 2
    vector<int> my_vec = {-9, -2, 0, 2, 3};

    if (mode == 1)    std::transform(my_vec.begin(), my_vec.end(), my_vec.begin(), [](int x){return x*x;});                   // variant 1 with unary operator (=lambda)
    if (mode == 2)    std::transform(my_vec.begin(), my_vec.end(), my_vec.begin(), my_vec.begin(), std::multiplies<int>());   // variant 2 with binary operator (multiply)
    std::sort(my_vec.begin(), my_vec.end());

    cout << "Mode = " << mode << endl;
    cout << "The squared and sorted vector is " << printVec(my_vec)  << endl;

    return 0;
}
