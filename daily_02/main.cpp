//Given an array of integers, return a new array such that each element at index i of the new array
//is the product of all the numbers in the original array except the one at i.
//
//For example, if our input was [1, 2, 3, 4, 5], the expected output would be [120, 60, 40, 30, 24]. If our input was [3, 2, 1], the expected output would be [2, 3, 6].
//
//Follow-up: what if you can't use division?

#include<QString>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <numeric>


using namespace std;


// performs division without using division operator
int divideInteger(int numerator, int denominator)
{
    // denominator must not be 0
    if (denominator == 0)
    {
        cerr << "Division by zero not possible. Exit!";
        exit(-1);
    }

    // determine whether result is positive or negative
    int sign_factor = 1;
    if (numerator < 0)
        sign_factor *= -1;
    if (denominator < 0)
        sign_factor *= -1;

    // denominator must be greater than numerator, otherwise the result is 0
    numerator = abs(numerator);
    denominator = abs(denominator);

    // do the division avoiding fractures
    int result = 0;
    while (numerator >= denominator)
    {
        numerator-=denominator;
        result++;
    }

    return sign_factor * result;
}


vector<int> calculateResultArray(const vector<int> &vec)
{
    vector<int> result_vec(vec.size(), 0);  // init with 0

    int num_zeros = 0;
    int first_zero_index = -1;
    int product = 1;
    int product_excluding_zero = 1;
    for(int i=0; i<vec.size(); i++)
    {
        product *= vec[i];  // unconditional product

        if (vec[i] == 0)
        {
            num_zeros++;
            if (num_zeros == 1)
            {
                first_zero_index = i;
            }
            else
            {
                break;   // more than one zero - we can stop here
            }
        }
        else
        {
            product_excluding_zero *= vec[i];  // product excluding the only zero
        }
    }

    cout << "product = " << product << " and num_zeros is " << num_zeros << endl;

    // more than one zero - return all zeros
    if (num_zeros > 1)
    {
        cout << "more than one zero - return all zeros" << endl;
        return result_vec;
    }

    // exactly one zero - return all zeros except for the index of the 0 itself
    if (num_zeros == 1)
    {
        cout << "exactly one zero - return all zeros except for the index of the 0 itself" << endl;
        result_vec[first_zero_index] = product_excluding_zero;
        return result_vec;
    }

    // no zeros - return product / vec[i]

    cout << "no zeros - return product / vec[i]" << endl;
    for(int i=0; i<vec.size(); i++)
    {
        //result_vec[i] = (product / vec[i]);               // using division
        result_vec[i] = divideInteger(product , vec[i]);    // without explicit division
    }

    return result_vec;
}

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

int main()
{
    vector<int> test01 = {1, 2, 3, 4, 5};      // [120, 60, 40, 30, 24]
    vector<int> test02 = {3, 2, 1};            // [2, 3, 6]
    vector<int> test03 = {1,2,3,0,4};          // [0, 0, 0, 24, 0]
    vector<int> test04 = {1,0,3,0,4};          // [0, 0, 0, 0, 0]
    vector<int> test05 = {3,9,2,1,100};        // [1800, 600, 2700, 5400, 54]


    vector< vector<int>>  test_vector;
    test_vector.push_back(test01);
    test_vector.push_back(test02);
    test_vector.push_back(test03);
    test_vector.push_back(test04);
    test_vector.push_back(test05);

    for (int i=0; i<test_vector.size(); i++)
    {
        vector<int> result = calculateResultArray( test_vector[i] );
        cout << "Test #" << (i+1) << " results in " << printVec(result) << endl << endl;
    }
    return 0;
}

