#include<QString>

#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
#include <sstream>

using namespace std;

// Helper method to print a vector of chars
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



int main(int argc, char *argv[])
{    
    vector<int> A = {1,3,5,7,9,11,13,15,17,19,-1,-1,-1,-1,-1};

    vector<int> B = {2,6,10,14,18};


    int a = maxIndex(A);    // oder: int a = std::max_element(A.begin(), A.end()) - A.begin();
    int b = B.size() - 1;
    int i = A.size()-1;
    cout << "a=" << a << "; b=" << b << "; i=" << i << endl;


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

    cout << "The merged vectors are: " << printVec(A) << endl;



    return 0;
}
