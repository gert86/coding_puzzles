#include <QString>


#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>

#include <QVector>
#include <QSet>
#include <unordered_set>


using namespace std;


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


int main(int argc, char *argv[])
{    
    QVector<int> amount_vector = {0, 1, 5, 6, 7, 9, 10, 20, 100};
    QVector<int> coins = {25, 10, 5, 1};

    for (int i=0; i<amount_vector.size(); i++)
    {
        int amount = amount_vector[i];

        // solution from book
        // Only works if coins are sorted in decreasing order
        // Returns 1 for an amount of 0!
//        QVector< QVector<int> > precompute_map;
//        precompute_map.resize(amount + 1);
//        for (int i=0; i<amount+1; i++)
//            precompute_map[i].resize(coins.size());
//        int num_possibilities = numPossibilitiesRef(amount, coins, 0, precompute_map);

        // ours
        // gives same solution than book without the disadvantages. Does not need additional memory!!!
        QSet< QPair<int,int> > hash_set;
        int num_possibilities = numPossibilities(amount, coins, hash_set);

        std::cout << "Num. possibilities for amount " << amount << " is " << num_possibilities <<  std::endl;
    }



    std::cout << std::endl << std::endl << std::endl;

    return 0;
}
