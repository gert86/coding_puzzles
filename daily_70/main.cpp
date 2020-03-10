//A number is considered perfect if its digits sum up to exactly 10.
//Given a positive integer n, return the n-th perfect number.
//For example, given 1, you should return 19. Given 2, you should return 28.


#include<QString>

#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
#include <unordered_map>

#include <math.h>       /* ceil */


using namespace std;



int getDigitSum(long num)
{
    int sum = 0;

    long moduloer = 10;
    long divisor = 1;

    while(divisor <= num)
    {
        sum += ((num % moduloer) / divisor);
        divisor *= 10;
        moduloer *= 10;
    }

    return sum;
}


long getPerfectNumTrivial(int num)
{
    if (num<=0)
        return -1;

    int N = 0;
    long i=1;
    while(true)
    {
        if (getDigitSum(i)==10)
        {
            N += 1;

            if (N==num)
                return i;
        }
        i += 1;
    }
}

long getPerfectNumOptimized(int num)
{
    if (num<=0)
        return -1;

    int N = 0;
    long i=1;
    while(true)
    {
        if (getDigitSum(i)==10)
        {
            N += 1;

            if (N>30000)
            {
                cout << "... Found #" << N << " to be " << i << endl;
            }

            if (N==num)
                return i;
        }
        i += 9;
    }
}

long getPerfectNumOptimized2(int num)
{
    if (num<=0)
        return -1;

    int N = 0;
    long i=1;
    while(true)
    {
        if (getDigitSum(i)==10)
        {
            N += 1;

            if (N==num)
                return i;

            // optimized increment
            // higher increment in case of many trailing zeros brings a huge speedup...
            if (i%10 == 0)
            {
                int first_non_zero_mod = 100;
                while (first_non_zero_mod <= 1e9)
                {
                    if (i%first_non_zero_mod != 0)
                        break;
                    first_non_zero_mod *= 10;
                }

                long remainder = first_non_zero_mod - i%first_non_zero_mod;
                int increment = ceil(remainder/9.0) * 9;
                i += increment;
                continue;

                // example: 820
                // first_non_zero_mod = 100
                // remainder = 100 - 20 = 80
                // increment = 9*9 = 81

                // example: 4600
                // first_non_zero_mod = 1000
                // remainder = 1000 - 600 = 400
                // increment = 45*9 = 405
            }
        }

        // fallback increment
        i += 9;
    }
}


int main(int argc, char *argv[])
{    
    vector<int> test_vector;
    test_vector.push_back(-5);          // -1
    test_vector.push_back(0);           // -1
    test_vector.push_back(1);           // 19
    test_vector.push_back(2);           // 28
    test_vector.push_back(5);           // 55
    test_vector.push_back(10);          // 109
    test_vector.push_back(50);          // 604
    test_vector.push_back(100);         // 1423
    test_vector.push_back(118);         // 1900
    test_vector.push_back(1000);        // 100036
    test_vector.push_back(7777);        // 5300200
    test_vector.push_back(100000);      // 1423077518


    for (int val : test_vector)
    {
        int n_th_perfect_num = getPerfectNumOptimized2(val);
        cout << "The #" << val << " perfect number is " << n_th_perfect_num << endl;
    }


    return 0;
}
