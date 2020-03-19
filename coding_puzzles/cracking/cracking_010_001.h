#pragma once

#define CLASSNAME Cracking_10_1

#include "base_header.h"

using namespace std;
using namespace Helper;

// -------------------- Program starts here -------------------------
//
// Sorted Merge: You are given two sorted arrays, A and B, where A has a large enough buffer at the
// end to hold B. Write a method to merge B into A in sorted order.

class CLASSNAME
{
public:
    CLASSNAME()
    {
        cout << "Running " << VERSION_STRING(CLASSNAME) << "..." << endl;
    }

    int maxIndex(const vector<int> &A)
    {
        if (A.empty())
            return -1;

        int max_idx = -1;
        int max_val = std::numeric_limits<int>::min();

        for(int i=0; i<A.size(); i++)
        {
            if (A[i] > max_val)
            {
                max_val = A[i];
                max_idx = i;
            }
        }

        return max_idx;
    }

    void mergeArrays(vector<int> &A, const vector<int> &B)
    {
        int a = maxIndex(A);    // oder: int a = std::max_element(A.begin(), A.end()) - A.begin();
        int b = B.size() - 1;
        int i = A.size()-1;
        //cout << "a=" << a << "; b=" << b << "; i=" << i << endl;


        if ( (i-a) != B.size() )
        {
            cerr << "Mismatch in vector lengths. Cannot proceed." << endl;
            exit(-1);
        }


        while(b>=0)
        {
            if (A[a] >= B[b])
            {
                A[i] = A[a];
                a--;
            }
            else
            {
                A[i] = B[b];
                b--;
            }

            i--;
        }
    }
};

TEST(CLASSNAME, Test1)
{    
    CLASSNAME instance;

    vector<int> A = {1,3,5,7,9,11,13,15,17,19,-1,-1,-1,-1,-1};
    vector<int> B = {2,6,10,14,18};
    instance.mergeArrays(A, B);

    cout << "The merged vectors are: " << printVec(A) << endl;
    vector<int> expected_result{1,2,3,5,6,7,9,10,11,13,14,15,17,18,19};
    ASSERT_EQ(expected_result, A);
}

#undef CLASSNAME
