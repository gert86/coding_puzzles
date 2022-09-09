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


    // A = [8, 9, -1, -1]
    // B = [1, 2]
    void mergeArrays(vector<int>& A, const vector<int> B)
    {
      int writeIdx = A.size() - 1;
      int readIdxB = B.size() - 1;
      int readIdxA = writeIdx - readIdxB - 1;

      while (readIdxB >= 0) {
        if (A[readIdxA] > B[readIdxB]) {
          A[writeIdx] = A[readIdxA];
          readIdxA--;
        }
        else  {
          A[writeIdx] = B[readIdxB];
          readIdxB--;
        }
        writeIdx--;
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
