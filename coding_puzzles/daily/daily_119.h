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
// NOTE: Habe Angabe falsch verstanden und stattdessen die intersecting elements aus allen gegebenen Intervallen rausgeholt!!!
// Stattdessen sollte die minimale Anzahl an Zahlen gefunden werden um alle Intervalle zu covern (schwieriger)

class CLASSNAME
{
public:
    CLASSNAME()
    {
        cout << "Running " << VERSION_STRING(CLASSNAME) << "..." << endl;
    }


    std::set<int> intervalToSet(const std::pair<int, int> &interval)
    {
        std::set<int> set;

        if (interval.first > interval.second)
        {
            cerr << "Malformed interval. Returning empty set." << endl;
            return set;
        }

        for(int i=interval.first; i<=interval.second; i++)
        {
            set.insert(i);
        }

        //cout << "The set has size " << set.size() << " and is " << printSet(set) << endl;
        return set;
    }

    std::set<int> getIntersectionSet(vector<pair<int, int>> intervals)
    {
        std::set<int> intersection_set;

        if (intervals.empty())
            return intersection_set;

        intersection_set = intervalToSet(intervals.back());
        intervals.pop_back();
        cout << "The initial intersection_set has size " << intersection_set.size() << " and is " << printSet(intersection_set) << endl;

        while(!intervals.empty())
        {
            std::set<int> next_set = intervalToSet(intervals.back());
            intervals.pop_back();
            //cout << "next_set has size " << next_set.size() << " and is " << printSet(next_set) << endl;

            std::set<int> result;

            // For std::set
            std::set_intersection(intersection_set.begin(), intersection_set.end(),
                                  next_set.begin(), next_set.end(),
                                  std::inserter(result, result.begin()));

            //cout << "result has size " << result.size() << " and is " << printSet(result) << endl << endl << endl;

    //        // For std:vector
    //        std::set_intersection(intersection_set.begin(), intersection_set.end(),
    //                              next_set.begin(), next_set.end(),
    //                              std::back_inserter(result));
            intersection_set = result;
        }

        return intersection_set;
    }
};

TEST(CLASSNAME, Test1)
{    
    CLASSNAME instance;

    vector<pair<int, int>> intervals;
    intervals.push_back(make_pair<int, int>(0, 9));
    intervals.push_back(make_pair<int, int>(2, 6));
    intervals.push_back(make_pair<int, int>(3, 7));
    intervals.push_back(make_pair<int, int>(2, 5));

    std::set<int> intersection_set = instance.getIntersectionSet(intervals);
    std::set<int> expected_intersection_set{3, 4, 5};
    cout << "The remaining set is " << printSet(intersection_set)  << endl;
    ASSERT_EQ(expected_intersection_set, intersection_set);
}

#undef CLASSNAME
