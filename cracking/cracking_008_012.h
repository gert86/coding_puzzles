#pragma once

#define CLASSNAME Cracking_8_12

#include "base_header.h"

using namespace std;
using namespace Helper;

// -------------------- Program starts here -------------------------
//
// Eight Queens: Write an algorithm to print all ways of arranging eight queens on an 8x8 chess board
// so that none of them share the same row, column, or diagonal. In this case, "diagonal" means all
// diagonals, not just the two that bisect the board

class CLASSNAME
{
public:
    CLASSNAME()
    {
        cout << "Running " << VERSION_STRING(CLASSNAME) << "..." << endl;
    }

    bool isPlacementValid(const vector<int> &columns)
    {
        for (int i=0; i<columns.size(); i++)
        {
            for (int j=i+1; j<columns.size(); j++)
            {
                // same row violation
                if (columns[i] == columns[j])
                    return false;

                int col_diff = j - i;
                int row_diff = abs(columns[j] - columns[i]);

                // same diagonal violation
                if (col_diff == row_diff)
                    return false;
            }
        }

        return true;
    }

    int numPlacements(int N, vector<int> &current_columns)
    {
        // we are done
        if (current_columns.size() == N)
            return 1;

        int num_valid = 0;
        for (int i=0; i<N; i++)
        {
            vector<int> column_copy = current_columns;
            column_copy.push_back(i);    // try a placement

            if (isPlacementValid(column_copy))
            {
                num_valid += numPlacements(N, column_copy);
            }
        }

        return num_valid;
    }

    int numPlacements(int N)
    {
        // These cases are a matter of definition
        if (N <= 0)
            return 0;

        vector<int> columns;
        return numPlacements(N, columns);
    }
};

TEST(CLASSNAME, Test1)
{    
    CLASSNAME instance;

    // See solutions: https://en.wikipedia.org/wiki/Eight_queens_puzzle#Counting_solutions
    vector<int>  result_vector{0, 1, 0, 0, 2, 10, 4, 40, 92, 352, 724, 2680};
    for(int i=0; i<result_vector.size(); i++)
    {
        int num_placements = instance.numPlacements(i);
        cout << "For N = " << i << " the number of placements is: " << num_placements << endl;
        ASSERT_EQ(result_vector[i], num_placements);
    }
}

#undef CLASSNAME
