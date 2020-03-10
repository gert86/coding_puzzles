//Given a list of integers, write a function that returns the largest sum of non-adjacent numbers. Numbers can be 0 or negative.
//
//For example, [2, 4, 6, 2, 5] should return 13, since we pick 2, 6, and 5. [5, 1, 1, 5] should return 10, since we pick 5 and 5.
//
//Follow-up: Can you do this in O(N) time and constant space?


#include <iostream>
#include <vector>


using namespace std;

int maximumSum(const std::vector<int> &vec)
{
    if (vec.size() == 0)
        return 0;

    if (vec.size() == 1)
        return vec[0];

    if (vec.size() == 2)
        return max(vec[0], vec[1]);

    int max_prev_prev = vec[0];               // maximum that can be reached without prev. element
    int max_prev      = max(vec[0], vec[1]);  // maximum that can be reached with prev. element


    int max_to_here = 0;
    for (int i=2; i<vec.size(); i++)
    {
        max_to_here = max(max_prev, max_prev_prev + vec[i]);

        // next iteration
        max_prev_prev = max_prev;
        max_prev = max_to_here;
    }

    return max_to_here;
}


int main()
{
    vector< vector<int> > testcases;
    vector<int> test01 = {2, 4, 6, 2, 5};       testcases.push_back(test01);   // Expected: 13
    vector<int> test02 = {5, 1, 1, 5};          testcases.push_back(test02);   // Expected: 10
    vector<int> test03 = {5, 1, 1, 20, 100};    testcases.push_back(test03);   // Expected: 106
    vector<int> test04 = {10, 100, 10};         testcases.push_back(test04);   // Expected: 100
    vector<int> test05 = {100, 50, -4, 20};     testcases.push_back(test05);   // Expected: 120

    for(int i=0; i<testcases.size(); i++)
    {
        int max_sum = maximumSum(testcases[i]);
        cout << "Test #" << (i+1) << " gives result: " << max_sum << endl;
    }

    return 0;
}
