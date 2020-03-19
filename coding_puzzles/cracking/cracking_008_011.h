#pragma once

#define CLASSNAME Cracking_8_11

#include "base_header.h"

using namespace std;
using namespace Helper;

// -------------------- Program starts here -------------------------
//
// Coins: Given an innnite number of quarters (25 cents), dimes (10 cents), nickels (5 cents), and
// pennies (1 cent), write code to calculate the number of ways of representing n cents.

class CLASSNAME
{
public:
    CLASSNAME()
    {
        cout << "Running " << VERSION_STRING(CLASSNAME) << "..." << endl;
    }

    // TODO: Add memoization and do not count different ordering twice (1,5,1 and 1,1,5 should not count twice).


    int numPossibilities(int amount, const QVector<int> &coins, QSet< QPair<int,int> > &hash_set)
    {
        Q_UNUSED(hash_set);

        // base cases that do not increase count
        if (coins.empty())
            return 0;

        if (amount <= 0)
            return 0;

        //std::cout << "#### Checking for amount " << amount << std::endl;



        int count = 0;
        for (int i=0; i<coins.size(); i++)
        {
    //        // check if we already were at this amount and then chose this coin
    //        bool known_case = hash_set.contains(QPair<int,int>(amount, coins[i]));
    //        if (known_case)
    //            return 0;
    //
    //        // remember for next time that we have been here
    //        hash_set.insert(QPair<int,int>(amount, coins[i]));

            // choose this coin and remove value from remaining amount
            int remaining_amount = amount - coins[i];

            // base case that increases count
            if (remaining_amount == 0)
            {
                count++;
                continue;
            }

            // check how many possibilities there are for the remaining count (do not allow previous values)
            count += numPossibilities(remaining_amount, coins.mid(i), hash_set);
        }

        return count;
    }


    // Solution from book
    int numPossibilitiesRef(int amount, const QVector<int> &coins, int index, QVector< QVector<int> > &precompute_map)
    {
        if (precompute_map[amount][index] > 0)
            return precompute_map[amount][index];

        // 1 denom remaining
        if (index >= coins.length() - 1)
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

    QVector<int> coins = {25, 10, 5, 1};
    QVector<int> test_vector;       QVector<int> result_vector;
    //test_vector.push_back(0);       result_vector.push_back(0);  // difference between reference solution and ours!!!
    test_vector.push_back(1);       result_vector.push_back(1);
    test_vector.push_back(5);       result_vector.push_back(2);
    test_vector.push_back(6);       result_vector.push_back(2);
    test_vector.push_back(7);       result_vector.push_back(2);
    test_vector.push_back(9);       result_vector.push_back(2);
    test_vector.push_back(10);      result_vector.push_back(4);
    test_vector.push_back(20);      result_vector.push_back(9);
    test_vector.push_back(100);     result_vector.push_back(242);


    for (int i=0; i<test_vector.size(); i++)
    {
        int amount = test_vector[i];

        // solution from book
        // Only works if coins are sorted in decreasing order
        // Returns 1 for an amount of 0!
        QVector< QVector<int> > precompute_map;
        precompute_map.resize(amount + 1);
        for (int i=0; i<amount+1; i++)
            precompute_map[i].resize(coins.size());
        int num_possibilities_ref = instance.numPossibilitiesRef(amount, coins, 0, precompute_map);
        cout << "Ref. Solution: Num. possibilities for amount " << amount << " is " << num_possibilities_ref <<  endl;
        ASSERT_EQ(result_vector[i], num_possibilities_ref);


        // my solution
        // gives same solution than book without the disadvantages. Does not need additional memory!!!
        // Returns 0 for an amount of 0! This is a question of convention and needs clarification with interviewer.
        QSet< QPair<int,int> > hash_set;
        int num_possibilities_ours = instance.numPossibilities(amount, coins, hash_set);
        cout << "My Solution: Num. possibilities for amount " << amount << " is " << num_possibilities_ours <<  endl << endl;
        ASSERT_EQ(result_vector[i], num_possibilities_ours);
    }
}

#undef CLASSNAME