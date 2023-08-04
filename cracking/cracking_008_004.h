#pragma once

#define CLASSNAME Cracking_8_4

#include "base_header.h"

using namespace std;
using namespace Helper;

// -------------------- Program starts here -------------------------
//
// Power Set: Write a method to return all subsets of a set.

class CLASSNAME
{
public:
    CLASSNAME()
    {
        cout << "Running " << VERSION_STRING(CLASSNAME) << "..." << endl;
    }

    // {}  ->  {}
    // {1} -> {}, {1}
    // {1, 2}    -> {}, {1}, {2}, {1,2}
    // {1, 2, 3} -> {}, {1}, {2}, {3}, {1,2}, {1,3}, {2,3}, {1,2,3}
    //           -> {}, {1}, {2}, {1,2},
    //              {3},{1,3}, {2,3}, {1,2,3}
    vector< set<int> > powerSets(const std::set<int> &inputSet)
    {
      vector< set<int> > setOfSets;

      set<int> empty;
      setOfSets.push_back(empty);

      for (const auto& val : inputSet) {
        vector< set<int> > newSets;
        for (const auto &resultSet : setOfSets) {
          auto resultSetWithNewVal = resultSet;
          resultSetWithNewVal.insert(val);
          newSets.push_back(resultSetWithNewVal);
        }
        for (const auto& s : newSets)
          setOfSets.push_back(s);
      }


      return setOfSets;
    }

};

TEST(CLASSNAME, Test1)
{    
    CLASSNAME instance;

    vector< set<int> > test_vector;                  vector<size_t>  result_vector;
    test_vector.push_back( {} );                        result_vector.push_back(1);
    test_vector.push_back( {1} );                       result_vector.push_back(2);
    test_vector.push_back( {1, 2} );                    result_vector.push_back(4);
    test_vector.push_back( {1, 2, 3} );                 result_vector.push_back(8);
    test_vector.push_back( {1, 2, 3, 4} );              result_vector.push_back(16);
    test_vector.push_back( {1, 2, 3, 4, 5} );           result_vector.push_back(32);
    test_vector.push_back( {1, 2, 3, 4, 5, 6} );        result_vector.push_back(64);

    for(int i=0; i<test_vector.size(); i++)
    {
        auto curr_power_sets = instance.powerSets(test_vector[i]);
        cout << "For set " << printSet(test_vector[i]) << " there are " << curr_power_sets.size() << " subsets. " << endl;
        EXPECT_EQ(result_vector[i], curr_power_sets.size());
    }
}

#undef CLASSNAME
