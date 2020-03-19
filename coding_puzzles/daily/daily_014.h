#pragma once

#define CLASSNAME Daily_014

#include "base_header.h"

using namespace std;
using namespace Helper;

// -------------------- Program starts here -------------------------
//
//The area of a circle is defined as πr^2. Estimate π to 3 decimal places using a Monte Carlo method.
//Hint: The basic equation of a circle is x2 + y2 = r2.

class CLASSNAME
{
public:
    CLASSNAME()
    {
        cout << "Running " << VERSION_STRING(CLASSNAME) << "..." << endl;
    }

    double estimatePi(int num_samples)
    {
        // random
        //default_random_engine generator;    // always the same values (unless a time-based seed is used)
        random_device generator;              // this one uses "real" randomness but is not supported on all platforms
        uniform_real_distribution<double> distribution(0.0, 1.0);

        int num_inliers = 0;
        for(int i=0; i<num_samples; i++)
        {
            float x = distribution(generator);
            float y = distribution(generator);

            if( (x*x + y*y) < 1.0 )
            {
                num_inliers++;
            }
            else if ((x*x + y*y) == 1.0)
            {
                cout << "Warning: Being exactly on the circle" << endl;
            }
        }

        return 4.0 * (static_cast<double>(num_inliers) / num_samples);
    }
};

TEST(CLASSNAME, Test1)
{    
    CLASSNAME instance;

    // Note: For 3 decimal places we need at least 1000 samples, but of course the more the better.
    // Maybe calculating the p-value for a given significance level (e.g. 5%) can give us a better number.
    int num_samples = 10000;
    double estimated_value = instance.estimatePi(num_samples);
    cout << "Estimated Pi with " << num_samples << " samples to be " << estimated_value;
    ASSERT_NEAR(M_PI, estimated_value, 0.1);  // make comparison not too strict
}

#undef CLASSNAME
