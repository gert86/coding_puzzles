#pragma once

#define CLASSNAME Cracking_8_2_Comparison_Top_Down_vs_Bottom_Up

#include "base_header.h"

using namespace std;
using namespace Helper;

// -------------------- Program starts here -------------------------
//
// Robot in a Grid: Imagine a robot sitting on the upper left corner of grid with r rows and c columns.
// The robot can only move in two directions, right and down, but certain cells are "off limits" such that
// the robot cannot step on them. Design an algorithm to find a path for the robot from the top left to
// the bottom right.

// NOTE: Tried to solve the problem top-down (=from destination back to start) and bottom-up (=from start to destination).
// CONCLUSION: Works both ways exactly the same way.
//
// Note that we only want to find ONE solution and not all possible solutions!!!
// Also the found solution must be stored (not sufficient to return possible/impossible), which is not difficult here.
// --> Compare with daily_012, where we want the number of all possible solutions.


struct Point
{
    int row;
    int col;

    Point(int r, int c) : row(r), col(c) {}
    bool operator==(const Point &another_point) const
    {
        return (row == another_point.row && col == another_point.col);
    }
};


// Hash function definition: necessary to use unordered_set
namespace std
{
    template <>
    struct hash<Point>
    {
        size_t operator()(const Point& point) const
        {
            std::hash<int> int_hasher;
            return int_hasher(point.row) ^ int_hasher(point.col);
        }
    };
}


class CLASSNAME
{
public:
    CLASSNAME()
    {
        cout << "Running " << VERSION_STRING(CLASSNAME) << "..." << endl;
    }

    void printMaze(const vector<vector<bool>> &maze)
    {
        for (int row=0; row<maze.size(); row++)
        {
            cout << "|";
            for (int col=0; col<maze[row].size(); col++)
            {
                if (maze[row][col])
                    cout << "X|";
                else
                    cout << " |";

            }
            cout << endl;
        }
    }


    ////////////////////////////////////////////////////////////////////////////////////////
    /// 01: Top-Down approach (=from dest backwards to start field)
    /// We took care of memoization using the hash_set (matrix would work too).
    /// We want to find only one path but want to know which path this is...
    ////////////////////////////////////////////////////////////////////////////////////////

    bool getPath01(const vector<vector<bool>> &maze, int dest_row, int dest_col, unordered_set<Point> &hash_set, vector<Point> &previous_path)
    {
        // Check if we are ALREADY out-of-bounds or if THIS is a nogo field
        if (dest_row < 0 || dest_col < 0 || maze[dest_row][dest_col])
        {
            return false;
        }

        // Remember which points we already checked
        Point p(dest_row, dest_col);
        if(hash_set.find(p)!=hash_set.end())
        {
            //cout << "We already visited " << p.row << ", " << p.col << endl;
            return false;
        }
        hash_set.insert(p);

        // Note: Since this is a depth-first search, we will only get back from the recursion if we have failed. Thus, we can also move
        // the insert down before the "return false", as the book suggests. However, it is more clear like this.

        // Check if we are done (could also be combined with following if statement)
        bool is_at_origin = (dest_row==0 && dest_col==0);
        if (is_at_origin)
        {
            previous_path.push_back(p);
            return true;
        }

        if (getPath01(maze, dest_row-1, dest_col, hash_set, previous_path) || getPath01(maze, dest_row, dest_col-1, hash_set, previous_path))
        {
            previous_path.push_back(p);
            return true;
        }

        return false;
    }

    vector<Point> getPath01(const vector<vector<bool>> &maze)
    {
        vector<Point> resulting_path;

        if (maze.size() <= 0  ||  maze[0].size() <= 0)
            return resulting_path;

        unordered_set<Point> hash_set;
        getPath01(maze, maze.size()-1, maze[0].size()-1, hash_set, resulting_path);
        return resulting_path;
    }



    ////////////////////////////////////////////////////////////////////////////////////////
    /// 02: Bottom-Up approach (=from start field forwards to dest field)
    /// We took care of memoization using the hash_set (matrix would work too).
    /// We want to find only one path but want to know which path this is...
    ////////////////////////////////////////////////////////////////////////////////////////

