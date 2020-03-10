#include<QString>

#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>

#include <unordered_map>

using namespace std;




bool compare(const pair<int, int>&a, const pair<int, int>&b)
{
   return a.second<b.second;
}



// Strategy:
// Iterate over each value and insert into hash map with value 1 if not yet exists (if exists, then continue).
// After inserting increase the value by 1 for each existing predecessor
// Then find existing successors and set their value to (val+1), (val+2), ...

int getLongestConsecutiveSequence(const vector<int> &array)
{
    if (array.size() == 0)
        return 0;

    unordered_map<int, int> hash_map;
    for (int key : array)
    {
        if (hash_map.find(key) != hash_map.end())
        {
            continue;
        }
        else
        {
            hash_map[key] = 1;

            // iterate over all direct predecessors and increment current value by 1 for each found
            int curr_predecessor_key = key - 1;
            while(hash_map.find(curr_predecessor_key) != hash_map.end())
            {
                hash_map[key]++;
                curr_predecessor_key--;
            }

            // iterate over all direct successors and increment set their value to val + i
            int curr_successor_key = key + 1;
            int index_diff = 1;
            while(hash_map.find(curr_successor_key) != hash_map.end())
            {
                hash_map[curr_successor_key] = hash_map[key] + index_diff;
                curr_successor_key++;
                index_diff++;
            }
        }
    }

    // return max. value from hash map
//    int current_max = std::numeric_limits<int>::min();
//    for (auto &it : hash_map)
//    {
//        //cout << "#### First: " << it.first << " --> Second: " << it.second << endl;
//        if (it.second > current_max)
//        {
//            current_max = it.second;
//        }
//    }
//    return current_max;


    // nicer way to do this
    return max_element(hash_map.begin(), hash_map.end(), compare)->second;
}



int main()
{
    vector<int> array = {46, 100, 44, 200, 45, 41, 43, 42, 47};
    int longest_seq = getLongestConsecutiveSequence(array);
    cout << "The longest cons. seq is " << longest_seq << endl;
    return 0;
}
