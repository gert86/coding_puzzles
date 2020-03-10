// Given a array of numbers representing the stock prices of a company in chronological order, write a function that calculates the maximum profit
// you could have made from buying and selling that stock once. You must buy before you can sell it.
//
//For example, given [9, 11, 8, 5, 7, 10], you should return 5, since you could buy the stock at 5 dollars and sell it at 10 dollars.

#include<QString>

#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>


using namespace std;

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


int main(int argc, char *argv[])
{
    int mode = 2; // 1, 2
    vector<int> prices = {9, 11, 8, 5, 7, 10};
    int max_profit = -1;

    if (mode==1)    max_profit = getMaxProfit(prices);
    if (mode==2)    max_profit = getMaxProfitSimple(prices);
    cout << "The maximum profit with these prices is " << max_profit << endl;

    return 0;
}
