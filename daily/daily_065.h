#pragma once

#define CLASSNAME Daily_065

#include "base_header.h"

using namespace std;
using namespace Helper;

// -------------------- Program starts here -------------------------
//
// Given a N by M matrix of numbers, print out the matrix in a clockwise spiral.


// Strategy and Example:
//
// 1   2  3  4  5
// 6   7  8  9 10
// 11 12 13 14 15
// 16 17 18 19 20
//
// Rechts (c++)       Runter (r++)       Links (c--)        Rauf (r--)
// 1 2 3 4 5          10 15 20           19 18 17 16        11  6
// r=0, c=0..C-1      r=1..R-1, c=C-1    r=R-1, c=C-2..0    r=R-2..1, c=0
//
// Rechts (c++)       Runter (r++)       Links (c--)
// 7  8  9            14                 13 12
// r=1, c=1..C-2      r=2..R-2, c=C-2    r=R-2, c=C-3..1
//
// M[r][c]
// R=4
// C=5

typedef vector<vector<int>> IntMatrix;

class CLASSNAME
{
public:
    CLASSNAME()
    {
        cout << "Running " << VERSION_STRING(CLASSNAME) << "..." << endl;
    }

    QString printMatrixClockwise(const IntMatrix &matrix)
    {
        QString result;

        int num_rows = matrix.size();
        if (num_rows==0)
            return result;

        int num_cols = matrix[0].size();
        if (num_cols==0)
            return result;


        int lowest_row = 0;
        int highest_row = matrix.size() - 1;
        int lowest_col = 0;
        int highest_col = matrix[0].size() - 1;

        int curr_row = 0;
        int curr_col = 0;
        while(true)
        {
            // go right
            if (curr_col > highest_col)
                break;
            for (int i=curr_col; i<=highest_col; i++)
                result += QString::number(matrix[curr_row][i]) + QString(" ");
            lowest_row++;            // lowest remaining row done
            curr_col = highest_col;  // next: highest col
            curr_row++;

            // go down
            if (curr_row > highest_row)
                break;
            for (int i=curr_row; i<=highest_row; i++)
                result += QString::number(matrix[i][curr_col]) + QString(" ");
            highest_col--;           // highest remaining col done
            curr_row = highest_row;  // next: highest row
            curr_col--;

            // go left
            if (curr_col < lowest_col)
                break;
            for (int i=curr_col; i>=lowest_col; i--)
                result += QString::number(matrix[curr_row][i]) + QString(" ");
            highest_row--;           // highest remaining row done
            curr_col = lowest_col;   // next: lowest col
            curr_row--;

            // go up
            if (curr_row < lowest_row)
                break;
            for (int i=curr_row; i>=lowest_row; i--)
                result += QString::number(matrix[i][curr_col]) + QString(" ");
            lowest_col++;           // lowest remaining col done
            curr_row = lowest_row;  // next: lowest row
            curr_col++;
        }


        return result;
    }
};

TEST(CLASSNAME, Test1)
{    
    CLASSNAME instance;

    vector<IntMatrix> test_vector;                  vector<QString> result_vector;
    test_vector.push_back( {{1,2,3,4,5},
                            {6,7,8,9,10},
                            {11,12,13,14,15},
                            {16,17,18,19,20}} );    result_vector.push_back(QString("1 2 3 4 5 10 15 20 19 18 17 16 11 6 7 8 9 14 13 12 "));
    test_vector.push_back( {{1,2,3}} );             result_vector.push_back(QString("1 2 3 "));
    test_vector.push_back( {{1},
                            {2},
                            {3}} );                 result_vector.push_back(QString("1 2 3 "));

    int val = 0;
    for (IntMatrix matrix : test_vector)
    {
        QString result = instance.printMatrixClockwise(matrix);
        cout << "The #" << val << " matrix is " << result.toStdString() << endl;
        ASSERT_EQ(result_vector[val], result);
        val++;
    }
}

#undef CLASSNAME
