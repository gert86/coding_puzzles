#pragma once

#define CLASSNAME Cracking_8_5

#include "base_header.h"

using namespace std;
using namespace Helper;

// -------------------- Program starts here -------------------------
//
// Recursive Multiply: Write a recursive function to multiply two positive integers without using the
// * operator. You can use addition, subtraction, and bit shifting, but you should minimize the number
// of those operations.

class CLASSNAME
{
public:
    CLASSNAME()
    {
        cout << "Running " << VERSION_STRING(CLASSNAME) << "..." << endl;
    }

    uint recursiveMultiplyHelper(uint bigger, uint smaller)
    {
        if (smaller == 0)
            return 0;

        if (smaller == 1)
            return bigger;

        int s = smaller >> 1;   // smaller divided by 2
        int halfProd = recursiveMultiplyHelper(bigger, s);

        if (smaller%2 == 0)
        {
            return halfProd + halfProd;
        }
        else
        {
            return halfProd + halfProd + bigger;
        }
    }

    uint recursiveMultiply(uint factor1, uint factor2)
    {
        uint smaller = (factor1 < factor2) ? factor1 : factor2;
        uint bigger  = (factor1 < factor2) ? factor2 : factor1;
        return recursiveMultiplyHelper(bigger, smaller);
    }
};

TEST(CLASSNAME, Test1)
{    
    CLASSNAME instance;

    vector< QPair<uint,uint> > test_vector;
    test_vector.push_back( QPair<uint,uint>(0,0) );
    test_vector.push_back( QPair<uint,uint>(0,5) );
    test_vector.push_back( QPair<uint,uint>(6,0) );
    test_vector.push_back( QPair<uint,uint>(1,90) );
    test_vector.push_back( QPair<uint,uint>(80,1) );
    test_vector.push_back( QPair<uint,uint>(6,80) );
    test_vector.push_back( QPair<uint,uint>(80,6) );
    test_vector.push_back( QPair<uint,uint>(100,100) );


    for(int i=0; i<test_vector.size(); i++)
    {
        int result = instance.recursiveMultiply(test_vector[i].first, test_vector[i].second);
        int expected_result = test_vector[i].first * test_vector[i].second;
        ASSERT_EQ(expected_result, result);
    }
}

#undef CLASSNAME
