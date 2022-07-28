#pragma once

#define CLASSNAME Daily_119                //< specify class name here

#include "base_header.h"

using namespace std;
using namespace Helper;

// -------------------- Program starts here -------------------------
//
// Given a set of closed intervals, find the smallest set of numbers that covers all the intervals. If there are multiple smallest sets, return any of them.
// For example, given the intervals [0, 3], [2, 6], [3, 4], [6, 9], one set of numbers that covers all these intervals is {3, 6}
//
//
// 0  1  2  3  4  5  6  7  8  9
// [        ]                       0-3   requires 1 from {0,1,2,3}
//       [           ]              2-6   requires 1 from {2,3,4,5,6}
//          [  ]                    3-4   requires 1 from {3,4}
//                   [        ]     6-9   requires 1 from {6,7,8,9}
//
// create std::map<int,int> counts and count how often any existing value occurrs
// pick the one with highest count, add it to result set, remove its map entry and all sets where it was contained
// repeat until no more remaining sets

class CLASSNAME
{
public:
    CLASSNAME()
    {
        cout << "Running " << VERSION_STRING(CLASSNAME) << "..." << endl;
    }

    void printMap(const std::map<int, int> &myMap)
    {
      for (const auto &[key,val] : myMap) {
        std::cout << "map[" << key << "] = " << val << std::endl;
      }
    }

    std::set<int> getIntersectionSet(std::vector<std::pair<int, int>> intervals)
    {
      std::set<int> resultSet;
      if (intervals.empty())
        return resultSet;

      // stores in how many sets a certain value exists
      std::map<int, int> countMap;
      for (const auto& interval : intervals) {
        for (int i=interval.first; i<=interval.second; i++) {
          countMap[i]++;
        }
      }
      printMap(countMap);


      while (!intervals.empty()) {
        // insert best element
        auto it = std::max_element(countMap.begin(), countMap.end(),
                                   [](const std::pair<int,int> &a, const std::pair<int,int> &b)
                                    {
                                      return a.second < b.second;
                                    });
        int val = it->first;
        resultSet.insert(val);
        std::cout << "  After insert the resultSet is " << printSet(resultSet) << std::endl;

        // remove sets, update countMap
        auto iit = intervals.begin();
        while (iit!=intervals.end()) {
          if (iit->first <= val && iit->second >=val) {
            for (int i=iit->first; i<=iit->second; i++ ) {
              countMap[i]--;
              std::cout << "                   Decreasing counts[" << i << "] to " << countMap[i] << std::endl;
            }
            iit = intervals.erase(iit);
          }
          else
            ++iit;
        }
        std::cout << "  After erasing the remaining num. intervals is " << intervals.size() << std::endl;
        std::cout << "  The updated map is: " <<  std::endl;
        printMap(countMap);
        std::cout << std::endl;
      }


      return resultSet;
    }
};

TEST(CLASSNAME, Test1)
{
    CLASSNAME instance;

    vector<pair<int, int>> intervals;
    intervals.push_back(make_pair<int, int>(0, 3));
    intervals.push_back(make_pair<int, int>(2, 6));
    intervals.push_back(make_pair<int, int>(3, 4));
    intervals.push_back(make_pair<int, int>(6, 9));

    std::set<int> intersection_set = instance.getIntersectionSet(intervals);
    std::set<int> expected_intersection_set{3, 6};
    cout << "The remaining set is " << printSet(intersection_set)  << endl;
    ASSERT_EQ(expected_intersection_set, intersection_set);
}

#undef CLASSNAME