    bool getPath02(const vector<vector<bool>> &maze, int start_row, int start_col, unordered_set<Point> &hash_set, vector<Point> &previous_path)
    {
        // Check if we are ALREADY out-of-bounds or if THIS is a nogo field
        if (start_row >= maze.size() || start_col >= maze[0].size() || maze[start_row][start_col])
        {
            return false;
        }

        // Remember which points we already checked
        Point p(start_row, start_col);
        if(hash_set.find(p)!=hash_set.end())
        {
            //cout << "We already visited " << p.row << ", " << p.col << endl;
            return false;
        }
        hash_set.insert(p);

        // Note: Since this is a depth-first search, we will only get back from the recursion if we have failed. Thus, we can also move
        // the insert down before the "return false", as the book suggests. However, it is more clear like this.

        // Check if we are done (could also be combined with following if statement)
        bool is_at_destination = (start_row==maze.size()-1 && start_col==maze[0].size()-1);
        if (is_at_destination)
        {
            previous_path.push_back(p);
            return true;
        }

        if (getPath02(maze, start_row+1, start_col, hash_set, previous_path) || getPath02(maze, start_row, start_col+1, hash_set, previous_path))
        {
            previous_path.push_back(p);
            return true;
        }

        return false;
    }

    vector<Point> getPath02(const vector<vector<bool>> &maze)
    {
        vector<Point> resulting_path;

        if (maze.size() <= 0  ||  maze[0].size() <= 0)
            return resulting_path;

        unordered_set<Point> hash_set;
        getPath02(maze, 0, 0, hash_set, resulting_path);

        std::reverse(resulting_path.begin(), resulting_path.end());

        return resulting_path;
    }


    // Helper
    vector< vector<bool> > create_maze_for_test(bool path_possible)
    {
        // create maze data structure, init with false
        int N = 8;
        vector< vector<bool> > maze(N);
        for(int i=0; i<N; i++)
        {
            vector<bool> columns(N, false);
            maze[i] = columns;
        }


        // set certain elements to NOGO (=true)
        maze[0][7] = true;
        maze[1][5] = true;
        maze[1][6] = true;
        maze[2][4] = true;
        maze[3][3] = true;
        maze[3][2] = true;
        if (!path_possible) maze[4][2] = true;   // this makes it impossible
        maze[4][4] = true;
        maze[5][5] = true;
        maze[6][6] = true;
        maze[5][1] = true;
        maze[6][1] = true;
        maze[7][1] = true;
        maze[7][3] = true;

        return maze;
    }
};

TEST(CLASSNAME, PathPossible)
{    
    CLASSNAME instance;

    vector< vector<bool> > maze = instance.create_maze_for_test(true);
    instance.printMaze(maze);

    vector<Point> path01 = instance.getPath01(maze);   // reverse = Top-Down
    ASSERT_EQ(false, path01.empty());
    ASSERT_EQ(Point(0,0), path01.front());
    ASSERT_EQ(Point(7,7), path01.back());
    cout << "Found one valid path with Top-Down approach. The path is: ";
    for (int i=0; i<path01.size(); i++)
    {
        cout << "(" << path01[i].row << "," << path01[i].col << ") ";
    }
    cout << endl << endl;

    vector<Point> path02 = instance.getPath02(maze);   // forward = Bottom-Up
    ASSERT_EQ(false, path02.empty());
    ASSERT_EQ(Point(0,0), path02.front());
    ASSERT_EQ(Point(7,7), path02.back());
    cout << "Found one valid path with Bottom-Up approach. The path is: ";
    for (int i=0; i<path02.size(); i++)
    {
        cout << "(" << path02[i].row << "," << path02[i].col << ") ";
    }
    cout << endl << endl;

    // NOTE: Top-Down and Bottom-Up find DIFFERENT paths!!!
}

TEST(CLASSNAME, PathNotPossible)
{
    CLASSNAME instance;

    vector< vector<bool> > maze = instance.create_maze_for_test(false);
    instance.printMaze(maze);

    vector<Point> path01 = instance.getPath01(maze);   // reverse = Top-Down
    ASSERT_EQ(true, path01.empty());
    cout << "Found no valid path with Top-Down approach. " << endl << endl;

    vector<Point> path02 = instance.getPath02(maze);   // forward = Bottom-Up
    ASSERT_EQ(true, path02.empty());
    cout << "Found no valid path with Bottom-Up approach. " << endl << endl;

}

#undef CLASSNAME
