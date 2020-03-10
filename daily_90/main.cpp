// Given an integer n and a list of integers l, write a function that randomly generates
// a number from 0 to n-1 that isn't in l (uniform).

#include<QString>

#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
#include <unordered_set>
#include <random>
#include <assert.h>

#include <algorithm>

using namespace std;


int randomNumberNotFromList(int N, const vector<int> &l)
{
    // Put all forbidden vals into a hash-set...
    std::unordered_set<int> forbidden_values;
    for (int i : l)
        forbidden_values.insert(i);

    // ... OR ...

    // ...make a unique vector (must be sorted first!)
    // HOWEVER, THIS SHOULD NOT BE USED BECAUSE FIND OPERATION WOULD TAKE LINEAR TIME (AND NEEDS MANUAL IMPLEMENTATION)!
    //std::vector<int> forbidden_values = l;
    //std::sort(forbidden_values.begin(), forbidden_values.end());
    //std::unique(forbidden_values.begin(), forbidden_values.end());


    // Calc. how many numbers can be omitted in random number generation
    int num_forbidden = forbidden_values.size();
    int N_reduced = N - num_forbidden;

    // Calculate random number
    random_device generator;              // this one uses "real" randomness but is not supported on all platforms
    std::uniform_int_distribution<int> distribution(0, N_reduced - 1);
    int rand_num = distribution(generator);


    // Map back the random number to its original range (excluding forbidden values)
    int num_valid = -1;
    for (int i=0; i<N; i++)
    {
        if (forbidden_values.find(i) == forbidden_values.end())
            num_valid++;

        if (num_valid == rand_num)
            return i;
    }

    cerr << "This should not happen..." << endl;
    return -1;
}



int main(int argc, char *argv[])
{    

    vector<int> l = {1,2,3,1};
    int N = 10;


    vector<int> histogram;
    histogram.resize(N);

    for (int i=0; i<100000; i++)
    {
        int num = randomNumberNotFromList(N, l);
        cout << "The random number is " << num << endl;
        assert(num >= 0);
        assert(num < N);
        histogram[num]++;
    }

    // Result
    cout << "----" << endl;
    for (int i=0; i<histogram.size(); i++)
    {
        cout << "The value " << i << " was returned " << histogram[i] << " times." << endl;
    }
    cout << "----" << endl;

    return 0;
}
