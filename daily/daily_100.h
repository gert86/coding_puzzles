#pragma once

#define CLASSNAME Daily_100                //< specify class name here

#include "base_header.h"

using namespace std;
using namespace Helper;

// -------------------- Program starts here -------------------------
//
// You are in an infinite 2D grid where you can move in any of the 8 directions:
// (x,y) to
//    (x+1, y),
//    (x - 1, y),
//    (x, y+1),
//    (x, y-1),
//    (x-1, y-1),
//    (x+1,y+1),
//    (x-1,y+1),
//    (x+1,y-1)
//
//You are given a sequence of points and the order in which you need to cover the points. Give the minimum number of steps in which you can achieve it. You start from the first point.
//Example:
//Input: [(0, 0), (1, 1), (1, 2)]
//Output: 2
//It takes 1 step to move from (0, 0) to (1, 1). It takes one more step to move from (1, 1) to (1, 2).

class CLASSNAME
{
public:
    CLASSNAME()
    {
        cout << "Running " << VERSION_STRING(CLASSNAME) << "..." << endl;
    }

    class Point2D
    {
    private:
        int m_x;
        int m_y;

    public:
        explicit Point2D(int x, int y) : m_x(x), m_y(y)  {}
        virtual ~Point2D() {}

        int getX() const
        {
            return m_x;
        }

        int getY() const
        {
            return m_y;
        }

        int stepDistanceTo(const Point2D &target)
        {
            int diff_x = abs(target.getX() - m_x);
            int diff_y = abs(target.getX() - m_x);
            return max(diff_x, diff_y);
        }

        int stepDistanceToAllOf(const vector<Point2D> &targets)
        {
            Point2D current_start_point = *this;
            int sum_distance = 0;
            for(int i=0; i<targets.size(); i++)
            {
                sum_distance += current_start_point.stepDistanceTo(targets[i]);
                current_start_point = targets[i];
            }
            cout << "It takes " << sum_distance << " steps to cover all " << targets.size() << " points." << endl << endl;
            return sum_distance;
        }
    };
};

TEST(CLASSNAME, Test1)
{    
    CLASSNAME instance;

    CLASSNAME::Point2D start_point(0,0);
    vector<CLASSNAME::Point2D> sequence;
    sequence.push_back(CLASSNAME::Point2D(1,1));  // 1
    ASSERT_EQ(1, start_point.stepDistanceToAllOf(sequence));

    sequence.push_back(CLASSNAME::Point2D(2,1));  // 1
    ASSERT_EQ(2, start_point.stepDistanceToAllOf(sequence));

    sequence.push_back(CLASSNAME::Point2D(4,3));  // 2
    ASSERT_EQ(4, start_point.stepDistanceToAllOf(sequence));

    sequence.push_back(CLASSNAME::Point2D(-2,3)); // 6
    ASSERT_EQ(10, start_point.stepDistanceToAllOf(sequence));

    sequence.push_back(CLASSNAME::Point2D(-2,3)); // 0
    ASSERT_EQ(10, start_point.stepDistanceToAllOf(sequence));

    sequence.push_back(CLASSNAME::Point2D(1,1));  // 3
    ASSERT_EQ(13, start_point.stepDistanceToAllOf(sequence));
}

#undef CLASSNAME
