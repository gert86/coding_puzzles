#pragma once

#define CLASSNAME Daily_062

#include "base_header.h"

using namespace std;
using namespace Helper;

// -------------------- Program starts here -------------------------
//
// There is an N by M matrix of zeroes. Given N and M, write a function to count the number of ways of starting at the top-left corner and getting to the bottom-right corner.
// You can only move right or down.
// For example, given a 2 by 2 matrix, you should return 2, since there are two ways to get to the bottom-right:
//    Right, then down
//    Down, then right
// Given a 5 by 5 matrix, there are 70 ways to get to the bottom-right.

class CLASSNAME
{
public:
    CLASSNAME()
    {
        cout << "Running " << VERSION_STRING(CLASSNAME) << "..." << endl;
    }

    // Note: This problem is very similar to cracking_8_2. However, the differences are that:
    // * Maze is not necesarrily square (does not matter)
    // * There are no restricted fields (easier)
    // * We need ALL possible paths, not just one (harder) ...
    // * ...which means we need not store any paths (easier)

    int getNumPaths(vector<vector<int>> &maze)
    {
        if (maze.size() <= 0  ||  maze[0].size() <= 0)
            return 0;

        for (int r=0; r<maze.size(); r++)
        {
            for (int c=0; c<maze[0].size(); c++)
            {
                if (r==0 || c==0)
                {
                    maze[r][c] = 1;
                }
                else
                {
                    maze[r][c] = maze[r-1][c] + maze[r][c-1];
                }
            }
        }

        int num_rows = maze.size();
        int num_cols = maze[0].size();
        int num = maze[num_rows-1][num_cols-1];

        // TODO: Clear maze to zero if necessary. Other option is to create a copy of maze. Clarify with interviewer.

        return num;
    }
};

TEST(CLASSNAME, Test1)
{    
    CLASSNAME instance;

    // create maze data structure, init with zeros
    int num_rows = 5;
    int num_cols = 5;
    vector<int>           column_vec(num_cols, 0);     // init with num_cols x 0
    vector< vector<int> > maze(num_rows, column_vec);  // init with num_rows x "column_vector"

    int num_valid_paths = instance.getNumPaths(maze);
    cout << "Number of valid paths is: " << num_valid_paths << endl;
    ASSERT_EQ(70, num_valid_paths);
}

#undef CLASSNAME
