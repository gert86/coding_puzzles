#include<QString>

#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>



using namespace std;

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
        return sum_distance;
    }
};

int main(int argc, char *argv[])
{    
    Point2D start_point(0,0);
    vector<Point2D> sequence;
    sequence.push_back(Point2D(1,1));  // 1
    sequence.push_back(Point2D(2,1));  // 1
    sequence.push_back(Point2D(4,3));  // 2
    sequence.push_back(Point2D(-2,3)); // 6
    sequence.push_back(Point2D(-2,3)); // 0
    sequence.push_back(Point2D(1,1));  // 3

    int overall_distance = start_point.stepDistanceToAllOf(sequence);

    cout << "The overall number of steps necessary is " << overall_distance << endl;

    return 0;
}
