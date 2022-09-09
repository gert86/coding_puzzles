#pragma once

#define CLASSNAME Daily_047

#include "base_header.h"

using namespace std;
using namespace Helper;

// -------------------- Program starts here -------------------------
//
// Given a array of numbers representing the stock prices of a company in chronological order, write a function that calculates the maximum profit
// you could have made from buying and selling that stock once. You must buy before you can sell it.
//
// For example, given [9, 11, 8, 5, 7, 10], you should return 5, since you could buy the stock at 5 dollars and sell it at 10 dollars.


// Strategy:
// Find rising price: A[i] > A[i-1]
// Store the buy price A[i-1]
// Proceed i++ as long as the price continues growing and keep track of the max. profit in each step
// When finding a falling price A[j] < A[j-1], this is the new buy price
// Repeat until finished

class CLASSNAME
{
public:
    CLASSNAME()
    {
        cout << "Running " << VERSION_STRING(CLASSNAME) << "..." << endl;
    }


    int getMaxProfit(const vector<int> &prices)
    {
        int best_profit = -1;
        int best_profit_start_idx = -1;
        int best_profit_end_idx = -1;

        int curr_profit = -1;
        int curr_min_start_price = -1;
        int curr_min_start_idx = -1;

        for (int i=0; i<prices.size(); i++)
        {
            if (curr_min_start_price < prices[i] && curr_min_start_price != -1)
            {
                // sell option - could sell stock with profit
                curr_profit = prices[i] - curr_min_start_price;
            }
            else
            {
                // buy option - could buy stock cheaper than ever
                curr_min_start_price = prices[i];
                curr_min_start_idx = i;
            }

            // snapshot the best result here
            if (curr_profit > best_profit)
            {
                best_profit = curr_profit;
                best_profit_start_idx = curr_min_start_idx;
                best_profit_end_idx = i;
            }
        }


        if (best_profit != -1)
            cout << "The best profit is " << best_profit << ", buy on day " << best_profit_start_idx << " and sell on day " << best_profit_end_idx << endl;
        else
            cout << "No profit possible." << endl;

        return best_profit;
    }


    // Does not store WHEN to buy and sell
    int getMaxProfitSimple(const vector<int> &prices)
    {
        int lowest_price = std::numeric_limits<int>::min();
        int best_profit = 0;

        for(int price : prices)
        {
            if (lowest_price == std::numeric_limits<int>::min() || lowest_price > price)
            {
                // got lowest price so far
                lowest_price = price;
            }

            if (price - lowest_price > best_profit)
            {
                // got best profit so far
                best_profit = price - lowest_price;
            }
        }

        return best_profit;
    }
};

TEST(CLASSNAME, Test1)
{    
    CLASSNAME instance;
    vector<int> prices = {9, 11, 8, 5, 7, 10};

    // Mode 1    
    int max_profit_mode_1 = instance.getMaxProfit(prices);
    cout << "The maximum profit with these prices is " << max_profit_mode_1 << endl;
    ASSERT_EQ(5, max_profit_mode_1);

    // Mode 2
    int max_profit_mode_2 = instance.getMaxProfitSimple(prices);
    ASSERT_EQ(5, max_profit_mode_2);
    cout << "--> same for mode 2" << endl << endl;
}

#undef CLASSNAME
