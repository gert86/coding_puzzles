#pragma once

#define CLASSNAME Cracking_8_11

#include "base_header.h"

#include <unordered_map>

using namespace std;
using namespace Helper;

// -------------------- Program starts here -------------------------
//
// Coins: Given an infinite number of quarters (25 cents), dimes (10 cents), nickels (5 cents), and
// pennies (1 cent), write code to calculate the number of ways of representing n cents.
//
// n = 0        -> 1  {}
// n = 1        -> 1  {1}
// n = 2        -> 1  {1,1}
// n = 3        -> 1  {1,1,1}
// n = 4        -> 1  {1,1,1,1}
// n = 5        -> 2  {1,1,1,1,1}, {5}
// n = 6        -> 2  {1,1,1,1,1,1}, {5,1}        -> do not count {1,5} extra
// n = 7        -> 2  {1,1,1,1,1,1,1}, {5,1,1}    -> do not count {1,5,1} or {1,1,5} extra
// n = 8        -> 2  {1,1,1,1,1,1,1,1}, {5,1,1,1}
// n = 9        -> 2  {1,1,1,1,1,1,1,1,1}, {5,1,1,1,1}
// n = 10       -> 4  {1,1,1,1,1,1,1,1,1,1}, {5,1,1,1,1,1},       -> reached from n-1 and appended 1
//                             x             {5,5},               -> reached from n-5 and appended 5 (skipped first)
//                    {10}                                        -> reached from n-10 and appended 10
// n = 11       -> 4
// n = 14       -> 4  {1,1,...,1}, {5,1,1,1,1,1,1,1,1,1},   {5,5,1,1,1,1},   {10,1,1,1,1}
// n = 15       -> X  {1,1,...,1}, {5,1,1,1,1,1,1,1,1,1,1}, {5,5,1,1,1,1,1}, {10,1,1,1,1,1}  -> reached from n-1 and appended 1
//                        x                   x             {5,5,5},  {10,5}                 -> reached from n-5 and appended 5 (skipped 2)
//                        x                   x                                              -> reached from n-10 ... (skipped 2)
//              ->    {}
//
// It's hard to know how many we can skip without storing all of them (sorted sets) and inserting
// so let's store them
//
class CLASSNAME
{
public:
    CLASSNAME()
    {
        cout << "Running " << VERSION_STRING(CLASSNAME) << "..." << endl;
    }

    // My solution - non-recursive
    std::map<int, std::set<std::vector<int>>> _cache;
    int numPossibilities(const std::vector<int>& coins, int amount)
    {
      if (_cache.find(0) == _cache.end())
        _cache[0].insert(std::vector<int>());

      if (_cache.find(amount) != _cache.end())
        return _cache[amount].size();

      for (int i=1; i <= amount; i++) {
        if (_cache.find(i) != _cache.end())
          continue;

        // create new combos from combos that are one coin away + that coin
        std::set<std::vector<int>> newCombos;
        for (const auto& coin : coins) {
          if (i-coin >= 0) {
            for (auto comboCopy : _cache[i-coin]) {
              comboCopy.push_back(coin);
              std::sort(comboCopy.begin(), comboCopy.end());  // note: could also use priority queues, but they seem to have no std::less
              newCombos.insert(comboCopy);
            }
          }
        }
        _cache[i] = newCombos;
      }

      return _cache[amount].size();
    }



    // Reference solution from book - recursive
    std::unordered_map<int, int> _memoMap;
    int numPossibilitiesRef(int amount, const std::vector<int> &coins, int index, std::vector< std::vector<int> > &precompute_map)
    {
        if (precompute_map[amount][index] > 0)
            return precompute_map[amount][index];

        // 1 denom remaining
        if (index >= coins.size() - 1)
            return 1;

        int coin_amount = coins[index];
        int count = 0;

        for (int i=0; i*coin_amount <= amount; i++)
        {
            // go to next coin, assuming i coins of coin_amount
            int amount_remaining = amount - i*coin_amount;
            count += numPossibilitiesRef(amount_remaining, coins, index+1, precompute_map);
        }

        precompute_map[amount][index] = count;
        return count;
    }
};

TEST(CLASSNAME, Test1)
{
    CLASSNAME instance;

    std::vector<int> coins = {25, 10, 5, 1};
    std::vector<int> test_vector;       std::vector<int> result_vector;
    test_vector.push_back(0);           result_vector.push_back(1);  // this is a question of definition
    test_vector.push_back(1);           result_vector.push_back(1);
    test_vector.push_back(5);           result_vector.push_back(2);
    test_vector.push_back(6);           result_vector.push_back(2);
    test_vector.push_back(7);           result_vector.push_back(2);
    test_vector.push_back(9);           result_vector.push_back(2);
    test_vector.push_back(10);          result_vector.push_back(4);
    test_vector.push_back(20);          result_vector.push_back(9);
    test_vector.push_back(100);         result_vector.push_back(242);


    for (int i=0; i<test_vector.size(); i++)
    {
        int amount = test_vector[i];

        // solution from book
        // Only works if coins are sorted in decreasing order
        // Returns 1 for an amount of 0!
        std::vector< std::vector<int> > precompute_map;
        precompute_map.resize(amount + 1);
        for (int i=0; i<amount+1; i++)
            precompute_map[i].resize(coins.size());
        int num_possibilities_ref = instance.numPossibilitiesRef(amount, coins, 0, precompute_map);
        std::cout << "Ref. Solution: Num. possibilities for amount " << amount << " is " << num_possibilities_ref <<  std::endl;
        ASSERT_EQ(result_vector[i], num_possibilities_ref);


        // my solution
        int num_possibilities_ours = instance.numPossibilities(coins, amount);
        std::cout << "My Solution: Num. possibilities for amount " << amount << " is " << num_possibilities_ours <<  std::endl <<  std::endl;
        ASSERT_EQ(result_vector[i], num_possibilities_ours);
    }
}

#undef CLASSNAME
