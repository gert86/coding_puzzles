//The area of a circle is defined as πr^2. Estimate π to 3 decimal places using a Monte Carlo method.
//
//Hint: The basic equation of a circle is x2 + y2 = r2.

#include<QString>
#include <iostream>
#include <vector>
#include <random>


using namespace std;


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


int main()
{

    // Note: For 3 decimal places we need at least 1000 samples, but of course the more the better.
    // Maybe calculating the p-value for a given significance level (e.g. 5%) can give us a better number.
    int num_samples = 10000;
    double estimated_value = estimatePi(num_samples);
    cout << "Estimated Pi with " << num_samples << " samples to be " << estimated_value;
    return 0;
}

